/*
   Main thread genera thread a, hanno in comune la var globale count, inizializzata a 0.
   Ad un certo punto il main gli da un valore , alchè il thread secondario, 
    in attesa che count sia diversa da 0, gli aggiunge 10 e poi finisce.
    Main thread aspetta il thread secondario
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int count=0;
pthread_mutex_t mutex; //mutex che regola l'accesso a count

void* f(){
    while(1){
        pthread_mutex_lock(&mutex);
        if(count != 0){
            printf("\nCount assegnato! Sommo 10");
            count = count+10;
            printf("\nAdesso count è %d ",count);
            printf("\nSto uscendo\n");
            pthread_exit(EXIT_SUCCESS);
        }else
            printf("\nCount non ancora assegnato. Aspetto");
        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
}

int main(){
    pthread_t threadA; //tid
    int res;
    
    pthread_mutex_init(&mutex,NULL);
    printf("\nMain : count inizializzato, mutex inizializzato: creo il thread\n");
    res=pthread_create(&threadA,NULL,f,NULL);
    if(res!=0){
        perror("Create failed");
    }else
        printf("\nCreato, sta eseguendo");
    
    sleep(1);
    pthread_mutex_lock(&mutex); //si mette in attesa, fino a quando non entra (threadA lo locka e unlocka continuamente quindi no problem
   
    printf("\nInserisci il valore di assegnazione a count != 0 : ");
    scanf("%d",&count);
    pthread_mutex_unlock(&mutex);
    //main ha finito, aspetta threadA
    pthread_join(threadA,NULL); //se in f  non c'è pthread_exit  ma solo exit da errore
    //ok ha finito, ora saluto
    
    printf("\nArrivederci");
    pthread_mutex_destroy(&mutex);
    exit(EXIT_SUCCESS);
    
}










