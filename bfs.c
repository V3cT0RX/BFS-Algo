#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIM 100

typedef struct node {
	int data;
	int pred;
	struct node *next;
} Node;

typedef struct q {
	Node *front, *rear;
} Queue;

Queue *initQueue() {
	Queue *q = (Queue*)malloc(sizeof(Queue));
	q->front = q->rear = NULL;
	return q;
}

int isEmpty(Queue *q) {
	if(q->front == NULL) {
		return 1;
	}
	return 0;
}

int pop(Queue *q) {
	int data = q->front->data;
	Node *f = q->front;
	q->front = q->front->next;
	free(f);
	return data;
}

void push(Queue *q, int d) {
	Node *neue = (Node*)malloc(sizeof(Node));
	neue->data = d;
	neue->next = NULL;
	if(q->front == NULL) {
		q->front = q->rear = neue;
	}
	q->rear->next = neue;
	q->rear = neue;
}

void printbfs(int adj[LIM][LIM], int n, int s) {
	int visited[LIM]={0,}, v, i;
	int dist[LIM]={0,};
	Queue *q = initQueue();
	
	push(q, s);
	dist[s]=0;
	printf("{%d(d:0)}", s+1);
	visited[s]=1;

	while(!isEmpty(q)) {
		v = pop(q);
		for(i=0;i<n;i++) {
			if(adj[v][i] != 0 && !visited[i]) {
				visited[i]=1;
				push(q,i);
				q->rear->pred = v;
				dist[i]=dist[v]+1;
				printf("->{%d(d:%d)}", i+1,dist[i]);
			}
		}
	}
	printf("\n\nNode format: {<vertex>(d:<distance>)}\n");
}

int main(int argc, char **argv) {
	FILE *fp;
	int v, adj[LIM][LIM]={0,}, lsize, i, n, j;
	char line[LIM], *tok;
	if(argc < 2) {
		printf("%s: Invalid number of arguments.\n", argv[0]);
		return -1;
	}

	if((fp = fopen(argv[1], "r"))==NULL) {
		printf("Unable to open file.\n");
		return -2;
	}

	n=0; //to count vertices
	while(NULL!=fgets(line, LIM, fp)) {
		tok = strtok(line," ");
		i = atoi(tok)-1;
		while((tok=strtok(NULL," "))!=NULL) { //adjacent vertex
			v = atoi(tok)-1;
			adj[i][v]++;
		}
		n++;
	}

	fclose(fp);
	
	printf("Enter source: ");
	scanf("%d", &v);

	printf("\nBFS Traversal:\n");
	printf("+------------------------------------------+\n");
	printbfs(adj, n, v-1);
	printf("+------------------------------------------+\n");

	return 0;
}
