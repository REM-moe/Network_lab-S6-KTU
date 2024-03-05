#include<stdio.h>
void main() {
	int num_of_nodes;
	printf("Enter no of nodes: ");
	scanf("%d",&num_of_nodes);
	int routing_table[num_of_nodes][num_of_nodes];
	printf("Enter Routing Table: \n");
	for(int i = 0; i<num_of_nodes; i++) {
		for(int j = 0; j<num_of_nodes; j++) {
			printf("node[%d][%d]: ", i , j);
			scanf("%d",&routing_table[i][j]);
		}
	}
	for(int  x = 0; x<num_of_nodes; x++) {
		for(int i = 0; i<num_of_nodes; i++) {
			for(int j = 0; j<num_of_nodes; j++) {
				for(int k = 0; k< num_of_nodes; k++) {
					if(routing_table[i][j] > routing_table[k][j] + routing_table[i][k]) {
						routing_table[i][j] = routing_table[i][k] + routing_table[k][j];
					}
				}
			}
		}
	}
	printf("\n Distance Vector Table\n");
	for(int i = 0; i<num_of_nodes; i++) {
			for(int j = 0; j<num_of_nodes; j++) {
				printf("%d\t", routing_table[i][j]);
			}
			printf("\n");
		}
}
