/*
 * Menu.h
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */

#ifndef MENU_MENSAJES_H_
#define MENU_MENSAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include "Utn_tomarDatos.h"
#include "Employee.h"

void menu_mensajesAlerta(int tipoMensaje);
int menu_VerificarCargasDeArchivosParaSalir(int banderaCargaTexto, int banderaCargaBinario);
int menu_EsPosibleOperarMenu(int bandera);
int menu_ImprimirMenuBajas(int opcion, int* pRespuesta);
int menu_ImprimirMenuOrdenamiento(int opcion, int* pRespuesta);
int menu_ImprimirMenuModificacion(int opcion, int* pRespuesta);
int menu_ImprimirMenuAltas(int* pRespuesta);
int menu_ImprimirMenuPrincipal(int* pRespuesta);
void menu_imprimirCantidadCargasDesdeArchivo(int contador, int estadoOperacion);
int menu_guardarListaVaciaEnArchivo(int esListaVacia);
int menu_ImprimirMenuSalir(int opcion, int* pRespuesta);
int menu_ImprimirMenuGuardarListaArchivo(int opcion, int* pRespuesta);
int menu_imprimirMenuTomaDeId();

#endif /* MENU_MENSAJES_H_ */
