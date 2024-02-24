#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>
using namespace std;
#include "Processor.cpp"

int main() 
{
    Processor sim(1);

    // sim.getCore(0).getRegisters()[16] = 0x10000000;
    
    ifstream inputFile("D:/CO_labs/Project_Phase-1/bubble_sort.asm");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file.\n";
        return 1; 
    }

    vector<string> instructions;
    string line;
    while (getline(inputFile, line)) {
        instructions.push_back(line);
    }
    
    sim.setCoreProgram(0, instructions);

    sim.run();

    for (int i = 0; i < 1; ++i) {
        const vector<int>& regs = sim.getCoreRegisters(i);
        for (int reg : regs) {
            cout << reg << " ";
        }
        cout << endl;
    }

    vector<int> v = sim.getMemory();
    for(int x : v)
    {
        if(x != 0)
            cout<<x<<" ";
    }
    return 0;
}