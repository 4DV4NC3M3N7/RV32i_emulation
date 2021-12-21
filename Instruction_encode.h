#ifndef INSTRUCTION_ENCODE_H_INCLUDED
#define INSTRUCTION_ENCODE_H_INCLUDED



//------------------------------------------------
using Byte = unsigned char;// 8bits
using Half = unsigned short;//16bits half-word
using Word = unsigned int;//32bits
//------------------------------------------------


Word Load(int imm_12, int RSB, int funct_3, int RSD, int opcode);
Word Store(int imm_7, int RSS, int RSB, int funct_3, int imm_5, int opcode);
Word Reg_imm(int imm_12, int RSC, int funct_3, int RSD, int opcode);
Word Shift_imm(int imm_7, int shamt, int RSC, int funct_3, int RSD, int opcode);
Word Reg_reg(int imm_7, int RSC_2, int RSC_1, int funct_3, int RSD, int opcode);
Word LUI(int imm_20,int RSD,int opcode);
Word AUIPC(int imm_20, int RSD, int opcode);


#endif