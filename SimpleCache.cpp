#include "SimpleCache.h"

SimpleCache::SimpleCache(int sizeKB, int blockSize, int associativity, int hitLatency)
    : blockSize(blockSize), assoc(associativity), latency(hitLatency) {
    size = sizeKB * 1024;
    sets = (size / blockSize) / assoc;

    lru.resize(sets);
    tagMap.resize(sets);
}

bool SimpleCache::access(unsigned long long address) {
    unsigned long long blockAddr = address / blockSize;
    int setIndex = blockAddr % sets;

    accesses++;

    // Cache hit
    if (tagMap[setIndex].count(blockAddr)) {
        // Move to front (MRU)
        lru[setIndex].erase(tagMap[setIndex][blockAddr]);
        lru[setIndex].push_front(blockAddr);
        tagMap[setIndex][blockAddr] = lru[setIndex].begin();
        hits++;
        return true;
    }

    // Cache miss
    // Evict if set is full
    if ((int)lru[setIndex].size() >= assoc) {
        unsigned long long lruBlock = lru[setIndex].back();
        lru[setIndex].pop_back();
        tagMap[setIndex].erase(lruBlock);
    }

    // Insert new block at front
    lru[setIndex].push_front(blockAddr);
    tagMap[setIndex][blockAddr] = lru[setIndex].begin();

    return false;
}

double SimpleCache::getHitRate() const {
    return accesses == 0 ? 0.0 : (double)hits / accesses;
}

int SimpleCache::getLatency() const {
    return latency;
}

int SimpleCache::getAccesses() const {
    return accesses;
}

int SimpleCache::getHits() const {
    return hits;
}
