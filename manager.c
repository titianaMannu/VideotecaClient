//
// Created by tiziana on 23/08/19.
//


#include "manager.h"


char query[256];
char buff[256];
struct configuration conf;


void managerRoutine() {
    int operation;
    MYSQL_STMT *stmt; // supporto per prepared statement
    MYSQL *con = mysql_init(NULL); //inizializza connessione
    load_file(&config, "../manager.json");
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
           "1: Fai repport annuale\n"
           "2: Fai repport mensile\n"
           "3: Inserisci impiegato\n"
           "4: Mostra dati di un impiegato\n"
           "5: Assegna Turno ad Impiegato\n"
           "6: Trova film più noleggiato\n"
           "7: Assegna impiego ad impiegato\n");
    operation = GetInputNumber("operazione da effettuare");
    switch (operation) {
        case 1:
            ReportAnnuale(con);
            break;
        case 2:
            ReportMensile(con);
            break;
        case 3:
            InserisciImpiegato(con);
            break;
        case 4:
            CheckDatiImpiegato(con);
            break;
        case 5:
            AssegnaTurno(con);
            break;
        case 6:
            FilmPiuNoleggiato(con);
            break;
        case 7:
            AssegnaImpiego(con);
            break;
        default:
            goto selezione;
    }

    // This is a general piece of code, to
    mysql_close(con);
}


void ReportAnnuale(MYSQL *con) {
    char *impiegato = malloc(16);
    unsigned long length[6];
    MYSQL_TIME *ts;
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
    strcpy(query, "call ReportAnnuale(?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));
    memset(buff, 0, 256); // clear buffer
    printf("codice fiscale impiegato: ");
    memset(impiegato, 0, 22);
    getInput(16, impiegato, false);
    length[0] = strlen(impiegato);

    ts = getInputDate(true);

    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer_length = 16;
    ps_params[0].buffer = impiegato;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_SHORT;
    ps_params[1].buffer = (char *) &ts->year;
    ps_params[1].length = 0;
    ps_params[1].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    free(impiegato);
    mysql_stmt_close(stmt);

}

void ReportMensile(MYSQL *con) {
    char *month = malloc(5);
    char *impiegato = malloc(22);
    unsigned long length[6];
    MYSQL_TIME *ts;
    MYSQL_BIND ps_params[5];
    MYSQL_STMT *stmt;
    int status;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call ReportMensile(?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));
    memset(buff, 0, 256); // clear buffer
    printf("codice fiscale impiegato: ");
    memset(impiegato, 0, 22);
    getInput(16, impiegato, false);
    length[0] = strlen(impiegato);
    printf("inserire un mese come <mm>: ");
    memset(month, 0, 5);
    getInput(2, month, false);
    length[1] = strlen(month);

    ts = getInputDate(true);

    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer_length = 16;
    ps_params[0].buffer = impiegato;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[1].buffer = (char *) month;
    ps_params[1].length = &length[1];
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_SHORT;
    ps_params[2].buffer = (char *) &ts->year;
    ps_params[2].length = 0;
    ps_params[2].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    free(impiegato);
    free(month);
    mysql_stmt_close(stmt);
}

void InserisciImpiegato(MYSQL *con) {
    char *impiegato = malloc(22);
    char recapito[45];
    char nome[20];
    char titoloStudio[45];
    unsigned long length[4];
    MYSQL_BIND ps_params[4];
    MYSQL_STMT *stmt;
    int status;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call Videoteca.InserisciImpiegato(?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));

    printf("codice fiscale impiegato: ");
    memset(impiegato, 0, 22);
    getInput(16, impiegato, false);
    length[0] = strlen(impiegato);

    printf("nome: ");
    memset(nome, 0, 5);
    getInput(20, nome, false);
    length[1] = strlen(nome);

    printf("recapito: ");
    memset(recapito, 0, 5);
    getInput(45, recapito, false);
    length[2] = strlen(recapito);

    printf("titolo studio: ");
    memset(titoloStudio, 0, 5);
    getInput(45, titoloStudio, false);
    length[3] = strlen(titoloStudio);


    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer_length = 16;
    ps_params[0].buffer = impiegato;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[1].buffer = (char *) nome;
    ps_params[1].length = &length[1];
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[2].buffer = (char *) recapito;
    ps_params[2].length = &length[2];
    ps_params[2].is_null = 0;

    ps_params[3].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[3].buffer = (char *) titoloStudio;
    ps_params[3].length = &length[3];
    ps_params[3].is_null = 0;
    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    free(impiegato);
    mysql_stmt_close(stmt);
}

