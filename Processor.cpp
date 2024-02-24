#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Core.cpp"
using namespace std;

class Processor 
{
private:
    vector<int> memory;
    vector<pair<string, int>> info;
    vector<Core> cores;
    int clock;

public:
    Processor(int numCores)
    {
        cores.resize(numCores);
        clock = 0;
    }

    int maxProgramLength()
    {
        int maxLen = 0;
        for (auto core : cores) 
        {
            maxLen = max(maxLen, static_cast<int>(core.program.size()));
        }
        return maxLen;
    }
    void run()
    {
        for(int j=0; j<cores.size(); j++)
        {   
            for (int i = 0; cores[j].pc < cores[j].program.size(); ++i) 
            {
                cores[j].execute(memory, info);
            }
            clock++;
        }
    }

    void setCoreProgram(int coreIndex, const vector<string>& program) 
    {
        if (coreIndex < cores.size()) 
        {
            cores[coreIndex].loadProgram(program);
        }
    }

    Core& getCore(int coreIndex) 
    {
        if (coreIndex < cores.size()) 
        {
            return cores[coreIndex];
        }
    }

    const vector<int>& getCoreRegisters(int coreIndex)
    {
        if (coreIndex < cores.size()) 
        {
            return cores[coreIndex].getRegisters();
        } 
        else 
        {
            static vector<int> emptyRegisters;
            return emptyRegisters;
        }
    }

    vector<int>& getMemory() 
    {
        return memory;
    }
};
