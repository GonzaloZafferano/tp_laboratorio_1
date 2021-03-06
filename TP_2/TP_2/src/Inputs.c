/*
 * Inputs.c
 *
 *  Created on: 5 oct 2021
 *      Author: GONZALO
 */

#include "Inputs.h"

#define TRUE 1
#define FALSE 0
#define LEN_BUFFER_STRING 51
#define LEN_BUFFER_INT 16
#define LEN_BUFFER_FLOAT 51
#define REINTENTOS 2
#define DATO_VALIDO 1
#define DATO_INVALIDO 0
#define OPERACION_EXITOSA 0
#define PUNTERO_NULL -1
#define LEN_INVALIDO -2
#define FGETS_NO_PUDO_ASIGNAR_LA_CADENA -3
#define SIN_MAS_REINTENTOS -4
#define REINTENTOS_NEGATIVOS -5
#define MINIMO_ES_MAYOR_QUE_EL_MAXIMO -6
#define ERROR_FUNCION_MYGETS -7
#define ERROR_FUNCION_ES_NUMERO_ENTERO -8
#define ERROR_FUNCION_ES_NOMBRE_O_APELLIDO -9
#define ERROR_FUNCION_ES_NUMERO_FLOAT -10
#define ID_FUERA_DE_RANGO -11
#define I_ES_IGUAL_QUE_J -13
#define NO_SE_PUDO_OBTENER_UNA_RESPUESTA_VALIDA -22
#define I_O_J_ESTA_FUERA_DE_RANGO -23
#define ERROR_AL_INTENTAR_BORRAR_ESPACIOS -24

static int esNumero (char caracter);
static int esSigno (char caracter);
static int esLetra (char caracter);
static int esNombreOApellido (char pCadena [], int largo);
static int darFormatoMayusculaMinuscula(char pNombre[], int len);
static int cambiarTabsPorEspacios(char pCadena[], int len);
static int borrarEspacios(char pCadena[], int len);
static int borrarEspaciosIniciales(char pCadena[], int len, int indiceInicial);
static int borrarEspaciosExtrasIntermedios(char pCadena[], int len);
static int borrarEspaciosFinales(char pCadena[], int len);
static int swapCaracteres(char plistaCaracteres[], int i, int j);
static int esNumeroEntero (char pCadena [], int largo);
static int esNumeroFloat (char pCadena [], int largo);
static int myGets(char pCadena[], int largo, char* pMensaje);

