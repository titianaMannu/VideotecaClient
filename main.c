#include "main.h"

struct configuration conf;

/**
 * Semplice main che in base al tipo di utente selezionato richiama la funzione corrispondente.
 * @param argc
 * @param argv
 * @return
 */
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("not correct input, usage: <user>.\nChoose between cliente, manager and impiegato\n");
        exit(EXIT_FAILURE);
    }
    if (strncmp("cliente", argv[1], 6) == 0) {
        ClienteRoutine();
    } else if (strncmp("impiegato", argv[1], 9) == 0) {
        ImpiegatoRoutine();
    } else if (strncmp("manager", argv[1], 7) == 0) {
        ManagerRoutine();
    } else {
        printf("selected user doesn't exist.\n");
        exit(EXIT_FAILURE);
    }
    return 0;
}
