/*
 ============================================================================
 Name        : TP_2.c
 Author      : Gonzalo Zafferano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "Inputs.h"
#include "ComprobarErrores.h"
#include "ArrayEmployees.h"
#include "Menus.h"

#define OPCION_INICIAL 0
#define NO_SE_PUEDE_OPERAR_MODIFICACION_BAJA_MUESTRA_DE_DATOS 0
#define MENU_PRINCIPAL_MINIMO 1
#define MENU_PRINCIPAL_MAXIMO 5
#define ELIMINACION_EXITOSA 0
#define NO_HAY_MAS_EMPLEADOS 0
#define MENU_BAJA 2
#define MENU_BAJA_CONTINUAR_DANDO_BAJAS 5
#define MENU_BAJA_MINIMO 1
#define MENU_BAJA_MAXIMO 2
#define MENU_SALIR 4
#define MENU_SALIR_DESEA_SALIR 8
#define MENU_SALIR_NO_SALIR 2
#define MENU_SALIR_SI_SALIR 1
#define VOLVER_ATRAS 2
#define CERRAR_APLICACION 6
#define TAM_LISTA_EMPLEADOS 1000
#define PUNTERO_NULL -1
#define LEN_INVALIDO -2

int main(void)
{
	setbuf(stdout, NULL);
	Employee listaEmpleados[TAM_LISTA_EMPLEADOS];
	int estadoOperacion;
	int idMaximo;
	int opcionElegida = OPCION_INICIAL;
	int banderaModificarBajaInformar = NO_SE_PUEDE_OPERAR_MODIFICACION_BAJA_MUESTRA_DE_DATOS;

	estadoOperacion = initEmployees(listaEmpleados, TAM_LISTA_EMPLEADOS);
	if(utn_comprobarEstadoDeOperacion(estadoOperacion))
	{
		do
		{
			imprimirMenuPrincipal();

			estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_PRINCIPAL_MINIMO,MENU_PRINCIPAL_MAXIMO);

			if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			{
				switch(opcionElegida)
				{
				case 1:
						estadoOperacion = buscarIndiceLibre(listaEmpleados, TAM_LISTA_EMPLEADOS);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion))
						{
							estadoOperacion = operarMenuAltas(listaEmpleados, TAM_LISTA_EMPLEADOS, &idMaximo, &banderaModificarBajaInformar);

							if(estadoOperacion == PUNTERO_NULL || estadoOperacion == LEN_INVALIDO)
							{
								opcionElegida = CERRAR_APLICACION;
							}
						}
						break;
					case 2:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							estadoOperacion = operarMenuModificacion(listaEmpleados, TAM_LISTA_EMPLEADOS, idMaximo);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
						break;
					case 3:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							do
							{
								opcionElegida = VOLVER_ATRAS;
								estadoOperacion = operarMenuBajas(listaEmpleados, TAM_LISTA_EMPLEADOS, idMaximo);
								utn_comprobarEstadoDeOperacion(estadoOperacion);

								if(estadoOperacion == ELIMINACION_EXITOSA)
								{
									estadoOperacion = verificarSiHayEmpleados(listaEmpleados, TAM_LISTA_EMPLEADOS);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										if(estadoOperacion == NO_HAY_MAS_EMPLEADOS)
										{
											printf("\n\t\t<-No hay mas empleados en el sistema!->\n");
											banderaModificarBajaInformar = NO_SE_PUEDE_OPERAR_MODIFICACION_BAJA_MUESTRA_DE_DATOS;
										}
										else
										{
											imprimirMenuSecundario(MENU_BAJA, MENU_BAJA_CONTINUAR_DANDO_BAJAS);
											estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_BAJA_MINIMO, MENU_BAJA_MAXIMO);
										}
									}
								}
							}while(opcionElegida != VOLVER_ATRAS);
						}
						break;
					case 4:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							estadoOperacion = operarMenuMostrarInformacion(listaEmpleados, TAM_LISTA_EMPLEADOS);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
						break;
					case 5:
						imprimirMenuSecundario(MENU_SALIR, MENU_SALIR_DESEA_SALIR);
						estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_SALIR_SI_SALIR, MENU_SALIR_NO_SALIR);
						if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida == MENU_SALIR_SI_SALIR)
						{
							opcionElegida = CERRAR_APLICACION;
						}
						break;
				}
			}
		}while(opcionElegida != CERRAR_APLICACION);
	}

	printf("\n\t\t<--Fin del programa-->");

	return EXIT_SUCCESS;
}
