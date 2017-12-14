#ifndef MATERIAL_H
#define MATERIAL_H

#include "dentalClinic.h"

void material(MYSQL* connection);

void listMaterial(MYSQL* connection);

void addMaterial(MYSQL* connection);

void deleteMaterial(MYSQL* connection);

#endif
