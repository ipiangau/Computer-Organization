"li t0,0 \n\t" 
"addi %[lw_cnt], %[lw_cnt],1\n\t"
"addi %[others_cnt], %[others_cnt], 1 \n\t"
"mv t1, %[m] \n\t"
"bitre: \n\t"
    "addi %[others_cnt], %[others_cnt], 1 \n\t"
    "beq t1, zero, finish \n\t"
    "addi %[others_cnt], %[others_cnt], 1 \n\t"
    "slli t0, t0, 1 \n\t"
    "addi %[others_cnt], %[others_cnt], 3 \n\t"
    "andi t2, %[b], 1 \n\t"
    "or t0, t0, t2 \n\t"     
    "srli %[b], %[b], 1 \n\t"
    "addi %[add_cnt], %[add_cnt], 1 \n\t"
    "addi t1, t1, -1 \n\t"
    "addi %[others_cnt], %[others_cnt], 1 \n\t"    
    "j bitre \n\t"
"finish: \n\t"
    "addi %[others_cnt], %[others_cnt], 1 \n\t"
    "mv %[b], t0 \n\t"
