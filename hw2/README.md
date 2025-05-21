鄧顏可 F74117077
I began by reviewing each C file from exercise2_1 -> exercise2_2 -> exercise3_1 -> exercise3_2 -> exercise1 because exercise1 need to implement a lot of files to get the correct result. After finished reviewing I started to the required asm volatile blocks to implement floating-point and integer operations using the appropriate RV64G or vector instructions. 

For exercise1:
implement c code for each file then converted into inline assembly, also add instructions count for each instruction

For exercise2_1:
implement based on given c code 

For exercise2_2:
using vsetvil, vle32.v (float), vfmul.vv, vfadd.vf, vse32,v by searching more information from internet and guideline from AI generation

For exercise3_1:
also implemented based on given c code

For exercise3_2:
use code from exercise3_1 but change float into double and for shift operands use double value (2->4)

Problem:
- (exercise1) After finishing all the code I realized that I still not getting the others_cnt correct so I have to put all the count (mostly before beq or jump instruction) in the front of the instruction 
- (overall) A lot of times that I use instruction those are not declaring in exercise_.c result to that instruction count(program see as operands) is unavailable so I have to open these files along with code writing 
- pi.c not accurate enough and I have to modify many times (asking chatgpt for help sometimes)

Performance Data Collection (macro_define.h)
Each function was instrumented to count instructions and compute:
- Total cycle count using macro_fft_cycle_count and similar macros
- CPU time with cycle_time constant
- CPU/Memory ratio using the provided formulas