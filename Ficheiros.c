#include <stdio.h>
#include "Ficheiros.h"
#include <stdlib.h>

/***
 * method that open a binary file with name "filanme" and write the date,len of the list and the client list.
 * @param filename name of file
 * @param clients client list
 * @param len length of client list
 * @param todayDate date
 */
void writeFile(char *filename,client *clients,int len,data todayDate){
    FILE *file;
    file = fopen(filename,"wb");
    if(file == NULL) return;
    if(fwrite(&len,sizeof(int),1,file) == 1){
        printf("LEN SAVED WITH SUCCESS\n");
    }
    if(fwrite(clients,sizeof(client),len,file) == len){
        printf("CLIENTS SAVED WITH SUCCESS\n");
    }
    if(fwrite(&todayDate,sizeof(data),1,file) == 1){
        printf("DATA SAVED WITH SUCCESS\n");
    }
    fclose(file);
}

/***
 * method that open a binary file with name "filanme" and read the date,len of the list and the client list.
 * @param filename name of file
 * @param len len of client list
 * @param todayDate date
 * @return client list
 */
client* readFile(char *filename,int *len,data *todayDate) {
    FILE *file;
    file = fopen(filename,"rb");
    if(file == NULL) return NULL;
    if(fread(len,sizeof(int),1,file) == 1){
        printf("LEN READED WITH SUCESS\n");
    }
    client *c = malloc(sizeof(client)* (*len));

    if(fread(c,sizeof(client),*len,file) == *len){
        printf("CLIENTS READED WITH SUCCESS\n");
    }
    if(fread(todayDate,sizeof(data),1,file)){
        printf("DATA READED WITH SUCESS\n");
    }
    fclose(file);
    return c;
}



