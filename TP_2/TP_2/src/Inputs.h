/*
 * Inputs.h
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#ifndef INPUTS_H_
#define INPUTS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ComprobarErrores.h"

int utn_getInt(int* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos);
int utn_getFloat(float* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos);
int utn_getNombreOApellido(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos);
int tomarID(int idMaximo);
int ingreseUnaOpcion(int* opcion, int minimo, int maximo);

#endif /* INPUTS_H_ */
