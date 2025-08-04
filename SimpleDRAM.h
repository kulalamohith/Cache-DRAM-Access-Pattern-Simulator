#ifndef SIMPLE_DRAM_H
#define SIMPLE_DRAM_H

class SimpleDRAM {
public:
    SimpleDRAM(int rowSizeKB, int numRows, int rowHitLatency, int rowMissLatency);

    int access(unsigned long long address); // returns latency in ns
    double getRowBufferHitRate() const;
    int getAccesses() const;
    int getHits() const;

private:
    int rowSize; // in bytes
    int rows;
    int rowHitLatency;
    int rowMissLatency;

    int accesses = 0;
    int hits = 0;

    int activeRow = -1; // -1 = no row active
};

#endif
