
#include "cliente.h"


char query[256];
char buff[256];

struct configuration conf;


void ClienteRoutine() {
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
    printf("\n************************************\n"
            "seleziona il numero dell'operazione da eseguire:\n"
           "1: Noleggia Film\n"
           "2: Chiudi Noleggio\n"
           "3: Leggi film in un centro\n"
           "4: Trova copie disponibili film in un centro\n"
           "5: Trova Remakes di un film\n"
           "6: Chiui l'applicazione\n");
    operation = GetInputNumber("operazione da effettuare");
    switch (operation) {
        case 1:
            NoleggiaFilm(con);
            goto selezione;
        case 2:
            ChiudiNoleggio(con);
            goto selezione;
        case 3:
            ListaFilmInCentro(con);
            goto selezione;
        case 4:
            TrovaCopieInCentro(con);
            goto selezione;
        case 5:
            TrovaRemakes(con);
            goto selezione;
        case 6:
            break;
        default:
            goto selezione;
    }

    // This is a general piece of code, to
    mysql_close(con);
}

void NoleggiaFilm(MYSQL *con) {
    char *ptr;
    int idCopia;
    int tessera;
    MYSQL_TIME *ts;
    MYSQL_BIND ps_params[3];
    MYSQL_STMT *stmt;
    int status;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }
    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "CALL `NoleggiaFilm`(?, ?, ?)"); //write query
    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    idCopia = GetInputNumber("id copia");

    tessera = GetInputNumber("tessera");

    ts = getInputDate(false);

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = (char *) &idCopia;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_LONG;
    ps_params[1].buffer = (char *) &tessera;
    ps_params[1].length = 0;
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_DATE;
    ps_params[2].buffer = (char *) ts;
    ps_params[2].length = 0;
    ps_params[2].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    mysql_stmt_close(stmt);

}

void ChiudiNoleggio(MYSQL *con) {
    MYSQL_BIND ps_params[1];
    MYSQL_STMT *stmt;
    int status, idNoleggio;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call ChiudiNoleggio(?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    idNoleggio = GetInputNumber("Id Noleggio");

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &idNoleggio;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void ListaFilmInCentro(MYSQL *con) {
    MYSQL_BIND ps_params[1];
    MYSQL_STMT *stmt;
    int status, centro;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call ListaFilmInCentro(?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    centro = GetInputNumber("centro");

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &centro;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void TrovaCopieInCentro(MYSQL *con) {
    char titolo[45];
    char regista[45];
    int idCentro;
    unsigned long length[8];
    MYSQL_BIND ps_params[8];
    MYSQL_STMT *stmt;
    int status;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call TrovaCopiaInCentro(?, ?, ?, ?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));
    idCentro = GetInputNumber("centro");

    printf("titolo film: ");
    memset(titolo, 0, 45);
    getInput(45, titolo, false);
    length[1] = strlen(titolo);

    printf("regista film: ");
    memset(regista, 0, 45);
    getInput(45, regista, false);
    length[2] = strlen(regista);

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &idCentro;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[1].buffer = (char *) titolo;
    ps_params[1].length = &length[1];
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[2].buffer = (char *) regista;
    ps_params[2].length = &length[2];
    ps_params[2].is_null = 0;


    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void TrovaRemakes(MYSQL *con) {
    char titolo[45];
    char regista[45];
    unsigned long length[2];
    MYSQL_BIND ps_params[2];
    MYSQL_STMT *stmt;
    int status;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call TrovaRemakes(?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));
    printf("titolo film: ");
    memset(titolo, 0, 45);
    getInput(45, titolo, false);
    length[0] = strlen(titolo);

    printf("regista film: ");
    memset(regista, 0, 45);
    getInput(45, regista, false);
    length[1] = strlen(regista);

    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer = (char *) titolo;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[1].buffer = (char *) regista;
    ps_params[1].length = &length[1];
    ps_params[1].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}