void CheckDatiImpiegato(MYSQL *con) {
    char *impiegato = malloc(20);
    unsigned long length[1];
    MYSQL_BIND ps_params[6];
    MYSQL_STMT *stmt;
    int status;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call checkDatiImpiegato(?, ?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));
    memset(buff, 0, 256); // clear buffer
    printf("codice fiscale impiegato: ");
    memset(impiegato, 0, 22);
    getInput(16, impiegato, false);
    length[0] = strlen(impiegato);

    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer_length = 16;
    ps_params[0].buffer = impiegato;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    free(impiegato);
    mysql_stmt_close(stmt);
}

void AssegnaTurno(MYSQL *con) {
    char *month = malloc(5);
    char *impiegato = malloc(16);
    unsigned long length[6];
    MYSQL_TIME *ts;
    MYSQL_BIND ps_params[6];
    MYSQL_STMT *stmt;
    int status, ore;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call AssegnaTurno(?, ?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));
    printf("codice fiscale impiegato: ");
    memset(impiegato, 0, 22);
    getInput(16, impiegato, false);
    length[0] = strlen(impiegato);

    ts = getInputDate(false);

    printf("inserire mese del turno come <mm>: ");
    memset(month, 0, 5);
    getInput(2, month, false);
    length[1] = strlen(month);

    MYSQL_TIME *ts1 = getInputDate(true);
    MYSQL_TIME *ts2 = getInputTime();

    ore = GetInputNumber("numero di ore del turno");

    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer_length = 16;
    ps_params[0].buffer = impiegato;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_DATE;
    ps_params[1].buffer = (char *) ts;
    ps_params[1].length = 0;
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[2].buffer = (char *) month;
    ps_params[2].length = &length[1];
    ps_params[2].is_null = 0;

    ps_params[3].buffer_type = MYSQL_TYPE_SHORT;
    ps_params[3].buffer = (char *) &ts1->year;
    ps_params[3].length = 0;
    ps_params[3].is_null = 0;

    ps_params[4].buffer_type = MYSQL_TYPE_TIME;
    ps_params[4].buffer = (char *) ts2;
    ps_params[4].length = 0;
    ps_params[4].is_null = 0;

    ps_params[5].buffer_type = MYSQL_TYPE_LONG;
    ps_params[5].buffer = (char *) &ore;
    ps_params[5].length = 0;
    ps_params[5].is_null = 0;
    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    free(impiegato);
    mysql_stmt_close(stmt);
}

void FilmPiuNoleggiato(MYSQL *con) {
    MYSQL_BIND ps_params[1];
    MYSQL_STMT *stmt;
    int status, idCentro;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call TrovaFilmPiuNoleggiato(?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    idCentro = GetInputNumber("centro");

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &idCentro;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void AssegnaImpiego(MYSQL *con) {
    char *impiegato = malloc(22);
    char qualifica[45];
    int idCentro;
    unsigned long length[3];
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
    strcpy(query, "call AssegnaImpiego(?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));

    printf("codice fiscale impiegato: ");
    memset(impiegato, 0, 22);
    getInput(16, impiegato, false);
    length[0] = strlen(impiegato);

    printf("qualifica: ");
    memset(qualifica, 0, 45);
    getInput(45, qualifica, false);
    length[1] = strlen(qualifica);

    idCentro = GetInputNumber("centro");

    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer_length = 16;
    ps_params[0].buffer = impiegato;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[1].buffer = (char *) qualifica;
    ps_params[1].length = &length[1];
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_LONG;
    ps_params[2].buffer = &idCentro;
    ps_params[2].length = 0;
    ps_params[2].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    free(impiegato);
    mysql_stmt_close(stmt);
}