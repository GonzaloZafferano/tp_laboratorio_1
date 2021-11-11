/*
 * Menu.c
 *
 *  Created on: 5 nov 2021
 *      Author: GONZALO
 */

#include "Menu_mensajes.h"

#define AMBOS_ARCHIVOS_CARGADOS 0
#define FALTA_CARGAR_ARCHIVOS 1
#define ARCHIVO_TEXTO_CARGADO 1
#define ARCHIVOS_INEXISTENTES 2
#define ARCHIVO_BINARIO_CARGADO 2
#define ARCHIVO_CARGADO_EN_SISTEMA 3
#define NINGUN_ARCHIVO_CARGADO 3
#define SE_PUEDE_CARGAR 10
#define CRITERIO 1
#define ORDEN 2
#define SI 1
#define NO 2
#define ERROR_PUNTERO_NULL -1
#define DAR_BAJA 1
#define CONFIRMAR_BAJA 2
#define ASCENDENTE 1
#define DESCENDENTE 0
#define MINIMO_MENU_ORDEN 1
#define MAXIMO_MENU_ORDEN 5
#define MINIMO_MENU_MODIFICACION 1
#define MAXIMO_MENU_MODIFICACION 4
#define MODIFICAR 1
#define MODIFICAR_CAMPOS 2
#define MINIMO_OPCION_MENU_PRINCIPAL 1
#define MAXIMO_OPCION_MENU_PRINCIPAL 10
#define SALIR 1
#define CONFIRMAR_SALIR 2
#define MOSTRAR_LISTA 1
#define GUARDAR_LISTA 2
#define ERROR_SIN_MAS_REINTENTOS -21
#define OBTENER_ACTUAL_ULTIMO_ID 1

