#include "backend/backend_factory.h"
#include "config/config_loader.h"
#include "logging/logger.h"

int main(int argc, char** argv) {
    (void)argc; (void)argv;
    execguard::Logger::Init();

    // Config-driven backend selection
    auto cfg = execguard::ConfigLoader::LoadFromEnvOrDefault();
    auto backend = execguard::BackendFactory::Create(cfg.backend);

    execguard::Logger::Info("execguard agent started");
    backend->Start();
    backend->Stop();
    return 0;
}
