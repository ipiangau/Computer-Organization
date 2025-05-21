#include <stdio.h>

int arraySearch(int *p_a, int arr_size, int target)
{
    int result = -1;
    // for (int i = 0; i < arr_size; i++) {
    //     if (p_a[i] == target) {
    //         return i; 
    //     }
    // }
    asm volatile(
        "li t0, 0\n\t"
        "Loop:\n\t"
            "bge t0,%[B],Exit\n\t"
            "slli t1, t0, 2\n\t"
            "add t2,%[A],t1\n\t" // t2 = &p_a[i]
            //"sd x0,0(x7)\n\t"
            "lw t3, 0(t2)\n\t" // t3 = p_a[i]
            "beq t3, %[C], found\n\t" //if p_a[i] == target
            "addi t0, t0, 1\n\t"
            "j Loop\n\t"
        "found:\n\t"
            "mv %[R],t0\n\t"
        "Exit:\n\t"
        :[R] "=r" (result)
        :[A]"r"(p_a), [B]"r"(arr_size), [C]"r"(target)
        :"t0","t1","t2","t3"
    );

    return result;
}

// Main function to test the implementation
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
    int target;
    fscanf(input, "%d", &target);
    fclose(input);

    int *p_a = &arr[0];

    int index = arraySearch(p_a, arr_size, target);

    // Print the result
    printf("%d ", index);
    printf("\n");

    return 0;
}