/*
* \brief Imprime el menu principal y toma una respuesta
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuPrincipal(int* pRespuesta)
{
	int estadoOperacion;
	static int banderaMenu = 0;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		if(banderaMenu)
		{
			printf("\n\t\t<--Volviendo al Menu Principal-->\n");
		}
		else
		{
			printf("\n\t<--Bienvenido al sistema de carga de datos-->\n");
			banderaMenu = 1;
		}

		printf("\n\t\t<--Menu Principal-->"
				"\n1 >>Cargar los datos de los empleados desde el archivo data.csv (modo texto)"
				"\n2 >>Cargar los datos de los empleados desde el archivo data.bin (modo binario)"
				"\n3 >>Alta de empleado"
				"\n4 >>Modificar datos de empleado"
				"\n5 >>Baja de empleado"
				"\n6 >>Listar empleados"
				"\n7 >>Ordenar empleados"
				"\n8 >>Guardar los datos de los empleados en el archivo data.csv (modo texto)"
				"\n9 >>Guardar los datos de los empleados en el archivo data.bin (modo binario)"
				"\n10 <<Salir");

    	estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, MINIMO_OPCION_MENU_PRINCIPAL, MAXIMO_OPCION_MENU_PRINCIPAL);
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de consulta para mostrar o guardar la lista clonada y toma una respuesta
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuGuardarListaArchivo(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Carga Archivos-->");
		switch(opcion)
		{
			case MOSTRAR_LISTA:
				printf("\nUn momento! No se pudieron cargar todos los elementos del archivo!"
						"\nDesea imprimir los elementos que se lograron cargar hasta el momento??\n\t1 >>Si, mostrar listado que se cargo correctamente del archivo\n\t2 <<No, no mostrar");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case GUARDAR_LISTA:
				printf("\n\nDesea guardar en la lista del sistema los elementos que se lograron cargar del archivo?\n\t1 >>Si, guardar la lista!\n\t2 <<No, descartar elementos y volver al menu!");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de altas y toma una respuesta
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuAltas(int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Altas-->");
		printf("\nDesea dar un alta? \n\t1 >>Si, dar una alta.\n\t2 <<No, volver al menu principal");
    	estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de modificacion y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuModificacion(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Modificacion-->");
		switch(opcion)
		{
			case MODIFICAR:
				printf("\nDesea realizar una modificacion? \n\t1 >>Si, hacer una modificacion.\n\t2 <<No, volver al menu principal");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case MODIFICAR_CAMPOS:
				printf("\nPor favor, seleccione el campo que desea modificar"
						"\n1 >>Nombre y apellido"
						"\n2 >>Horas Trabajadas"
						"\n3 >>Salario"
						"\n4 <<Atras");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, MINIMO_MENU_MODIFICACION, MAXIMO_MENU_MODIFICACION);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de ordenamiento y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuOrdenamiento(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Ordenamiento-->");
		switch(opcion)
		{
			case CRITERIO:
				printf("\nIngrese criterio de ordenamiento"
					"\n1 >>Ordenar por ID"
					"\n2 >>Ordenar por Nombre"
					"\n3 >>Ordenar por Salario"
					"\n4 >>Ordenar por cantidad de horas trabajadas"
					"\n5 <<Atras");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, MINIMO_MENU_ORDEN, MAXIMO_MENU_ORDEN);
				break;
			case ORDEN:
				printf("\nIngrese el orden\n0 >>Descendente \n1 >>Ascendente");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, DESCENDENTE, ASCENDENTE);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de Bajas y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuBajas(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Bajas-->");
		switch(opcion)
		{
			case DAR_BAJA:
				printf("\nDesea dar una baja? \n\t1 >>Si, dar una baja.\n\t2 <<No, volver al menu principal");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case CONFIRMAR_BAJA:
				printf("\nSeguro quiere eliminar este empleado?\n\t1 >>Si\n\t2 <<No");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de confirmacion para guardar una lista vacia
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_guardarListaVaciaEnArchivo(int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\nLa lista se encuentra vacia! Desea guardar la lista vacia en el archivo de todos modos?"
				"\n\t1 >>Si, guardar lista vacia en archivo! \n\t2 <<No, no guardar y volver al menu principal");
		estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Imprime el menu de SALIR y toma una respuesta
* \param int opcion - Determina las opciones del menu y el dato a pedir
* \param int* pRespuesta - puntero a variable que espera una respuesta del usuario
* \return Retorna INT. Retorna -1 si el puntero es NULL o
*  retorna el estado de la operacion de toma de datos (0 Si opero correctamente, negativo si ocurrio un error)
*/
int menu_ImprimirMenuSalir(int opcion, int* pRespuesta)
{
	int estadoOperacion;
	int retorno = ERROR_PUNTERO_NULL;

	if(pRespuesta != NULL)
	{
		printf("\n\t\t<--Menu Salir del Programa-->");
		switch(opcion)
		{
			case SALIR:
				printf("\nSeguro desea salir?\n\t1 >>Si, salir del programa.\n\t2 <<No, no salir.");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
			case CONFIRMAR_SALIR:
				printf("\nSeguro desea salir y perder todos los cambios? (Los ids generados se mantendran)\n\t1 >>Si, salir del programa.\n\t2 <<No, no salir.");
				estadoOperacion = utn_ingreseUnaOpcion(pRespuesta, SI, NO);
				break;
		}
		retorno = estadoOperacion;
	}
	return retorno;
}

/*
* \brief Toma el Id del empleado con el que se quiere operar.
* \return Retorna INT. Retorna un numero positivo que es el ID ingresado por el usuario,
*         retorno -21 si se quedo sin reintentos para ingresar el ID
*/
int menu_imprimirMenuTomaDeId()
{
	int id;
	int estadoOperacion;
	int idMaximo = employee_getLastOrNextId(OBTENER_ACTUAL_ULTIMO_ID);
	int retorno = ERROR_SIN_MAS_REINTENTOS;

	if(idMaximo >0)
	{
		printf("\n\t\t<--Menu Toma de ID-->\n>>Ingrese un Id valido. \n<<O pulse '0' para Volver al menu");
		estadoOperacion = utn_ingreseUnaOpcion(&id, 0, idMaximo);
		if(!estadoOperacion)
		{
			retorno = id;
		}
	}
	return retorno;
}

