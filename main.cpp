#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "SimpleCache.h"
#include "SimpleDRAM.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: ./simulator <trace_file.txt>\n";
        return 1;
    }

    std::ifstream traceFile(argv[1]);
    if (!traceFile) {
        std::cerr << "Error: Cannot open trace file.\n";
        return 1;
    }

    // Cache: 8KB, 64B blocks, 2-way, 2ns latency
    SimpleCache cache(8, 64, 2, 2);
    
    // DRAM: 8KB rows, 128 rows, 10ns hit, 45ns miss
    SimpleDRAM dram(8, 128, 10, 45);

    unsigned long long addr;
    unsigned long long totalLatency = 0;
    int totalAccesses = 0;

    while (traceFile >> std::hex >> addr) {
        totalAccesses++;
        if (cache.access(addr)) {
            totalLatency += cache.getLatency();
        } else {
            totalLatency += dram.access(addr);
        }
    }

    traceFile.close();

    std::cout << "Total Accesses: " << totalAccesses << "\n";
    std::cout << "Cache Hit Rate: " << cache.getHitRate() * 100 << "%\n";
    std::cout << "DRAM Row Buffer Hit Rate: " << dram.getRowBufferHitRate() * 100 << "%\n";
    std::cout << "Average Access Latency: " << (double)totalLatency / totalAccesses << " ns\n";

    return 0;
}
