#include <iostream>

typedef struct vertex vertex;
typedef struct edge edge;
typedef struct min min;

typedef struct min {
	int min;
	int vertex1, vertex2;
	vertex * to;
}min;

typedef struct vertex {
	int vertex;
	struct vertex * next;
	min min;
	int in_tree = 0;
	int way = 1000;

	edge * head = nullptr;

}vertex;

typedef struct edge {
	int vertex1, vertex2, price;
	struct edge * next;
	vertex * to;
}edge;



void add_vertex(vertex * & head, int vertex_value) {

	vertex * new_vertex = new(vertex);
	new_vertex->vertex = vertex_value;
	new_vertex->min.min = 100;

	if (!head) {
		new_vertex->next = NULL;
		head = new_vertex;
		return;
	}
	vertex * tracer = head;

	while (tracer->next != NULL) {
		tracer = tracer->next;
	}
	tracer->next = new_vertex;
	new_vertex->next = NULL;

}

// mb bug here
void find_min_l(vertex * & element) {

	edge * tracer = element->head;
	element->min.min = 100;
	while (tracer != NULL) {

		if (tracer->price < element->min.min) {
			element->min.min = tracer->price;
			element->min.vertex1 = tracer->vertex1;
			element->min.vertex2 = tracer->vertex2;
			element->min.to = tracer->to;
		}

		tracer = tracer->next;

	}
}

void delete_edge(vertex * & head, int vertex1, int vertex2) {
	vertex * tracer = head;

	while (tracer != NULL) {


		if ((tracer->vertex == vertex1) || (tracer->vertex == vertex2)) {

			edge * tracer_edge = tracer->head;
			edge * prev = tracer_edge;


			if ((tracer_edge->vertex1 == vertex1 || tracer_edge->vertex1 == vertex2) && (tracer_edge->vertex2 == vertex1 || tracer_edge->vertex2 == vertex2)) {
				edge * tmp = tracer_edge;
				tracer->head = (tracer->head)->next;
				delete tmp;
				tracer_edge = head->head;


				//if ((tracer_edge->vertex1 < -1) && (tracer_edge->next == NULL)) {
				//	tracer_edge = NULL;
				//}

			}

			while (tracer_edge != NULL) {

				if ((tracer_edge->vertex1 == vertex1 || tracer_edge->vertex1 == vertex2) && (tracer_edge->vertex2 == vertex1 || tracer_edge->vertex2 == vertex2)) {

					prev->next = tracer_edge->next;
					delete tracer_edge;
					tracer_edge = prev->next;
					continue;

				}

				prev = tracer_edge;
				tracer_edge = tracer_edge->next;


			}

		}
		find_min_l(tracer);
		tracer = tracer->next;
	}
}



// you created new struct min to get data about vertixe that minimum effect, to use func in tree to finish algo becouse it was skiping som elements
void find_min_tree(vertex * head, min * & minimal) {
	minimal->min = 100;
	vertex * tracer = head;

	while (tracer != NULL) {
		if (tracer->in_tree) {

			if (tracer->min.min < minimal->min) {
				minimal->min = tracer->min.min;
				minimal->vertex1 = tracer->min.vertex1;
				minimal->vertex2 = tracer->min.vertex2;

			}

		}


		tracer = tracer->next;
	}
}

vertex * search(vertex * head, int vert_val) {

	vertex * tracer = head; 

	while (tracer != NULL) {

		if (tracer->vertex == vert_val) {
			return tracer;
		}
		
		tracer = tracer->next;
	}
	return NULL;
}

