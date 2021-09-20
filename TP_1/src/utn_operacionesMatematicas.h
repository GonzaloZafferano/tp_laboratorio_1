/*
 * utn_operacionesMatematicas.h
 *
 *  Created on: 20 sept 2021
 *      Author: GONZALO
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef UTN_OPERACIONESMATEMATICAS_H_
#define UTN_OPERACIONESMATEMATICAS_H_

int utn_operacionSumar(float numeroUno, float numeroDos, float* pResultado);
int utn_operacionRestar(float numeroUno, float numeroDos, float* pResultado);
int utn_operacionMultiplicar(float numeroUno, float  numeroDos, float* pResultado);
int utn_operacionDividir(float numeroUno, float  numeroDos, float* pResultado);
int utn_operacionCalcularFactorial(float numeroIngresado, float* pResultado);
int utn_esEntero(float numero);

#endif /* UTN_OPERACIONESMATEMATICAS_H_ */
