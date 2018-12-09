#include <iostream>

// structs --------------------

typedef struct tops top;
typedef struct edges edge;

typedef struct edges {
	int top1, top2, price;
	top * to;
	struct edges * next;
}edge;

typedef struct tops {
	int top;
	int min = 100;
	int in_tree = 0;
	int amount = 1;
	struct tops * next;
	int skip;
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
			head->amount = head->amount + 1;
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

// search

top * add_to_tree(top * head, int top1, int top2) {
	top * tmp = head;
	while (tmp != NULL) {
		if (tmp->top = top1) {
			tmp->in_tree = 1;
		}
		else if (tmp->top = top2) {
			tmp->in_tree = 1;
		}
		tmp = tmp->next;
	}
	return head;
}

// create edge node
edge * create_edge_node(top * head1, edge * head, int val1, int val2, int price, int val) {
	edge * tmp = head;
	while (tmp != NULL) {
		if (tmp->next == NULL) {
			edge * new_edge = new(edge);
			//data
			new_edge->top1 = val;
			if (val != val1) {
				new_edge->top2 = val1;
			}
			else new_edge->top2 = val2;

			new_edge->price = price;
			/*new_edge->to = search(head1, new_edge->top2);*/

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
			tmp->head = create_edge_node(head, tmp->head, top1, top2, price, tmp->top);
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
	while ((tmp_edge != NULL) && (tmp_edge != nullptr)) {
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

// find min global 
int find_min_t(top * head) {
	top * tmp = head;
	int min = 100;
	while (tmp != NULL) {

		if (tmp->in_tree) {
			if (tmp->min < min) {
				min = tmp->min;
			}
		}
		tmp = tmp->next;
	}
	return min;
}

// in_tree 
// rework

int in_tree(top * head, edge * tmp_edge) {
	// check

	top * tmp_tree_check = head;
	while (tmp_tree_check != NULL) {

		if (tmp_tree_check->in_tree) {


			if (tmp_edge->top2 == tmp_tree_check->top) {
				//min = find_min_t(head);
				return 1;
			}
		}


		tmp_tree_check = tmp_tree_check->next;
	}
	return 0;
	// check
}

top * Prima_AlgoV2(top * head) {
	top * tmp = head;
	tmp->in_tree = 1;
	while (tmp != NULL) {
		top * tmp_tree = head;
		int min = find_min_t(head);

		while (tmp_tree->in_tree) {
			if (tmp_tree->next == NULL) {
				break;
			}
			edge * tmp_edge = tmp_tree->head;
			while (tmp_edge != NULL) {
				if (in_tree(head, tmp_edge)) {

					if (tmp->skip) {

						tmp_edge = tmp_edge->next;
						continue;
					}

					head = &*delete_edge(head, tmp_edge->top1, tmp_edge->top2);
					min = find_min_t(head);
					tmp_edge = tmp_edge->next;
					continue;

				}
				if (tmp_edge->price == min) {
					std::cout << "Top " << tmp_tree->top << ' ' << "edge >> " << tmp_edge->top1 << ' ' << tmp_edge->top2 << std::endl;


					head = &*delete_edge(head, tmp_edge->top1, tmp_edge->top2);
					break;
				}

				tmp_edge = tmp_edge->next;
			}

			tmp_tree = tmp_tree->next;
		}
		tmp = tmp->next;
	}
	return head;
}

top * Prima_Algo(top * head) {


	top * tmp = head;
	(tmp->next)->in_tree = 1;



	while (tmp != NULL) {
		int minimal = find_min_t(head);

		if (tmp->in_tree) {

			edge * tmp_edge = tmp->head;

			while (tmp_edge != NULL) {

				if (tmp_edge->price == minimal) {
					head = add_to_tree(head, tmp_edge->top1, tmp_edge->top2);
					tmp = delete_edge(head, tmp_edge->top1, tmp_edge->top2);
				}

				tmp_edge = tmp_edge->next;
			}

		}

		tmp = tmp->next;
	}
	return head;


}



int main() {

	top * start = new(top);
	start->list = new(edge);
	start->head = start->list;
	start->skip = 1;
	start->list->next = NULL;
	start->next = NULL;
	top * head = start;





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


	printe(head);

	printe(head);
	//prima_Algo(head);
	printe(head);
	std::cout << std::endl << std::endl << std::endl;

	head = Prima_Algo(head);
	// at start min is 100 this is the problem!
	system("pause");

}