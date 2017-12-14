#ifndef PATIENT_H
#define PATIENT_H

#include "dentalClinic.h"

void patient(MYSQL* connection);

void listPatient(MYSQL* connection);

void listPatientCode(MYSQL* connection);

void updatePatient(MYSQL* connection);

void addPatient(MYSQL* connection);

void deletePatient(MYSQL* connection);

#endif
