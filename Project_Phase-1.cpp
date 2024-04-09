#include <fstream>
#include "Processor.cpp"

int main() 
{
    Processor sim(2,512, 8, 8);

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

    bool fwd;
    cout<<"Enter 1 for forwading and 0 for w/o forwading: ";
    cin>>fwd;

    sim.setcore_forwading(fwd);
    
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

    cout<<endl<<"********************************************************"<<endl; 
    for (int i = 0; i < 2; ++i) 
    {
        int x = sim.getcoreInstr_retired(i);
        int y = sim.getcore_clock(i);
        float z = (float)x/y;
        int x1 = sim.getcore_stall(i);
        float z1 = sim.Predict_acc(i);
        cout<<"No. of clock in core-"<<i<<" is: "<<y<<endl;
        cout<<"IPC in core-"<<i<<" is: "<<z<<endl;
        cout<<"stall in core-"<<i<<" is: "<<x1<<endl;
        cout<<"Branch prediction accuracy in core-"<<i<<" is: "<<z1*100<<" %"<<endl;
        cout<<"********************************************************"<<endl;
    }

    sim.print_hit_rate();
    
    return 0;
}