#pragma once
#include <iostream>


// struct for edge
typedef struct nedge {
	int top1, top2;
	struct nedge * next;
} edge;


// struct for tops of graph
typedef struct toplist {
	int top;
	edge* list;
	edge** head;
	struct toplist * next;
}top;




// function to create new top node
void create_node_top(top **head, int val) {
	top * new_node = new(top);
	new_node->top = val;
	new_node->next = *head;
	// creating elements for edges
	new_node->list = new(edge);
	new_node->list->next = NULL;
	new_node->head = &new_node->list;
	*head = new_node;
}


// function to create new edge node

void create_node_edge(edge **head, int val1, int val2) {
	edge * new_node_edge = new(edge);
	new_node_edge->next = *head;
	new_node_edge->top1 = val1;
	new_node_edge->top2 = val2;
	*head = new_node_edge;
}


// create edge
void create_edge(top** head, int top1, int top2) {
	top * tmp = *head;

	while (tmp != NULL) {
		if (tmp->top == top1 || tmp->top == top2) {
			create_node_edge(tmp->head, top1, top2);
		}
		tmp = tmp->next;
	}
}

void print_list(top ** head) {
	top * current = *head;

	while (current != NULL) {
		std::cout << current->top << " ";
		current = current->next;
	}
}

int main() {
	top * node1 = new(top);
	node1->top = 1;
	node1->next = NULL;
	top ** head1 = &node1;
	create_node_top(head1, 2);
	create_node_top(head1, 3);
	create_node_top(head1, 4);
	create_node_top(head1, 5);
	create_edge(head1, 1, 2);
	print_list(head1);
	system("pause");
}


//#include <iostream>
//
//typedef struct nlist {
//	int value;
//	struct nlist * next;
//} node;
//
//void print_list(node ** head) {
//	node * current = *head;
//
//	while (current != NULL) {
//		std::cout << current->value << " ";
//		current = current->next;
//	}
//}
//
//void create_node(node **head, int val) {
//	node * new_node = new(node);
//	new_node->value = val;
//	new_node->next = *head;
//	*head = new_node;
//}
//int main() {
//	node* first = new(node);
//	node** head = &first;
//	first->value = 5;
//	node* second = new(node);
//	first->next = second;
//	second->next = NULL;
//	second->value = 17;
//	node n;
//	create_node(head, 6);
//	print_list(head);
//	system("pause");
//}