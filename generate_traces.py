import random

def write_trace(filename, addresses):
    with open(filename, "w") as f:
        for addr in addresses:
            f.write(f"{hex(addr)}\n")

# Parameters
block_size = 64  # 64 bytes
num_accesses = 1000

# 1. Sequential: 0x0, 0x40, 0x80, ...
sequential = [i * block_size for i in range(num_accesses)]
write_trace("trace_seq.txt", sequential)

# 2. Strided: 0x0, 0x100, 0x200, ...
stride = 4  # 4-block stride = 256B
strided = [i * block_size * stride for i in range(num_accesses)]
write_trace("trace_stride.txt", strided)

# 3. Random: pick randomly in a 512KB space
random.seed(42)
random_addrs = [random.randint(0, 512 * 1024) & ~0x3F for _ in range(num_accesses)]
write_trace("trace_rand.txt", random_addrs)
