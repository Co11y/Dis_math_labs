#include <iostream>

// structs --------------------
typedef struct edges {
	int top1, top2, price;
	struct edges * next;
}edge;

typedef struct tops {
	int top;
	int min = 100;
	struct tops * next;
	edge * list;
	edge * head;
}top;

typedef struct mins {
	int min;
	top ** element;
}min;
// ----------------------------

top * create_top(top * head, int top_value) {
	top * tmp = head;
	while (tmp != NULL) {
		if (tmp->next == NULL) {
			top * new_top = new(top);
			new_top->top = top_value;
			new_top->next = NULL;

			new_top->list = new(edge);
			new_top->list->next = NULL;
			new_top->head = new_top->list;
			tmp->next = new_top;
			return head;
		}
		tmp = tmp->next;
	}
	return head;
}

// create edge node
edge * create_edge_node(edge * head, int val1, int val2, int price) {
	edge * tmp = head;
	while (tmp != NULL) {
		if (tmp->next == NULL) {
			edge * new_edge = new(edge);
			//data
			new_edge->top1 = val1;
			new_edge->top2 = val2;
			new_edge->price = price;

			new_edge->next = NULL;
			tmp->next = new_edge;
			return head;
		}
		tmp = tmp->next;
	}
}

// create edge
top* create_edge(top * head, int top1, int top2, int price = 0) {
	top * tmp = head;
	while (tmp != NULL) {
		if (tmp->top == top1 || tmp->top == top2) {
			if (price < tmp->min) {
				tmp->min = price;
			}
			tmp->head = create_edge_node(tmp->head, top1, top2, price);
		}
		tmp = tmp->next;
	}
	return head;
}


// out 
void printe(top * head) {
	top * tmp = head;
	while (tmp != NULL) {
		if (tmp->top > -1) {
			std::cout << "this is top: " << tmp->top << " this min price " << tmp->min << std::endl;
			edge * tmp_edge = tmp->head;
			while (tmp_edge != NULL) {
				if ((tmp_edge->top1 > -1) && (tmp_edge->top2 > -1)) {
					std::cout << "this is edges: " << tmp_edge->top1 << ' ' << tmp_edge->top2 << ' ' << "price: " << tmp_edge->price << std::endl;
				}
				tmp_edge = tmp_edge->next;
			}
		}
		tmp = tmp->next;
	}
}

// find min
int find_min(top * head) {
	int min = 100;
	edge * tmp_edge = head->head;
	while (tmp_edge != NULL) {
		if ((min > tmp_edge->price) && (tmp_edge->price > -1)) {
			min = tmp_edge->price;
		}
		tmp_edge = tmp_edge->next;
	}
	return min;
}

// delete edge
top * delete_edge(top * head, int top1, int top2) {
	top * tmp = head;
	while (tmp != NULL) {
		if ((tmp->top == top1 || tmp->top == top2)) {
			edge * tmp_edge = tmp->head;
			edge * prev = tmp->head;
			while (tmp_edge != NULL) {
				if ((tmp_edge->top1 == top1 || tmp_edge->top1 == top2) && (tmp_edge->top2 == top1 || tmp_edge->top2 == top2)) {
					prev->next = tmp_edge->next;
					delete tmp_edge;
					tmp_edge = prev->next;
					tmp->min = find_min(tmp);
					continue;
             }
				prev = tmp_edge;
				tmp_edge = tmp_edge->next;

			}
		}
		tmp = tmp->next;
	}
	return head;
}

top * insert_copy;

// inialising new linked list

top * initialise(top * head1) {
	top * start = new(top);
	start->list = new(edge);
	start->head = start->list;
	start->list->next = NULL;
	start->next = NULL;
	head1 = start;

	return head1;
}

void prima_Algo(top * head) {
	top * tmp = head;
	while (tmp != NULL) {
		std::cout << " Top is " << tmp->top << std::endl;

		edge * tmp_edge = tmp->head;
		while (tmp_edge != NULL) {
			if (tmp_edge->price == tmp->min) {
				std::cout << "Min edge is " << tmp_edge->top1 << ' ' << tmp_edge->top2 << std::endl;
				head = delete_edge(head, tmp_edge->top1, tmp_edge->top2);
				break;
			}
			tmp_edge = tmp_edge->next;
		}
		tmp = tmp->next;
	}
}


void Prima_Algo(top * head, top* head_p) {
	top * tmp = head;
	while (tmp != NULL) {


		}
		tmp = tmp->next;
	}



int main() {

	top * start = new(top);
	start->list = new(edge);
	start->head = start->list;
	start->list->next = NULL;
	start->next = NULL;
	top * head = start;

	top * start_p = new(top);
	start_p->list = new(edge);
	start_p->head = start_p->list;
	start_p->list->next = NULL;
	start_p->next = NULL;
	top * head_p = start_p;



	// --------------------- PRIMA here

	// tops creating
	head = create_top(head, 1);
	head = create_top(head, 2);
	head = create_top(head, 3);
	head = create_top(head, 4);
	head = create_top(head, 5);
	head = create_top(head, 6);
	head = create_top(head, 7);
	head = create_top(head, 8);
	head = create_top(head, 9);
	head = create_top(head, 10);
	head = create_top(head, 11);

	// creating edges

	head = create_edge(head, 1, 2, 1);
	head = create_edge(head, 1, 3, 2);
	head = create_edge(head, 1, 4, 3);

	head = create_edge(head, 2, 5, 3);
	head = create_edge(head, 2, 7, 4);

	head = create_edge(head, 3, 5, 7);
	head = create_edge(head, 3, 6, 6);

	head = create_edge(head, 4, 6, 2);
	head = create_edge(head, 4, 7, 4);

	head = create_edge(head, 5, 8, 7);
	head = create_edge(head, 5, 9, 5);

	head = create_edge(head, 6, 8, 7);
	head = create_edge(head, 6, 10, 3);

	head = create_edge(head, 7, 9, 5);
	head = create_edge(head, 7, 10, 4);

	head = create_edge(head, 8, 11, 4);
	
	head = create_edge(head, 9, 11, 1);

	head = create_edge(head, 10, 11, 2);


	prima_Algo(head);
	/*Prima_Algo(head);*/
	system("pause");

}