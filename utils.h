//
// Created by tiziana on 23/08/19.
//

#ifndef VIDEOTECACLIENT_PRINT_RESULTS_H

#define VIDEOTECACLIENT_PRINT_RESULTS_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "program.h"

#endif //VIDEOTECACLIENT_PRINT_RESULTS_H
void test_stmt_error(MYSQL_STMT * stmt, int status);
void printer( MYSQL_STMT *stmt, MYSQL *con);
MYSQL_TIME *getInputDate(bool year);
void finish_with_error(MYSQL *con, char *err);
MYSQL_TIME *getInputTime();
int GetInputNumber();