void add_edge_body(vertex *  head, vertex * & vertex_node, int vertex1, int vertex2, int price) {

	edge * new_edge = new(edge);
	new_edge->vertex1 =  vertex_node->vertex;
	int vert = 1;
	if (vertex_node->vertex != vertex1) vert = vertex1;
	else if (vertex_node->vertex != vertex2) vert = vertex2;
	new_edge->vertex2 = vert;
	new_edge->price = price;
	// 111
	new_edge->to = search(head, new_edge->vertex2);

	if (!vertex_node->head) {
		new_edge->next = NULL;
		vertex_node->head = new_edge;
		return;
	}
	edge * tracer = vertex_node->head;

	while (tracer->next != NULL) {
		tracer = tracer->next;
	}
	tracer->next = new_edge;
	new_edge->next = NULL;

}

void add_edge(vertex *  head, int vertex_value1, int vertex_value2, int price) {
	vertex * tracer = head;

	while (tracer != NULL) {

		if ((tracer->vertex == vertex_value1) || (tracer->vertex == vertex_value2)) {

			add_edge_body(head, tracer, vertex_value1, vertex_value2, price);
			find_min_l(tracer);

		}

		tracer = tracer->next;
	}

}

void printe(vertex * head) {
	vertex * tracer = head;
	while (tracer != NULL) {
		std::cout << "This is vetex " << tracer->vertex << " this is min " << tracer->min.min << std::endl;

		edge * tracer_edge = tracer->head;

		while (tracer_edge != NULL) {


			std::cout << "This is vertexes " << tracer_edge->vertex1 << ' ' << tracer_edge->vertex2 << ' ' << "this is price " << tracer_edge->price << std::endl;

			tracer_edge = tracer_edge->next;

		}

		tracer = tracer->next;
	}

}

void add_to_tree(vertex * & head, int vertex1, int vertex2) {
	vertex * tracer = head;

	while (tracer != NULL) {

		if (tracer->vertex == vertex1 || tracer->vertex == vertex2) {
			tracer->in_tree = 1;
		}

		tracer = tracer->next;

	}
}

int if_in_tree(vertex * head, int vertex_value) {

	vertex * tracer = head;

	while (tracer != NULL) {

		if (tracer->in_tree) {

			if (tracer->vertex == vertex_value) {
				return 1;
			}

		}

		tracer = tracer->next;
	}
	return 0;

}

void prima_algo(vertex * & head) {
	vertex * tracer = head;
	tracer->in_tree = 1;

	int i = 0;

	while ((tracer != NULL) && (i != 11)) {
		int add = 0;
		min * minimal = new(min);
		find_min_tree(head, minimal);
		if (i != 0) {
			if ((if_in_tree(head, minimal->vertex1)) && (if_in_tree(head, minimal->vertex2))) {
				delete_edge(head, minimal->vertex1, minimal->vertex2);
			}
		}

		if (tracer->in_tree) {

			edge * tracer_edge = tracer->head;

			while (tracer_edge != NULL) {

				if (tracer_edge->price == minimal->min) {
					std::cout << "vertex " << tracer_edge->vertex1 << ' ' << tracer_edge->vertex2 << ' ' << "price is " << tracer_edge->price << std::endl;
					add_to_tree(head, tracer_edge->vertex1, tracer_edge->vertex2);
					delete_edge(head, tracer_edge->vertex1, tracer_edge->vertex2);
					tracer = head;
					add = 1;
					i++;
					break;
				}

				tracer_edge = tracer_edge->next;
			}

		}
		if (add) continue;
		tracer = tracer->next;

	}
}

void go_to();

void dijkstra_algo(vertex * & head, vertex * & last, int goal) {

	last = head;
	last->way = 0;

	vertex * tracer = head;

	while (true) {

		if (last->vertex == goal) return;

			edge * tracer_edge = last->head;
			find_min_l(last);
			if ((last->min.to)->in_tree) {
				delete_edge(head, last->min.vertex1, last->min.vertex2);
				find_min_l(last);
			}

			while (tracer_edge != NULL) {
				// bug with to
				if (tracer_edge->vertex2 == goal) {
					std::cout << "found";
					return;
				}
				if ((tracer_edge->to)->way > (last->way + tracer_edge->price)) {

					(tracer_edge->to)->way = (last->way + tracer_edge->price);

				}
				tracer_edge = tracer_edge->next;

			}
			(last->min.to)->in_tree = 1;
			//if ((last->min.to)->in_tree) {
			//	delete_edge(head, last->min.vertex1, last->min.vertex2);
			//	tracer_edge = last->head;
			//	continue;
			//}
			vertex * tmp = last->min.to;
			delete_edge(head, last->min.vertex1, last->min.vertex2);
			last = tmp;
			std::cout << "currently in " << last->vertex << std::endl;









	}




}

