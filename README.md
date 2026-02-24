# appdenykdriver
The project is open source implementation of application control software. 
I started as a simple kernel module but decided to add ebpf module also along with it.
This is still work in progress.

Application deny prototype with pluggable kernel backends (LSM module or eBPF LSM).

## Build (userspace)
```sh
cmake -S . -B build
cmake --build build -j
```
