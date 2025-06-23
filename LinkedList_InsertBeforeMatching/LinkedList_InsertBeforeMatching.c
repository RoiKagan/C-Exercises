/*
============================================
Linked-List INSERT BEFORE MATCHING NODES

This program creates a doubly linked list of random integers.
It then inserts a new node with a specified value before every node
in the list that contains a matching target value.

============================================
*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LIST_LENGTH 20
#define MAX_VALUE 10

// Doubly linked list node definition
typedef struct TwoWay_LinkedList{
	int data;
	struct TwoWay_LinkedList* prev;
	struct TwoWay_LinkedList* next;
} Node;

// Creates a new node with the given value
Node* Create_Node(int val) {
	Node* new_node = (Node*)malloc(sizeof(Node));
	if (!new_node) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	new_node->data = val;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

// Generates a doubly linked list of random integers
Node* Generate_Random_TwoWay_LinkedList(int len,int max_val) {
	Node* head = Create_Node(rand()%(max_val+1));
	Node* prev_node = head;

	for (int i = 1; i < len; i++) {
		Node* new_node = Create_Node(rand() % (max_val)+1);
		prev_node->next = new_node;
		new_node->prev = prev_node;
		prev_node = new_node;
	}

	return head;
}

// Inserts a node with insert_value before the given node
void InsertBefore(Node* node, int insert_value, Node** head) {
	Node *new_node= (Node*)malloc(sizeof(Node));
	if (!new_node) {
		printf("Memory allocation failed.\n");
		exit(1);
	}
	new_node->data = insert_value;
	new_node->prev = node->prev;
	new_node->next = node;

	if (node->prev) 
		node->prev->next = new_node;
	else 
		*head = new_node;// Inserting before the head
	node->prev = new_node;
}

// Inserts a node with insert_value before every node whose data matches match_value
void InsertBeforeAllMatching(Node** head, int match_value, int insert_value) {
	Node* current = *head;
	while (current) {
		if (current->data == match_value)
			InsertBefore(current, insert_value, head);
		current = current->next;
	}
}

// Prints the list from head to tail
void Print_List(Node* head){
	Node* current = head;
	while (current) {
		if (current->next) printf("%d, ", current->data);
		else printf("%d\n", current->data);
		current = current-> next;
	}
}

// Frees all memory used by the list
void Free_List(Node* head) {
	Node* current = head;
	while (current) {
		Node* next_node = current->next;
		free(current);
		current = next_node;
	}
}

int main() {
	srand((unsigned int)time(NULL));

	Node* head = Generate_Random_TwoWay_LinkedList(LIST_LENGTH,MAX_VALUE); 

	printf("Original List:\n ");
	Print_List(head);

	int match_value = rand() % (MAX_VALUE + 1);  // Pick a random value to match
	int insert_value = 0;

	printf("\nInserting %d before every occurrence of %d: \n", insert_value, match_value);

	printf("Modified List:\n ");
	InsertBeforeAllMatching(&head, match_value, insert_value);

	Print_List(head);

	Free_List(head);
	return 0;
}