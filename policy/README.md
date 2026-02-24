# Policies

Policies are backend-independent JSON documents.

- Allowlist entries are hash-based (SHA-256 hex).
- Backends (LSM vs BPF) should consume the same policy format.
