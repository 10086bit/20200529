#include<stdio.h>
#include <malloc.h>
#include "SeqCQueue.h"
#define Maxvertices 5
typedef struct Node{
	int dest;
	struct Node *next;
}Edge;

typedef struct {
	int data;
	int source;
	Edge* adj;

}AdjHeight;

typedef struct {
	AdjHeight a[Maxvertices];
	int numOfverts;
	int numOfEdge;
}ADjLGraph;

typedef struct {
	int row;
	int col;
}RC;

void CreateGraph(ADjLGraph* g, RC* d, int* v, int e, int n);
void InsertVertex(ADjLGraph* g, int i, int vertex);
void AdjInitiate(ADjLGraph* g);
bool InsertEdge(ADjLGraph* g, int v1, int v2);
bool DeleteEdge(ADjLGraph* g, int v1, int v2);
bool DestroyADj(ADjLGraph* g);
int  GetFristVex(ADjLGraph* g, int v);
int GetNextVex(ADjLGraph* g, int v1, int v2);
void DepthFSearch(ADjLGraph* g, int v, int visited[]);
void BroadFSearch(ADjLGraph* g, int v, int visited[]);

void CreateGraph(ADjLGraph *g,RC *d,int *v,int e,int n) {
	int i;
	AdjInitiate(g);
	
	for (i = 0; i < n; i++) {
		InsertVertex(g, i, v[i]);
	}
	for (i = 0; i < e; i++) {
		InsertEdge(g, d[i].row, d[i].col);
	}
}

void AdjInitiate(ADjLGraph* g) {
	int i = 0;
	g->numOfEdge = 0;
	g->numOfverts = 0;
	for (i = 0; i < Maxvertices; i++) {
		g->a[i].source = i;
		g->a[i].adj = NULL;
	}
}

void InsertVertex(ADjLGraph* g, int i, int vertex) {
	if (i >= 0 && i < Maxvertices) {
		g->a[i].data = vertex;
		g->numOfverts++;
	}
	else {
		printf("¶¥µã´íÎó");
	}
}

bool InsertEdge(ADjLGraph* g, int v1, int v2) {
	Edge* p;
	if (v1<0 || v1>=g->numOfverts || v2<0 || v2>=g->numOfverts) {
		printf("error");
		return false;
	}
	p = (Edge*)malloc(sizeof(Edge));
	p->dest=v2;
	p->next = g->a[v1].adj;
	g->a[v1].adj = p;
	g->numOfEdge++;

}

bool DeleteEdge(ADjLGraph *g,int v1, int v2) {
	Edge* pre, * curr;
	if (v1<0 || v1>Maxvertices || v2<0 || v2>Maxvertices) {
		printf("error");
		return false;
	}
	curr = g->a[v1].adj;
	pre = curr;
	while (curr != NULL && curr->dest != v2) {
		pre = curr;
		curr = curr->next;
	}
	if (curr != NULL && curr->dest == v2) {
		pre->next = curr->next;
		free(curr);
		g->numOfEdge--;
		return true;
	}
	else {
		printf("²»´æÔÚ");
		return false;
	}
}

bool DestroyADj(ADjLGraph* g) {
	int i;
	Edge* p, * q;
	for (i = 0; i < g->numOfverts; i++) {
		p = g->a[i].adj;
		while (p!=NULL) {
			q = p;
			p = p->next;
			free(q);
		}
	}
	return true;
}

int  GetFristVex(ADjLGraph* g, int v) {
	Edge* p;
	if (v < 0 || v >= Maxvertices) {
		printf("error");
		return -1;
	}
	p = g->a[v].adj;
	if (p != NULL) {
		return p->dest;
	}
	else {
		return -1;
	}
}

int GetNextVex(ADjLGraph* g, int v1, int v2) {
	Edge* p;
	if (v1<0 || v1>Maxvertices || v2<0 || v2>Maxvertices) {
		printf("error");
		return -1;
	}
	p = g->a[v1].adj;
	while (p != NULL) {
		if (p->dest != v2) {
			p = p->next;
		}
		else
		{
			break;
		}
	}
	p = p->next;
	if (p != NULL) {
		return p->dest;

	}
	else
	{
		return -1;
	}
}

void DepthFSearch(ADjLGraph* g, int v, int visited[]) {
	int w;
	printf("%d", g->a[v].data);
	visited[v] = 1;
	w = GetFristVex(g, v);
	while (w != -1) {
		if (!visited[w]) {
			DepthFSearch(g, w, visited);
		}
		w = GetNextVex(g, v, w);
	}
}

void BroadFSearch(ADjLGraph* g, int v,int visited[]) {
	int u, w;
	QUEUE que;
	printf("%d", g->a[v].data);
	visited[v] = 1;
	InitQueue(&que);
	EnQueue(&que, v, 5);
	while (EmptyQueue(&que)) {
		DelQueue(&que, &u, 5);
		w = GetFristVex(g, u);
		while (w != -1) {
			if (!visited[w]) {
				printf("%d", g->a[w].data);
				visited[w] = 1;
				EnQueue(&que, w, 5);
			}
			w = GetNextVex(g, u, w);
		}
	}
}