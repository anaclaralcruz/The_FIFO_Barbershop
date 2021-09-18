// Autora: Ana Clara Loureiro Cruz
// Data: 14-09-2021

/*  TRABALHO 2 - SISTEMAS OPERACIONAIS  */
    // Resolver FIFO Barbeshop usando variaveis de estado

/* "barbearia.h" ------------------------------------------------- */
/* Inicializa as funcoes que representam acoes na barbearia */

#ifndef BARBEARIA_H
#define BARBEARIA_H

#define QUANTIDADE_DE_CLIENTES  6
#define QUANTIDADE_DE_CADEIRAS  4

#define OK  0

int cutHair(long unsigned int);
void vazar();

void *barbeiro(void *);
void *cliente(void *);

#endif