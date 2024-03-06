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
    int instr_retired;
    int clock;

    // Define pipeline registers
    int EX_MEM_rd, EX_MEM_aluResult, MEM_WB_rd, MEM_WB_memData;
    bool EX_MEM_valid, MEM_WB_valid;

public:
    Core()
    {
        registers.resize(32,0);
        pc = 0;
        instr_retired = 0;
        clock = 0;

        // Initialize pipeline registers
        EX_MEM_valid = false;
        MEM_WB_valid = false;
    }  

    void fetch(vector<int> &memory, vector<pair<string, int>> &info) 
    {
        if (pc > program.size())
            return;

        if (pc < program.size()) 
        {
            string line = program[pc];
            clock++;
            // Decode and execute in the next stage
            decode_execute(line, memory, info);
        }
    }

    void decode_execute(const string& line, vector<int>& memory, vector<pair<string, int>>& info) 
    {
        
        // Decode Instruction
        string opcode;
        istringstream iss(line);
        iss >> opcode;
        instr_retired++;
        // clock++;

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
        if (opcode == "add" || opcode == "addi" || opcode == "sub") 
        {
            clock++;
            // Execute arithmetic/logical instructions
            execute_arithmetic(opcode, iss);
        }
        else if(opcode == "beq" || opcode == "ble" || opcode == "blt" || opcode == "bgt" || opcode == "bge" || opcode == "j")
        {
            clock++;
            // Execute branch/jump instructions
            execute_branch(opcode, iss);
        }
        else if(opcode=="srli" || opcode=="slli" || opcode=="slt")
        {
            clock++;
            // Execute bitwise manipulation instructions
            execute_bitwise(opcode, iss);
        }
        else if (opcode == "lw" || opcode == "sw" || opcode == "la" || opcode == "la") 
        {
            clock++;
            // Execute load/store instructions
            execute_memory(opcode, iss, memory, info);
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

    int get_instr_retired()
    {
        return instr_retired;
    }

    int get_clock()
    {
        return clock;
    }

private:

    void execute_arithmetic(const string& opcode, istringstream& iss) 
    {
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
    }

    void execute_memory(const string& opcode, istringstream& iss, vector<int>& memory,  vector<pair<string, int>>& info) 
    {
        if (opcode == "li") 
        {
            //ld x3 value
            int rd, value;
            iss >> rd >> value;
            registers[rd] = value;
        }
        else if(opcode == "la")
        {
            //la x5 label
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
    }

    void execute_branch(const string& opcode, istringstream& iss)
    {
        if (opcode == "beq") 
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
        else if (opcode == "blt") 
        {
            //ble x1 x2 Label
            int rs1, rs2;
            string label;
            iss >> rs1 >> rs2 >> label;
            label += ':' ;
            if (registers[rs1] < registers[rs2]) 
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
        else if (opcode == "bge") 
        {
            //bgt x5 x6 Label
            int rs1, rs2;
            string label;
            iss >> rs1 >> rs2 >> label;
            label += ':' ;
            if (registers[rs1] >= registers[rs2]) 
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
    }

    void execute_bitwise(const string& opcode, istringstream& iss)
    {
        if(opcode=="srli")
        {
            //srl x5 x20 1
            int rd, rs1,value;
            iss>> rd >> rs1 >> value;
            registers[rd] = registers[rs1]>>value;
        }
        else if(opcode=="slli")
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
    }
};
