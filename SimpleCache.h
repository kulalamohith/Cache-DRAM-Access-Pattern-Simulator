#ifndef SIMPLE_CACHE_H
#define SIMPLE_CACHE_H

#include <vector>
#include <list>
#include <unordered_map>

class SimpleCache {
public:
    SimpleCache(int sizeKB, int blockSize, int associativity, int hitLatency);
    bool access(unsigned long long address); // returns true if hit

    double getHitRate() const;
    int getLatency() const;
    int getAccesses() const;
    int getHits() const;

private:
    int size;
    int blockSize;
    int assoc;
    int latency;

    int sets;
    int accesses = 0;
    int hits = 0;

    std::vector<std::list<unsigned long long>> lru;  // one list per set
    std::vector<std::unordered_map<unsigned long long, std::list<unsigned long long>::iterator>> tagMap;
};

#endif
