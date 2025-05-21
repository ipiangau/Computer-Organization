"vsetvli t0, %[arr_size], e32,m1 \n\t"     
"vle32.v v0, (%[h]) \n\t"                   
"vle32.v v1, (%[x]) \n\t"                    
"addi %[lw_cnt], %[lw_cnt], 2 \n\t"      

"vfmul.vv v2, v0, v1 \n\t"                
"addi %[fmul_cnt], %[fmul_cnt], 1 \n\t"

"vfadd.vf v2, v2, %[id] \n\t"            
"addi %[fadd_cnt], %[fadd_cnt], 1 \n\t"

"vse32.v v2, (%[y]) \n\t"                   
"addi %[sw_cnt], %[sw_cnt], 1 \n\t"

"addi %[others_cnt], %[others_cnt], 1 \n\t"