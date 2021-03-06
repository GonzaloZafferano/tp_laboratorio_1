/*
 * Controller.h
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include "ComprobarErrores.h"
#include "Utn_tomarDatos.h"
#include "Controller.h"
#include "parser.h"
#include "Menu_mensajes.h"

int controller_loadFromText(char* path , LinkedList* pArrayListEmployee);
int controller_loadFromBinary(char* path , LinkedList* pArrayListEmployee);
int controller_addEmployee(LinkedList* pArrayListEmployee);
int controller_editEmployee(LinkedList* pArrayListEmployee);
int controller_removeEmployee(LinkedList* pArrayListEmployee);
int controller_ListEmployee(LinkedList* pArrayListEmployee);
int controller_sortEmployee(LinkedList* pArrayListEmployee);
int controller_saveAsText(char* path , LinkedList* pArrayListEmployee);
int controller_saveAsBinary(char* path , LinkedList* pArrayListEmployee);
int controller_exitApp(LinkedList* pArraylist, int banderaArchivoTexto, int banderaArchivoBinario, int banderaModificacion);

#endif /* CONTROLLER_H_ */
