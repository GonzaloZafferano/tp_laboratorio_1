/*
 * ComprobarErrores.c
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#include "ComprobarErrores.h"
#define EXITO 1
#define ERROR 0

static void imprimirErrores(int codigoError);

/*
* \brief Evalua el codigo de error recibido, e imprime el error asociado (si corresponde).
* \param int codigoError - Codigo de identificacion del error
* \return void.
*/
static void imprimirErrores(int codigoError)
{
	switch(codigoError)
	{
		case -1:
			printf("\n\t\t--ERROR. Direccion de memoria de parametros es NULL. No se puede operar.--\n");
			break;
		case -2:
			printf("\n\t\t--ERROR. Longitud de ARRAY es invalida o supera el limite del buffer. No se puede operar.--\n");
			break;
		case -3:
			printf("\n\t\t--ERROR. Funcion fgets() No se pudo asignar el dato ingresado. No se puede operar--\n");
			break;
		case -4:
			printf("\n\t\t--ERROR. Se acabaron los reintentos para operar.--\n");
			break;
		case -5:
			printf("\n\t\t--ERROR. Cantidad de reintentos no puede ser negativa. No se puede operar--\n");
			break;
		case -6:
			printf("\n\t\t--ERROR. Error con los maximos y minimos. El minimo no puede ser mayor que el maximo.--\n");
			break;
		case -7:
			printf("\n\t\t--ERROR. La funcion mygets() devolvio un error.--\n");
			break;
		case -8:
			printf("\n\t\t--ERROR. La funcion esNumeroEntero() devolvio un error.--\n");
			break;
		case -9:
			printf("\n\t\t--ERROR. La funcion esNombreOApellido() devolvio un error.--\n");
			break;
		case -10:
			printf("\n\t\t--ERROR. La funcion esNumeroFloat() devolvio un error.--\n");
			break;
		case -11:
			printf("\n\t\t--ERROR. ID invalido.--\n");
			break;
		case -12:
			printf("\n\t\t--ERROR. No hay ningun empleado cargado con ese Id.--\n");
			break;
		case -13:
			printf("\n\t\t--ERROR. El parametro 'i' y el parametro 'j' no pueden ser el mismo numero.--\n");
			break;
		case -14:
			printf("\n\t\t--ERROR. No se pudieron tomar los datos correctamente.\n\t\t  No se aplicaron cambios en el sistema.--\n");
			break;
		case -15:
			printf("\n\t\t--ERROR. No se aplicaron modificaciones sobre el empleado.--\n");
			break;
		case -16:
			printf("\n\t\t--ERROR. No hay empleados cargados en la lista del sistema.--\n");
			break;
		case -17:
			printf("\n\t\t--ERROR. No se calculo el promedio de salarios.--\n");
			break;
		case -18:
			printf("\n\t\t--ERROR. Debido a un error, no se pudieron imprimir los datos de los salarios.--\n");
			break;
		case -19:
			printf("\n\t\t--No se aplicaron bajas en el sistema.--\n");
			break;
		case -20:
			printf("\n\t\t--No se encontraron datos asociados al ID indicado.--\n");
			break;
		case -21:
			printf("\n\t\t--ERROR. El listado esta lleno. No se pueden cargar mas empleados.--\n");
			break;
		case -22:
			printf("\n\t\t--ERROR. No se pudo obtener una respuesta valida.--\n");
			break;
		case -23:
			printf("\n\t\t--ERROR. El parametro i o j estan fuera de rango.--\n");
			break;
		case -24:
			printf("\n\t\t--ERROR. Error al intentar borrar espacios en blanco.--\n");
			break;
		case -25:
			printf("\n\t\t--ERROR. No se pudo llevar a cabo ningun alta.--\n");
			break;
		default :
			printf("\n\t\t--ERROR.--\n");
	}
}

/*
* \brief Evalua el exito de una operacion. Si hay exito, no realiza acciones.
*        Ante una falla (estado menor que 0), se apoya en otra funcion imprimirErrores (int codigoError),
*        enviandole el estado recibido de la operacion (que almacena el codigo de error).
* \param int estadoOperacion - Valor que identifica el estado (exito o falla) de una operacion.
* \return retorna un INT. 1 si la operacion recibida fue exitosa.
* 		  retorna 0 si la operacion recibida no fue exitosa.
*/
int utn_comprobarEstadoDeOperacion(int estadoOperacion)
{
	int retorno = EXITO;

	if(estadoOperacion < 0)
	{
		imprimirErrores(estadoOperacion);
		retorno = ERROR;
	}
	return retorno;
}
