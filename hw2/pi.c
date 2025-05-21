"addi %[add_cnt], %[add_cnt], 3\n\t"
    "addi t1, zero, 0\n\t" 
    "addi t2, zero, 1\n\t"                     
    "addi t4, zero, 1\n\t"         

"looop:\n\t"
    "slli t3, t1, 1\n\t"   
    "addi %[others_cnt], %[others_cnt], 1\n\t"                  
    "addi t3, t3, 1\n\t"                   
    "addi %[add_cnt], %[add_cnt], 1\n\t"

    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "fcvt.s.w f1, t2\n\t"                    
    "fcvt.s.w f2, t3\n\t"                   
    "addi %[others_cnt], %[others_cnt], 1\n\t"

    "fdiv.s f1, f1, f2\n\t"                
    "addi %[fdiv_cnt], %[fdiv_cnt], 1\n\t"

    "fadd.s %[pi], %[pi], f1\n\t"            
    "addi %[fadd_cnt], %[fadd_cnt], 1\n\t"

    "add t1, t1, t4\n\t"                     
    "addi %[add_cnt], %[add_cnt], 1\n\t"

    "sub t2, zero, t2\n\t"        
    "addi %[sub_cnt], %[sub_cnt], 1\n\t"

    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "blt t1, %[N], looop\n\t"
