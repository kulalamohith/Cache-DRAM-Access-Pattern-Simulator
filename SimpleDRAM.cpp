#include "SimpleDRAM.h"

SimpleDRAM::SimpleDRAM(int rowSizeKB, int numRows, int rowHitLatency, int rowMissLatency)
    : rowSize(rowSizeKB * 1024), rows(numRows),
      rowHitLatency(rowHitLatency), rowMissLatency(rowMissLatency) {}

int SimpleDRAM::access(unsigned long long address) {
    int row = address / rowSize;
    accesses++;

    if (row == activeRow) {
        hits++;
        return rowHitLatency;
    } else {
        activeRow = row;
        return rowMissLatency;
    }
}

double SimpleDRAM::getRowBufferHitRate() const {
    return accesses == 0 ? 0.0 : (double)hits / accesses;
}

int SimpleDRAM::getAccesses() const {
    return accesses;
}

int SimpleDRAM::getHits() const {
    return hits;
}
