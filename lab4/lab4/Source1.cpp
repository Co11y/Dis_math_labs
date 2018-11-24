#include <iostream>


// struct for edges
typedef struct edges {
	int tops1, tops2, price;
	struct edges * next;
}edge;


// struct for tops
typedef struct tops {
	int value;
	struct tops * next;
	edge * list;
	edge ** home;
}top;

// create ege
void create_edge(edge ** home, int top1, int top2, int prices) {
	edge * new_node = new(edge);
	new_node->next = *home;
	new_node->tops1 = top1;
	new_node->tops2 = top2;
	new_node->price = prices;
	*home = new_node;
}

// create new edge node
void create_edge_node(top ** home, int top1, int top2, int prices) {
	top * tmp = *home;
	while (tmp != NULL) {
		if (tmp->value == top1 || tmp->value ==  top2) {
			create_edge(tmp->home, top1, top2, prices);
		}
		tmp = tmp->next;
	}
}

// create new top node
void create_node_top(top ** home, int val) {
	top * new_node = new(top);
	new_node->next = *home;
	new_node->value = val;
	*home = new_node;
	// initialist for edge
	new_node->list = new(edge);
 	new_node->list->next = NULL;
	new_node->list->tops1 = -1;
	new_node->list->tops2 = -1;
	new_node->home = &new_node->list;

}


// print
void printe(top ** home) {
	top * tmp = *home;
	while (tmp != NULL) {
		if (tmp->value != -1) {
			std::cout << tmp->value << " " << "this is top ";

			if (tmp->list->tops1 != -1 && tmp->list->tops2 != -1) {
				std::cout << tmp->list->tops1 << ' ' << tmp->list->tops2 << ' ' << tmp->list->price << ' '; 
				std::cout << "this is rebro ";
			}
		}
		tmp = tmp->next;
	}
}

int main() {
	top * first = new(top);
	first->next = NULL;
	top ** home = &first;
	first->value = -1;
	// initialist for edge
	first->list = new(edge);
	first->list->next = NULL;
	first->home = &first->list;

	create_node_top(home, 5);
	create_node_top(home, 6);
	create_node_top(home, 9);

	create_edge_node(home, 5, 9, 14);
	printe(home);
	system("pause");
}