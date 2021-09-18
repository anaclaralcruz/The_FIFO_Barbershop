// Autora: Ana Clara Loureiro Cruz
// Data: 14-09-2021

/*  TRABALHO 2 - SISTEMAS OPERACIONAIS  */
    // Resolver FIFO Barbeshop usando variaveis de estado

/* "main.c" ------------------------------------------------- */
/* Contem a funcao principal */

#include <pthread.h>
#include <stdio.h>

#include "barbearia.h"

// Variaveis globais
long unsigned int fila[QUANTIDADE_DE_CLIENTES];
int contadorInsercao=0;
int contadorBarbeiro=0;
int clientes=0;

// Inicializacao do mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t barbeiroLivre = PTHREAD_COND_INITIALIZER;
pthread_cond_t barbeiroPronto = PTHREAD_COND_INITIALIZER;
pthread_cond_t clienteLivre = PTHREAD_COND_INITIALIZER;
pthread_cond_t clientePronto = PTHREAD_COND_INITIALIZER;
pthread_cond_t usouOLock = PTHREAD_COND_INITIALIZER;


int cutHair(long unsigned int clienteId) {
    printf("Cortando o cabelo do cliente id = %ld...\n", clienteId);
    return OK;
}

void vazar() {
    printf("Todos os assentos ocupados, cliente id = %ld saindo da loja.\n", pthread_self());
}

void *cliente(void *arg) {
    pthread_mutex_lock(&mutex);
        printf("%d Cliente: Id %ld\n", clientes+1, pthread_self());
        if (clientes == QUANTIDADE_DE_CADEIRAS) {
            pthread_mutex_unlock(&mutex);
            vazar();
        }
        // Cliente vai pra sala de espera
        clientes += 1;
        // Cliente entra na fila
        fila[contadorInsercao] = pthread_self();
        contadorInsercao++;

    pthread_mutex_unlock(&mutex);

    // Acordar o barbeiro ou esperar ele estar livre
    pthread_cond_signal(&clientePronto);

    // Cortar o cabelo

    // Avisar que o cliente terminou
    
    printf("Esperando o barbeiro ficar livre\n");
    pthread_cond_wait(&barbeiroLivre,&mutex);

    pthread_mutex_lock(&mutex);
        clientes -= 1;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *barbeiro(void *arg) {
    pthread_cond_signal(&barbeiroLivre);
    for (int i; i<QUANTIDADE_DE_CLIENTES; i++) {
    //    printf("Esperando o cliente ficar pronto\n");
    //    pthread_cond_wait(&clientePronto,&mutex);

        pthread_mutex_lock(&mutex);
            long unsigned int clienteDaVez = fila[i];
            cutHair(clienteDaVez);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&barbeiroLivre);
    }
    
    return NULL;
}

int main() {
    pthread_t barb,client;

    for (int i=0; i<QUANTIDADE_DE_CLIENTES; i++) {
        pthread_create(&client, NULL, cliente, NULL); 
    }
    pthread_create(&barb, NULL, barbeiro, NULL);
    pthread_join(barb,NULL);
    pthread_join(client,NULL);
    return 0;
}