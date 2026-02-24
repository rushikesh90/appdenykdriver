CLANG ?= clang

BPF_CFLAGS := -O2 -g -target bpf -D__TARGET_ARCH_x86

all: mini_exec_bpf.o

mini_exec_bpf.o: mini_exec_bpf.c
	$(CLANG) $(BPF_CFLAGS) -c $< -o $@

clean:
	rm -f mini_exec_bpf.o
