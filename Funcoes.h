

#ifndef UNTITLED10_FUNCOES_H
#define UNTITLED10_FUNCOES_H
#include "Estruturas.h"
#include "Ficheiros.h"
int int_input(int max);
void loadAccount( client_list *list);
void insertClient(client_list *l);
void changeDate(data *actual);
void removeStudent(client_list *list);
void clientInfo(client_list *list);
double double_input(int max);
void descbalance_list(client_list *list);
void makeExpense(client_list *list,expense_list *explist,data todayDate);
int verify_char(const char s[]);
void makeExpenseList(expense_list *list);
void saveInformation(int len_aux,client_list *list,data todayDate);


#endif //UNTITLED10_FUNCOES_H
