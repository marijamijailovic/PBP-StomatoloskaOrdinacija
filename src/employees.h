#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "dentalClinic.h"

void employees(MYSQL* connection);

void listEmployees(MYSQL* connection);

void updateEmployees(MYSQL* connection);

void addEmployees(MYSQL* connection);

void deleteEmployees(MYSQL* connection);

#endif
