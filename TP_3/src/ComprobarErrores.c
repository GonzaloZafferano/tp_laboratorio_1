/*
 * ComprobarErrores.c
 *
 *  Created on: 27 oct 2021
 *      Author: GONZALO
 */

#include "ComprobarErrores.h"
#define EXITO 1
#define ERROR 0
#define LEN_MENSAJE 200

static void imprimirErrores(int codigoError);

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

/*
* \brief Evalua el codigo de error recibido, e imprime el error asociado (si corresponde).
* \param int codigoError - Codigo de identificacion del error
* \return void.
*/
static void imprimirErrores(int codigoError)
{
	char mensaje[LEN_MENSAJE];

	switch(codigoError)
	{
		///////////////////////////ERRORES CON LOS PARAMETROS
		case -1:
			strncpy(mensaje,"\n\t\t--ERROR. Puntero tiene una direccion de memoria NULL. No se puede operar.--\n", LEN_MENSAJE);
			break;
		case -2:
			strncpy(mensaje,"\n\t\t--ERROR. Longitud de ARRAY es invalida o supera el limite del buffer. No se puede operar.--\n", LEN_MENSAJE);
			break;
		case -3:
			strncpy(mensaje,"\n\t\t--ERROR. Cantidad de reintentos no puede ser negativa. No se puede operar--\n", LEN_MENSAJE);
			break;
		case -4:
			strncpy(mensaje,"\n\t\t--ERROR. Error con los maximos y minimos. El minimo no puede ser mayor que el maximo.--\n" , LEN_MENSAJE);
			break;
		case -5:
			strncpy(mensaje,"\n\t\t--ERROR. El parametro 'i' y el parametro 'j' no pueden ser el mismo numero.--\n", LEN_MENSAJE);
			break;
		case -6:
			strncpy(mensaje,"\n\t\t--ERROR. El parametro i o j estan fuera de rango.--\n", LEN_MENSAJE);
			break;
		case -7:
			strncpy(mensaje,"\n\t\t--ERROR. El elemento recibido esta vacio.--\n", LEN_MENSAJE);
			break;
		case -8:
			strncpy(mensaje,"\n\t\t--ERROR. Indice fuera de rango.--\n", LEN_MENSAJE);
			break;
		case -9:
			strncpy(mensaje,"\n\t\t--ERROR. Dato fuera de rango.--\n", LEN_MENSAJE);
			break;
		case -10:
			strncpy(mensaje,"\n\t\t--ERROR. Puntero tiene una direccion de memoria NULL. No se puede operar.--\n", LEN_MENSAJE);
			break;
		case -11:
			strncpy(mensaje,"\n\t\t--ERROR. Dato invalido.--\n", LEN_MENSAJE);
			break;
			///////////////////////////ERRORES EN LA TOMA DE DATOS
		case -20:
			strncpy(mensaje,"\n\t\t--ERROR. Una de las funciones internas no pudo completar su operacion. No se puede operar--\n", LEN_MENSAJE);
			break;
		case -21:
			strncpy(mensaje,"\n\t\t--ERROR. Se acabaron los reintentos para operar.--\n", LEN_MENSAJE);
			break;
		case -22:
			strncpy(mensaje,"\n\t\t--ERROR. No se han ingresado caracteres o la cadena perdio el '\0'.--\n", LEN_MENSAJE);
			break;
		case -23:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudieron tomar los datos correctamente--\n\t\t--No se aplicaron cambios en el sistema.--\n", LEN_MENSAJE);
			break;
		case -24:
			strncpy(mensaje,"\n\t\t--ERROR. ID invalido.--\n" , LEN_MENSAJE);
			break;
		case -25:
			strncpy(mensaje,"\n\t\t--ERROR. No se obtuvo una respuesta valida!.--\n" , LEN_MENSAJE);
			break;
			///////////////////////////ERRORES RELACIONADOS CON ABM
		case -30:
			strncpy(mensaje,"\n\t\t<--Un momento! La lista se encuentra vacia! No se puede operar esta opcion!.-->\n", LEN_MENSAJE);
			break;
		case -31:
			strncpy(mensaje,"\n\t\t<--Un momento! Hay un solo empleado en la lista! No se puede ordenar!-->\n", LEN_MENSAJE);
			break;
		case -32:
			strncpy(mensaje,"\n\t\t--ERROR. No se encontraron datos asociados al ID indicado.--\n" , LEN_MENSAJE);
			break;
		case -33:
			strncpy(mensaje,"\n\t\t--ERROR. El empleado que estaba asociado a ese Id ha sido dado de baja.--\n", LEN_MENSAJE);
			break;
		case -34:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudo llevar a cabo el alta.--\n", LEN_MENSAJE);
			break;
		case -35:
			strncpy(mensaje,"\n\t\t--ERROR. No se aplicaron modificaciones sobre el empleado.--\n", LEN_MENSAJE);
			break;
		case -36:
			strncpy(mensaje,"\n\t\t--ERROR. No se aplicaron bajas en el sistema.--\n", LEN_MENSAJE);
			break;
		case -37:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudieron obtener los datos corretamente para imprimir el empleado.--\n", LEN_MENSAJE);
			break;
		case -38:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudieron obtener los datos del empleado.--\n", LEN_MENSAJE);
			break;
		case -39:
			strncpy(mensaje,"\n\t\t--ERROR. Error al intentar ordenar la lista.--\n", LEN_MENSAJE);
			break;
			///////////////////////////ERRORES RELACIONADOS CON ARCHIVOS
		case -40:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudieron cargar todos los datos de la lista correctamente en el archivo!.--\n", LEN_MENSAJE);
			break;
		case -41:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudo cargar empleado a la lista!.--\n", LEN_MENSAJE);
			break;
		case -42:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudieron cargar todos los empleados del archivo a la lista!.--\n", LEN_MENSAJE);
			break;
		case -43:
			strncpy(mensaje,"\n\t\t--ERROR. Se encontraron datos invalidos en el archivo por lo que se interrumpio la carga del archivo!.--\n", LEN_MENSAJE);
			break;
		case -44:
			strncpy(mensaje,"\n\t\t--ERROR. Error al intentar cargar datos en el archivo! Se interrumpio la carga!.--\n", LEN_MENSAJE);
			break;
		case -45:
			strncpy(mensaje,"\n\t\t--ERROR. Ha ocurrido un error al intentar cargar el archivo de Texto! ARCHIVO NO EXISTE!.--\n\t\t--Por favor, reintente con cargar el archivo Binario--\n", LEN_MENSAJE);
			break;
		case -46:
			strncpy(mensaje,"\n\t\t--ERROR. No hay datos cargados en el archivo!.--\n", LEN_MENSAJE);
			break;
		case -47:
			strncpy(mensaje,"\n\t\t--ERROR. Ha ocurrido un error al intentar cargar el archivo Binario! ARCHIVO NO EXISTE!.--\n\t\t--Por favor, reintente con cargar el archivo de Texto--\n", LEN_MENSAJE);
			break;
		case -48:
			strncpy(mensaje,"\n\t\t--ERROR. Archivo no encontrado!--", LEN_MENSAJE);
			break;
		case -49:
			strncpy(mensaje,"\n\t\t--ERROR. No se pudo guardar ultimo Id en Archivo!--", LEN_MENSAJE);
			break;
		default :
			strncpy(mensaje,"\n\t\t--ERROR--", LEN_MENSAJE);
			break;
	}
	printf("%s", mensaje);
}
