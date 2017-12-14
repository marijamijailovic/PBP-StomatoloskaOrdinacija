#ifndef INTERVENTION_H
#define INTERVENTION_H

#include "dentalClinic.h"

void intervention(MYSQL* connection);

void listDentalWork(MYSQL* connection);

int listDentalCode(MYSQL* connection);

void updateIntervention(MYSQL* connection);

void addIntervention(MYSQL* connection,int idOblasti);

void deleteInterention(MYSQL* connection);

#endif
