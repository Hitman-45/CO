#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

class Core 
{
public:
    vector<int> registers;
    int pc;
    vector<string> program;

public:
    Core()
    {
        registers.resize(32,0);
        pc = 0;
    }  

    void execute(vector<int> &memory, vector<pair<string, int>> &info) 
    {
        if (pc > program.size())
            return;

        string line = program[pc];
        string opcode;
        istringstream iss(line);
        iss >> opcode;

        if(opcode==".data")
        {
            pc += 1;
            while(pc < program.size() && program[pc] != ".text")
            {
                string line1 = program[pc];
                string opcode1, opcode2;
                istringstream iss1(line1);
                iss1 >> opcode1 >>opcode2;
                if(opcode2==".word")
                {
                    int count=1;
                    int x;
                    int memsize = 0;
                    for(int i=0; i<memory.size(); i++)
                    {
                        if(memory[i]!=0)
                        {
                            memsize++;
                        }
                    }
                    while(iss1 >> x)
                    {
                        if(count==1)
                        {
                            info.push_back({opcode1.substr(0, opcode1.size() - 1),memsize});
                        }

                        count=0;
                        memory.push_back(x);
                    }
                }

                pc++;
            }    
        }
        if (opcode == "add") 
        {
            // add x1 x2 x3
            int rd, rs1, rs2;
            iss >> rd >> rs1 >> rs2;
            registers[rd] = registers[rs1] + registers[rs2];
        } 
        else if (opcode == "addi") 
        {
            //addi x5 x20 3
            int rd, rs1, imm;
            iss >> rd >> rs1 >> imm;
            registers[rd] = registers[rs1] + imm;
        }
        else if (opcode == "sub") 
        {
            //sub x1 x2 x3
            int rd, rs1, rs2;
            iss >> rd >> rs1 >> rs2;
            registers[rd] = registers[rs1] - registers[rs2];
        }
        else if (opcode == "beq") 
        {
            //beq x5 x6 Label
            int rs1, rs2;
            string label;
            iss >> rs1 >> rs2 >> label;
            label += ':' ;
            if (registers[rs1] == registers[rs2]) 
            {
                for(int i=0; i<program.size(); i++)
                {
                    if(label==program[i])
                    {
                        pc = i;
                    }
                }
            }
        }
        else if (opcode == "ble") 
        {
            //ble x1 x2 Label
            int rs1, rs2;
            string label;
            iss >> rs1 >> rs2 >> label;
            label += ':' ;
            if (registers[rs1] <= registers[rs2]) 
            {
                for(int i=0; i<program.size(); i++)
                {
                    if(label==program[i])
                    {
                        pc = i;
                    }
                }
            }
        } 
        else if (opcode == "bgt") 
        {
            //bgt x5 x6 Label
            int rs1, rs2;
            string label;
            iss >> rs1 >> rs2 >> label;
            label += ':' ;
            if (registers[rs1] > registers[rs2]) 
            {
                for(int i=0; i<program.size(); i++)
                {
                    if(label==program[i])
                    {
                        pc = i;
                    }
                }
            }
        } 
        else if(opcode == "j") 
        {
            //j Label
            string label = "";
            iss >> label;
            label += ':' ;
            for(int i=0; i<program.size(); i++)
            {
                if(label==program[i])
                {
                    pc = i;
                }
            }
            return;
        }
        else if(opcode=="srl")
        {
            //srl x5 x20 1
            int rd, rs1,value;
            iss>> rd >> rs1 >> value;
            registers[rd] = registers[rs1]>>value;
        }
        else if(opcode=="sll")
        {
            //sll x5 x20 1
            int rd, rs1,value;
            iss>> rd >> rs1 >> value;
            registers[rd] = registers[rs1]<<value;
        }
        else if(opcode=="slt")
        {
            //slt x5 x20 x21
            int rd, rs1, rs2;
            iss>> rd >> rs1 >> rs2;
            if(rs1<rs2)
            {
                registers[rd] = 1;
            }
            else
            {
                registers[rd] = 0;
            }
        }
        else if (opcode == "li") 
        {
            //ld x3 value
            int rd, value;
            iss >> rd >> value;
            registers[rd] = value;
        }
        else if(opcode == "Lw")
        {
            // Lw x5 label
            string label; int rd;
            iss>>rd>>label;
            for(int i=0; i<info.size(); i++)
            {
                if(info[i].first == label)
                {
                    registers[rd] =(info[i].second)*4;
                    break;
                }
            }
        }
        else if (opcode == "lw") 
        {
            //lw x5 7(x20)
            int rd, offset, rs1;
            char x;
            iss >> rd >> offset>> x >> rs1;
            registers[rd] = memory[registers[rs1]/4 + offset/4];
        }
        else if (opcode == "sw")
        {
            // sw x5 8(x20)
            int rs1, offset, rd;
            char x;
            iss >> rs1 >> offset>> x >> rd;
            // cout<<registers[6]<<endl;
            memory[registers[rd]/4 + offset/4] = registers[rs1];
        }

        pc++;
    }

    void loadProgram(const  vector<string> &prog) 
    {
        program = prog;
    }

    vector<int>& getRegisters()
    {
        return registers;
    }
};
