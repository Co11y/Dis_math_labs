#include <iostream>

typedef struct vertex vertex;
typedef struct edge edge;

typedef struct vertex {
	int vertex;
	struct vertex * next;
	int min;

	edge * head = nullptr;

}vertex;

typedef struct edge {
	int vertex1, vertex2, price;
	struct edge * next;
}edge;

void add_vertex(vertex * & head, int vertex_value) {

	vertex * new_vertex = new(vertex);
	new_vertex->vertex = vertex_value;

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

void find_min(vertex * head);

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

		}

		tracer = tracer->next;
	}

}

void printe(vertex * head) {
	vertex * tracer = head;
	while (tracer != NULL) {
		std::cout << "This is vetex " << tracer->vertex << std::endl;

		edge * tracer_edge = tracer->head;

		while (tracer_edge != NULL) {


			std::cout << "This is vertexes " << tracer_edge->vertex1 << ' ' << tracer_edge->vertex2 << ' ' << "this is price " <<  tracer_edge->price << std::endl;

			tracer_edge = tracer_edge->next;

		}

		tracer = tracer->next;
	}
}
int main() {
	vertex * head = nullptr;


	add_vertex(head, 1);
	add_vertex(head, 2);
	add_vertex(head, 3);
	add_vertex(head, 4);

	add_edge(head, 1, 2, 10);
	add_edge(head, 1, 3, 4);

	printe(head);
	system("pause");
}