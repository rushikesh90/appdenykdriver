#include <atomic>
#include <csignal>
#include <fcntl.h>
#include <grp.h>
#include <iostream>
#include <memory>
#include <pwd.h>
#include <stdexcept>
#include <sys/file.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "backend/backend_factory.h"
#include "config/config_loader.h"
#include "logging/logger.h"
#include "policy/policy_manager.h"

static std::atomic<bool> g_running(true);
static int g_pid_fd = -1;

/* =========================
   Signal Handling
   ========================= */

void signal_handler(int sig) {
  if (sig == SIGTERM || sig == SIGINT) {
    Logger::info("Shutdown signal received");
    g_running = false;
  } else if (sig == SIGHUP) {
    Logger::info("SIGHUP received (reload not implemented)");
  }
}

void install_signal_handlers() {
  struct sigaction sa{};
  sa.sa_handler = signal_handler;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;

  sigaction(SIGTERM, &sa, nullptr);
  sigaction(SIGINT, &sa, nullptr);
  sigaction(SIGHUP, &sa, nullptr);
}

/* =========================
   Single Instance Lock
   ========================= */

void acquire_pid_lock(const std::string &pid_file) {
  g_pid_fd = open(pid_file.c_str(), O_RDWR | O_CREAT, 0644);
  if (g_pid_fd < 0)
    throw std::runtime_error("Failed to open PID file");

  if (flock(g_pid_fd, LOCK_EX | LOCK_NB) < 0)
    throw std::runtime_error("Another instance is already running");

  ftruncate(g_pid_fd, 0);
  std::string pid = std::to_string(getpid());
  write(g_pid_fd, pid.c_str(), pid.size());
}

void release_pid_lock() {
  if (g_pid_fd >= 0) {
    flock(g_pid_fd, LOCK_UN);
    close(g_pid_fd);
  }
}

/* =========================
   Privilege Dropping
   ========================= */

void drop_privileges(const std::string &user) {
  struct passwd *pw = getpwnam(user.c_str());
  if (!pw)
    throw std::runtime_error("User not found for privilege drop");

  if (setgid(pw->pw_gid) != 0)
    throw std::runtime_error("Failed to drop group privileges");

  if (setuid(pw->pw_uid) != 0)
    throw std::runtime_error("Failed to drop user privileges");

  Logger::info("Privileges dropped to user: " + user);
}

/* =========================
   Main
   ========================= */

int main(int argc, char *argv[]) {
  try {
    /* 1️⃣ Load Configuration */
    Config config = ConfigLoader::load("/etc/execguard/agent.conf");

    /* 2️⃣ Initialize Logging */
    Logger::initialize(config.log_path);
    Logger::info("ExecGuard daemon starting...");

    /* 3️⃣ Ensure Single Instance */
    acquire_pid_lock("/var/run/execguard.pid");

    /* Install Signal Handlers */
    install_signal_handlers();

    /* Create Backend */
    std::unique_ptr<IKernelBackend> backend = BackendFactory::create(config);

    Logger::info("Backend created");

    /* Initialize Backend */
    if (!backend->initialize())
      throw std::runtime_error("Backend initialization failed");

    Logger::info("Backend initialized");

    /* Load Policy */
    Policy policy = PolicyManager::load(config.policy_file);

    if (!backend->loadPolicy(policy))
      throw std::runtime_error("Policy loading failed");

    Logger::info("Policy loaded");

    /* Enable Enforcement */
    if (!backend->enable())
      throw std::runtime_error("Failed to enable enforcement");

    Logger::info("Enforcement enabled");

    /* Drop Privileges (optional) */
    if (config.drop_privileges) {
      drop_privileges(config.run_as_user);
    }

    /* Event Loop */
    Logger::info("Entering main event loop");

    while (g_running) {
      backend->poll(); // Non-blocking or timed blocking
    }

    /* Shutdown */
    Logger::info("Shutting down...");

    backend->disable();
    release_pid_lock();

    Logger::info("ExecGuard stopped cleanly");
  } catch (const std::exception &ex) {
    try {
      Logger::fatal(std::string("Fatal error: ") + ex.what());
    } catch (...) {
      std::cerr << "Fatal error (logger unavailable): " << ex.what()
                << std::endl;
    }

    release_pid_lock();
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}