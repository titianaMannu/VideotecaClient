//
// Created by tiziana on 24/08/19.
//


#include "impiegato.h"
char query[256];
char buff[256];

struct configuration conf;


void ImpiegatoRoutine() {
    int operation;
    MYSQL_STMT *stmt; // supporto per prepared statement
    MYSQL *con = mysql_init(NULL); //inizializza connessione
    load_file(&config, "../cliente.json");
    parse_config();
    dump_config();
    if (con == NULL) {
        fprintf(stderr, "Initilization error: %s\n", mysql_error(con));
        exit(1);
    }
    if (mysql_real_connect(con, conf.host, conf.username, conf.password, conf.database, conf.port, NULL, 0) == NULL) {
        finish_with_error(con, "Connection");
    }

    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    selezione:
    printf("seleziona il numero dell'operazione da eseguire:\n"
           "1: Noleggia Film\n"
           "2: Chiudi Noleggio\n"
           "3: Leggi film in un centro\n"
           "4: Trova copie disponibili film in un centro\n"
           "5: Trova Remakes di un film\n");
    operation = GetInputNumber("operazione da effettuare");
    switch (operation) {
        case 1:
            break;

        default:
            goto selezione;
    }

    // This is a general piece of code, to
    mysql_close(con);
}
