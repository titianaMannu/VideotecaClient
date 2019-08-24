//
// Created by tiziana on 23/08/19.
//

#ifndef VIDEOTECACLIENT_CLIENTE_H
#define VIDEOTECACLIENT_CLIENTE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <errno.h>
#include "utils.h"
#include "program.h"

#endif //VIDEOTECACLIENT_CLIENTE_H


void NoleggiaFilm(MYSQL *con) ;
void ChiudiNoleggio(MYSQL *con);
void ClienteRoutine();
void ListaFilmInCentro(MYSQL *con);
void TrovaCopieInCentro(MYSQL *con);
void TrovaRemakes(MYSQL *con);