#include "impiegato.h"

char query[256];
char buff[256];

struct configuration conf;


void ImpiegatoRoutine() {
    int operation;
    MYSQL_STMT *stmt; // supporto per prepared statement
    MYSQL *con = mysql_init(NULL); //inizializza connessione
    load_file(&config, "../impiegato.json");
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
    do {
        printf("\n************************************\n"
               "seleziona il numero dell'operazione da eseguire:\n"
               "1: Inserisci nuovo cliente\n"
               "2: Leggi dati cliente\n"
               "3: Trova clienti irregolari in un centro\n"
               "4: Assegna collocazione\n"
               "5: Inserisci Film\n"
               "6: Leggi dati noleggio\n"
               "7: Aggiungi Copie in settore\n"
               "8: Modifica posizione di un film\n"
               "9: Chiudi applicazione\n");
        operation = GetInputNumber("operazione da effettuare");
        switch (operation) {
            case 1:
                InserisciCliente(con);
                break;
            case 2:
                LeggiDatiCliente(con);
                break;
            case 3:
                TrovaClientiIrregolari(con);
                break;
            case 4:
                AssegnaCollocazione(con);
                break;
            case 5:
                InserisciFilm(con);
                break;
            case 6:
                LeggiDatiNoleggio(con);
                break;
            case 7:
                AggiungiCopie(con);
                break;
            case 8:
                ModificaPosizione(con);
                break;
            default:
                break;
        }
    } while (operation != 9);

    mysql_close(con);
}

void InserisciCliente(MYSQL *con) {
    char *codFiscale = malloc(22);
    char cognome[45];
    char nome[45];
    char residenza[45];
    MYSQL_TIME *ts;
    char contatto[100];
    unsigned long length[7];
    MYSQL_BIND ps_params[7];
    MYSQL_STMT *stmt;
    int status;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call `InserisciCliente&Contatto`(?, ?, ?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    memset(length, 0, sizeof(length));

    printf("codice fiscale codFiscale: ");
    memset(codFiscale, 0, 22);
    getInput(16, codFiscale, false);
    length[0] = strlen(codFiscale);

    printf("nome: ");
    memset(nome, 0, 45);
    getInput(45, nome, false);
    length[1] = strlen(nome);

    printf("cognome: ");
    memset(cognome, 0, 45);
    getInput(45, cognome, false);
    length[2] = strlen(cognome);

    ts = getInputDate(false);

    printf("residenza: ");
    memset(residenza, 0, 45);
    getInput(45, residenza, false);
    length[4] = strlen(residenza);

    printf("contatto: ");
    memset(contatto, 0, 100);
    getInput(100, contatto, false);
    length[5] = strlen(contatto);


    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer_length = 16;
    ps_params[0].buffer = codFiscale;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[1].buffer = (char *) nome;
    ps_params[1].length = &length[1];
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[2].buffer = (char *) cognome;
    ps_params[2].length = &length[2];
    ps_params[2].is_null = 0;

    ps_params[3].buffer_type = MYSQL_TYPE_DATE;
    ps_params[3].buffer = (char *) ts;
    ps_params[3].length = 0;
    ps_params[3].is_null = 0;

    ps_params[4].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[4].buffer = (char *) residenza;
    ps_params[4].length = &length[4];
    ps_params[4].is_null = 0;

    ps_params[5].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[5].buffer = (char *) contatto;
    ps_params[5].length = &length[5];
    ps_params[5].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);

    free(codFiscale);
    mysql_stmt_close(stmt);
}

