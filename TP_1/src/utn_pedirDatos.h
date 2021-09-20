/*
 * utn_pedirDatos.h
 *
 *  Created on: 15 sept 2021
 *      Author: GONZALO
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef UTN_PEDIRDATOS_H_
#define UTN_PEDIRDATOS_H_

int utn_pedirNumeroIntConMaxYMin(int* pNumero, int minimo, int maximo, int reintentos, char* pMensaje, char* pMensajeError);
int utn_pedirNumeroIntSinMaxYMin(int* pNumero, int reintentos, char* pMensaje, char* pMensajeError);
int utn_pedirNumeroFloatConMaxYMin(float* pNumero, float minimo, float maximo, int reintentos, char* pMensaje, char* pMensajeError);
int utn_pedirNumeroFloatSinMaxMin(float* pNumero, int reintentos, char* pMensaje, char* pMensajeError);

#endif /* UTN_PEDIRDATOS_H_ */
