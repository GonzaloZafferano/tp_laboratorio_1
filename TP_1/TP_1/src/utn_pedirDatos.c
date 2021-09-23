/*
 * utn_pedirDatos.c
 *
 *  Created on: 23 sept 2021
 *      Author: GONZALO
 */


#include "utn_pedirDatos.h"

/*
* \brief Pide un numero int al usuario (CON RANGO). Verifica la validez del numero ingresado.
* \param int* pNumero - Direccion de memoria donde se almacenara el numero ingresado, luego de ser validado.
* \param int minimo - Valor Minimo permitido al validar
* \param int maximo - Valor maximo permitido al validar
* \param int reintentos - Cantidad de reintentos para ingresar un dato valido
* \param char* mensaje - Mensaje de informacion para el usuario
* \param char* mensajeError - Mensaje de error en caso de ingresar un valor invalido.
* \return -1 si el puntero int* pNumero/ char* pMensaje/ char* pMensajeError apunta una direccion de memoria NULL.
*          0 OK: si las direcciones de memoria son distintas de NULL y si se valido satisfactoriamente el numero ingresado.
*	      -2 Si se queda sin reintentos
*	      -8 Si el valor minimo no es menor que el maximo.
*/
int utn_pedirNumeroIntConMaxYMin(int* pNumero, int minimo, int maximo, int reintentos, char* pMensaje, char* pMensajeError)
{
	int retorno =-1;
	int numeroIngresado;
	int i;
	int salidaScanf;

	if(pNumero!= NULL && reintentos >= 0 && pMensaje!= NULL && pMensajeError != NULL)
	{
		retorno = -8;
		if(minimo < maximo)
		{
			for(i = 0; i <= reintentos; i++)
			{
				printf("\n%s", pMensaje);
				fflush(stdin);
				salidaScanf = scanf("%d", &numeroIngresado);

				if(salidaScanf>0 && numeroIngresado >= minimo && numeroIngresado <= maximo)
				{
					*pNumero = numeroIngresado;
					retorno = 0;
					break;
				}
				else
				{
					printf("\n%s", pMensajeError);
					retorno = -2;
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Pide un numero int al usuario (SIN RANGO). Verifica la validez del numero ingresado.
* \param int* pNumero - Direccion de memoria donde se almacenara el numero ingresado, luego de ser validado.
* \param int reintentos - Cantidad de reintentos para ingresar un dato valido
* \param char* mensaje - Mensaje de informacion para el usuario
* \param char* mensajeError - Mensaje de error en caso de ingresar un valor invalido.
* \return -1 si el puntero int* pNumero/ char* pMensaje/ char* pMensajeError apunta una direccion de memoria NULL.
*          0 OK: si las direcciones de memoria son distintas de NULL y si se valido satisfactoriamente el numero ingresado.
*	      -2 Si se queda sin reintentos
*/
int utn_pedirNumeroIntSinMaxYMin(int* pNumero, int reintentos, char* pMensaje, char* pMensajeError)
{
	int retorno =-1;
	int numeroIngresado;
	int i;
	int salidaScanf;

	if(pNumero!= NULL && reintentos >= 0 && pMensaje!= NULL && pMensajeError != NULL)
	{
		for(i = 0; i <= reintentos; i++)
		{
			printf("\n%s", pMensaje);
			fflush(stdin);
			salidaScanf = scanf("%d", &numeroIngresado);

			if(salidaScanf>0)
			{
				*pNumero = numeroIngresado;
				retorno = 0;
				break;
			}
			else
			{
				printf("\n%s", pMensajeError);
				retorno = -2;
			}
		}
	}
	return retorno;
}

/*
* \brief Pide un numero float al usuario (CON RANGO). Verifica la validez del numero ingresado.
* \param float* pNumero - Direccion de memoria donde se almacenara el numero ingresado, luego de ser validado.
* \param float minimo - Valor Minimo permitido al validar
* \param float maximo - Valor maximo permitido al validar
* \param int reintentos - Cantidad de reintentos para ingresar un dato valido
* \param char* mensaje - Mensaje de informacion para el usuario
* \param char* mensajeError - Mensaje de error en caso de ingresar un valor invalido.
* \return -1 si el puntero float* pNumero/ char* pMensaje/ char* pMensajeError apunta una direccion de memoria NULL.
*          0 OK: si las direcciones de memoria son distintas de NULL y si se valido satisfactoriamente el numero ingresado.
*	      -2 Si se queda sin reintentos
*	      -8 Si el valor minimo no es menor que el maximo.
*/
int utn_pedirNumeroFloatConMaxYMin(float* pNumero, float minimo, float maximo, int reintentos, char* pMensaje, char* pMensajeError)
{
	int retorno =-1;
	float numeroIngresado;
	int i;
	int salidaScanf;

	if(pNumero!= NULL && reintentos >= 0 && pMensaje!= NULL && pMensajeError != NULL)
	{
		retorno = -8;
		if(minimo < maximo)
		{

			for(i = 0; i <= reintentos; i++)
			{
				printf("\n%s", pMensaje);
				fflush(stdin);
				salidaScanf = scanf("%f", &numeroIngresado);

				if(salidaScanf>0 && numeroIngresado >= minimo && numeroIngresado <= maximo)
				{
					*pNumero = numeroIngresado;
					retorno = 0;
					break;
				}
				else
				{
					printf("\n%s", pMensajeError);
					retorno = -2;
				}
			}
		}

	}
	return retorno;
}

/*
* \brief Pide un numero float al usuario (SIN RANGO). Verifica la validez del numero ingresado.
* \param float* pNumero - Direccion de memoria donde se almacenara el numero ingresado, luego de ser validado.
* \param int reintentos - Cantidad de reintentos para ingresar un dato valido
* \param char* mensaje - Mensaje de informacion para el usuario
* \param char* mensajeError - Mensaje de error en caso de ingresar un valor invalido.
* \return -1 si el puntero float* pNumero/ char* pMensaje/ char* pMensajeError apunta una direccion de memoria NULL.
*          0 OK: si las direcciones de memoria son distintas de NULL y si se valido satisfactoriamente el numero ingresado.
*	      -2 Si se queda sin reintentos
*/
int utn_pedirNumeroFloatSinMaxMin(float* pNumero, int reintentos, char* pMensaje, char* pMensajeError)
{
	int retorno =-1;
	float numeroIngresado;
	int i;
	int salidaScanf;

	if(pNumero!= NULL && reintentos >= 0 && pMensaje!= NULL && pMensajeError != NULL)
	{
		for(i = 0; i <= reintentos; i++)
		{
			printf("\n%s", pMensaje);
			fflush(stdin);
			salidaScanf = scanf("%f", &numeroIngresado);

			if(salidaScanf>0)
			{
				*pNumero = numeroIngresado;
				retorno = 0;
				break;
			}
			else
			{
				printf("\n%s", pMensajeError);
				retorno = -2;
			}
		}
	}
	return retorno;
}
