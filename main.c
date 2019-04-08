#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 1000


int** read_Key(int keysize, char keyfilename[]){/*Reads input key file*/

    FILE *fp;
    char str[MAXCHAR];
    fp = fopen(keyfilename, "r");
    int size = keysize;
    if (fp == NULL){
        printf("Could not open file %s",keyfilename);
        return 1;
    }
    int a = 0;
    int **key = (int **)malloc(size * sizeof(int *));/*Create dynamic 2d array*/
    for (a=0; a<size; a++)
         key[a] = (int *)malloc(size * sizeof(int));
    int count = 0;
    int row = 0;
    while (fgets(str, MAXCHAR, fp) != NULL){
        char *token;

        /* first token */
        token = strtok(str, " ");

        /* other tokens */
        count = 0;
        while( token != NULL ) {
            key[row][count] = atoi(token);/*Cast to integer*/

            token = strtok(NULL, " ");

            count++;
        }
        row++;
 }
        fclose(fp);
    return key;


}

int** read_Map(int mapSize[2], char mapfilename[]){/*Read input map file*/

    FILE *fp;
    char str[MAXCHAR];
    fp = fopen(mapfilename, "r");
    if (fp == NULL){
        printf("Could not open file %s",mapfilename);
        return 1;
    }
    int a = 0;
    int row = mapSize[0];
    int column = mapSize[1];
    int **map = (int **)malloc(row * sizeof(int *));/*Create dynamic 2d array*/
    for (a=0; a<row; a++)
         map[a] = (int *)malloc(column * sizeof(int));
    int count = 0;
    int rc = 0;
    while (fgets(str, MAXCHAR, fp) != NULL){
        char *token;

        /* first token */
        token = strtok(str, " ");

        /* other tokens */
        count = 0;
        while( token != NULL ) {
            map[rc][count] = atoi(token);/*Cast to integer*/

            token = strtok(NULL, " ");

            count++;
        }
        rc++;

    }
          fclose(fp);
    return map;

}

void find_Treasure(FILE* out, int** key, int** map, int keysize, int mapSize[2], int row, int column){

    int i, j = 0;
    int multiplication = 0;
    for(i=0;i<keysize;i++){
        for(j=0;j<keysize;j++){
            multiplication += map[row+i][column+j]*key[i][j];/*calculate the matrix multiplication*/

        }
    }

    fprintf(out,"%d,%d:%d\n", row+(keysize-1)/2, column+(keysize-1)/2,multiplication);/*print out to the output txt*/


    if(multiplication%5==0){/*FOUND TREASURE*/
        return 0;
    }else if(multiplication%5==1){/* GO UP*/
        if(map[row][column+1] == 0){/*hit the border*/
            find_Treasure(out, key, map, keysize, mapSize, row+keysize, column);
        }else
            find_Treasure(out, key, map, keysize, mapSize, row-keysize, column);

    }else if(multiplication%5==2){/*GO DOWN*/
        if(map[row+keysize-1][column+1] == 0){/*hit the border*/
            find_Treasure(out, key, map, keysize, mapSize, row-keysize, column);
        }else
            find_Treasure(out, key, map, keysize, mapSize, row+keysize, column);

    }else if(multiplication%5==3){/*GO RIGHT*/
        if(map[row+1][column+keysize-1] == 0){/*hit the border*/
            find_Treasure(out, key, map, keysize, mapSize, row, column-keysize);
        }else
            find_Treasure(out, key, map, keysize, mapSize, row, column+keysize);

    }else if(multiplication%5==4){ /*GO LEFT*/
        if(map[row+1][column] == 0){/*hit the border*/
            find_Treasure(out, key, map, keysize, mapSize, row, column+keysize);
        }else
            find_Treasure(out, key, map, keysize, mapSize, row, column-keysize);

    }

}

int main(int argc, char *argv[]) {

    int keysize= atoi(argv[2]);
    int i, j, k = 0;
    int mapSize[2];
    FILE *f;
    f = fopen(argv[5], "w");

    char *tok = strtok(argv[1], "x");

        /* other tokens */
        while( tok != NULL ) {
            mapSize[k++] = atoi(tok);

            tok = strtok(NULL, "x");
        }

    int **key = read_Key(keysize, argv[4]);/*function call to read and create key matrix*/
    int **map = read_Map(mapSize, argv[3]);/**/


    find_Treasure(f, key, map, keysize, mapSize, 0, 0);/*function call to read and create map matrix*/
    fclose(f);
    return 0;
}
