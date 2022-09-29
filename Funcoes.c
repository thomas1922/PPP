#include "Funcoes.h"
#include "Estruturas.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BUFFER 150

/***
 * method to remove the left spaces of a string
 * @param s string
 * @return string without left spaces
 */
char *leftSpaces(char s[])
{
    while(isspace(*s)) s++;
    return s;
}

/***
 * method to remove the right spaces of a string
 * @param s string
 * @return string without right spaces
 */
char *righSpaces(char s[])
{
    char* back;
    int len = (int)strlen(s);
    back = s + len;
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

/***
 * method that uses two auxliar methods to remove spaces before and after names in string
 * @param s
 * @return string without left and right spaces
 */

char *removespaces(char s[])
{
    return righSpaces(leftSpaces(s));
}

/**
 * method that verify if string have only spaces
 * @param s string
 * @return 1 in case of success otherside return -1
 */
int verify_space(char s[]){
    int i = 0;
    while(s[i]!='\0') {
        if (!isspace(s[i])) {
            return -1;
        }
        i++;
    }
    return 1;
}

/***
 * mehtod that verify if string have only numbers or spaces
 * @param s string
 * @return 1 in case of success otherside return -1
 */
int verify_num(char s[]){

    int i = 0;
    while(s[i]!='\0'){
        if (isdigit(s[i])|| isspace(s[i])){
            i++;
        }
        else{
            return -1;
        }
    }
    return 1;
}

/***
 * mehtod that verify if string have only a float number
 * @param s string
 * @return 1 in case of success otherside return -1
 */
int verify_double(char s[]){
    int i = 0;
    int conta = 0;
    while(s[i]!='\0'){
        if (isdigit(s[i])|| isspace(s[i])) {
            i++;
        }
        else if(s[i] == '.' && conta == 0){
            i++;
            conta+=1;
        }
        else{
            return -1;
        }
    }
    return 1;
}

/***
 * method that verify if string have only characters and spaces
 * @param s string
 * @return 1 in case of success otherside return -1
 */
int verify_char(const char s[]){
    int i = 0;
    while(s[i]!='\0'){
        if (s[i] >= 'a' && s[i]<='z' || s[i] >= 'A' && s[i]<='Z' || isspace(s[i])){
            i++;
        }
        else{
            return -1;
        }
    }
    return 1;
}

/***
 * method to receive a int
 * @param max length of string
 * @return int value
 */
int int_input(int max){
    char line[max];int len;int c;int num = 0;unsigned long numaux;
    char *trash;
    while(1){

        fgets(line,100,stdin);
        len = (int)strlen(line);
        if(line[len-1]!='\n') {
            printf("LINE TOO LONG\n");
            while ((c = fgetc(stdin)) != EOF && c != '\n');
        }
        if(verify_num(line) == 1){
            numaux = strtol(line,&trash,0);
            if(strlen(trash) == 1 || verify_space(trash) == 1){
                num = (int)numaux;
                return num;
            }

        }
        else{
            printf("ENTER A NUMBER\n");
        }
    }
}

/***
 * method to receive a double
 * @param max length of string
 * @return double value
 */
double double_input(int max){
    char line[max];int len;int c;double num = 0.0;
    char *trash;
    while(1){
        fgets(line,100,stdin);
        len = (int)strlen(line);
        if(line[len-1]!='\n') {
            printf("LINE TOO LONG\n");
            while ((c = fgetc(stdin)) != EOF && c != '\n');
        }
        if(verify_double(line) == 1){
            num = strtod(line,&trash);
            if(strlen(trash) == 1 || verify_space(trash) == 1){
                return num;
            }
            else{
                printf("ENTER ONLY A NUMBER\n");
            }
        }
        else{
            printf("ENTER A NUMBER\n");
        }
    }
}

/***
 * method that make and show a order by descend balance client list wich balance is over certain value
 * @param list client list
 */
void descbalance_list(client_list *list){
    double value = 0.0;
    if(list == NULL) return;
    printf("ENTER A VALUE:");
    value = double_input(MAX_BUFFER);
    if(list->length == 0) return;
    client_list *aux = malloc(sizeof(client_list));
    if (aux == NULL) return;
    initClist(aux);
    no_client *no = list->begin;
    while(no!=NULL){
        if(no->client.balance < value){
            addClientBalance(aux,no->client);
        }
        no = no -> pseg;
    }
    if(aux->length == 0){
        free(aux);
    }
    else{
        show_balance(aux);
        free(aux);
    }

}

/***
 *  methot that try to find a client and load the account with the value inserted
 * @param list client list
 */
void loadAccount( client_list *list){
    char name[MAX_BUFFER];char name_aux[MAX_BUFFER];double value;
    if(list == NULL)return;
    if(list->length == 0){
        printf("EMPTY LIST\n");
        return;
    }
    printf("ENTER CLIENT NAME:");
    fgets(name_aux,MAX_BUFFER,stdin);
    if(verify_char(name_aux)==1){
        strupr(name_aux);
        strcpy(name, removespaces(name_aux));
        printf("ENTER A VALUE:");
        value  = double_input(MAX_BUFFER);
        if(value<0){
            printf("VALUE MUST BE OVER 0\n");
            while(value<0){
                printf("VALUE MUST BE OVER 0\n");
                value = double_input(MAX_BUFFER);
            }
        }

        no_client *temp = list->begin;

        if(temp!=NULL && strcmp(temp->client.student.name,name) == 0){
            temp->client.balance+=value;
            return;
        }

        while(temp!=NULL && strcmp(temp->client.student.name,name)!=0){
            temp=temp->pseg;
        }
        if(temp == NULL) return;
        temp->client.balance+=value;

        return;
    }
    else{
        printf("INVALID INPUT OF NAME\n");
        return;
    }

}

/***
 * method that insert client into a client list.
 * @param list client list
 */
//method to put a student in a list.
void insertClient(client_list *list){
    char name[MAX_BUFFER];char name_aux[MAX_BUFFER];
    int day,month,birhtyear,ID,class,year;
    if(list == NULL) return;
    client *new = malloc(sizeof(client));
    if(new == NULL) return;

    printf("ENTER A NAME:");
    fgets(name_aux,MAX_BUFFER,stdin);
    if(verify_char(name_aux)==1){
        strupr(name_aux);
        strcpy(name, removespaces(name_aux));
        strcpy(new->student.name,name);
    }
    else{
        printf("INVALID INPUT OF NAME\n");
        return;
    }
    data *birthdate = malloc(sizeof(data));
    printf("ENTER DAY OF BIRTH:");
    day = int_input(MAX_BUFFER);
    printf("ENTER MONTH OF BIRTH:");
    month = int_input(MAX_BUFFER);
    printf("ENTER YEAR OF BIRTH:");
    birhtyear = int_input(MAX_BUFFER);
    if(setDate(birthdate,day,month,birhtyear)==1){
        new->student.birthDate = *birthdate;
    }
    else{
        printf("INVALID DATA TYPE\n");
        return;
    }
    printf("ENTER THE ID:");
    ID = int_input(MAX_BUFFER);
    if(ID > 0){
        new->student.ID = ID;
    }
    else{
        printf("ID MUST BE OVER 0\n");
        return;
    }
    printf("ENTER THE YEAR:");
    year = int_input(MAX_BUFFER);
    if(year > 0){
        new->student.year = year;
    }
    else{
        printf("ID MUST BE OVER 0\n");
        return;
    }
    printf("ENTER THE CLASS:");
    class = int_input(MAX_BUFFER);
    if(class > 0){
        new->student.class = class;
    }
    new->balance = 0;
    new->numberExpenses = 0;
    addClient(list,*new);
}

/***
 * method that remove a client from client list
 * @param list client list
 */
void removeStudent(client_list *list) {
    char name[MAX_BUFFER];char name_aux[MAX_BUFFER];
    if (list == NULL) return;
    printf("ENTER CLIENT NAME:");
    fgets(name_aux, MAX_BUFFER, stdin);
    if (verify_char(name_aux) == 1) {
        strupr(name_aux);
        strcpy(name, removespaces(name_aux));
        if(removeClient(list,name)== 1){
            printf("CLIENT REMOVED WITH SUCESS\n");
        }
        else{
            printf("CLIENT DOESNT EXIST\n");
            }
        }
    }

/***
 * methot that try to find a client and if have success show the client information
 * @param list client list
 */
void clientInfo(client_list *list) {
    char name[MAX_BUFFER];
    char name_aux[MAX_BUFFER];
    if (list == NULL) return;
    if (list->length == 0) {
        printf("LIST DONT HAVE CLIENTS");
        return;
    }
    printf("ENTER CLIENT NAME:");
    fgets(name_aux, MAX_BUFFER, stdin);
    if (verify_char(name_aux) == 1) {
        strupr(name_aux);
        strcpy(name, removespaces(name_aux));
        no_client *temp = list->begin;

        if (temp != NULL && strcmp(temp->client.student.name, name) != 0) {
            while (temp != NULL && strcmp(temp->client.student.name, name) != 0) {
                temp = temp->pseg;
            }
            if (temp == NULL) {
                printf("CLIENT DONT EXITS\n");
                return;
            }
        }
        infoClient(temp);
    }
}

/***
 * method to make a expense that receive a list where try to find client, and a expense list with expense.
 * if client dont exists or ID of product dont exists the operation is aborted.
 * @param list client list
 * @param explist expense list
 * @param todayDate date
 */
void makeExpense(client_list *list,expense_list *explist,data todayDate){
    int ID;char name[MAX_BUFFER];
    char name_aux[MAX_BUFFER];
    if(list == NULL){
        return;
    }
    if(list->length == 0){
        printf("EMPTY LIST\n");
        return;
    }

    no_client *temp = list->begin;
    printf("ENTER A NAME:");
    fgets(name_aux,MAX_BUFFER,stdin);
    if(verify_char(name_aux)==-1) {
        printf("INVALID NAME\n");
        return;
    }
    strupr(name_aux);
    strcpy(name, removespaces(name_aux));

    //search if client exists
    if(temp!=NULL && strcmp(temp->client.student.name,name) != 0){
        while(temp!=NULL && strcmp(temp->client.student.name,name)!=0){
            temp=temp->pseg;
        }
        if(temp == NULL) {
            printf("CLIENT DONT EXITS\n");
            return;
        }
    }
    printf("STUDENT:%s\n",temp->client.student.name);
    while(1){
        if(showExpenselist(explist)!=-1){
            printf("ENTER A EXPENSE ID:");
            ID = int_input(MAX_BUFFER);
            no_expense *aux = explist->begin;
            //search if expense exists
            if(aux->expense.ID != ID){
                while(aux!=NULL && aux->expense.ID!=ID){
                    aux=aux->pseg;
                }
                if(aux == NULL) {
                    printf("ID DONT EXITS\n");
                    break;
                }
            }
            if(temp->client.balance >= aux->expense.value){
                temp->client.balance -= aux->expense.value;
                expense new = aux->expense;
                new.buydate = todayDate;
                temp->client.expenses[temp->client.numberExpenses] = new;
                temp->client.numberExpenses+=1;
                printf("THANK YOU\n");
                break;
            }
            else{
                printf("DONT HAVE ENOUGH MONEY\n");
            }
        }else{
            printf("DONT HAVE PRODUCTS TO BUY\n");
            break;
        }
    }

}

/***
 * method to make a list of expenses
 * @param list expense list
 */
void makeExpenseList(expense_list *list){
    if(list == NULL) return;
    char string[8][20] = {"AGUA","REFRIGERANTE","LEITE","SANDES","TORRADA","CROISSANT","CAFE"};
    double values[] = {0.80,1.4,1.2,1.8,1.5,2.0,0.35};
    int j = 0;
    for(int i = 0;i<7;++i){
        expense new;
        new.value = values[i];
        strcpy(new.description,string[i]);
        new.ID = j;
        ++j;
        addExpense(list,new);
    }
}

/***
 * method to save information of clients if exists
 * @param len_aux length of list
 * @param list client list
 * @param todayDate date
 */
void saveInformation(int len_aux,client_list *list,data todayDate){
    int i = 0;
    if(len_aux > 0){
        client *c = malloc(sizeof(client)*len_aux);
        no_client *nc = list->begin;
        while(nc!=NULL){
            client new;
            strcpy(new.student.name,nc->client.student.name);
            new.student.birthDate = nc->client.student.birthDate;
            new.student.year =nc->client.student.year;
            new.student.class = nc->client.student.class;
            new.student.ID = nc->client.student.ID;
            new.balance = nc->client.balance;
            if(nc->client.numberExpenses > 0){
                int number = 0;
                new.numberExpenses = nc->client.numberExpenses;
                for(int j = 0;j<nc->client.numberExpenses;j++){
                    expense newexp;
                    strcpy(newexp.description,nc->client.expenses[j].description);
                    newexp.value = nc->client.expenses[j].value;
                    newexp.ID = nc->client.expenses[j].ID;
                    newexp.buydate = nc->client.expenses[j].buydate;
                    new.expenses[number++] = newexp;
                }
            }
            c[i++] = new;
            nc = nc->pseg;
        }
        writeFile("clients.bin",c,len_aux,todayDate);
    }
    else{
        printf("NO INFORMATION TO SAVE\n");
    }
}

/***
 * methot to change date, if date is valid and date is later than the current one
 * @param actual date
 */
void changeDate(data *actual){
    data d;
    int day,month,year;
    printf("DAY: ");
    day = int_input(100);
    printf("MONTH: ");
    month = int_input(100);
    printf("YEAR: ");
    year = int_input(100);
    if(setDate(&d,day,month,year)==1){
        if(compareDates(d,*actual)==0){
            *actual = d;
            printf("DATE CHANGED WITH SUCCESS\n");
        }
        else{
            printf("DATE CANNOT BE BEFORE THE CURRENT DATE\n");
        }

    }
    else{
        printf("INVALID INPUT OF DATE\n");
    }

}
