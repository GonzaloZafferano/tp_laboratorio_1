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
#define SE_PUEDE_OPERAR_MODIFICACION_BAJA_MUESTRA_DE_DATOS 1
#define MENU_PRINCIPAL_MINIMO 1
#define MENU_PRINCIPAL_MAXIMO 5
#define ALTA_EXITOSA 0
#define ELIMINACION_EXITOSA 0
#define NO_HAY_MAS_EMPLEADOS 0
#define MENU_ALTAS 0
#define MENU_ALTAS_COMPLETAR_CAMPOS_DE_DATOS 0
#define MENU_BAJA 2
#define MENU_BAJA_CONTINUAR_DANDO_BAJAS 5
#define MENU_BAJA_MINIMO 1
#define MENU_BAJA_MAXIMO 2
#define MENU_INFORMACION 3
#define MENU_INFORMACION_COMO_DESEA_VER_LISTADO 6
#define MENU_INFORMACION_MINIMO 0
#define MENU_INFORMACION_MAXIMO 2
#define MENU_SALIR 4
#define MENU_SALIR_DESEA_SALIR 8
#define MENU_SALIR_NO_SALIR 2
#define MENU_SALIR_SI_SALIR 1
#define VOLVER_ATRAS 2
#define CERRAR_APLICACION 6
#define TAM_LISTA_EMPLEADOS 1000
#define NO_SE_CARGARON_TODOS_LOS_CAMPOS -14

int main(void)
{
	setbuf(stdout, NULL);
	Employee listaEmpleados[TAM_LISTA_EMPLEADOS];
	int estadoOperacion;
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
							imprimirMenuSecundario(MENU_ALTAS, MENU_ALTAS_COMPLETAR_CAMPOS_DE_DATOS);
							estadoOperacion = tomarDatosEmpleados(listaEmpleados, TAM_LISTA_EMPLEADOS);
							utn_comprobarEstadoDeOperacion(estadoOperacion);

							if(estadoOperacion == ALTA_EXITOSA)
							{
								printf("\n\t\t<-Empleado cargado exitosamente!->\n");
								banderaModificarBajaInformar = SE_PUEDE_OPERAR_MODIFICACION_BAJA_MUESTRA_DE_DATOS;
							}
							else
							{
								//El error -14 indica que no se cargaron correctamente los datos, por
								//lo que puede continuar reintentando y operando el menu.
								//Otro tipo de error, como memoria NULL, len invalido o ID fuera de limite,
								//no permitiran operar los distintos menu, por lo que no tiene sentido continuar.
								if(estadoOperacion != NO_SE_CARGARON_TODOS_LOS_CAMPOS)
								{
									opcionElegida = CERRAR_APLICACION;
								}
							}
						}
						break;
					case 2:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							estadoOperacion = operarMenuModificacion(listaEmpleados, TAM_LISTA_EMPLEADOS);
							utn_comprobarEstadoDeOperacion(estadoOperacion);
						}
						break;
					case 3:
						if(esPosibleOperar(banderaModificarBajaInformar))
						{
							do
							{
								opcionElegida = VOLVER_ATRAS;
								estadoOperacion = operarMenuBajas(listaEmpleados, TAM_LISTA_EMPLEADOS);
								utn_comprobarEstadoDeOperacion(estadoOperacion);

								if(estadoOperacion == ELIMINACION_EXITOSA) //Si es 0, se realizo una eliminacion exitosa.
								{
									//Despues de haber eliminado al empleado, verifico que aun existan empleados en la lista.
									estadoOperacion = verificarSiHayEmpleados(listaEmpleados, TAM_LISTA_EMPLEADOS);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										if(estadoOperacion == NO_HAY_MAS_EMPLEADOS) //Si es 0, ya no quedan empleados
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
							imprimirMenuSecundario(MENU_INFORMACION, MENU_INFORMACION_COMO_DESEA_VER_LISTADO);

							estadoOperacion = ingreseUnaOpcion(&opcionElegida, MENU_INFORMACION_MINIMO, MENU_INFORMACION_MAXIMO);

							if(utn_comprobarEstadoDeOperacion(estadoOperacion) && opcionElegida < VOLVER_ATRAS)
							{
								estadoOperacion = sortEmployees(listaEmpleados, TAM_LISTA_EMPLEADOS, opcionElegida);
								if(utn_comprobarEstadoDeOperacion(estadoOperacion))
								{
									estadoOperacion = printEmployees(listaEmpleados, TAM_LISTA_EMPLEADOS);
									if(utn_comprobarEstadoDeOperacion(estadoOperacion))
									{
										estadoOperacion = imprimirDatosDeSalario(listaEmpleados, TAM_LISTA_EMPLEADOS);
										utn_comprobarEstadoDeOperacion(estadoOperacion);
									}
								}
							}
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