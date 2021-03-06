/*
 * Menus.h
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#ifndef MENUS_H_
#define MENUS_H_

#include <stdio.h>
#include <stdlib.h>
#include "Inputs.h"
#include "ComprobarErrores.h"
#include "ArrayEmployees.h"

void imprimirMenuPrincipal(void);
void imprimirMenuSecundario(int opcionUno, int opcionDos);
int esPosibleOperar(int bandera);
int operarMenuAltas(Employee listaEmpleados[], int len, int* idMaximo, int* banderaAltas);
int operarMenuModificacion(Employee listaEmpleados[], int len, int idMaximo);
int operarMenuBajas(Employee listaEmpleados[], int len, int idMaximo);
int operarMenuMostrarInformacion(Employee listaEmpleados[], int len);

#endif /* MENUS_H_ */
