
#ifndef UNTITLED10_ESTRUTURAS_H
#define UNTITLED10_ESTRUTURAS_H
#define MAX_BUFFER 150


typedef struct{
    int day;
    int month;
    int year;
}data;

typedef struct{
    char name[MAX_BUFFER];
    int ID;
    int year;
    int class;
    data birthDate;
}student;

typedef struct{
    int ID;
    double value;
    char description[MAX_BUFFER];
    data buydate;
}expense;

typedef struct no_expense {
    expense expense;
    struct no_expense *pseg;
}no_expense;

typedef struct{
    int length;
    no_expense *begin;
}expense_list;

typedef struct{
    student student;
    double balance;
    expense expenses[MAX_BUFFER];
    int numberExpenses;
}client;

typedef struct no_client{
    client client;
    struct no_client *pseg;
}no_client;

typedef struct {
    int length;
    no_client *begin;
}client_list;

int compareDates(data new, data old);
int setDate(data *new,int day,int month,int year);
int initElist(expense_list *list);
int addExpense(expense_list *list,expense expense);
int showExpenselist(expense_list *list);
int expenseInfo(no_expense *no);
int clientExpenseInfo_aux(expense *exp);
int initClist(client_list *list);
int addClient(client_list *list, client client);
int addClientBalance(client_list *list, client client);
int removeClient(client_list *list, char *name);
int show_balance(client_list *list);
int show_list (client_list *list);
void infoClient(no_client *noClient);

#endif //UNTITLED10_ESTRUTURAS_H