int main() {
	vertex * head = nullptr;
	vertex * last;


	add_vertex(head, 1);
	add_vertex(head, 2);
	add_vertex(head, 3);
	add_vertex(head, 4);
	add_vertex(head, 5);
	add_vertex(head, 6);
	add_vertex(head, 7);
	add_vertex(head, 8);
	add_vertex(head, 9);
	add_vertex(head, 10);
	add_vertex(head, 11);
	add_vertex(head, 12);
	add_vertex(head, 13);
	add_vertex(head, 14);
	add_vertex(head, 15);
	add_vertex(head, 16);
	add_vertex(head, 17);
	add_vertex(head, 18);
	add_vertex(head, 19);
	add_vertex(head, 20);
	add_vertex(head, 21);
	add_vertex(head, 22);
	add_vertex(head, 23);
	add_vertex(head, 24);
	add_vertex(head, 25);
	add_vertex(head, 26);
	add_vertex(head, 27);
	add_vertex(head, 28);
	add_vertex(head, 29);
	add_vertex(head, 30);

	add_edge(head, 1, 2, 6);
	add_edge(head, 1, 6, 4);

	add_edge(head, 2, 3, 3);
	add_edge(head, 2, 7, 2);

	add_edge(head, 3, 4, 5);
	add_edge(head, 3, 8, 1);

	add_edge(head, 4, 5, 3);
	add_edge(head, 4, 9, 7);

	add_edge(head, 5, 10, 4);


	add_edge(head, 6, 11, 1);
	add_edge(head, 6, 7, 8);

	add_edge(head, 7, 12, 1);
	add_edge(head, 7, 8, 7);

	add_edge(head, 8, 13, 3);
	add_edge(head, 8, 9, 2);

	add_edge(head, 9, 14, 3);
	add_edge(head, 9, 10, 2);

	add_edge(head, 10, 15, 7);



	add_edge(head, 11, 16, 1);
	add_edge(head, 11, 11, 3);

	add_edge(head, 12, 17, 4);
	add_edge(head, 12, 13, 1);

	add_edge(head, 13, 18, 7);
	add_edge(head, 13, 14, 7);

	add_edge(head, 14, 19, 1);
	add_edge(head, 14, 15, 3);

	add_edge(head, 15, 20, 3);


	add_edge(head, 16, 21, 3);
	add_edge(head, 16, 17, 1);

	add_edge(head, 17, 22, 2);
	add_edge(head, 17, 18, 4);

	add_edge(head, 18, 23, 5);
	add_edge(head, 18, 19, 8);

	add_edge(head, 19, 24, 1);
	add_edge(head, 19, 20, 8);

	add_edge(head, 20, 25, 3);


	add_edge(head, 21, 26, 5);
	add_edge(head, 21, 22, 3);

	add_edge(head, 22, 27, 4);
	add_edge(head, 22, 23, 1);

	add_edge(head, 23, 28, 2);
	add_edge(head, 23, 24, 4);

	add_edge(head, 24, 29, 8);
	add_edge(head, 24, 25, 1);

	add_edge(head, 25, 30, 6);


	add_edge(head, 26, 27, 7);

	add_edge(head, 27, 28, 7);

	add_edge(head, 28, 29, 5);

	add_edge(head, 29, 30, 7);







	printe(head);
	std::cout << "--------------------------------" << std::endl;
	dijkstra_algo(head, last, 4);

	system("pause");
}