/*
* \brief Evalua si es posible realizar una operacion del menu. Si es posible, no realiza acciones.
*        Si no es posible, informa el motivo.
* \param int bandera - Valor que identifica la posibilidad de realizar una operacion.
* \return retorna un INT. 1 si es posible realizar la operacion en base a la bandera recibida.
* 		  retorna 0 si la operacion no puede ser realizada.
*/
int menu_EsPosibleOperarMenu(int bandera)
{
	int retorno = 0;
	switch(bandera)
	{
		case ARCHIVO_TEXTO_CARGADO:
			printf("\n\t\t<--Un momento! Ya ha cargado la lista desde el archivo en modo Texto!-->"
					"\n\t\t<--No se cargara el archivo para evitar duplicar informacion-->\n");
			break;
		case ARCHIVO_BINARIO_CARGADO:
			printf("\n\t\t<--Un momento! Ya ha cargado la lista desde el archivo en modo Binario!-->"
					"\n\t\t<--No se cargara el archivo para evitar duplicar informacion-->\n");
			break;
		case ARCHIVO_CARGADO_EN_SISTEMA:
			printf("\n\t\t<--Un momento! Ya hay un archivo cargado en el sistema!-->"
				   "\n\t\t<--No se cargara el archivo para evitar duplicar informacion-->\n");
			break;
		case SE_PUEDE_CARGAR:
			retorno = 1;
			break;
	}
	return retorno;
}

/*
* \brief Verifica el estado de cargas del archivo binario y de texto. Si falta una o ambas cargas,
*        lo informa.
* \param int banderaCargaTexto - Valor que identifica el estado de carga del archivo de texto
* \param int banderaCargaBinario - Valor que identifica el estado de carga del archivo binario
* \return retorna un INT. 0 si ambos archivos estan cargados
* 		  retorna 1 si solo esta cargado el archivo de texto
* 		  retorna 2 si solo esta cargado el archivo binario
* 		  retorna 3 si ningun archivo esta cargado
*/
int menu_VerificarCargasDeArchivosParaSalir(int banderaCargaTexto, int banderaCargaBinario)
{
	int retorno = AMBOS_ARCHIVOS_CARGADOS;

	if(!banderaCargaBinario && !banderaCargaTexto)
	{
		printf("\nUn momento! No ha guardado las modificaciones realizadas en ningun archivo!"
			   "\nSi finaliza sin guardar perdera todos los cambios (altas, modificaciones, bajas, orden)"
			   "\nCon excepcion de los ids generados!\n");
		retorno = NINGUN_ARCHIVO_CARGADO;
	}
	else
	{
		if(!banderaCargaTexto)
		{
			printf("\n<--Un momento! Se realizaron modificaciones en el sistema, pero la lista solo "
					"\nse guardo en el archivo Binario! Por seguridad, se guardara la informacion "
					"\nen el archivo de Texto para mantener la consistencia entre ambos archivos!-->\n");
			retorno = ARCHIVO_BINARIO_CARGADO;
		}
		else
		{
			if(!banderaCargaBinario)
			{
				printf("\n<--Un momento! Se realizaron modificaciones en el sistema, pero la lista solo "
						"\nse guardo en el archivo Texto! Por seguridad, se guardara la informacion "
						"\nen el archivo Binario para mantener la consistencia entre ambos archivos!-->\n");
				retorno = ARCHIVO_TEXTO_CARGADO;
			}
		}
	}
	return retorno;
}

/*
* \brief Imprime un mensaje de alerta, segun el parametro recibido.
* \param int tipoMensaje - Valor que identifica el mensaje de alerta que se debe imprimir
* \return VOID
*/
void menu_mensajesAlerta(int tipoMensaje)
{
	switch(tipoMensaje)
	{
		case FALTA_CARGAR_ARCHIVOS:
			printf("\n\t\t<--Un momento! No se pueden guardar los datos en el archivo-->"
				   "\n\t\t<--Primero debe cargar el archivo (modo Binario o Texto) en el sistema!-->\n");
			break;
		case ARCHIVOS_INEXISTENTES:
			printf("\n\t\t<--Un momento! Se detecto que no existe ni el archivo Texto ni Binario-->"
				   "\n\t\t<--Se habilita la creacion/guardado de archivos automatica con opcion 8 o 9!-->\n");
			break;
	}
}

/*
* \brief Imprime la cantidad de cargas realizadas desde el archivo al sistema, con la opcion 1 o 2 del Menu
* \param int contador - Cantidad de cargas realizadas al sistema
* \param int estadoOperacion - estado de la operacion de cargas
* \return VOID
*/
void menu_imprimirCantidadCargasDesdeArchivo(int contador, int estadoOperacion)
{
	if(contador == 0 && !estadoOperacion)
	{
		printf("\n\t\t<--Se completo la carga del archivo, pero el mismo se encontraba vacio!-->\n");
	}
	else
	{
		if(contador >=0)
		{
			printf("\n\t\t<--Se han cargado %d empleados del archivo a la lista!-->\n", contador);
		}
	}
}
