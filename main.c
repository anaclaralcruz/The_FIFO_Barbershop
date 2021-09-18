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
int clientes=0;

// Inicializacao do mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t barbeiroLivre = PTHREAD_COND_INITIALIZER;


int cutHair(long unsigned int clienteId) {
    printf("Cortando o cabelo do cliente id = %ld...\n", clienteId);
    return OK;
}

// Quando o cliente encontra a sala de espera cheia ele vai embora
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

    // Cortar o cabelo

    // Esperar o cabelereiro terminar
    pthread_cond_wait(&barbeiroLivre,&mutex);

    // Confirmar o corte
    pthread_mutex_lock(&mutex);
        clientes -= 1;
    pthread_mutex_unlock(&mutex);

    return NULL;
}

void *barbeiro(void *arg) {
    // Avisar que acordou
    pthread_cond_signal(&barbeiroLivre);

    // Cortar o cabelo na ordem em que os clientes chegam
    for (int i; i<QUANTIDADE_DE_CLIENTES; i++) {

        // Evitar chamar uma posicao que ainda nao chegou
        if (fila[i])
            cutHair(fila[i]);
        while (fila[i]==0) {
            if (fila[i])
                cutHair(fila[i]);
        }
        // Avisar que esta pronto para cortar outro cabelo
        pthread_cond_signal(&barbeiroLivre);
    }
    pthread_cond_signal(&barbeiroLivre);
    printf("\nNao ha mais clientes, Barbearia fechou.\n");
    return NULL;
}

int main() {
    pthread_t barb,client;

    for (int i=0; i<QUANTIDADE_DE_CLIENTES; i++) {
        pthread_create(&client, NULL, cliente, NULL); 
    }
    pthread_create(&barb, NULL, barbeiro, NULL);
    pthread_join(barb,NULL);
    return OK;
}