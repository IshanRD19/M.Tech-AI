#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>


// Define a Linked List structure
struct Node
{
	int data;
	struct Node* next;
};


/* ----------------- */
/* UTILITY FUNCTIONS */
/* ----------------- */


// To create a new linked list node
struct Node* create_node(int data)
{
	// Define pointer for a new node
	struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));

	// Initialize the  new node
	new_node -> data = data;
	new_node -> next = NULL;
	return new_node;
}


// To insert a node in the beginning of the linked list
struct Node* insert_node(struct Node* head, int data)
{
	struct Node* new_node = create_node(data);
	new_node -> next = head;
	head = new_node;
	return head;
}


// To display the linked list
void display_linked_list(struct Node* head)
{
  if(head -> next != NULL)
  {
    display_linked_list(head -> next);
  }
  printf("%d", head -> data);
  return;
}


// To compute the product of a linked list with a single digit
struct Node* compute_product(struct Node* base_list, unsigned long long n)
{
  int digit;
  bool is_trail = true;
  unsigned long long carry, product;

  struct Node *base_pointer, *product_pointer;

  base_pointer = base_list;
  product_pointer = NULL;
  carry = 0;

  // Calculate the next power of n
  while(base_pointer != NULL)
  {
    if(is_trail && base_pointer -> data == 0)
    {
      // Insert the digit in the linked list
      product_pointer = insert_node(product_pointer, base_pointer -> data);
      base_pointer = base_pointer -> next;
      continue;
    }
    else
    {
      is_trail = false;
    }
    // Calculate the product
    product = base_pointer -> data * n + carry;

    // Separate out the digit
    digit = product % 10;

    // Insert the digit in the linked list
    product_pointer = insert_node(product_pointer, digit);

    // Update the carry-over
    carry = product / 10;

    // Move to the next digit in the next node
    base_pointer = base_pointer -> next;
  }

  // Add the carry-over to the Linked list
  while(carry > 0)
  {
    // Separate out the digit
    digit = carry % 10;

    // Insert the digit in the linked list
    product_pointer = insert_node(product_pointer, digit);

    // Update the carry-over
    carry = carry / 10;
  }
  return product_pointer;
}


// To count the number of trailing 0s
int count_trailing_zeros(struct Node* head)
{
  int count = 0;

  while(head != NULL)
  {
    if(head -> data == 0)
    {
      count = count + 1;
      head = head -> next;
    }
    else
    {
      break;
    }
  }
  return count;
}


// To reverse the linked list
struct Node* reverse_linked_list(struct Node* head)
{
  // Declare pointers
  struct Node *current_node, *last_node, *next_node;

  // Initialize pointers
  current_node = head;
  last_node = NULL;
  next_node = NULL;

  while(current_node != NULL)
  {
    // Store the next node
    next_node = current_node -> next;

    // Reverse the current node pointer
    current_node -> next = last_node;

    // Traverse to next node in list
    last_node = current_node;
    current_node = next_node;
  }
  head = last_node;
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


// To count the number of nodes in linked list
int count_nodes(struct Node* head)
{
  int count = 0;
  while(head != NULL)
  {
    count++;
    head = head -> next;
  }
  return count;
}


// To search the pattern in the final linked list
int search_pattern(struct Node* final_list, struct Node* search_key, int search_count)
{
  int pattern_count;

  pattern_count = 0;

  if(search_count == 1)
  {
    while(final_list != NULL)
    {
      if(final_list -> data == search_key -> data)
      {
        pattern_count++;
      }
      final_list = final_list -> next;
    }
  }

  else if(search_count == 2)
  {
    while(final_list -> next != NULL)
    {
      if(final_list -> data == search_key -> data
        && final_list -> next -> data == search_key -> next ->data)
      {
        pattern_count++;
      }
      final_list = final_list -> next;
    }
  }

  else
  {
    while(final_list -> next -> next != NULL)
    {
      if(final_list -> data == search_key -> data
        && final_list -> next -> data == search_key -> next ->data
        && final_list -> next -> next -> data == search_key -> next -> next ->data)
      {
        pattern_count++;
      }
      final_list = final_list -> next;
    }
  }
  return pattern_count;
}


/* ------------- */
/* MAIN FUNCTION */
/* ------------- */


void main()
{
  int i, n, N, zero_count,t, test_cases, search_count, pattern_count;
  unsigned long long n_septa, n_hexa, n_penta, n_quad, n_cube, n_square;
  char inputs[3];
  struct Node *search_key, *n_hash_final;

  // Get the number of test cases
	scanf("%d\n", &test_cases);

  // For each testcase
  for(t=0; t<test_cases; t++)
  {
    // Receive User inputs
    scanf("%d %s", &N, &inputs);

    int z = 0;
    int pattern_len = 0;

    // Declare pointer for search key
    search_key = NULL;

    // For each character in input pattern
    while(inputs[z])
    {
      // Store the search pattern in a linked list
      search_key = insert_node(search_key, (int)inputs[z] - 48);
      z++;
    }

    // Get the length of the pattern to search
    search_count = count_nodes(search_key);

    // Check for invalid input
    if(N == 0)
    {
      if(search_count == 1 && search_key -> data == 0)
      {
        printf("1 1 0\n");
      }
      else
      {
        printf("1 0 0\n");
      }
      continue;
    }

    n = 0;

    // Define the main linked list1
    n_hash_final = NULL;

    // Set first term as a linked list
    n_hash_final = insert_node(n_hash_final, 1);

    // Iterate 2 to N
    for(n=2; n<=N; n++)
    {
      n_septa = pow(n, 7);
      n_hexa = pow(n, 6);
      n_penta = pow(n, 5);
      n_quad = pow(n, 4);
      n_cube = pow(n, 3);
      n_square = pow(n, 2);

      i = 0;

      while(i != n)
      {
        // Multiply by n^7
        if(i+7 <= n)
        {
          n_hash_final = compute_product(n_hash_final, n_septa);
          i = i + 7;
        }

        // Multiply by n^6
        else if(i+6 <= n)
        {
          n_hash_final = compute_product(n_hash_final, n_hexa);
          i = i + 6;
        }

        // Multiply by n^5
        else if(i+5 <= n)
        {
          n_hash_final = compute_product(n_hash_final, n_penta);
          i = i + 5;
        }

        // Multiply by n^4
        else if(i+4 <= n)
        {
          n_hash_final = compute_product(n_hash_final, n_quad);
          i = i + 4;
        }

        // Multiply by n^3
        else if(i+3 <= n)
        {
          n_hash_final = compute_product(n_hash_final, n_cube);
          i = i + 3;
        }

        // Multiply by n^2
        else if(i+2 <= n)
        {
          n_hash_final = compute_product(n_hash_final, n_square);
          i = i + 2;
        }

        // Multiply by n^1
        else
        {
          n_hash_final = compute_product(n_hash_final, n);
          i++;
        }
        n_hash_final = reverse_linked_list(n_hash_final);
      }
    }
    // Count the total number of trailing 0s
    zero_count = count_trailing_zeros(n_hash_final);
    printf("%d ", zero_count);

    // Search for the given pattern in the final linked list
    pattern_count = search_pattern(n_hash_final, search_key, search_count);
    printf("%d ", pattern_count);

    // Reverse the final n hash linked list to get readable form
    display_linked_list(n_hash_final);
    printf("\n");

    // Free the nodes and delete the linked list
    delete_linked_list(&search_key);
    delete_linked_list(&n_hash_final);
  }
  return;
}
