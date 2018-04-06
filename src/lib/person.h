#include "graph.h"

#ifndef PERSON_H
#define PERSON_H

typedef struct person Person;

Person * Person_create(int id, int age);

void Person_destroy(void *person);

Vertex * Graph_searchPersonVertexById(Graph *graph, int id);

void Person_spreadMusic(Vertex *vertex, int* counter);

void Graph_destroyPeople(Graph *graph);

void Graph_sortVerticesByPersonId(Graph *graph);

#endif