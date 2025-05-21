#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n", argv[1]);
        return 1;
    }
    int arr_size;
    fscanf(input, "%d", &arr_size);
    int arr[arr_size];

    // Read integers from input file into the array
    for (int i = 0; i < arr_size; i++) {
        int data;
        fscanf(input, "%d", &data);
        arr[i] = data;
    }
    fclose(input);

    int *p_a = &arr[0];

    // array a bubble sort
    /* Original C code segment
        if (*(p_a + j) > *(p_a + j + 1)) {
            int tmp = *(p_a + j);
            *(p_a + j) = *(p_a + j + 1);
            *(p_a + j + 1) = tmp;
        }
    */

    for (int i = 0; i < arr_size - 1; i++) {
        for (int j = 0; j < arr_size - i - 1; j++) {
            asm volatile(
                "slli t0,%[B],2\n\t" // t0 = j * 4
                "add t1,%[A],t0\n\t" // t1 = &arr[j]
                "lw t2,0(t1)\n\t" // t2 = arr[j]
                "lw t3,4(t1)\n\t" // t3 = arr[j+1]
                "ble t2, t3, Loop\n\t" // if arr[j] <= arr[j+1]
                
                "sw t3, 0(t1)\n\t" // arr[j] = t3
                "sw t2, 4(t1)\n\t" // arr[j+1] = t2
            "Loop:\n\t" 

                :
                :[A]"r"(p_a), [B]"r"(j)
                :"t0", "t1", "t2","t3","memory"
            );
            
        }
    }
    p_a = &arr[0];
    for (int i = 0; i < arr_size; i++)
        printf("%d ", *p_a++);
    printf("\n");
    return 0;
}


