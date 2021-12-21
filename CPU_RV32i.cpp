#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include "ISA.h"
#include "Instruction_encode.h"

 

#define start_address 0x1000// the allocated first address of the main program

                            //0x0->0x0fff may contain pseudo instruction


//------------------------------------------------
using Byte = unsigned char;// 8bits
using Half = unsigned short;//16bits half-word
using Word = unsigned int;//32bits
//------------------------------------------------


int bit(int bit_num, Word input)// this is to mask a single bit out for wiring sigle bit 
{
    Word temp = 0;
    bool answer = 0;
    temp = (1 << bit_num) & input; //one = 0x00000001
    answer = (temp == (1 << bit_num)) ? 1 : 0;
    return answer;
}
void binary_converter(int input)
{
    for (int i = 31; i > -1; i--) { printf("%d", bit(i, input)); }printf("\n");
}
Word *mem_start;
//======================================================================================
struct MEM { //max is 0xffff memory start from address[mem_start + (0->0xffff)], 
    
    Word *Data= (Word*)malloc(0xffff*32); // memory data with memory allocation
    void initialise() //initialise memory with memory allocation
    {
        mem_start = Data;
        for (int i=0;i<0xffff;i++)
        {
            *(Data + i) = 0;
        }
    }
};
//======================================================================================
struct CPU {
    // program counter 
    Word PC;       
    const Word ZERO = 0x0;
/*===============================================================
DWord SP;//stack pointer, There is no dedicated stack pointer or
//subroutine return address link register in the Base Integer ISA
===============================================================*/
    Word x[32];     //x[31->1] general register.
                    //x[0] zero register all bits are set to zeros.
//================================================================
    Byte    N = 0,      //Negative flag
            Z = 1,      //Zero flag
            C = 0,      //Carry-out flag
            V = 0;      //Overflowe flag
//================================================================
    void reset(MEM& memory)
    {
        PC = start_address;
        memory.initialise();
////////// set "0x0" to all general purpose registers
        for (int i = 0; i < 32; i++){x[i] = 0x0;}
    }

