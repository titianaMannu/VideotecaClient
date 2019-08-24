//
// Created by tiziana on 24/08/19.
//

#ifndef VIDEOTECACLIENT_IMPIEGATO_H
#define VIDEOTECACLIENT_IMPIEGATO_H
#include <mysql/mysql.h>
#include <stdio.h>

#include "program.h"
#include "utils.h"
#endif //VIDEOTECACLIENT_IMPIEGATO_H
void ImpiegatoRoutine();
void InserisciCliente(MYSQL *con);
void LeggiDatiCliente(MYSQL *con);
void TrovaClientiIrregolari(MYSQL *con);
void AssegnaCollocazione(MYSQL *con);
void InserisciFilm(MYSQL *con);
void LeggiDatiNoleggio(MYSQL *con);
void AggiungiCopie(MYSQL *con);