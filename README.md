# RV32i_emulation
RISCV rv32 base-integer emulation 
With 40 instructions.

![image](https://user-images.githubusercontent.com/39961019/146964111-f6b25b9c-53be-4874-80c8-1a6d4a6496d6.png)

The program design:
![image](https://user-images.githubusercontent.com/39961019/147882584-6ab3cbc9-703b-4980-90f0-7643807218ab.png)

the memory:

![image](https://user-images.githubusercontent.com/39961019/147882595-965fcd74-2574-471b-aab3-29fe9d37bf85.png)


running an example 

ADdi x6,x6,4

addi x7,X7,-3

AdDi x6,x6,-1

BNE X7,x6,-4

sb x6,0(x0)

lbu x8,0(x0)

EBREAK

result: 
![image](https://user-images.githubusercontent.com/39961019/147866464-310702aa-3a59-4965-a923-f9793bc999af.png)