    Word fetch(Word& cycles, MEM& memory)
    {
        Word Data = *(memory.Data + PC);
        PC++; cycles--;
        return Data;
    }
    void execute(Word cycle, MEM& memory)
    {
        while (cycle > 0)
        {
            Word inst = fetch(cycle, memory);
//==========================================================================
            binary_converter(inst);
            
            switch (inst & 0x7f)
            {
            case INST_load_imm_opcode:// load immediate 
            {
                Word imm_12 = inst >> 20,       //immediate 12bits extraction
                     rsb = (inst&0x000f8000) >> 15,          //base register 5bits address
                     funct_3 = (inst & 0x00007000) >> 12,    //function 3 ALU controller
                     rsd = (inst & 0x00000f80) >> 7;         //destination register 5bits address
                
                imm_12 = ((imm_12 & 0x800) == 0x800) ? imm_12*-1:imm_12;//sign-extension
                
                switch (funct_3) 
                {
                case LB:
                {
                    if (((x[rsd] = *(memory.Data + x[rsb] + imm_12)) & 0x00000080) == 0x00000080)
                    {
                        x[rsd] = (*(memory.Data + x[rsb] + imm_12) & 0x000000ff) + 0xffffff00;
                        printf("loaded 0x%x\n", x[rsd]); break;
                    }
                    else { x[rsd] = *(memory.Data + x[rsb] + imm_12) & 0x000000ff; printf("loaded 0x%x\n", x[rsd]); break;}
                    break;
                }
                case LH:
                {
                    if (((x[rsd] = *(memory.Data + x[rsb] + imm_12)) & 0x00008000) == 0x00008000) 
                    {
                        x[rsd] = (*(memory.Data + x[rsb] + imm_12) & 0x0000ffff) + 0xffff0000;
                        printf("loaded 0x%x\n", x[rsd]); break;
                    }
                    else { x[rsd] = *(memory.Data + x[rsb] + imm_12) & 0x0000ffff; printf("loaded 0x%x\n", x[rsd]); break;}
                    break;
                }
                case LW:
                {x[rsd] = *(memory.Data + x[rsb] + imm_12) & 0xffffffff; printf("loaded 0x%x\n", x[rsd]); break; }
                case LBU:
                {x[rsd] = *(memory.Data + x[rsb] + imm_12 ) & 0x000000ff; printf("loaded 0x%x\n", x[rsd]); break; }
                case LHU:
                {x[rsd] = *(memory.Data + x[rsb] + imm_12) & 0x0000ffff; printf("loaded 0x%x\n", x[rsd]); break; }
                default: {printf("Unknown funct_3\n"); break; }
                }
                //x[rsd] = *(x[rsb] + imm_12 + memory.Data);
                break;
            }
            case INST_store_imm_opcode:// store immediate
            {
                Word imm_7 = inst >> 25,       //immediate 12bits extraction
                     rss = (inst & 0x01f00000) >> 20,          //source register 5bits address
                     rsb = (inst & 0x000f8000) >> 15,         //base register 5bits address
                     funct_3 = (inst & 0x00007000) >> 12,    //function 3 ALU controller
                     imm_5 = (inst & 0x00000f80) >> 7,
                     imm_12 = (imm_7 << 5) + imm_5 ;
                
                imm_12 = ((imm_12 & 0x800) == 0x800) ? imm_12 * -1 : imm_12;//sign-extension
                switch (funct_3)
                {
                case SB: 
                {
                    *(memory.Data + x[rsb] + imm_12) = x[rss] & 0x000000ff; printf("stored 0x%x\n", *(memory.Data + x[rsb] + imm_12));
                    break;
                }
                case SH:
                {
                    *(memory.Data + x[rsb] + imm_12) = x[rss] & 0x0000ffff; printf("stored 0x%x\n", *(memory.Data + x[rsb] + imm_12));
                    break;
                }
                case SW:
                {
                    *(memory.Data + x[rsb] + imm_12) = x[rss]; printf("stored 0x%x\n", *(memory.Data + x[rsb] + imm_12));
                    break;
                }
                default: {printf("Unknown funct_3\n"); break; }
                }
                break;
            }
            case INST_register_imm_opcode:// register-immediate 
            {
                Word imm_12 = inst >> 20,       //immediate 12bits extraction
                    imm_7 = inst >> 25,
                    imm_5 = (inst & 0x01f00000) >> 20,
                    rsc = (inst & 0x000f8000) >> 15,          //base register 5bits address
                    funct_3 = (inst & 0x00007000) >> 12,    //function 3 ALU controller
                    rsd = (inst & 0x00000f80) >> 7;         //destination register 5bits address

                // At this arithmetic and logical calculation we should sign-extending at each function,
                // not for the whole opcode
                /*============================================================================
                //imm_12 = ((imm_12 & 0x800) == 0x800) ? imm_12 * -1 : imm_12;//sign-extension
                ============================================================================*/
                
                switch (funct_3) 
                {
                case ADDI: 
                {
                    imm_12 = ((imm_12 & 0x800) == 0x800) ? imm_12 * -1 : imm_12;//sign-extension
                    x[rsd] = x[rsc] + imm_12; //oveflow is ignored !!!
                    printf("added immediate 0x%x to register x[%d]\n", imm_12,rsc); 
                    break;
                }
                case SLTI: 
                {
                    imm_12 = ((imm_12 & 0x800) == 0x800) ? imm_12 * -1 : imm_12;//sign-extension
                    int a=x[rsc], b=imm_12;// do it because of x[rsc] and imm_12 were unsigned, not signed so we need to cast signed int to the comparison
                    x[rsd] = (a < b); // compare lesser between source register and the immediate in signed.
                    if(x[rsd]==true)printf("x[%d] < %d\n", rsd, imm_12); else printf("x[%d] > or = %d\n", rsd,imm_12);
                    break;
                }
                case SLTIU: 
                {
                    imm_12 = ((imm_12 & 0x800) == 0x800) ? imm_12 * -1 : imm_12;//sign-extension
                    x[rsd] = (x[rsc] < imm_12); // compare lesser between source register and the immediate in unsigned.
                    if (x[rsd] == true)printf("x[%d] < %u\n", rsd, imm_12); else printf("x[%d] > or = %u\n", rsd, imm_12);
                    break;
                }
                case XORI: 
                {
                    x[rsd] = x[rsc] ^ imm_12;
                    printf("x[%d] Xor-ed imm_12 = 0x%x\n",rsc,x[rsd]);
                    break; 
                }
                case ORI:
                {
                    x[rsd] = x[rsc] | imm_12;
                    printf("x[%d] Or-ed imm_12 = 0x%x\n", rsc, x[rsd]);
                    break;
                }
                case ANDI:
                {
                    x[rsd] = x[rsc] & imm_12;
                    printf("x[%d] And-ed imm_12 = 0x%x\n", rsc, x[rsd]);
                    break;
                }
                case SLLI: {break; }
                case SRLI_SRAI: {break; }
                
                default: {printf("Unknown funct_3\n"); break; }
                }
                break;
            }
            case INST_register_register_opcode:// register-register
            {
                break;
            }
            case INST_conditional_branch_opcode:// register-register
            {
                break;
            }
            case INST_unconditional_jump_opcode:// unconditional jump 
            {
                break;
            }
            case INST_indirect_jump_opcode:// indirect jump
            {
                break;
            }
            case INST_FENCE_opcode:// FENCE
            {
                break;
            }
            case INST_ECALL_EBREAK_opcode:// ECALL or EBREAK
            {
                Word funct_12 = inst >> 20;
                switch (funct_12)
                {
                case ECALL: {   break; }
                case EBREAK: {  break; }
                }
                break;
            }
            default: {printf("Instruction not handled : %x\n", inst); break; }
            }
//======================================================================================         
        }
    }
};



