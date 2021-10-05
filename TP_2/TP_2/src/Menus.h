/*
 * Menus.h
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#include <stdio.h>
#include <stdlib.h>
#include "Inputs.h"
#include "ComprobarErrores.h"
#include "ArrayEmployees.h"

#ifndef MENUS_H_
#define MENUS_H_

void imprimirMenuPrincipal();
void imprimirMenuSecundario(int opcionUno, int opcionDos);
int esPosibleOperar(int bandera);
int operarMenuBajas(Employee listaEmpleados[], int len);
int operarMenuModificacion(Employee listaEmpleados[], int len);

#endif /* MENUS_H_ */
