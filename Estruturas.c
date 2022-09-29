#include "Estruturas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/***
 * method that checks if the new date is earlier than the current date. If is true returns 1 otherside returns 0.
 */
int compareDates(data new, data old) {
    if (new.year == old.year) {
        if (new.month < old.month) {
            return 1;
        } else {
            if (new.month == old.month) {
                if (new.day < old.day) {
                    return 1;
                }
            }
        }
    }
    if (new.year < old.year) {
        return 1;
    }
    return 0;
}

/***
 * method to set date
 * @param new new date
 * @param day day
 * @param month month
 * @param year year
 * @return 1 in case of success otherside return 0
 */
int setDate(data *new,int day,int month,int year) {
    if (new == NULL) return -1;
    if(day>0 && month>0 && year>0){
        if(month == 2 && year%4 == 0 && year%100!=0){
            if(day<30){
                new->day = day;
                new->month = month;
                new->year = year;
                return 1;
            }
            else{
                return -1;
            }
        }
        if(month == 2){
            if(day<29){
                new->day = day;
                new->month = month;
                new->year = year;
                return 1;
            }
            else{
                return -1;
            }
        }

        if(month == 4| month == 6||month == 9||month ==11){
            if(day<31){
                new->day = day;
                new->month = month;
                new->year = year;
                return 1;
            }
        }
        if(month == 1|| month == 3||month == 5||month == 7|| month == 8||month == 10||month == 12){
            if(day<32){
                new->day = day;
                new->month = month;
                new->year = year;
                return 1;
            }

        }
    }
    return -1;
}

/***
 * method that initialize a expense list.Return 1 in case of success otherside return -1
 * @param list list
 * @return 1 in case of success otherside return 0
 */
int initElist(expense_list *list){
    if(list == NULL) return -1;
    list -> begin = NULL;
    list->length = 0;
    return 1;
}

/***
 * method that put a expense in list(FIFO)
 * @param list list
 * @param expense expense
 * @return 1 in case of success otherside return 0
 */
int addExpense(expense_list *list,expense expense){
    if (list == NULL) return -1;
    no_expense *new = malloc(sizeof(struct no_expense));
    if(new == NULL)return -1;

    new->expense = expense;
    no_expense *aux;
    if(list->length == 0){
        new->pseg = NULL;
        list->begin = new;
        list->length+=1;
        return 1;
    }
    for(aux = list->begin;aux->pseg!=NULL;aux = aux->pseg);
    new->pseg = NULL;
    aux->pseg = new;
    list->length+=1;

    return 1;
}

/***
 * method to show expense info
 * @param no expense node
 * @return 1 in case of success otherside return 0
 */
int expenseInfo(no_expense *no){
    if(no == NULL) return -1;
    printf("EXPENSE: ");
    printf("ID:%d ",no->expense.ID);
    printf("DESCRIPTION:%s ",no->expense.description);
    printf("VALUE:%f\n",no->expense.value);
    return 1;
}

/***
 * mehthod to show clients expenses
 * @param exp expense
 * @return 1 in case of success otherside return 0
 */
int clientExpenseInfo_aux(expense *exp){
    if(exp == NULL) return -1;
    printf("EXPENSE: ");
    printf("ID:%d DESCRIPTION:%s VALUE:%.4f DATE:%d/%d/%d\n",exp->ID,exp->description,exp->value,exp->buydate.day,exp->buydate.month,exp->buydate.year);
    return 1;
}

/***
 * method to show expense list
 * @param list expense list
 * @return 1 in case of success otherside return 0
 */
int showExpenselist(expense_list *list){
    if(list == NULL) return -1;
    if(list->length == 0) return -1;
    no_expense *no = list->begin;
    printf("LIST:\n");
    while(no!=NULL){
        expenseInfo(no);
        no = no -> pseg;
    }
    printf("\n");
    return 1;
}

/***
 * method that initialize a client list
 * @param list
 * @return 1 in case of success otherside return 0
 */
int initClist(client_list *list){
    if(list == NULL) return -1;
    list -> begin = NULL;
    list->length = 0;
    return 1;
}

/***
 * method that put a client in list order by alphabetical order
 * @param list client list
 * @param client client
 * @return 1 in case of success otherside return 0
 */