int main() 
{    
        //create the cpu core and RAM
        CPU cpu; MEM mem;
        //reset the memory for initial run
        cpu.reset(mem);
        // executation of the cpu
        cpu.x[5] = 0x4;
        cpu.x[6] = 0x0f;
        cpu.x[7] = 0xf0;
        *(mem.Data + start_address) = Load(0x0, x_5, LW, x_5, INST_load_imm_opcode);
        *(mem.Data + start_address + 1) = Store(0x0, x_6, x_5, SW, 0x0, INST_store_imm_opcode);
        *(mem.Data + start_address + 2) = Reg_imm(0x123, x_6, SLTI, x_7, INST_register_imm_opcode);
        *(mem.Data + start_address + 3) = Reg_imm(0xfff, x_6, SLTIU, x_7, INST_register_imm_opcode);
        *(mem.Data + start_address + 4) = Reg_imm(0xfff, x_6, ANDI, x_7, INST_register_imm_opcode);
        //==================
        cpu.execute(5, mem);
        //==================
        for (int i = 0; i < 32; i++)
        {
            if (i <= 9) {
                printf("x[%d ] = 0x%x | %d | ", i, cpu.x[i], cpu.x[i]); //}
                binary_converter(cpu.x[i]);
            }
            else {
                printf("x[%d] = 0x%x | %d | ", i, cpu.x[i], cpu.x[i]); //}
                binary_converter(cpu.x[i]);
            }
        }
        printf("\nPC = 0x%x\n", cpu.PC);
        printf("Negative flag   = %d\n", cpu.N);
        printf("Zero flag       = %d\n", cpu.Z);
        printf("Carry_out flag  = %d\n", cpu.C);
        printf("Overflowe flag  = %d\n", cpu.V);
    return 0;
}
/* Reuse code */
//===================================================================================================
////binary_converter(*(mem.Data + 0));
//===================================================================================================