//
// Created by tiziana on 23/08/19.
//


#include "utils.h"

#define MAX_LEN 256
char buff[256];

void finish_with_error(MYSQL *con, char *err) {
    fprintf(stderr, "%s error: %s\n", err, mysql_error(con));
    mysql_close(con);
    exit(1);
}

MYSQL_TIME *getInputDate(bool onlyYear) {
    char *ptr = NULL;
    char *token;
    MYSQL_TIME *ts = malloc(sizeof(MYSQL_TIME));
    if (ts == NULL) {
        printf("unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    //ritenta:
    while(1) {
        if (!onlyYear) printf("inserire data come yyyy-mm-dd: ");
        else printf("inserire anno: ");
        ptr = NULL;

        memset(ts, 0, sizeof(MYSQL_TIME));

        memset(buff, 0, 256); // clear buffer
        getInput(20, buff, false);
        token = strtok(buff, "-");
        if (buff == ptr || token == NULL) {
            printf("Data non valida\n");
            continue;
        }
        ts->year = strtol(token, &ptr, 10);
        if (errno == ERANGE) {
            perror("strtol error");
            continue;
        }
        if (!onlyYear) {
            //*********settaggio mese
            token = strtok(NULL, "-");
            if (buff == ptr || token == NULL) {
                printf("Data non valida\n");
                continue;
            }
            ts->month = (unsigned int) strtol(token, &ptr, 10);
            if (errno == ERANGE) {
                perror("strtol error");
                continue;
            } else if (ts->month > 12 || ts->month < 1) {
                printf("mese non valido\n");
                continue;
            }
            //*********settaggio giorno
            token = strtok(NULL, "-");
            if (buff == ptr || token == NULL) {
                printf("Data non valida\n");
                continue;
            }
            ts->day = (unsigned int) strtol(token, &ptr, 10);
            if (errno == ERANGE) {
                perror("strtol error");
                continue;
            } else if (ts->day > 31 || ts->day < 1) {
                printf("giorno non valido\n");
                continue;
            }
        }
        break;
    }

    return ts;

}

MYSQL_TIME *getInputTime() {
    char *ptr;
    char *token;
    MYSQL_TIME *ts = malloc(sizeof(MYSQL_TIME));
    if (ts == NULL) {
        printf("unable to allocate memory\n");
        exit(EXIT_FAILURE);
    }

    while(1) {
        printf("inserire orario come hh:mm ");
        ptr = NULL;

        memset(ts, 0, sizeof(MYSQL_TIME));

        memset(buff, 0, 256); // clear buffer
        getInput(20, buff, false);
        token = strtok(buff, ":");
        if (buff == ptr || token == NULL) {
            printf("Orario non valido\n");
            continue;
        }
        ts->hour = strtol(token, &ptr, 10);
        if (errno == ERANGE) {
            perror("strtol error");
            continue;
        } else if (ts->hour < 1 || ts->hour > 24) {
            printf("ora non valida\n");
            continue;
        }

        token = strtok(NULL, ":");
        if (buff == ptr || token == NULL) {
            printf("Orario non Valido\n");
            continue;
        }
        ts->minute = strtol(token, &ptr, 10);
        if (errno == ERANGE) {
            perror("strtol error");
            continue;
        } else if (ts->minute > 60 || ts->minute < 0) {
            printf("minuti non valid1\n");
            continue;
        }
        break;
    }
    return ts;
}

void test_stmt_error(MYSQL_STMT *stmt, int status) {
    if (status) {
        fprintf(stderr, "Error: %s (errno: %d)\n",
                mysql_stmt_error(stmt), mysql_stmt_errno(stmt));
        perror("");
        exit(EXIT_FAILURE);
    }
}

void printer(MYSQL_STMT *stmt, MYSQL *con) {
    MYSQL_RES *rs_metadata;
    int num_fields;    // number of columns in result
    MYSQL_FIELD *fields; // for result set metadata
    MYSQL_BIND *rs_bind; // for output buffers
    int status;

    do {
        /* the column count is > 0 if there is a result set */
        /* 0 if the result is only the final status packet */
        num_fields = mysql_stmt_field_count(stmt);

        if (num_fields > 0) {

            // what kind of result set is this?
            if (con->server_status & SERVER_PS_OUT_PARAMS)
                printf("The stored procedure has returned output in OUT/INOUT parameter(s)\n");

            // Get information about the outcome of the stored procedure
            rs_metadata = mysql_stmt_result_metadata(stmt);
            test_stmt_error(stmt, rs_metadata == NULL);

            // Retrieve the fields associated with OUT/INOUT parameters
            fields = mysql_fetch_fields(rs_metadata);
            rs_bind = (MYSQL_BIND *) malloc(sizeof(MYSQL_BIND) * num_fields);
            if (!rs_bind) {
                printf("Cannot allocate output buffers\n");
                exit(1);
            }
            memset(rs_bind, 0, sizeof(MYSQL_BIND) * num_fields);//costruisco la tupla di out dinamicamente
            void *buffer[num_fields];
            my_bool is_null[num_fields];
            // set up and bind result set output buffers
            for (int i = 0; i < num_fields; ++i) {
                buffer[i] = malloc(256);
                if (buffer[i] == NULL) {
                    printf("unable to allocate memory\n");
                    exit(EXIT_FAILURE);
                }
                memset(buffer[i], 0, 256);
                rs_bind[i].buffer_type = fields[i].type;
                rs_bind[i].is_null = &is_null[i];

                switch (fields[i].type) {
                    case MYSQL_TYPE_NEWDECIMAL:
                        rs_bind[i].buffer = buffer[i];
                        rs_bind[i].buffer_length = MAX_LEN;
                        break;
                    case MYSQL_TYPE_LONG:
                        rs_bind[i].buffer = buffer[i];
                        rs_bind[i].buffer_length = MAX_LEN;
                        break;
                    case MYSQL_TYPE_VAR_STRING:
                        rs_bind[i].buffer = buffer[i];
                        rs_bind[i].buffer_length = MAX_LEN;
                        break;
                    case MYSQL_TYPE_SHORT:
                        rs_bind[i].buffer = buffer[i];
                        rs_bind[i].buffer_length = MAX_LEN;
                        break;
                    case MYSQL_TYPE_YEAR:
                        rs_bind[i].buffer = buffer[i];
                        rs_bind[i].buffer_length = MAX_LEN;
                        break;
                    case MYSQL_TYPE_DATE:
                        rs_bind[i].buffer = buffer[i];
                        rs_bind[i].buffer_length = MAX_LEN;
                        break;
                    default:
                        fprintf(stderr, "ERROR: unexpected type: %d.\n", fields[i].type);
                        exit(1);
                }
            }

            status = mysql_stmt_bind_result(stmt, rs_bind);//binding inverso => recupera info in out
            test_stmt_error(stmt, status);

            // fetch and display result set rows
            while (1) {
                status = mysql_stmt_fetch(stmt);

                if (status == 1 || status == MYSQL_NO_DATA)
                    break;

                for (int i = 0; i < num_fields; ++i) {
                    switch (rs_bind[i].buffer_type) {
                        case MYSQL_TYPE_VAR_STRING: // Not used in this stored procedure
                            if (*rs_bind[i].is_null)
                                printf(" val[%d] = NULL;", i);
                            else
                                printf("%s val[%d] = %s; ", fields[i].name, i, rs_bind[i].buffer);
                            break;
                        case MYSQL_TYPE_LONG:
                            if (*rs_bind[i].is_null)
                                printf(" val[%d] = NULL;", i);
                            else
                                printf("%s val[%d] = %lu; ", fields[i].name, i, *(long *) rs_bind[i].buffer);
                            break;
                        case MYSQL_TYPE_SHORT: //YEAR
                            if (*rs_bind[i].is_null)
                                printf(" val[%d] = NULL; ", i);
                            else
                                printf("%s val[%d] = %d; ", fields[i].name, i, (short) rs_bind[i].buffer);
                            break;
                        case MYSQL_TYPE_NEWDECIMAL:
                            if (*rs_bind[i].is_null)
                                printf(" val[%d] = NULL;", i);
                            else
                                printf("%s val[%d] = %s; ", fields[i].name, i, rs_bind[i].buffer);
                            break;
                        case MYSQL_TYPE_YEAR:
                            if (*rs_bind[i].is_null)
                                printf(" val[%d] = NULL;", i);
                            else
                                printf("%s val[%d] = %lu; ", fields[i].name, i, *(long *) rs_bind[i].buffer);
                            break;
                        case MYSQL_TYPE_DATE:
                            if (*rs_bind[i].is_null)
                                printf(" val[%d] = NULL;", i);
                            else
                                printf("%s val[%d] = %u-%u-%u; ", fields[i].name, i,
                                       ((MYSQL_TIME *) rs_bind[i].buffer)->year,
                                       ((MYSQL_TIME *) rs_bind[i].buffer)->month,
                                       ((MYSQL_TIME *) rs_bind[i].buffer)->day);
                            break;

                        default:
                            printf("ERROR: unexpected type (%d)\n", rs_bind[i].buffer_type);
                    }
                }
                printf("\n");
            }
            for (int i = 0; i < num_fields; i++) {
                free(buffer[i]);
            }
            mysql_free_result(rs_metadata);    // free metadata
            free(rs_bind);    // free output buffers
        } else {
            // no columns = final status packet
            printf("End of procedure output\n");
        }

        // more results? -1 = no, >0 = error, 0 = yes (keep looking)
        status = mysql_stmt_next_result(stmt);
        if (status > 0)
            test_stmt_error(stmt, status);
    } while (status == 0);

}


int GetInputNumber(char *str) {
    char *ptr;
    int number;
    while (1) {
        ptr = NULL;
        printf("Inserire %s\n", str);
        memset(buff, 0, 256); // clear buffer
        printf("%s: ", str);
        getInput(10, buff, false);
        if (strlen(buff) == 0) {
            printf("Non è stato inserito nulla, riprovare.\n");
            continue;
        }
        number = (int) strtol(buff, &ptr, 10);
        if (buff == ptr){
            printf("Non è stato inserito un numero\n");
            continue;
        }
        if (errno == ERANGE) {
            perror("Numero non valido\n");
        } else break;
    }

    return number;
}