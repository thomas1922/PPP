#include <stdio.h>
#include "Funcoes.h"
#include "Ficheiros.h"


/***
 * method that reads a binary file if exists, make a expense list and show the menu of the program where
 * the user can do all the possible operations
 */
void menu() {
    data todayDate = {0,0,0};
    client_list list;
    expense_list exp;
    //initialize lists
    initClist(&list);
    initElist(&exp);

    //add clients received from a binary file
    int len = 0;
    client *d = readFile("clients.bin",&len,&todayDate);
    if(d == NULL) printf("NÃO EXISTEM DADOS\n");
    for(int i = 0;i<len;++i){
        addClient(&list,d[i]);
    }

    //make expense list
    makeExpenseList(&exp);

    //menu
    int continuar = -2;
    do {
        printf("----MENU----\n");
        printf("0-Sair\n");
        printf("1-Mostrar data\n");
        printf("2-Mudar data\n");
        printf("3-Inserir novo cliente\n");
        printf("4-Eliminar cliente\n");
        printf("5-Lista todos os clientes\n");
        printf("6-listar alunos com saldo abaixo de x\n");
        printf("7- Dados de um aluno\n");
        printf("8- Efetuar despesa\n");
        printf("9- Carregar conta\n");
        continuar = int_input(100);
        switch(continuar){
            case 0:{
                //Save information
                int len_aux;
                len_aux = list.length;
                saveInformation(len_aux,&list,todayDate);
                continuar = -1;
                break;
            }
            case 1:{
                //Date
                printf("DATE:%d/%d/%d\n",todayDate.day,todayDate.month,todayDate.year);
                break;
            }
            case 2:{
                //change date
                changeDate(&todayDate);
                break;
            }
            case 3:{
                //insert client into list
                insertClient(&list);
                break;
            }
            case 4:{
                //remove student from the list
                removeStudent(&list);
                break;
            }
            case 5:{
                //show student list
                show_list(&list);
                break;
            }
            case 6:{
                //show student list wich balance is over certain value
                descbalance_list(&list);
                break;
            }
            case 7:{
                //show informations of a client
                clientInfo(&list);
                break;
            }
            case 8:{
                //make a expense
                makeExpense(&list,&exp,todayDate);
                break;
            }
            case 9:{
                //load account
                loadAccount(&list);
                break;
            }
            default:{
                break;
            }
        }
    } while (continuar != -1);
}
int main() {
    menu();
    return 0;
}
