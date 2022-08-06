// Import header files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// Define a Linked List structure
struct Node
{
	int coeff;
	int power;
	struct Node* next;
};


/* ----------------- */
/* UTILITY FUNCTIONS */
/* ----------------- */


// To create a new linked list node
struct Node* create_node(int coeff, int power)
{
	// Define pointer for a new node
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	// Initialize the  new node
	new_node -> coeff = coeff;
	new_node -> power = power;
	new_node -> next = NULL;

	return new_node;
}


// To insert a node in the beginning of the linked list
struct Node* insert_node(struct Node* head, int coeff, int power)
{
	struct Node* new_node = create_node(coeff, power);
	new_node -> next = head;
	head = new_node;
	return head;
}


// To create a polynomial from the linked list
struct Node* create_polynomial(struct Node* head, char* inputs)
{
	int i;

	for(i=0; i<=inputs[0]; i++)
	{
		// No node required if coefficient is 0
		if(i==0 || inputs[inputs[0]-i+1])
		{
			head = insert_node(head, inputs[inputs[0]-i+1], i);
		}
	}
	return head;
}


// To free the linked list nodes and delete the linked list
void delete_linked_list(struct Node** head)
{
  // Declare pointers for linked list nodes
  struct Node *current_node, *next_node;
  current_node = *head;

  // Traverse through linked list and delete each node
  while (current_node != NULL)
  {
    next_node = current_node -> next;
    free(current_node);
    current_node = next_node;
  }
  *head = NULL;
}


// To display the polynomial linked list in readable form
void display_linked_list(struct Node* current_node)
{
	int coeff, power, clean_coeff;
	bool is_max_term = true;

	while(current_node != NULL)
	{
		coeff = current_node -> coeff;
		power = current_node -> power;

		// Skip terms with coefficient as 0
		if(!is_max_term && coeff == 0)
		{
			current_node = current_node -> next;
			continue;
		}
		else if(is_max_term && coeff == 0)
		{
			is_max_term = false;
			printf("0");
			current_node = current_node -> next;
			continue;
		}

		// Add sign for each term except first
		if(!is_max_term)
		{
			if (coeff > 0)
			{
				printf(" + ");
			}
			else
			{
				printf(" - ");
			}
			clean_coeff = abs(coeff);
		}
		else
		{
			is_max_term = false;
			clean_coeff = coeff;
		}

		// Check for power
		if(power > 0)
		{
			printf("%dx^%d", clean_coeff, power);
		}
		else
		{
			printf("%d", clean_coeff);
		}

		// Update current_node to next node
		if(current_node -> next != NULL)
		{
			current_node = current_node -> next;
		}
		else
		{
			break;
		}
	}
	printf("\n");
	return;
}


// To display the readable form of polynomials
void display_polynomials(struct Node* p1, struct Node* p2, struct Node* p3)
{
	// Display P1
	printf("P1(x): ");
	display_linked_list(p1);

	// Display P2
	printf("P2(x): ");
	display_linked_list(p2);

	// Display P3
	printf("P3(x): ");
	display_linked_list(p3);

	return;
}


// To sort the polynomial linked list in decreasing order of power
struct Node* sort_polynomial(struct Node* head)
{
	int temp_power, temp_coeff;
	bool is_same;
	struct Node *node_pointer, *last_pointer;

	// Check for blank linked list
	if(head == NULL)
	{
		printf("Empty Polynomial Received!\n");
		return head;
	}

	// Initialize last node pointer as NULL
	last_pointer = NULL;

	// Implement bubble sort for decreasing order of power
	while(true)
	{
		is_same = false;
		node_pointer = head;

		// Traverse until last unsorted node
		while(node_pointer -> next != last_pointer)
		{
			if(node_pointer -> power < node_pointer -> next -> power)
			{
				// Swap polynomial terms
				temp_coeff = node_pointer -> coeff;
				node_pointer -> coeff = node_pointer -> next -> coeff;
				node_pointer -> next -> coeff = temp_coeff;

				temp_power = node_pointer -> power;
				node_pointer -> power = node_pointer -> next -> power;
				node_pointer -> next -> power = temp_power;

				is_same = true;
			}
			// Update the pointer to next node
			node_pointer = node_pointer -> next;
		}
		// Break the loop if linked list is sorted
		if(!is_same)
		{
			break;
		}
		// Update last node pointer to sorted node
		last_pointer = node_pointer;
	}
	return head;
}


// To sum up coefficients having same power
struct Node* clean_polynomial(struct Node* head)
{
	struct Node *slow_pointer, *fast_pointer, *to_remove;
	slow_pointer = head;

