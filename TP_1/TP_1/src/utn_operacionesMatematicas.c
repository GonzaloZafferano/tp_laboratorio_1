/*
 * utn_operacionesMatematicas.c
 *
 *  Created on: 23 sept 2021
 *      Author: GONZALO
 */


#include "utn_operacionesMatematicas.h"

/*
* \brief Realiza la suma de dos numeros
* \param float numeroUno - Primer numero para operar
* \param float numeroDos - Segundo numero para operar
* \param float* pResultado - Direccion de memoria donde se almacenara el resultado de la suma
* \return -1 si la direccion de memoria de float* pResultado es NULL
*          0 OK: si la direccion de memoria es distinto de NULL y pudo operar satisfactoriamente.
*
*/
int utn_operacionSumar(float numeroUno, float numeroDos, float* pResultado)
{
	int retorno = -1;

	if(pResultado != NULL)
	{
		*pResultado = numeroUno + numeroDos;
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Realiza la resta de dos numeros
* \param float numeroUno - Primer numero para operar
* \param float numeroDos - Segundo numero para operar
* \param float* pResultado - Direccion de memoria donde se almacenara el resultado de la resta
* \return -1 si la direccion de memoria de float* pResultado es NULL
*          0 OK: si la direccion de memoria es distinto de NULL y pudo operar satisfactoriamente.
*/
int utn_operacionRestar(float numeroUno, float numeroDos, float* pResultado)
{
	int retorno = -1;

	if(pResultado != NULL)
	{
		*pResultado = numeroUno - numeroDos;
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Realiza la multiplicacion de dos numeros
* \param float numeroUno - Primer numero para operar
* \param float numeroDos - Segundo numero para operar
* \param float* pResultado - Direccion de memoria donde se almacenara el resultado de la multiplicacion
* \return -1 si la direccion de memoria de float* pResultado es NULL
*          0 OK: si la direccion de memoria es distinto de NULL y pudo operar satisfactoriamente.
*/
int utn_operacionMultiplicar(float numeroUno, float  numeroDos, float* pResultado)
{
	int retorno = -1;

	if(pResultado != NULL)
	{
		*pResultado = numeroUno * numeroDos;
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Verifica si es posible realizar la division de dos numeros, y la ejecuta en caso serlo.
* \param float numeroUno - Primer numero para operar
* \param float numeroDos - Segundo numero para operar
* \param float* pResultado - Direccion de memoria donde se almacenara el resultado de la division
* \return -1 si la direccion de memoria de float* pResultado es NULL.
*          0 OK: si la direccion de memoria es distinto de NULL y pudo operar satisfactoriamente.
*         -6 si no pudo realizar la operacion (segundo parametro para operar es 0)
*/
int utn_operacionDividir(float numeroUno, float  numeroDos, float* pResultado)
{
	int retorno = -1;

	if(pResultado != NULL)
	{
		if(numeroDos != 0.0)
		{
			*pResultado = numeroUno / numeroDos;
			retorno = 0;
		}
		else
		{
			retorno = -6; //Retorna -6 si el segundo numero es 0
		}
	}
	return retorno;
}

/*
* \brief Verifica si un numero es entero.
* \param float numero - Numero a evaluar.
* \return 1 si el numero es entero.
*         0 si el numero no es entero.
*/
int utn_esEntero(float numeroOriginal)
{
	int retorno = 1;
	int parteEntera = (int)numeroOriginal;

	if(numeroOriginal - parteEntera != 0) //Si la resta NO ES 0, entonces hay decimales, y el numero NO ES ENTERO.
	{
		retorno = 0;
	}
	return retorno;
}

/*
* \brief Realiza el factorial de un numero entero POSITIVO. Esta funcion no opera con numeros negativos ni decimales.
* 		 En caso de recibir un decimal o negativo, guardara 0 en la variable destino.
* \param float numeroUno - Numero para operar
* \param int* pResultado - Direccion de memoria donde se almacenara el resultado de la operacion Factorial
* \return -1 si la direccion de memoria de float* pResultado es NULL
*          0 OK: si la direccion de memoria es distinto de NULL y pudo operar satisfactoriamente.
*		  -9 si el numero ingresado es NEGATIVO.
*		  -10 si el numero ingresado tiene parte decimal.
*		  -11 Si el operando es mayor a 12 (limite de esta calculadora).
*/
int utn_operacionCalcularFactorial(float numeroIngresado, float* pResultado)
{
	int i;
	int numeroEntero;
	int retorno = -1; //Asumo que hay un error con la direccion de memoria de los parametros.
	int acumulador = 1;

	if(pResultado != NULL)
	{
		retorno = -10; //Asumo que va a ser un numero con decimal.
		*pResultado = 0.0;
		//Si el numero es negativo o decimal, se almacena un 0 en el *pResultado. Se eligio el valor 0 por defecto, ya que ningun factorial da 0.

		if(numeroIngresado < 0.0)
		{
			retorno = -9; //Si es negativo, retorno el error por el lado de los negativos.
		}
		else
		{
			retorno = -11; //Asumo que sera mayor que 12 (lo cual no podria calcular)

			if(numeroIngresado <= 12)
			{
				if(utn_esEntero(numeroIngresado)) //Si entra en este IF, el numero es Positivo y Entero. Entonces puedo retornar 0.
				{
					numeroEntero = (int)numeroIngresado; //Casteo a INT para trabajar

					if(numeroEntero == 0)
					{
						*pResultado = 1; //El factorial de 0 es 1.
					}
					else
					{
						for(i = 1; i <= numeroEntero; i++)
						{
							acumulador = acumulador * i;
						}
						*pResultado = acumulador;
					}
					retorno= 0;
				}
			}
		}
	}
	return retorno;
}




