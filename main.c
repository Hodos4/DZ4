#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){
    int mode;
    printf("0 - digraph\n1 - graph\n");
    scanf("%d", &mode);
    
    if(!( mode == 1 || mode == 0 ))
        exit(101);
    
    printf("Amount of vertexs:\n> ");
    int amount;
    scanf("%d",&amount);
    if (amount <= 0){
        printf("Negative nummer\n");
        exit(102);
    }
    
    getchar();
    printf("Call vertexs\n");
    
    char **table;
    table = calloc(amount, sizeof(char*));
    for(int i=0; i<amount; i++){
        table[i] = calloc(amount+1, sizeof(char));
    }
    
    for(int i=0; i<amount; i++){
        printf("%d: ",i);
        table[i][0] = getchar();
        getchar();

        if(!(('A' <= table[i][0] && table[i][0] <= 'Z') || ('a' <= table[i][0] && table[i][0] <= 'z'))){
            printf("Enter Letters!\n");
            i--;
        } else {
            for(int j=0; j<i; j++){
                if( table[i][0] == table[j][0] ){
                    printf("Enter another name\n");
                    i--;
                }
            }
        }
    }
        
    for(int i=0; i<amount; i++){
        for(int j=1; j<amount; j++){
            table[i][j] = 0;
        }
    }
    
    printf("Enter connections\n");
    
    char str[1024] = {0};
    scanf("%s", str);
    
    int i=0;
    while(str[i] != '\0'){
        char name1, name2;
        int numname1 = -1, numname2 = -1;
        name1 = str[i++];
        i++;
        name2 = str[i++];
        i++;

        for(int k=0; k<amount; k++){
            if(table[k][0] == name1){
                numname1 = k;
            }
            if(table[k][0] == name2){
                numname2 = k;
            }
        }
        table[numname1][numname2+1]++;
    }

    printf("\n");
    int graph_check = 1;
    
    for(int i=0; i<amount; i++){
        int temp_graph_check = 0;
        for(int j=0; j<amount; j++){
            if(table[i][j+1] == 1)
                temp_graph_check = 1;
    
            if(table[j][i+1] == 1)
                temp_graph_check = 1;
        }
        if(temp_graph_check == 0)
            graph_check=0;
    }
    
    if(graph_check == 0){
        printf("unrelated graph\n");
    } else {
        printf("related graph\n");

    }
    printf("--------------------\n");

    for(int i=0; i<amount; i++) {
        
        printf("%c: ", table[i][0]);
        
        for (int j=1; j<amount+1; j++) {
            printf("%d  ", table[i][j]);
        }

        printf("\n");
    }

    int stepen[amount];
    for(int i=0; i<amount; i++){
        for(int j=1; j<amount+1; j++){
            stepen[i] += table[i][j];
            stepen[i] += table[i][j];
        }
    }
    
    
    for (int gap = amount/2; gap > 0; gap /= 2) {
        for (int i = gap; i < amount; i++) {
            for (int j = i-gap; j >= 0 && stepen[j] > stepen[j+gap]; j-=gap) {
                int temp = stepen[j];
                stepen[j] = stepen[j+gap];
                stepen[j+gap] = temp;
                
                temp = table[j][0];
                table[j][0] = table[j+gap][0];
                table[j+gap][0] = temp;
                
                for(int k=1; k<amount+1; k++){
                    temp = table[j][k];
                    table[j][k] = table[j+gap][k];
                    table[j+gap][k] = temp;
                }
                
                for(int k=0; k<amount; k++){
                    temp = table[k][j+1];
                    table[k][j+1] = table[k][j+gap+1];
                    table[k][j+gap+1] = temp;
                }
                
            }
        }
    }

    printf("\nWith sorting\n");
    for(int i=0; i<amount; i++) {
        
        printf("%c: ", table[i][0]);
        
        for (int j=1; j<amount+1; j++) {
            printf("%d  ", table[i][j]);
        }

        printf("\n");
    }

    FILE *fp=fopen("graph.dot", "w");
    if(fp == NULL) {
        printf("Unable to create file\n");
        exit(0);
    }

    char file[1024] = {0};
    char arrow[3] = "";
    
    if(mode == 0){
        strcat(file, "digraph G {");
        strcat(arrow, "->");
    } else {
        strcat(file, "graph G {");
        strcat(arrow, "--");
    }
    for(int i=0; i<amount; i++){
        char elem[3] = "";
        elem[0] = table[i][0];
        strcat(file, elem);
        strcat(file, "; ");
    }
    for(int i=0; i<amount; i++){
        for(int j=0; j<amount; j++){
            for(int k=0; k<table[i][j+1]; k++){
                char elem[2] = "";
                elem[0] = table[i][0];
                
                strcat(file, elem);
                strcat(file, arrow);
                
                elem[0] = table[j][0];
                strcat(file, elem);
                strcat(file, "; ");
            }
        }
    }
    strcat(file, "}");
    fputs(file, fp);
    fclose(fp);
    
    return 0;
}
