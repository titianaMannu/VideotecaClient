//
// Created by tiziana on 23/08/19.
//

#ifndef VIDEOTECACLIENT_MANAGER_H
#define VIDEOTECACLIENT_MANAGER_H
#include <stdio.h>
#include <string.h>
#include "program.h"
#include "utils.h"
#include <mysql/mysql.h>
#include <errno.h>
#endif //VIDEOTECACLIENT_MANAGER_H
void ReportAnnuale(MYSQL *con);
void managerRoutine();
void ReportMensile(MYSQL *con);
void InserisciImpiegato(MYSQL *con);
void CheckDatiImpiegato(MYSQL *con);
void AssegnaTurno(MYSQL *con);
void FilmPiuNoleggiato(MYSQL *con);
void AssegnaImpiego(MYSQL *con);