void LeggiDatiCliente(MYSQL *con) {
    MYSQL_BIND ps_params[1];
    MYSQL_STMT *stmt;
    int status, tessera;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call LeggiDatiCliente(?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    tessera = GetInputNumber("numero tessera");

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &tessera;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void TrovaClientiIrregolari(MYSQL *con) {
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
    strcpy(query, "call ClientiNoleggiScaduti(?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    centro = GetInputNumber("numero centro");

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

void AssegnaCollocazione(MYSQL *con) {
    int status, centro, settore;
    char titolo[45], regista[45], *tipologia[] = {"VHS", "DVD"};
    int occ, pos, val;

    unsigned long length[7];
    MYSQL_BIND ps_params[7];
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call AssegnaCollocazione(?, ?, ?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    centro = GetInputNumber("centro");
    settore = GetInputNumber("settore");

    printf("titolo film: ");
    memset(titolo, 0, 45);
    getInput(45, titolo, false);
    length[2] = strlen(titolo);

    printf("regista film: ");
    memset(regista, 0, 45);
    getInput(45, regista, false);
    length[3] = strlen(regista);

    printf("seleziona la tipologia:\n"
           "-0 VHS\n"
           "-1 DVD\n");
    val = GetInputNumber("tipologia");
    occ = GetInputNumber("numero occorrenze");
    pos = GetInputNumber("posizione");

    length[6] = 3;

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &centro;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_LONG;
    ps_params[1].buffer = &settore;
    ps_params[1].length = 0;
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[2].buffer = (char *) titolo;
    ps_params[2].length = &length[2];
    ps_params[2].is_null = 0;

    ps_params[3].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[3].buffer = (char *) regista;
    ps_params[3].length = &length[3];
    ps_params[3].is_null = 0;

    ps_params[4].buffer_type = MYSQL_TYPE_LONG;
    ps_params[4].buffer = &occ;
    ps_params[4].length = 0;
    ps_params[4].is_null = 0;

    ps_params[5].buffer_type = MYSQL_TYPE_LONG;
    ps_params[5].buffer = &pos;
    ps_params[5].length = 0;
    ps_params[5].is_null = 0;

    ps_params[6].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[6].buffer = (char *) tipologia[val];
    ps_params[6].length = &length[6];
    ps_params[6].is_null = 0;


    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void InserisciFilm(MYSQL *con) {
    int status, costo;
    char titolo[45], regista[45], titoloOriginale[45], registaOriginale[45], *tipologia[] = {"classico", "nuovo"};
    int val;

    MYSQL_TIME *ts;
    unsigned long length[7];
    MYSQL_BIND ps_params[7];
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call InserisciFilm(?, ?, ?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    printf("titolo film: ");
    memset(titolo, 0, 45);
    getInput(45, titolo, false);
    length[0] = strlen(titolo);

    printf("regista film: ");
    memset(regista, 0, 45);
    getInput(45, regista, false);
    length[1] = strlen(regista);

    costo = GetInputNumber("costo");
    ts = getInputDate(true);

    printf("seleziona la tipologia:\n"
           "-0 classico\n"
           "-1 nuovo\n");
    val = GetInputNumber("tipologia");
    length[4] = strlen(tipologia[val]);

    printf("titolo originale: ");
    memset(titoloOriginale, 0, 45);
    getInput(45, titoloOriginale, false);
    length[5] = strlen(titoloOriginale);

    printf("regista originale: ");
    memset(registaOriginale, 0, 45);
    getInput(45, registaOriginale, false);
    length[6] = strlen(registaOriginale);


    ps_params[0].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[0].buffer = (char *) titolo;
    ps_params[0].length = &length[0];
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[1].buffer = (char *) regista;
    ps_params[1].length = &length[1];
    ps_params[1].is_null = 0;

    ps_params[3].buffer_type = MYSQL_TYPE_SHORT;
    ps_params[3].buffer = (char *) &ts->year;
    ps_params[3].length = 0;
    ps_params[3].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_LONG;
    ps_params[2].buffer = &costo;
    ps_params[2].length = 0;
    ps_params[2].is_null = 0;

    ps_params[4].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[4].buffer = (char *) tipologia[val];
    ps_params[4].length = &length[4];
    ps_params[4].is_null = 0;

    ps_params[5].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[5].buffer = (char *) titoloOriginale;
    ps_params[5].length = &length[5];
    ps_params[5].is_null = 0;

    ps_params[6].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[6].buffer = (char *) registaOriginale;
    ps_params[6].length = &length[6];
    ps_params[6].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void LeggiDatiNoleggio(MYSQL *con) {
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
    strcpy(query, "call LeggiDatiNoleggio(?)"); //write query

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

void AggiungiCopie(MYSQL *con) {
    int status, centro, settore;
    char titolo[45], regista[45], *tipologia[] = {"VHS", "DVD"};
    int occ, val;

    unsigned long length[6];
    MYSQL_BIND ps_params[6];
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call AggiungiCopie(?, ?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    centro = GetInputNumber("centro");
    settore = GetInputNumber("settore");

    printf("titolo film: ");
    memset(titolo, 0, 45);
    getInput(45, titolo, false);
    length[2] = strlen(titolo);

    printf("regista film: ");
    memset(regista, 0, 45);
    getInput(45, regista, false);
    length[3] = strlen(regista);

    printf("seleziona la tipologia:\n"
           "-0 VHS\n"
           "-1 DVD\n");
    val = GetInputNumber("tipologia");
    occ = GetInputNumber("numero occorrenze");

    length[5] = 3;
    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &centro;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_LONG;
    ps_params[1].buffer = &settore;
    ps_params[1].length = 0;
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[2].buffer = (char *) titolo;
    ps_params[2].length = &length[2];
    ps_params[2].is_null = 0;

    ps_params[3].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[3].buffer = (char *) regista;
    ps_params[3].length = &length[3];
    ps_params[3].is_null = 0;

    ps_params[4].buffer_type = MYSQL_TYPE_LONG;
    ps_params[4].buffer = &occ;
    ps_params[4].length = 0;
    ps_params[4].is_null = 0;

    ps_params[5].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[5].buffer = (char *) tipologia[val];
    ps_params[5].length = &length[5];
    ps_params[5].is_null = 0;


    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}

void ModificaPosizione(MYSQL *con) {
    int status, centro, settore;
    char titolo[45], regista[45];
    int pos, val;

    unsigned long length[5];
    MYSQL_BIND ps_params[5];
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(con); //inizializzazione dello statement
    if (!stmt) {
        printf("Could not initialize statement\n");
        exit(1);
    }

    memset(ps_params, 0, sizeof(ps_params));
    memset(query, 0, 256); // clear buffer
    strcpy(query, "call ModificaPosizione(?, ?, ?, ?, ?)"); //write query

    status = mysql_stmt_prepare(stmt, query, strlen(query));
    test_stmt_error(stmt, status);

    centro = GetInputNumber("centro");
    settore = GetInputNumber("settore");

    printf("titolo film: ");
    memset(titolo, 0, 45);
    getInput(45, titolo, false);
    length[2] = strlen(titolo);

    printf("regista film: ");
    memset(regista, 0, 45);
    getInput(45, regista, false);
    length[3] = strlen(regista);

    pos = GetInputNumber("nuova posizione");

    ps_params[0].buffer_type = MYSQL_TYPE_LONG;
    ps_params[0].buffer = &centro;
    ps_params[0].length = 0;
    ps_params[0].is_null = 0;

    ps_params[1].buffer_type = MYSQL_TYPE_LONG;
    ps_params[1].buffer = &settore;
    ps_params[1].length = 0;
    ps_params[1].is_null = 0;

    ps_params[2].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[2].buffer = (char *) titolo;
    ps_params[2].length = &length[2];
    ps_params[2].is_null = 0;

    ps_params[3].buffer_type = MYSQL_TYPE_VAR_STRING;
    ps_params[3].buffer = (char *) regista;
    ps_params[3].length = &length[3];
    ps_params[3].is_null = 0;

    ps_params[4].buffer_type = MYSQL_TYPE_LONG;
    ps_params[4].buffer = &pos;
    ps_params[4].length = 0;
    ps_params[4].is_null = 0;

    status = mysql_stmt_bind_param(stmt, ps_params);
    test_stmt_error(stmt, status);

    status = mysql_stmt_execute(stmt);
    test_stmt_error(stmt, status);

    printer(stmt, con);
    mysql_stmt_close(stmt);
}