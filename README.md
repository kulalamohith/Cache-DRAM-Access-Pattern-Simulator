# DRAM–Cache Access Pattern Simulation

##  Problem

Modern computing systems often suffer from memory stalls due to poor cache usage and high DRAM access latency. Though caching and DRAM row buffers significantly improve performance, their efficiency is tightly bound to the **access pattern**.

This project aims to answer:

>  *How do sequential, strided, and random memory access patterns impact cache hit rate, DRAM row buffer usage, and average memory access latency?*

Understanding these effects is essential for optimizing system architectures .

---

## 🛠️ Action

We built a modular C++ simulator that accurately models:

### 🔧 L1 Cache
- 8KB total size, 64B block size
- 2-way set-associative
- LRU eviction via `std::list` + `unordered_map`
- Access latency: 2 ns

### 🔧 DRAM
- 128 rows × 8KB each
- Active **row buffer** modeled
- Row buffer hit latency: 10 ns
- Row buffer miss latency: 45 ns

###  Trace-Driven Simulation
- Input: trace files with memory addresses (`trace_seq.txt`, `trace_stride.txt`, `trace_rand.txt`)
- Generated using a Python script
- Each address is passed through the cache first, then DRAM if needed

---

##  Example: How a Single Address Is Handled

###  Input (from trace file):
0x00000000

###  Step-by-Step Execution:

####  Cache Access:
- Block size = 64B → block address = `0 / 64 = 0`
- Cache sets = 64 → set index = `0 % 64 = 0`
- Tag = 0

Result: **Cache MISS** (set is empty)

####  DRAM Access:
- Row size = 8192B → row = `0 / 8192 = 0`
- Active row = none → **Row Buffer MISS**

Set active row to 0 → Latency = **45 ns**

---

###  Next Address:

0x00000040

- Same set, new tag → **Cache MISS**
- Still row 0 → **Row Buffer HIT**

Latency = **10 ns**

---

##  How to Build & Run

### 🛠 Build (on WSL/Linux)
make

###  Run Simulation
./simulator trace_seq.txt
./simulator trace_stride.txt
./simulator trace_rand.txt

###  Regenerate Traces
python3 generate_traces.py

---

##  Results (for 1000 accesses)

| Pattern     | Cache Hit Rate | DRAM Row Buffer Hit Rate | Average Latency |
|-------------|:--------------:|:-----------------------:|:--------------:|
| Sequential  |     85.1%      |          75.3%          |     8.3 ns     |
| Strided     |     22.7%      |          18.2%          |    28.5 ns     |
| Random      |     15.2%      |          5.1%           |    38.6 ns     |

---

##  Insights

- **Sequential Access:** High cache & DRAM efficiency due to spatial locality.
- **Strided Access:** Partial locality, lower reuse.
- **Random Access:** Breaks locality → high latency due to misses.
- **Overall:** Sequential patterns were up to 5× faster than random ones.

---

##  Learning Outcome

- Implemented LRU cache with std::list for O(1) eviction.
- Simulated DRAM row buffer and timing penalties.
- Analyzed trace-driven performance using real-world patterns.
- Observed how architectural choices affect access latency.

---

## 🛠 Requirements

- g++ (C++11)
- Python 3
- Make + WSL or Linux terminal










