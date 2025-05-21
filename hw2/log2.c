"addi %[others_cnt], %[others_cnt], 1\n\t"
"beq %[N], zero, done\n\t"               // One branch check before loop
 //"addi %[others_cnt], %[others_cnt], 1\n\t"
"loop:\n\t"
 "addi %[others_cnt], %[others_cnt], 1\n\t"
    "srli %[N], %[N], 1\n\t"             // Logical shift right (still 'others')
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[log], %[log], 1\n\t"
    "addi %[others_cnt], %[others_cnt], 1\n\t"
    "bnez %[N], loop\n\t"                // Only one conditional jump
// "addi %[others_cnt], %[others_cnt], 1\n\t"
    "done:\n\t"
    "addi %[add_cnt], %[add_cnt], 1\n\t"
    "addi %[log], %[log], -1\n\t"
