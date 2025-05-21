#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Split the linked list into two parts
void splitList(Node *head, Node **firstHalf, Node **secondHalf)
{
    // Node *slow = head;
    // Node *fast = head->next;

    // while (fast && fast->next) {
    //     slow = slow->next;
    //     fast = fast->next->next;
    // }

    // *firstHalf = head;
    // *secondHalf = slow->next;
    // slow->next = NULL;
    asm volatile(
        "mv t0, %[head]\n\t\t"        // t0 = slow
        "ld t1, 8(%[head])\n\t\t"     // t1 = fast = head->next

    "Loop:\n\t\t"                    // loop_start
        "beqz t1, Loop2\n\t\t"           // if fast == NULL, break
        "ld t2, 8(t1)\n\t\t"          // t2 = fast->next
        "beqz t2, Loop2\n\t\t"           // if fast->next == NULL, break

        "ld t0, 8(t0)\n\t\t"          // slow = slow->next
        "ld t1, 8(t2)\n\t\t"          // fast = fast->next->next
        "j Loop\n\t\t"                  // repeat loop

    "Loop2:\n\t\t"                    // end loop
        "sd %[head], 0(%[fh])\n\t\t"  // *firstHalf = head
        "ld t3, 8(t0)\n\t\t"          // t3 = slow->next
        "sd t3, 0(%[sh])\n\t\t"       // *secondHalf = t3
        "sd zero, 8(t0)\n\t\t"        // slow->next = NULL

        :
        : [head] "r"(head), [fh] "r"(firstHalf), [sh] "r"(secondHalf)
        : "t0", "t1", "t2", "t3", "memory"
    );
}

// Merge two sorted linked lists
Node *mergeSortedLists(Node *a, Node *b)
{
    Node *result = NULL;
    Node *tail = NULL;
    /*if (a == NULL) return b;
    if (b == NULL) return a;

    if (a->data < b->data) {
        result = a;
        tail = a;
        a = a->next;
    } else {
        result = b;
        tail = b;
        b = b->next;
    }
    while (a != NULL && b != NULL) {
        if (a->data < b->data) {
            tail->next = a;
            tail = a;
            a = a->next;
        } else {
            tail->next = b;
            tail = b;
            b = b->next;
        }
    }
    while (a != NULL) {
        tail->next = a;
        tail = a;
        a = a->next;
    }

    while (b != NULL) {
        tail->next = b;
        tail = b;
        b = b->next;
    }*/
    asm volatile(       
        "beqz %[a], bcase\n\t"          
        "beqz %[b], acase\n\t"           
        "lw t0, 0(%[a])\n\t"          // a->data
        "lw t1, 0(%[b])\n\t"          // b->data
        "bge t0, t1, Else\n\t"          

    "acase:\n\t"                     
        "mv %[result], %[a]\n\t"      
        "mv %[tail], %[a]\n\t"       
        "lw %[a], 8(%[a])\n\t"        
        "j Looop\n\t"                   
        
    "Else:\n\t"                     
        "mv %[result], %[b]\n\t"      
        "mv %[tail], %[b]\n\t"       
        "lw %[b], 8(%[b])\n\t"
        "j Looop\n\t"                   
        
    "bcase:\n\t"                   
        "mv %[result], %[b]\n\t"     
        "j Done\n\t"                  
        
    "Looop:\n\t"
        "beqz %[a], gobagain\n\t"          
        "beqz %[b], goaagain\n\t"           
        
        "lw t0, 0(%[a])\n\t"          // a->data
        "lw t1, 0(%[b])\n\t"          // b->data
        "bge t0, t1, forb\n\t"        
        
        "sd %[a], 8(%[tail])\n\t"     // tail->next = a
        "mv %[tail], %[a]\n\t"        
        "lw %[a], 8(%[a])\n\t"       
        "j Looop\n\t"                   
        
    "forb:\n\t"                    
        "sd %[b], 8(%[tail])\n\t"   
        "mv %[tail], %[b]\n\t"       
        "lw %[b], 8(%[b])\n\t"     
        "j Looop\n\t"                   
        
    "gobagain:\n\t"                  
        "beqz %[b], Done\n\t"        
        "sd %[b], 8(%[tail])\n\t"     
        "mv %[tail], %[b]\n\t"       
        "lw %[b], 8(%[b])\n\t"      
        "j gobagain\n\t"                  
    
    "goaagain:\n\t"                    
        "beqz %[a], Done\n\t"         
        "sd %[a], 8(%[tail])\n\t"     
        "mv %[tail], %[a]\n\t"       
        "lw %[a], 8(%[a])\n\t"      
        "j goaagain\n\t"                   
        
    "Done:\n\t"                     
    : [result] "+r" (result), [tail] "+r" (tail)
    : [a] "r" (a), [b] "r" (b)
    : "t0", "t1", "memory"

    );
    return result;
}

// Merge Sort function for linked list
Node *mergeSort(Node *head)
{
    if (!head || !head->next)
        return head; // Return directly if there is only one node

    Node *firstHalf, *secondHalf;
    splitList(head, &firstHalf,
              &secondHalf); // Split the list into two sublists

    firstHalf = mergeSort(firstHalf);   // Recursively sort the left half
    secondHalf = mergeSort(secondHalf); // Recursively sort the right half

    return mergeSortedLists(firstHalf, secondHalf); // Merge the sorted sublists
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        printf("Usage: %s <input_file>\n\t", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error opening file: %s\n\t", argv[1]);
        return 1;
    }
    int list_size;
    fscanf(input, "%d", &list_size);
    Node *head = (list_size > 0) ? (Node *)malloc(sizeof(Node)) : NULL;
    Node *cur = head;
    for (int i = 0; i < list_size; i++) {
        fscanf(input, "%d", &(cur->data));
        if (i + 1 < list_size)
            cur->next = (Node *)malloc(sizeof(Node));
        cur = cur->next;
    }
    fclose(input);

    // Linked list sort
    head = mergeSort(head);

    cur = head;
    while (cur) {
        printf("%d ", cur->data);
        //cur = cur->next;
        asm volatile(
            "ld %[p], 8(%[p])\n\t\t"
            : [p] "+r"(cur)
            :
            : "memory"
            );
    }
    printf("\n");
    return 0;
}

