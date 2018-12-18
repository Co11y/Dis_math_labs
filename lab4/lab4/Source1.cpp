#include <iostream>

typedef struct vertex vertex;
typedef struct edge edge;
typedef struct min min;

typedef struct min {
	int min;
	int vertex1, vertex2;
}min;

typedef struct vertex {
	int vertex;
	struct vertex * next;
	min min;
	int in_tree = 0;

	edge * head = nullptr;

}vertex;

typedef struct edge {
	int vertex1, vertex2, price;
	struct edge * next;
}edge;



void add_vertex(vertex * & head, int vertex_value) {

	vertex * new_vertex = new(vertex);
	new_vertex->vertex = vertex_value;
	new_vertex->min.min = 100;

	if (!head) {
		new_vertex->next = NULL;
		head  = new_vertex;
		return;
	}
	vertex * tracer = head;

	while (tracer->next != NULL) {
		tracer = tracer->next;
	}
	tracer->next = new_vertex;
	new_vertex->next = NULL;

}

void find_min_l(vertex * & element) {

	edge * tracer = element->head;
	element->min.min = 100;
	while (tracer != NULL) {

		if (tracer->price < element->min.min) {
			element->min.min = tracer->price;
			element->min.vertex1 = tracer->vertex1;
			element->min.vertex2 = tracer->vertex2;
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

void add_edge_body(vertex * & vertex_node, int vertex1, int vertex2, int price) {
	
	edge * new_edge = new(edge);
	new_edge->vertex1 = vertex1;
	new_edge->vertex2 = vertex2;
	new_edge->price = price;

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

			add_edge_body(tracer,  vertex_value1,  vertex_value2,  price);
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


			std::cout << "This is vertexes " << tracer_edge->vertex1 << ' ' << tracer_edge->vertex2 << ' ' << "this is price " <<  tracer_edge->price << std::endl;

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
	int price_forest = 0;
	vertex * tracer = head;
	tracer->in_tree = 1;

	int i = 0;

	while ((tracer != NULL) && (i != 11)) {
		int add = 0;
		min * minimal = new(min);
		find_min_tree(head, minimal);
		if (i != 0) {
			if ( (if_in_tree(head, minimal->vertex1)) && (if_in_tree(head, minimal->vertex2)) ) {
				delete_edge(head, minimal->vertex1, minimal->vertex2);
			}
		}

		if (tracer->in_tree) {

			edge * tracer_edge = tracer->head;

			while (tracer_edge != NULL) {

				if (tracer_edge->price == minimal->min) {
					std::cout << "vertex " << tracer_edge->vertex1 << ' ' << tracer_edge->vertex2 << ' ' << "price is " << tracer_edge->price << std::endl;
					add_to_tree(head, tracer_edge->vertex1, tracer_edge->vertex2);
					price_forest += tracer_edge->price;
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
	std::cout << "price of the forest is " << price_forest << std::endl;
}

int main() {
	vertex * head = nullptr;


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

	// creating edges

	add_edge(head, 1, 4, 3);
	add_edge(head, 1, 3, 2);
	add_edge(head, 1, 2, 1);



	add_edge(head, 2, 5, 3);
	add_edge(head, 2, 7, 4);

	add_edge(head, 3, 5, 7);
	add_edge(head, 3, 6, 6);

	add_edge(head, 4, 6, 2);
	add_edge(head, 4, 7, 4);

	add_edge(head, 5, 8, 7);
	add_edge(head, 5, 9, 5);

	add_edge(head, 6, 8, 7);
	add_edge(head, 6, 10, 3);

	add_edge(head, 7, 9, 5);
	add_edge(head, 7, 10, 4);

	add_edge(head, 8, 11, 4);

	add_edge(head, 9, 11, 1);

	add_edge(head, 10, 11, 2);

	printe(head);
	std::cout << "--------------------------------" << std::endl;
	printe(head);

	prima_algo(head);

	system("pause");
}