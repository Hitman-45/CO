#include "Core.cpp"
#include "Cache.cpp"

class Processor 
{
private:
    vector<int> memory;
    vector<pair<string, int>> info1;
    vector<pair<string, int>> info2;
    vector<Core> cores;
    CacheSimulator cac;
    Cache2 cac2;

public:
    Processor(int numCores, int cacheSize, int blockSize, int associativity): cac(cacheSize,blockSize,associativity), cac2(cacheSize*4, blockSize, associativity)
    {
        cores.resize(numCores);
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
                if(j==0)
                {
                    int* xyz = reinterpret_cast<int*>(&cores[j].program[cores[j].pc]);
                    bool hmm = cac.access(*xyz);
                    if(!hmm)
                    {
                        cac2.access(*xyz);
                    }
                    cores[j].fetch(memory, info1,cores[j].pc);
                }
                if(j==1)
                {
                    int* xyz = reinterpret_cast<int*>(&cores[j].program[cores[j].pc]);
                    bool hmm1 = cac.access(*xyz);
                    if(!hmm1)
                    {
                        cac2.access(*xyz);
                    }
                    cores[j].fetch(memory, info2,cores[j].pc);
                }
            }
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

    int getcoreInstr_retired(int coreIndex)
    {
        if (coreIndex < cores.size()) 
        {
            return cores[coreIndex].get_instr_retired();
        } 
    }

    vector<int>& getMemory() 
    {
        return memory;
    }

    int getcore_clock(int coreIndex)
    {
        if (coreIndex < cores.size()) 
        {
            return cores[coreIndex].get_clock();
        }
    }

    int getcore_stall(int coreIndex)
    {
        if (coreIndex < cores.size()) 
        {
            return cores[coreIndex].get_stall();
        }
    }

    void setcore_forwading(bool fwd)
    {
        for(int i=0; i<cores.size(); i++)
        {
            cores[i].forwading = fwd;
        }
    }

    float Predict_acc(int coreIndex)
    {
        if (coreIndex < cores.size()) 
        {
            int x = cores[coreIndex].get_true_branch();
            int y = cores[coreIndex].get_false_branch();
            int x1 = x+y;
            float z = (float)x/x1;
            return z;
        }
    }

    void print_hit_rate()
    {
        cout<<"Hit-Rate for the first level Cache : "<<cac.hit_rate()*100<<" %"<<endl;
        cout<<"Hit-Rate for the second level Cache : "<<cac2.hit_rate()*100<<" %"<<endl;
    }
};