/**
* \brief Evalua si el caracter recibido por parametro corresponde a un numero o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a un numero.
*         retorna 0 (para falso) si el caracter NO corresponde a un numero.
*/
static int esNumero (char caracter)
{
	int retorno = TRUE;

	if(caracter < 48 || caracter > 57) //48 ASCII para el caracter '0' y 57 para '9'
	{
		retorno = FALSE;
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a un signo ('+' o '-') o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a un signo ('+' o '-').
*         retorna 0 (para falso) si el caracter NO corresponde a un signo.
*/
static int esSigno (char caracter)
{
	int retorno = TRUE;

	if(caracter != 43 && caracter != 45) //43 ASCII para el caracter '+' y 45 para '-'
	{
		retorno = FALSE;
	}
	return retorno;
}

/**
* \brief Evalua si el caracter recibido por parametro corresponde a una letra o no.
* \param char caracter - Caracter recibido para evaluar.
* \return retorna un INT, 1 (para verdadero) si el caracter corresponde a una letra.
*         retorna 0 (para falso) si el caracter NO corresponde a una letra.
*/
static int esLetra (char caracter)
{
	int retorno = TRUE;

	if((caracter > 122 || caracter < 97) && (caracter > 90 || caracter < 65))
	{
		retorno = FALSE;
	}
	return retorno;
}

/**
* \brief Obtiene una cadena y verifica si es un nombre o un apellido valido.
* \param char pCadena[] - array de tipo CHAR a evaluar.
* \param int largo - Largo del array de caracteres recibido.
* \return retorna INT. 1 si el dato es valido.
*         retorna  0 si el dato es invalido
*         retorna -1 si la direccion de memoria del puntero es NULL.
*         retorna -2 si la longitud del array es invalida.
*/
static int esNombreOApellido (char pCadena [], int largo)
{
	int i;
	int longitudActual;
	int retorno = PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;

		if(largo > 0)
		{
			retorno = DATO_INVALIDO;

			longitudActual = strnlen(pCadena, largo);

			if(longitudActual > 0)
			{
				retorno = DATO_VALIDO;

				for(i = 0; i < longitudActual; i++)
				{
					if(esLetra(pCadena[i]) == 0 && pCadena[i] != 32)
					{
							retorno = DATO_INVALIDO;
							break;

					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Recibe una cadena de caracteres (previamente validada con solo letras y espacios permitidos)
*        Convierte la primer letra de cada palabra en Mayuscula y el resto en minusculas.
* \param char pNombre[] - Array de caracteres
* \param int len - largo del Array
* \return retorna INT. 0 si esta todo OK.
*         retorna -1 si la direccion de memoria del array es NULL.
*         retorna -2 si el len es invalido.
*/
static int darFormatoMayusculaMinuscula(char pNombre[], int len)
{
	int largo;
	int i=0;
	int retorno = PUNTERO_NULL;

	if(pNombre !=NULL)
	{
		retorno = LEN_INVALIDO;
		if(len >0)
		{
			largo = strnlen(pNombre, len);
			retorno = OPERACION_EXITOSA;

			if(pNombre[i] > 90)
			{
				pNombre[i] = pNombre[i] - 32;
			}

			for(i = 1; i < largo; i++)
			{
				if(pNombre[i] != 32)
				{
					if(pNombre[i] < 97)
					{
						pNombre[i] = pNombre[i] + 32;
					}
				}
				else
				{
					if(pNombre[i+1] > 90)
					{
						pNombre[i+1] = pNombre[i+1] - 32;
						i++;
					}
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Reemplaza los tabs que se encuentre por espacios en blanco.
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return Retorna INT. 0 Si se opero correctamente,
*         retorna -1 si la direccion de memoria del array es NULL,
*         retorna -2 si el len es invalido
*/
static int cambiarTabsPorEspacios(char pCadena[], int len)
{
	int i;
	int largo;
	int retorno = PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_BUFFER_STRING)
		{
			largo = strnlen(pCadena, len);

			retorno = OPERACION_EXITOSA;

			for(i=0; i < largo; i++)
			{
				 if(pCadena[i] == '\t')
				 {
					 pCadena[i] = 32;
				 }
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco (al inicio de la cadena, al final y los extras en el medio)
* 		 Se apoya en 4 funciones para operar correctamente.
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*          retorna -24 si ocurrio un error al intentar borrar los espacios en blanco.
*/
static int borrarEspacios(char pCadena[], int len)
{
	int i = 0;
	int retorno = PUNTERO_NULL;
	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_BUFFER_STRING)
		{
			retorno = ERROR_AL_INTENTAR_BORRAR_ESPACIOS;

			if(cambiarTabsPorEspacios(pCadena, len) == 0)
			{
				if(borrarEspaciosIniciales(pCadena, len,i) == 0)
				{
					if(borrarEspaciosExtrasIntermedios(pCadena, len) == 0)
					{
						if(borrarEspaciosFinales(pCadena, len) == 0)
						{
							retorno = OPERACION_EXITOSA;
						}
					}
				}
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco a partir de la posicion especificada, hasta que detecta una letra
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \param int indiceInicial - Indice a partir del cual empieza a borrar espacios.
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*/
static int borrarEspaciosIniciales(char pCadena[], int len, int indiceInicial)
{
	int largo;
	int i = indiceInicial;
	int j = indiceInicial;
	int banderaHayLetras = 0;
	int retorno = PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;

		if(len > 0 && len <= LEN_BUFFER_STRING)
		{
			largo = strnlen(pCadena, len);

			retorno = OPERACION_EXITOSA;

			for(	;i < largo; i++)
			{
				 if(pCadena[i] != 32)
				 {
					 banderaHayLetras = 1;
					 swapCaracteres(pCadena, i, j);
					 j++;
				 }
				 else
				 {
				  //Si la posicion [i] es igual al caracter 32, y ademas ya detecte una letra,
				  //ROMPO EL BUCLE, porque ya habria acomodado todas las letras a la izquierda.
				  //Ese espacio "intermedio" se deja, porque se interpreta que se utiliza para
				  //separar palabras o nombres.
					 if(banderaHayLetras == 1)
					 {
						 break;
					 }
				 }
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco EXTRAS (mas de 1) que esten en medio de la cadena, hasta que detecta una letra
* \param char pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*/
static int borrarEspaciosExtrasIntermedios(char pCadena[], int len)
{
	int largo;
	int i=0;
	int j=1;
	int retorno = PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;
		if(len > 0 && len <= LEN_BUFFER_STRING)
		{
			retorno = OPERACION_EXITOSA;
			largo =	strnlen(pCadena, len)-1;
			while(i < largo)
			{
				if(pCadena[i] == 32 && pCadena[j] == 32)//Si ambos son espacios en blanco, borro el segundo.
				{
					borrarEspaciosIniciales(pCadena, len, j);//Paso el indice j, para que sea borrado, y salvar el espacio en i.
				}
				i++;
				j++;
			}
		}
	}
	return retorno;
}

/*
* \brief Borra los espacios en blanco que esten al final de la cadena, hasta que detecta una letra
* \param cha pCadena[] - Array de caracteres que contiene la cadena.
* \param int len - largo del array
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -2 si el len es invalido
*/
static int borrarEspaciosFinales(char pCadena[], int len)
{
	int i;
	int retorno = PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;

		if(len > 0 && len <= LEN_BUFFER_STRING)
		{
			i = strnlen(pCadena, len)-1;
			retorno = OPERACION_EXITOSA;

			while (i >= 0)
			{
				if(pCadena[i] == 32) //32 es para el espacio en blanco ' '
				{
					pCadena[i] = '\0';
				}
				else
				{
					break;
				}
				i--;
			}
		}
	}
	return retorno;
}

/*
* \brief intercambia 2 caracteres de posicion en un array de caracteres especificado.
* \param char pCadena[] - Array de caracteres que contiene la cadena.
* \param int i - Indice uno que se intercambiara con el Indice dos
* \param int j - Indice dos que se intercambiara con el indice uno
* \return Retorna INT. 0 Si se opero correctamente,
*          retorna -1 si la direccion de memoria del array es NULL,
*          retorna -13 si el parametro i no es distinto del parametro j.
*          retorna -23 si i o j estan fuera del rango.
*/
static int swapCaracteres(char plistaCaracteres[], int i, int j)
{
	char auxiliar;
	int retorno = PUNTERO_NULL;

	if(plistaCaracteres != NULL)
	{
		retorno = I_O_J_ESTA_FUERA_DE_RANGO;
		if((i >= 0 && i < LEN_BUFFER_STRING) && (j >= 0 && j < LEN_BUFFER_STRING))
		{
			retorno = I_ES_IGUAL_QUE_J;
			if( i != j )
			{
				auxiliar = plistaCaracteres[i];
				plistaCaracteres[i] = plistaCaracteres[j];
				plistaCaracteres[j] = auxiliar;
				retorno = OPERACION_EXITOSA;
			}
		}
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un numero ENTERO VALIDO.
* \param char pCadena [] - Cadena que se evaluara, para determinar si contiene un ENTERO valido.
* \param int largo - Largo del array recibido por parametro.
* \return retorna INT. 1 si el dato es Entero
*         retorna  0 es si el dato es invalido
* 		  retorna -1 si el puntero apunta a una direccion de memoria NULL,
*         retorna -2 si el largo total del array es invalido
*/
static int esNumeroEntero (char pCadena [], int largo)
{
	int longitudActual;
	int i=0;
	int retorno = PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;

		if(largo > 0)
		{
			retorno = DATO_INVALIDO;

			longitudActual = strnlen(pCadena, largo);

			if(longitudActual > 0)
			{
				retorno = DATO_VALIDO;

				if(esSigno(pCadena[0]) == 1 && longitudActual > 1)
				{
					i++;
				}

				for(	; i < longitudActual; i++)
				{
					if(esNumero(pCadena[i]) == 0)
					{
						retorno = DATO_INVALIDO;
						break;
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Verifica si una cadena representa un numero FLOAT VALIDO.
* \param char pCadena [] - Cadena que se evaluara, para determinar si contiene un FLOAT valido.
* \param int largo - Largo del array recibido por parametro.
* \return retorna INT. 1 si el dato es FLOAT
*         retorna  0 es si el dato es invalido
* 		  retorna -1 si el puntero apunta a una direccion de memoria NULL,
*         retorna -2 si el largo total del array es invalido*
*/
static int esNumeroFloat (char pCadena [], int largo)
{
	int longitudActual;
	int i=0;
	int contadorPuntos = 0;
	int retorno = PUNTERO_NULL;

	if(pCadena != NULL)
	{
		retorno = LEN_INVALIDO;

		if(largo > 0)
		{
			retorno = DATO_INVALIDO;

			longitudActual = strnlen(pCadena, largo);
			if(longitudActual > 0)
			{
				retorno = DATO_VALIDO; //todo OK.

				//Para validar un signo '-' o '+', la longitud debe ser necesariamente mayor a 1.
				//Esto es porque el signo ocupa 1 caracter, por lo que la cadena NO PUEDE TENER
				//ESE UNICO CARACTER, debe tener por lo menos 2 (1 ocupado por el signo, y el otro por un digito).
				if(esSigno(pCadena[0]) == 1 && longitudActual > 1 )
				{
					i++;
				}

				for(	;i < longitudActual; i++)
				{
					if(esNumero(pCadena[i]) == 0)
					{
						if(pCadena[i] == 46 && contadorPuntos == 0)//46 para '.'
						{
							contadorPuntos++;
						}
						else
						{
							retorno = DATO_INVALIDO;
							break;
						}
					}
				}
			}
		}
	}
	return retorno;
}

/**
* \brief Recibe un array de caracteres en donde almacenara el texto ingresado por el usuario
*        de forma segura. Elimina el ENTER de la cadena, en caso de haber uno.
* \param char pCadena[] - Cadena de caracteres donde almacenara el texto ingresado por el usuario
* \param int largo - Largo de la cadena de caracteres.
* \return retorna INT. 0 si pudo operar correctamente,
*  		  retorna -1 si el puntero apunta a una direccion de memoria NULL,
*         retorna -2 si el largo total del array es invalido o supera el limite del BufferString.
*         retorna -3 si fgets() no pudo asignar la cadena.
*/
static int myGets(char pCadena[], int largo, char* pMensaje)
{
    int indiceFinalDeCadena;
    char bufferString [LEN_BUFFER_STRING];
    int retorno= PUNTERO_NULL;

    if(pCadena != NULL && pMensaje != NULL)
    {
    	retorno = LEN_INVALIDO;

    	if(largo > 0 && largo <= LEN_BUFFER_STRING)
    	{
    		retorno = FGETS_NO_PUDO_ASIGNAR_LA_CADENA;
    		printf("%s->", pMensaje);
    		fflush(stdin);

			if(fgets(bufferString,largo,stdin) != NULL)
			{
				indiceFinalDeCadena = strnlen(bufferString, largo) -1;

				if(bufferString[indiceFinalDeCadena] == '\n')
				{
					bufferString[indiceFinalDeCadena] = '\0';
				}

				strncpy(pCadena, bufferString, largo);
				retorno = OPERACION_EXITOSA;
			}
    	}
    }
    return retorno;
}

/**
* \brief Obtiene un numero INT del usuario, verificando que sea valido.
* \param int pNumero - Direccion de memoria de la variable INT donde almacenara el numero ingresado por el usuario, una vez validado.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero es NULL,
*         retorna -4 si se quedo sin reintentos
*         retorna -5 si la cantidad de reintentos es Invalida (negativa)
*         retorna -6 si hay un error con los maximos y minimos
*         retorna -7 si hay un error con la funcion mygets().
*         retorna -8 si hay un error con la funcion esNumeroEntero()
*/
int utn_getInt(int* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos)
{
    int i;
    int bufferInt;
    int estadoOperacion;
    int banderaExito = 0; //Asumo que es falso (no hubo exito).
    char bufferCadenaAuxiliar[LEN_BUFFER_INT];
    int retorno = PUNTERO_NULL; //Asumo que hay problema con la direccion de memoria.

    if(pNumero != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
		retorno = REINTENTOS_NEGATIVOS;//Los reintentos son negativos

		if(reintentos >= 0)
		{
			retorno = MINIMO_ES_MAYOR_QUE_EL_MAXIMO;//El minimo es mayor que el maximo.

			if(minimo <= maximo)
			{
				for(i = 0; i <= reintentos; i++)
				{
					estadoOperacion = myGets(bufferCadenaAuxiliar, LEN_BUFFER_INT, pMensaje);

					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						estadoOperacion = esNumeroEntero(bufferCadenaAuxiliar, LEN_BUFFER_INT);
						utn_comprobarEstadoDeOperacion(estadoOperacion);

						if(estadoOperacion == 1)
						{
							bufferInt = atoi(bufferCadenaAuxiliar);

							if(bufferInt >= minimo && bufferInt <= maximo)
							{
								*pNumero = bufferInt;
								banderaExito = 1;
								retorno = OPERACION_EXITOSA;
								break;
							}
						}
						else
						{
							if(estadoOperacion < 0)
							{
								retorno = ERROR_FUNCION_ES_NUMERO_ENTERO;
								break;
							}
						}
						printf("%s\n--Solo se aceptan numeros enteros (dentro del rango %d - %d)--\n", pMensajeError, minimo, maximo);
					}
					else
					{
						retorno = ERROR_FUNCION_MYGETS;
						break;
					}
				}
				if(banderaExito == 0 && estadoOperacion >= 0)
				{
					retorno = SIN_MAS_REINTENTOS;
				}
			}
		}
	}
    return retorno;
}

/**
* \brief Obtiene un numero FLOAT del usuario, verificando que sea valido.
* \param float pNumero - Direccion de memoria de la variable FLOAT donde almacenara el numero ingresado por el usuario, una vez validado.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero es NULL,
*         retorna -4 si se quedo sin reintentos
*         retorna -5 si la cantidad de reintentos es Invalida (negativa)
*         retorna -6 si hay un error con los maximos y minimos
*         retorna -7 si hay un error con la funcion mygets().
*         retorna -10 si hay un error con la funcion esNumeroFloat()
*/
int utn_getFloat(float* pNumero, char* pMensaje, char* pMensajeError, int minimo, int maximo, int reintentos)
{
    int i;
    int estadoOperacion;
    float bufferFloat;
    int banderaExito = 0; //Asumo que es falso (no hubo exito).
    char bufferCadenaAuxiliar[LEN_BUFFER_FLOAT];
    int retorno = PUNTERO_NULL; //Asumo que hay problema con la direccion de memoria.

    if(pNumero != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
		retorno = REINTENTOS_NEGATIVOS;//Los reintentos son negativos

		if(reintentos >= 0)
		{
			retorno = MINIMO_ES_MAYOR_QUE_EL_MAXIMO;//El minimo es mayor que el maximo.

			if(minimo <= maximo)
			{
				for(i = 0; i <= reintentos; i++)
				{
					estadoOperacion = myGets(bufferCadenaAuxiliar,LEN_BUFFER_FLOAT, pMensaje);

					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						estadoOperacion = esNumeroFloat(bufferCadenaAuxiliar, LEN_BUFFER_FLOAT);
						utn_comprobarEstadoDeOperacion(estadoOperacion);

						if(estadoOperacion == 1)
						{
							bufferFloat = atof(bufferCadenaAuxiliar);

							if(bufferFloat >= minimo && bufferFloat <= maximo)
							{
								*pNumero = bufferFloat;
								banderaExito = 1;
								retorno = OPERACION_EXITOSA;
								break;
							}
						}
						else
						{
							if(estadoOperacion < 0)
							{
								retorno = ERROR_FUNCION_ES_NUMERO_FLOAT;
								break;
							}
						}
						printf("%s\n", pMensajeError);
					}
					else
					{
						retorno = ERROR_FUNCION_MYGETS;
						break;
					}
				}

				if(banderaExito == 0 && estadoOperacion >= 0)
				{
					retorno = SIN_MAS_REINTENTOS;
				}
			}
		}
	}
    return retorno;
}

/**
* \brief Obtiene un nombre o apellido del usuario. Evalua si es valido.
* \param char pCadena[] - Direccion de memoria de la variable CHAR donde almacenara el dato ingresado por el usuario, una vez validado.
* \param int largo - Largo de la cadena de caracteres.
* \param char* pMensaje - Mensaje informativo al usuario
* \param char* pMensajeError - Mensaje en caso de ingresar un dato invalido
* \param int reintentos - Reintentos en caso de ingresar datos invalidos
* \return retorna INT. 0 si pudo operar correctamente
*         retorna -1 si el puntero es NULL,
*         retorna -2 si la longitud del array es negativa o 0.
*         retorna -4 si se quedo sin reintentos
*         retorna -5 si la cantidad de reintentos es Invalida (negativa)
*         retorna -7 si hay un error con la funcion mygets().
*         retorna -9 si hay un error con la funcion esNombreOApellido()
*/
int utn_getNombreOApellido(char pCadena[], int largo, char* pMensaje, char* pMensajeError, int reintentos)
{
    int i;
    int estadoOperacion;
    int banderaExito = 0;
    char bufferCadenaAuxiliar[LEN_BUFFER_STRING];
    int retorno = PUNTERO_NULL;

    if(pCadena != NULL && pMensaje != NULL && pMensajeError != NULL)
	{
    	retorno = LEN_INVALIDO;
    	if(largo > 0 && largo <= LEN_BUFFER_STRING)
    	{
			retorno = REINTENTOS_NEGATIVOS;

			if(reintentos >= 0)
			{
				for(i = 0; i <= reintentos; i++)
				{
					estadoOperacion = myGets(bufferCadenaAuxiliar,LEN_BUFFER_STRING, pMensaje);

					if(utn_comprobarEstadoDeOperacion(estadoOperacion))
					{
						borrarEspacios(bufferCadenaAuxiliar, LEN_BUFFER_STRING);

						estadoOperacion = esNombreOApellido(bufferCadenaAuxiliar, LEN_BUFFER_STRING);
						utn_comprobarEstadoDeOperacion(estadoOperacion);

						if(estadoOperacion == 1)
						{
							estadoOperacion = darFormatoMayusculaMinuscula(bufferCadenaAuxiliar, LEN_BUFFER_STRING);
							if(utn_comprobarEstadoDeOperacion(estadoOperacion))
							{
								strncpy(pCadena, bufferCadenaAuxiliar, largo);
								banderaExito = 1;
								retorno = OPERACION_EXITOSA;
								break;
							}
						}
						else
						{
							if(estadoOperacion < 0)
							{
								retorno = ERROR_FUNCION_ES_NOMBRE_O_APELLIDO;
								break;
							}
						}
						printf("%s\n", pMensajeError);
					}
					else
					{
						retorno = ERROR_FUNCION_MYGETS;
						break;
					}
				}

				if(banderaExito == 0 && estadoOperacion == 0)
				{
					retorno = SIN_MAS_REINTENTOS;
				}
			}
		}
	}
    return retorno;
}

/*
* \brief Toma el Id del empleado con el que se quiere operar.
* \param int idMaximo - Id mas alto generado hasta el momento
* \return Retorna INT. Retorna un numero positivo que es el ID ingresado por el usuario,
*         retorna -11 si no se pudo tomar el dato del Id.
*/
int tomarID(int idMaximo)
{
	int id;
	int estadoOperacion;
	int retorno = ID_FUERA_DE_RANGO;

	estadoOperacion = utn_getInt(&id, "\nIngrese Id", "Error, Id invalido.", 0, idMaximo, REINTENTOS);
	if(utn_comprobarEstadoDeOperacion(estadoOperacion))
	{
		retorno = id;
	}
	return retorno;
}

/*
* \brief Solicita el ingreso de una opcion al usuario. Requiere maximo y minimo.
* \param int* opcion - retorna a traves de este parametro la opcion seleccionada
* \param int minimo - minimo valor de la opcion
* \param int maximo - maximo valor de la opcion
* \return retorna INT. Retorna un numero positivo que representa la opcion seleccionada.
* 		  retorna   0 si esta OK.
* 		  retorn   -1 si el puntero apunta a una direccion de memoria NULL
*         retorna  -6 si el minimo es mayor que el maximo.
*         retorna -22 si no se pudo obtener una respuesta valida.
*/
int ingreseUnaOpcion(int* opcion, int minimo, int maximo)
{
	int estadoOperacion;
	int retorno = PUNTERO_NULL;

	if(opcion != NULL)
	{
		retorno = MINIMO_ES_MAYOR_QUE_EL_MAXIMO;
		if(minimo <= maximo)
		{
			retorno = NO_SE_PUDO_OBTENER_UNA_RESPUESTA_VALIDA;
			 estadoOperacion = utn_getInt(opcion, "\nIngrese una opcion", "Error. Opcion invalida.", minimo, maximo, REINTENTOS);
			 if(utn_comprobarEstadoDeOperacion(estadoOperacion))
			 {
				 retorno = OPERACION_EXITOSA;
			 }
		}
	}
	return retorno;
}
