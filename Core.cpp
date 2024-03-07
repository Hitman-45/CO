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
    int temp_WB;
    int temp_MEM;
    int temp_EX;
    int temp_Dec;
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
            instr_retired++;
            // Decode and execute in the next stage
            decode(line, memory, info);
            pc++;
        }
    }

    void decode(const string& line, vector<int>& memory, vector<pair<string, int>>& info) 
    {
        
        // Decode Instruction
        string opcode;
        istringstream iss(line);
        iss >> opcode;
        clock++;

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
       else
        {
            // Execute stage
            execute(opcode, iss, memory, info);
        }
    }

    void execute(const string& opcode, istringstream& iss, vector<int>& memory, vector<pair<string, int>>& info)
    {
        if (opcode == "add" || opcode == "addi" || opcode == "sub" || opcode == "li") 
        {
            clock++;
            // Execute arithmetic/logical instructions
            execute_arithmetic(opcode, iss, memory);
        }
        else if(opcode == "beq" || opcode == "ble" || opcode == "blt" || opcode == "bgt" || opcode == "bge" || opcode == "j")
        {
            clock++;
            // Execute branch/jump instructions
            execute_branch(opcode, iss, memory);
        }
        else if(opcode=="srli" || opcode=="slli" || opcode=="slt")
        {
            clock++;
            // Execute bitwise manipulation instructions
            execute_bitwise(opcode, iss, memory);
        }
        else if (opcode == "lw" || opcode == "sw" || opcode == "la") 
        {
            clock++;
            // Execute memory instructions
            execute_memory(opcode, iss, memory, info);
        }
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

    void Memory(int temp,int rd, int type, vector<int>& memory)
    {
        if(type == 0)
        {
            WB(temp,rd,type);
        }
        else if(type == 1)
        {
            memory[rd] = temp;
            WB(temp,rd,type);
        }
        else if(type == 2)
        {
            WB(temp,rd,type);
        }
    }

    void WB(int temp,int rd, int type)
    {
        if(type==0)
            registers[rd] = temp;
        else if(type==1)
            type = 1;
        else if(type==2)
            pc = temp;
    }

private:

    void execute_arithmetic(const string& opcode, istringstream& iss, vector<int>& memory) 
    {
        int temp;
        if (opcode == "add") 
        {
            // add x1 x2 x3
            int rd, rs1, rs2;
            iss >> rd >> rs1 >> rs2;
            temp = registers[rs1] + registers[rs2];
            Memory(temp, rd, 0, memory);
        } 
        else if (opcode == "addi") 
        {
            //addi x5 x20 3
            int rd, rs1, imm;
            iss >> rd >> rs1 >> imm;
            temp = registers[rs1] + imm;
            Memory(temp, rd, 0, memory);
        }
        else if (opcode == "sub") 
        {
            //sub x1 x2 x3
            int rd, rs1, rs2;
            iss >> rd >> rs1 >> rs2;
            temp = registers[rs1] - registers[rs2];
            Memory(temp, rd, 0, memory);
        }
        else if (opcode == "li") 
        {
            //ld x3 value
            int rd, value;
            iss >> rd >> value;
            temp = value;
            Memory(temp, rd, 0, memory);
        }
    }

    void execute_memory(const string& opcode, istringstream& iss, vector<int>& memory,  vector<pair<string, int>>& info) 
    {
        int temp;
        if(opcode == "la")
        {
            //la x5 label
            string label; int rd;
            iss>>rd>>label;
            for(int i=0; i<info.size(); i++)
            {
                if(info[i].first == label)
                {
                    temp =(info[i].second)*4;
                    Memory(temp, rd, 0, memory);
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
            temp = memory[registers[rs1]/4 + offset/4];
            Memory(temp, rd, 0, memory);
        }
        else if (opcode == "sw")
        {
            // sw x5 8(x20)
            int rs1, offset, rd, ab;
            char x;
            iss >> rs1 >> offset>> x >> rd;
            temp = registers[rs1];
            ab = registers[rd]/4 + offset/4;
            Memory(temp, ab, 1, memory);
        }
    }

    void execute_branch(const string& opcode, istringstream& iss, vector<int>& memory)
    {
        int temp;
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
                        temp = i;
                        Memory(temp, i, 2, memory);
                        break;
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
                        temp = i;
                        Memory(temp, i, 2, memory);
                        break;
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
                        temp = i;
                        Memory(temp, i, 2, memory);
                        break;
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
                        temp = i;
                        Memory(temp, i, 2, memory);
                        break;
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
                        temp = i;
                        Memory(temp, i, 2, memory);
                        break;
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
                    temp = i;
                    Memory(temp, i, 2, memory);
                    break;
                }
            }
        }
    }

    void execute_bitwise(const string& opcode, istringstream& iss, vector<int>& memory)
    {
        int temp;
        if(opcode=="srli")
        {
            //srl x5 x20 1
            int rd, rs1,value;
            iss>> rd >> rs1 >> value;
            temp = registers[rs1]>>value;
            Memory(temp, rd, 0, memory);
        }
        else if(opcode=="slli")
        {
            //sll x5 x20 1
            int rd, rs1,value;
            iss>> rd >> rs1 >> value;
            temp = registers[rs1]<<value;
            Memory(temp, rd, 0, memory);
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