	// Select an element
	while(slow_pointer != NULL && slow_pointer -> next != NULL)
	{
		// Use current node as basis and look at next node
		fast_pointer = slow_pointer;

		// Match with each element
		while(fast_pointer -> next != NULL)
		{
			// Check if next node has same power
			if(slow_pointer -> power == fast_pointer -> next -> power)
			{
				// Add coefficients
				slow_pointer -> coeff = slow_pointer -> coeff + fast_pointer -> next -> coeff;

				// Point to the node to be removed
				to_remove = fast_pointer -> next;

				// Update the pointer to bypass the next node
				fast_pointer -> next = fast_pointer -> next -> next;

				// Remove the redundant node
				free(to_remove);
			}
			else
			{
				// Update the pointer to next node
				fast_pointer = fast_pointer -> next;
			}
		}
		// Update the current node to next available node
		slow_pointer = slow_pointer -> next;
	}
	return head;
}


// To multiply two given polynomials
struct Node* implement_multiplication(struct Node* p1, struct Node* p2, struct Node* p3)
{
	struct Node *p1_pointer, *p2_pointer;

	p1_pointer = p1;
	p2_pointer = p2;

	while(p1_pointer != NULL)
	{
		while (p2_pointer != NULL)
		{
			int coeff_prod, power_sum;

			// Perform basic multiplication of two polynomial terms
			coeff_prod = (p1_pointer -> coeff) * (p2_pointer -> coeff);
			power_sum = (p1_pointer -> power) + (p2_pointer -> power);

			// Create and insert a new node in P3
			p3 = insert_node(p3, coeff_prod, power_sum);

			// Update P2 pointer to next term
			p2_pointer = p2_pointer -> next;
		}
		// Reset the P2 pointer
		p2_pointer = p2;

		// Update P1 pointer to next term
		p1_pointer = p1_pointer -> next;
	}

	// Clean and sort P3 in decreasing order of power
	p3 = clean_polynomial(p3);
	p3 = sort_polynomial(p3);

	return p3;
}


// To evaluate the value of polynomial for a given value of x
int evaluate_polynomial(struct Node* head, int x_val)
{
	int result = 0;

	while(head != NULL)
	{
		result = result + head -> coeff * pow(x_val, head -> power);
		head = head -> next;
	}
	return result;
}


// To display the evaluated values of polynomials
void display_evaluations(struct Node* p1, struct Node* p2, struct Node* p3, int x_val)
{
	int p1_val, p2_val, p3_val;

	// Evaluate P1
	p1_val = evaluate_polynomial(p1, x_val);
	printf("P1(%d) = %d\n", x_val, p1_val);

	// Evaluate P2
	p2_val = evaluate_polynomial(p2, x_val);
	printf("P2(%d) = %d\n", x_val, p2_val);

	// Evaluate P3
	p3_val = evaluate_polynomial(p3, x_val);
	printf("P3(%d) = %d\n", x_val, p3_val);

	return;
}


/* ------------ */
/* MAIN PROGRAM */
/* ------------ */


void main()
{
	// Declare variables
	int i, j, t, test_cases, x_val, p1_len, p2_len;
	char p1_input[100], p2_input[100], ch;

	// Get the number of test cases
	scanf("%d\n", &test_cases);

	// For each test case
	for(t=0; t<test_cases; t++)
	{
		p1_len=0;
		p2_len=0;

		// Get the P1 polynomial
	  do {
	      scanf("%d%c", &p1_input[p1_len], &ch);
	      p1_len++;
	  } while(ch != '\n');

		// Get the P2 polynomial
		do {
				scanf("%d%c", &p2_input[p2_len], &ch);
				p2_len++;
		} while(ch != '\n');

		// Get the value of x to evaluate
		scanf("%d", &x_val);

		// Initialize pointers for polynomial linked lists
		struct Node* p1 = NULL;
		struct Node* p2 = NULL;
		struct Node* p3 = NULL;

		p1 = create_polynomial(p1, p1_input);
		p2 = create_polynomial(p2, p2_input);

		// Store the product of P1 and P2 in P3
		p3 = implement_multiplication(p1, p2, p3);

		// Display the polynomials
		display_polynomials(p1, p2, p3);

		// Display the polynomial value after evaluation
		display_evaluations(p1, p2, p3, x_val);

		// Free the nodes and delete the linked list
		delete_linked_list(&p1);
		delete_linked_list(&p2);
		delete_linked_list(&p3);
	}
	return;
}
