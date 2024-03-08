#include <fstream>
#include "Processor.cpp"

int main() 
{
    Processor sim(2);

    // sim.getCore(0).getRegisters()[16] = 0x10000000;
    
    ifstream inputFile("./bubble_sort.asm");
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

    ifstream inputFile1("./selection_sort.asm");
    if (!inputFile1.is_open()) {
        cerr << "Error: Could not open the file.\n";
        return 1; 
    }

    vector<string> instructions1;
    string line1;
    while (getline(inputFile1, line1)) {
        instructions1.push_back(line1);
    }

    sim.setCoreProgram(1, instructions1);
    
    sim.run();

    cout << endl;
    for (int i = 0; i < 2; ++i) {
        const vector<int>& regs = sim.getCoreRegisters(i);
        cout<<"core-"<<i<<": ";
        for (int reg : regs) {
            cout << reg << " ";
        }
        cout << endl;
    }

    vector<int> v = sim.getMemory();
    cout<<"Memory: ";
    for(int x : v)
    {
        if(x != 0)
            cout<<x<<" ";
    }

    cout<<endl; 
    for (int i = 0; i < 2; ++i) 
    {
        int x = sim.getcoreInstr_retired(i);
        int y = sim.getcore_clock(i);
        float z = (float)x/y;
        cout<<"IPC in core-"<<i<<" is: "<<z<<endl;
    }

    for (int i = 0; i < 2; ++i) 
    {
        int x = sim.getcore_stall(i);
        cout<<"stall in core-"<<i<<" is: "<<x<<endl;
    }

    return 0;
}