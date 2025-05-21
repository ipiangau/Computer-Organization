First, knowing C language concept and write the code. Then, converting C language into assembly part.

Inline assembly: 
exercise 1:
	if (*(p_a + j) > *(p_a + j + 1)) {
            int tmp = *(p_a + j);
            *(p_a + j) = *(p_a + j + 1);
            *(p_a + j + 1) = tmp;
        }
studying how to write if-else in assembly from chapter 2 p.39
studying how array works in assembly
asking chatGPT for help when there is an error or searching more information

exercise 2:
	for (int i = 0; i < arr_size; i++) {
        	if (p_a[i] == target) {
        		return i; 
        	}
     	}
studying for from chapter 2 p.82
studying return value from chapter 2 p.49, p.53, p.47

exercise 3:
	Block A (splitList)
		Node *slow = head;
		Node *fast = head->next;

		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
		}

		*firstHalf = head;
		*secondHalf = slow->next;
		slow->next = NULL;

	Block B (mergeSortedList)
		if (a == NULL) return b;
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
		}
	
	Block C (to next node)
		cur = cur->next;

I have going through the internet to explore how to access struct in assembly and ask chatGPT for help summarize the data, also clarifying things
