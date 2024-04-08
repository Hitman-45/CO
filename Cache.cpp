#include <iostream>
#include <vector>
#include <bits/stdc++.h> 
using namespace std;
struct CacheBlock 
{
  uint64_t tag;
  bool valid;
};

class CacheSimulator 
{
  private:
    vector<CacheBlock> cache;
    unsigned int cacheSize;
    unsigned int blockSize;
    unsigned int numBlocks;
    int hit;
    int accesses;

    pair<uint64_t, uint64_t> splitAddress(uint64_t address) 
    {
      // variable address if for byte
      int num_bits_offset = log2(blockSize);
      address = address >> num_bits_offset;
      uint64_t index = address & ((1 << numBlocks) - 1);
      uint64_t tag = address >> (int)log2(numBlocks);
      return make_pair(tag, index);
    }

  public:
    CacheSimulator(unsigned int _cacheSize, unsigned int _blockSize): cacheSize(_cacheSize), blockSize(_blockSize) 
    { 
        hit = 0;
        accesses = 0;   
        if(cacheSize % blockSize == 0);
        {
            numBlocks = cacheSize / blockSize;
            cache.resize(numBlocks);
        }
        for (auto b : cache) 
        {
            b.valid = false;
        }
    }

    void access (uint64_t address) {
      // split the address: |---------tag --------------| --index---| --offset---|
      auto a = splitAddress(address);
      uint64_t index = a.second;
      uint64_t tag = a.first;
      accesses++;
      if (cache[index].tag == tag && cache[index].valid == true) {
        hit++;
      }
      else {
        cache[index].tag = tag;
        cache[index].valid = true;
      }
    }

    double hit_rate()
    {
      double x = (double)hit / accesses;
      return x;
    }
};















