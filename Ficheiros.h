

#ifndef UNTITLED11_FICHEIROS_H
#define UNTITLED11_FICHEIROS_H
#include "Estruturas.h"
void writeFile(char *filename,client *clients,int len,data todayDate);
client* readFile(char *filename,int *len,data *todayDate);
#endif //UNTITLED11_FICHEIROS_H
