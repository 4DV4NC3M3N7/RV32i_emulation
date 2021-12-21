

/* Instruction opcode */
//==========================================================================
#define	 INST_load_imm_opcode			0x03
#define	 INST_store_imm_opcode			0x23
#define	 INST_register_imm_opcode		0x13
#define	 INST_register_register_opcode  0x33
#define  INST_conditional_branch_opcode 0x63
#define	 INST_unconditional_jump_opcode 0x6f//JAL
#define	 INST_indirect_jump_opcode		0x67//JALR
#define	 INST_FENCE_opcode				0x0f
#define  INST_ECALL_EBREAK_opcode		0x73
//==========================================================================

/* Instruction funct_3 for "INST_conditional_branch_opcode" */
//==========================================================================
#define BEQ 0x0 
#define BNE 0x1
#define BLT 0x4
#define BGE 0x5
#define BLTU 0x6
#define BGEU 0x7
//==========================================================================



/* Instruction funct_3 for "INST_load_imm_opcode" */
//==========================================================================
#define LB 0x0 //load byte, 8bits, signed extend
#define LH 0x1 //load half word, 16bits, signed extend
#define LW 0x2 //load Word, 32bits
#define LBU 0x4 //load byte, 8bits, unsigned
#define LHU 0x5 //load half word, 16bits, unsigned
//==========================================================================


/* Instruction funct_3 for "INST_store_imm_opcode" */
//==========================================================================
#define SB 0x0 //store byte, 8bits, signed extend
#define SH 0x1 //store half word, 16bits, signed extend
#define SW 0x2 //store Word, 32bits
//==========================================================================


/* Instruction funct_3 for "INST_register_imm_opcode" */
//==========================================================================
#define ADDI	0x0 //add immediate 12bits arithmetic
#define SLTI	0x2 //
#define SLTIU	0x3 //
#define XORI	0x4	//immediate exclusive or 12bits logic
#define ORI		0x6 //immediate or 12bits logic
#define ANDI	0x7 //immediate and 12bits logic
//========================================================================== with "shamt"-shift amount = 5bits
#define SLLI		0x1
#define SRLI_SRAI	0x5
//==========================================================================


/* Instruction funct_7 for "INST_register_imm_opcode" and "INST_register_register_opcode" */
//==========================================================================
#define ALU_unsigned	0x0
#define ALU_signed		0x20
//==========================================================================

/* Instruction funct_12 for "INST_ECALL_EBREAK_opcode" */
//==========================================================================
#define ECALL	0x0
#define EBREAK	0x1
//==========================================================================


/* Instruction */
//==========================================================================

//==========================================================================

/* General Register */
//==========================================================================
#define x_0 0x0
#define x_1 0x1
#define x_2 0x2
#define x_3 0x3
#define x_4 0x4
#define x_5 0x5
#define x_6 0x6
#define x_7 0x7
#define x_8 0x8
#define x_9 0x9
#define x_10 0xa
#define x_12 0xb
#define x_13 0xc
#define x_14 0xd
#define x_15 0xe
#define x_16 0xf
#define x_17 0x10
#define x_18 0x11
#define x_19 0x12
#define x_20 0x13
#define x_21 0x14
#define x_22 0x15
#define x_23 0x16
#define x_24 0x17
#define x_25 0x18
#define x_26 0x19
#define x_27 0x1a
#define x_28 0x1b
#define x_29 0x1c
#define x_30 0x1d
#define x_31 0x1e
//==========================================================================
