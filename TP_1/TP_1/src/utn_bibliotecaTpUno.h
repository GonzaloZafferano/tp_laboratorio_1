/*
 * utn_bibliotecaTpUno.h
 *
 *  Created on: 23 sept 2021
 *      Author: GONZALO
 */

#include <stdio.h>
#include <stdlib.h>

#ifndef UTN_BIBLIOTECATPUNO_H_
#define UTN_BIBLIOTECATPUNO_H_

void utn_imprimirMenu(int banderaPrimerNumero, int banderaSegundoNumero, int banderaMenu, float primerNumero, float segundoNumero);
int utn_imprimirResultados(float numeroUno, float numeroDos, float pListaResutadosOperaciones[], int longitudResultadosOperaciones);
int utn_realizarOperaciones (float numeroUno, float numeroDos, float pListaResutadosOperaciones [], int longitudResultadosOperaciones);
int utn_inicializarArray(float pArray[], int longitudArray, float valorInicial);

#endif /* UTN_BIBLIOTECATPUNO_H_ */
