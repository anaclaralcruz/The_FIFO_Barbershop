// Autora: Ana Clara Loureiro Cruz
// Data: 14-09-2021

/*  TRABALHO 2 - SISTEMAS OPERACIONAIS  */
    // Resolver FIFO Barbeshop usando variaveis de estado

/* "barbearia.h" ------------------------------------------------- */
/* Contem as funcoes que representam acoes na barbearia */

#include "tarefas.h"


// TAREFA 1 cria um filho que realiza um sorteio e envia o resultado atraves de um pipe para o pai.
int tarefa_1 (int* comandoParaExecutar) {
    // Codigo relacionado a pipe baseado em https://drive.google.com/file/d/1MV2c6G6BnabduHefR0ZUB_nRpOiiMzbs/view
    int descritoresPipe[2];

    // Criando pipe
    if (pipe (descritoresPipe)) {
        printf ("Pipe da tarefa 1 falhou :(\n");
        return PIPE_FALHOU;
    }

    // Criando o filho:
    pid_t pid = fork ();
    if (pid < 0) {
        printf ("Fork falhou.\n");
        return FORK_FALHOU;
    }

    // Codigo do pai
    if (pid > 0) {
        // Proceso pai fecha ponta de escrita do pipe
        close (descritoresPipe[1]);
        // Aguarda o processo filho:
        wait(NULL);
        // Le o pipe e armazena no comandoParaExecutar
        read(descritoresPipe[0], comandoParaExecutar, sizeof(comandoParaExecutar));
        close(descritoresPipe[0]);

        return OK;
    }

    // Codigo do filho
    else {
        // Sorteio do numero
        srand(time(NULL));
        int numeroSorteado = rand() % 100 + 1; // sorteio de 1 a 100

        printf ("Numero sorteado: %d\n", numeroSorteado);

        // Escrevendo o resultado do sorteio no pipe
        write(descritoresPipe[1], &numeroSorteado, sizeof(&numeroSorteado));

        // Fechar o pipe
        close(descritoresPipe[1]);
        close(descritoresPipe[0]);

        exit(OK);
    }
}

// Cria um filho que faz um ping dependendo do numero que foi sorteado anteriormente.
int tarefa_2 (int* comandoParaExecutar) {
    // Criando o filho:
    pid_t pid = fork ();
    if (pid < 0) {
        printf ("Fork falhou.\n");
        return FORK_FALHOU;
    }

    // Codigo do pai
    if (pid > 0) {
        wait(NULL);
        return OK;
    }

    // Codigo do filho
    else {
        if (*comandoParaExecutar == 0) {
            printf ("\nNao ha comando a executar.\n");
            exit (OK);
        }
        if (*comandoParaExecutar % 2 == 0) {
            execlp("/bin/ping", "ping", "8.8.8.8", "-c", "5", NULL);
        }
        else {
            execlp("/bin/ping", "ping", "paris.testdebit.info", "-c", "5", "-i", "2", NULL);
        } 
        exit(OK);
    }
    return OK;
}