int addClient(client_list *list, client client) {
    if (list == NULL) return -1;
    no_client *new = malloc(sizeof(struct no_client));
    if(new == NULL)return -1;

    new->client = client;
    no_client *aux;


    if(list->begin == NULL){
        new->pseg = NULL;
        list->begin = new;
        list->length+=1;
        return 1;
    }

    if(strcmp(new->client.student.name,list->begin->client.student.name)<0){
        new->pseg = list->begin;
        list->begin = new;
        list->length+=1;
    }
    else{
        for(aux = list->begin;aux->pseg!=NULL && (strcmp(aux->pseg->client.student.name,new->client.student.name)<0);aux = aux->pseg);
        new->pseg = aux->pseg;
        aux->pseg = new;
        list->length+=1;
    }
    return 1;
}

/***
 * method that put a client in list order by descend balance
 * @param list client list
 * @param client client
 * @return Return 1 in case of success otherside return -1
 */
int addClientBalance(client_list *list, client client) {
    if (list == NULL) return -1;
    no_client *aux;
    struct no_client *new = malloc(sizeof(struct no_client));
    if(new == NULL)return -1;

    new->client = client;
    if(list->begin == NULL){
        new->pseg = NULL;
        list->begin = new;
        list->length+=1;
        return 1;
    }
    if(new->client.balance > list->begin->client.balance){
        new->pseg = list->begin;
        list->begin = new;
        list->length+=1;
    }
    else{
        for(aux = list->begin;aux->pseg!=NULL && new->client.balance < aux->pseg->client.balance;aux = aux->pseg);
        new->pseg = aux->pseg;
        aux->pseg = new;
        list->length+=1;
    }
    return 1;
}

/***
 * method that receive a client name and remove these client.
 * @param list client list
 * @param name client name
 * @return Return 1 in case of success otherside return -1
 */
int removeClient(client_list *list, char *name){
    if(list == NULL) return -1;
    if(list->begin == NULL) return -1;

    no_client *temp = list->begin, *anterior;
    if(temp == NULL) return -1;

    if(strcmp(temp->client.student.name,name) == 0){
        list->begin=temp->pseg;
        free(temp);
        list->length--;
        return 1;
        }

    else {
        while (temp->pseg != NULL && strcmp(temp->client.student.name, name) != 0) {
            anterior = temp;
            temp = temp->pseg;
        }
        if(strcmp(temp->client.student.name,name) == 0){
            anterior->pseg = temp->pseg;
            list->length--;
            free(temp);
        }
        else{
            return -1;
        }
        }
    return 1;
}

/***
 * method to show client balance
 * @param list client list
 * @return Return 1 in case of success otherside return -1
 */
int show_balance(client_list *list){
    if(list == NULL) return -1;
    if(list->begin == NULL) return -1;
    no_client *no = list->begin;
    printf("LIST:\n");
    while(no!=NULL){
        printf("NAME: %s BALANCE:%.4f\n",no->client.student.name,no->client.balance);
        no = no -> pseg;
    }
    printf("\n");
    return 1;
}

/***
 * method that receive a no_client and show client info.
 * @param noClient cliente node
 */
void infoClient(no_client *noClient) {
    if (noClient == NULL) {
        return;
    }
    printf("-----STUDENT-----\n");
    printf("NAME:%s ID:%d YEAR:%d CLASS:%d BIRTHDATE:%d/%d/%d BALANCE:%.4f\n", noClient->client.student.name,noClient->client.student.ID
    ,noClient->client.student.year,noClient->client.student.class,noClient->client.student.birthDate.day,
           noClient->client.student.birthDate.month, noClient->client.student.birthDate.year,noClient->client.balance);
    if(noClient->client.numberExpenses>0){
        for(int i = 0;i<noClient->client.numberExpenses;++i){
            clientExpenseInfo_aux(&noClient->client.expenses[i]);
        }
    }
    else{
        printf("EXPENSES:EMPTY\n");
    }

}

/***
 * method to show a full client list
 * @param list client list
 * @return Return 1 in case of success otherside return -1
 */
int show_list(client_list *list){
    if(list == NULL) return -1;
    if(list->length == 0){
        printf("EMPTY LIST\n");
        return -1;
    }
    no_client *no = list->begin;
    printf("LIST:\n");
    while(no!=NULL){
        printf("NAME:%s ID:%d\n",no->client.student.name,no->client.student.ID);

        no = no -> pseg;
    }
    printf("\n");
    return 1;
}

