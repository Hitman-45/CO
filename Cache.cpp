#include <iostream>
#include <vector>
#include <cmath>
#include <bits/stdc++.h> 
using namespace std;

struct CacheBlock {
    bool valid;
    int tag;
    vector<int> data;
    int accessTime; // For LRU and MRU
};

class CacheSimulator 
{
private:
    int cacheSize;
    int blockSize;
    int associativity;
    bool replacement_policy;
    int memoryAccess;
    int miss,hit;
    int numSets;
    
    vector<vector<CacheBlock>> cache;

public:
    CacheSimulator(int size, int bSize, int assoc)
    {
        cacheSize = size;
        blockSize = bSize;
        associativity = assoc;
        numSets = cacheSize / (blockSize * associativity);
        memoryAccess = 0;
        miss = 0; hit = 0;
        replacement_policy = true;//for LRU and false for MRU
        cache.resize(numSets, vector<CacheBlock>(associativity, {false, -1, vector<int>(blockSize, 0), 0}));
    }

    // Access cache to read/write data
    bool access(int address) 
    {
        int setIndex = (address / blockSize) % numSets;
        int tag = address / (blockSize * numSets);
        memoryAccess++;

        // Search for the block in the cache
        for (int i = 0; i < associativity; ++i) {
            if (cache[setIndex][i].valid && cache[setIndex][i].tag == tag) 
            {
                // Cache hit
                cache[setIndex][i].accessTime = memoryAccess; // Update access time
                hit++;
                return true;
            }
        }
        // Cache miss
        insertBlock(address);
        miss++;
        return false;
    }

    // Insert block into cache
    void insertBlock(int address) 
    {
        int setIndex = (address / blockSize) % numSets;
        int tag = address / (blockSize * numSets);

        // Find an empty slot or evict a block based on a replacement policy
        int emptySlot = -1;
        for (int i = 0; i < associativity; ++i) 
        {
            if (!cache[setIndex][i].valid) 
            {
                emptySlot = i;
                break;
            }
        }

        if (emptySlot != -1) 
        {
            // Found an empty slot
            cache[setIndex][emptySlot].valid = true;
            cache[setIndex][emptySlot].tag = tag;
            cache[setIndex][emptySlot].accessTime = memoryAccess; // Update access time
        } 
        else 
        {
            //replacement policy
            int replaceIndex = -1;
            if (replacement_policy) 
            {
                // Find the least recently used block
                int minAccessTime = numeric_limits<int>::max();
                for (int i = 0; i < associativity; ++i) {
                    if (cache[setIndex][i].accessTime < minAccessTime) {
                        minAccessTime = cache[setIndex][i].accessTime;
                        replaceIndex = i;
                    }
                }
            } 
            else 
            {
                // Find the most recently used block
                int maxAccessTime = numeric_limits<int>::min();
                for (int i = 0; i < associativity; ++i) {
                    if (cache[setIndex][i].accessTime > maxAccessTime) {
                        maxAccessTime = cache[setIndex][i].accessTime;
                        replaceIndex = i;
                    }
                }
            }

            // Evict the block based on the replacement policy (LRU or MRU)
            cache[setIndex][replaceIndex].valid = true;
            cache[setIndex][replaceIndex].tag = tag;
            cache[setIndex][replaceIndex].accessTime = memoryAccess; // Update access time

        }
    }

    double hit_rate()
    {
      double x = (double)hit / memoryAccess;
      return x;
    }
    
    int misses()
    {
        return miss;
    }
};

class Cache2 {
    private:
    int cacheSize;
    int blockSize;
    int associativity;
    bool replacement_policy;
    int memoryAccess;
    int miss,hit;
    int numSets;
    
    vector<vector<CacheBlock>> cache;

public:
    Cache2(int size, int bSize, int assoc)
    {
        cacheSize = size;
        blockSize = bSize;
        associativity = assoc;
        numSets = cacheSize / (blockSize * associativity);
        memoryAccess = 0;
        miss = 0; hit = 0;
        replacement_policy = true;//for LRU and false for MRU
        cache.resize(numSets, vector<CacheBlock>(associativity, {false, -1, vector<int>(blockSize, 0), 0}));
    }
    
    // Access cache to read/write data
    void access(int address) 
    {
        int setIndex = (address / blockSize) % numSets;
        int tag = address / (blockSize * numSets);
        memoryAccess++;

        // Search for the block in the cache
        for (int i = 0; i < associativity; ++i) {
            if (cache[setIndex][i].valid && cache[setIndex][i].tag == tag) 
            {
                // Cache hit
                cache[setIndex][i].accessTime = memoryAccess; // Update access time
                hit++;
                return;
            }
        }
        // Cache miss
        insertBlock(address);
        miss++;
        return;
    }

    // Insert block into cache
    void insertBlock(int address) 
    {
        int setIndex = (address / blockSize) % numSets;
        int tag = address / (blockSize * numSets);

        // Find an empty slot or evict a block based on a replacement policy
        int emptySlot = -1;
        for (int i = 0; i < associativity; ++i) 
        {
            if (!cache[setIndex][i].valid) 
            {
                emptySlot = i;
                break;
            }
        }

        if (emptySlot != -1) 
        {
            // Found an empty slot
            cache[setIndex][emptySlot].valid = true;
            cache[setIndex][emptySlot].tag = tag;
            cache[setIndex][emptySlot].accessTime = memoryAccess; // Update access time
        } 
        else 
        {
            //replacement policy
            int replaceIndex = -1;
            if (replacement_policy) 
            {
                // Find the least recently used block
                int minAccessTime = numeric_limits<int>::max();
                for (int i = 0; i < associativity; ++i) {
                    if (cache[setIndex][i].accessTime < minAccessTime) {
                        minAccessTime = cache[setIndex][i].accessTime;
                        replaceIndex = i;
                    }
                }
            } 
            else 
            {
                // Find the most recently used block
                int maxAccessTime = numeric_limits<int>::min();
                for (int i = 0; i < associativity; ++i) {
                    if (cache[setIndex][i].accessTime > maxAccessTime) {
                        maxAccessTime = cache[setIndex][i].accessTime;
                        replaceIndex = i;
                    }
                }
            }

            // Evict the block based on the replacement policy (LRU or MRU)
            cache[setIndex][replaceIndex].valid = true;
            cache[setIndex][replaceIndex].tag = tag;
            cache[setIndex][replaceIndex].accessTime = memoryAccess; // Update access time

        }
    }

    double hit_rate()
    {
      double x = (double)hit / memoryAccess;
      return x;
    }
    
    int misses()
    {
        return miss;
    }
};