#include<stdio.h>

int main() {

    printf("Enter no of nodes: ");
    int no_nodes = 0;
    scanf("%d",&no_nodes);

    int map[no_nodes][no_nodes];
    printf("\nENTER THE TABLE\n");

    for(int i = 0; i<no_nodes; i++) {
        for(int j = 0; j<no_nodes; j++) {
            scanf("%d",&map[i][j]);
        }
    }

    for(int i = 0; i<no_nodes; i++) {
        for(int j = 0; j<no_nodes; j++) {
            for(int k = 0; k<no_nodes; k++) {
                if(map[i][j] > map[i][k] + map[k][j]){
                    map[i][j] = map[i][k] + map[k][j];
                }
            }
        }
    }

    printf("\n ***** DVR ***** \n");
    for(int i = 0; i<no_nodes; i++) {
        for(int j = 0; j<no_nodes; j++) {
            printf("%d\t",map[i][j]);
        }
        printf("\n");
    }

}