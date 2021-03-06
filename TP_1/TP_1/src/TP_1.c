/*
 ============================================================================
 Name        : TP_1.c
 Author      : Gonzalo Zafferano
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "utn_operacionesMatematicas.h"
#include "utn_pedirDatos.h"
#include "utn_comprobaciones.h"
#include "utn_bibliotecaTpUno.h"

#define CANTIDAD_RESULTADOS_OPERACIONES 6
#define VALOR_INICIAL_ARRAY 0.0
#define CERRAR_APLICACION 5
#define OPCIONES_MINIMO_MENU 1
#define OPCIONES_MAXIMO_MENU 5
#define REINTENTOS_MENU 2

int main(void)
{
	setbuf(stdout,NULL);
	float numeroUno;
	float numeroDos;
	int opcion;
	int estadoOperacion;
	int estadoActualNumeros;
	int estadoPrimerNumero=1;
	int estadoSegundoNumero=1;
	int banderaParaRealizarOperaciones=1;
	int banderaMenu = 1;
	int banderaOperarNuevamente = 0;
	float listaResutadosOperaciones [CANTIDAD_RESULTADOS_OPERACIONES];

 	estadoOperacion = utn_inicializarArray(listaResutadosOperaciones, CANTIDAD_RESULTADOS_OPERACIONES, VALOR_INICIAL_ARRAY);

 	//Si se pudo inicializar correctamente el array, se puede proceder con la aplicacion.
 	//Si hay un error con la direccion de memoria, o la longitud del array es 0 (o menor), se finaliza el programa.
 	if(utn_comprobarEstadoDeOperacion(estadoOperacion) == 0)
 	{
		printf("\t-- B I E N V E N I D O  --  ");

		do
		{
			utn_imprimirMenu(estadoPrimerNumero, estadoSegundoNumero, banderaMenu, numeroUno, numeroDos);
			banderaMenu = 0;
			estadoOperacion = utn_pedirNumeroIntConMaxYMin(&opcion, OPCIONES_MINIMO_MENU, OPCIONES_MAXIMO_MENU, REINTENTOS_MENU,"Por favor, ingrese una opcion valida...", "-----Error. Opcion invalida-----");

			//Si hay un problema para tomar datos, o se acaban los reintentos para elegir
			//una opcion valida del Menu, no tiene sentido continuar el programa.
			if(utn_comprobarEstadoDeOperacion(estadoOperacion) != 0)
			{
				opcion = CERRAR_APLICACION;
			}
			else
			{
				if(opcion != CERRAR_APLICACION)
				{
					switch(opcion)
					{
						case 1:
							//Primero guardo el estado actual del primer operando.
							estadoActualNumeros = estadoPrimerNumero;

							//Al ingresarse correctamente el numero, pedir Float retorna un 0.
							//de esta forma, se asigna el primer estado con 0 (necesario para la opcion 3)
							estadoPrimerNumero = utn_pedirNumeroFloatSinMaxMin(&numeroUno, 2, "Por favor, ingrese el numero para Operando A...", "-----ERROR. Dato invalido-----");

							//La unica forma de entrar en este IF, es que se haya ingresado el operando A correctamente,
							//y que se hayan realizado las operaciones (opcion 3) por lo menos una vez, ya que en la opcion 3
							//se asigna la bandera para realizar operaciones en 0.
							if(utn_comprobarEstadoDeOperacion(estadoPrimerNumero) == 0 && banderaParaRealizarOperaciones == 0)
							{
								//Estar dentro del IF, significa que se realizaron las operaciones (opcion 3) pero se volvio a
								//ingresar un operando A. Por lo que no puedo mostrar los resultados (opcion 4) sin antes ACTUALIZAR
								//la opcion 3 nuevamente.

								banderaParaRealizarOperaciones = 2;
								banderaOperarNuevamente = 0;

								//Al cambiar la bandera de operaciones, asignandole un 2, NO SE PUEDEN
								//mostrar los resultados (requiere que la bandera sea 0). Esto obliga a que se vuelva a ingresar
								//la opcion 3, que es donde la bandera se asigna a 0, habilitando la muestra. De paso, se actualizan
								//las operaciones con los nuevos operandos.
							}
							else
							{
								if(estadoPrimerNumero < 0 )
								{
									//Si el estado del primer numero es negativo, significa que hubo un error al pedir
									//datos al usuario (error con la direccion de memoria o los reintentos).

									//No es deseable perder el estado del primer numero. Solo puede ser 1 o 0, para determinar el
									//mensaje que se imprimira del menu.
									//(Si es 1, aun no se ingreso ningun numero, si es 0, se ingreso correctamente un numero).
									//Por eso, ante un error, volvemos a asignar el valor 1 o 0 que tenia antes de ingresar al CASE.
									estadoPrimerNumero = estadoActualNumeros;
								}
							}
							break;

						case 2:
							estadoActualNumeros = estadoSegundoNumero;//Se guarda el estado actual del segundo operando

							//Al ingresarse correctamente el numero, pedir Float retorna un 0.
							//de esta forma, se inicializa el segundo estado con 0 (necesario para la opcion 3)
							estadoSegundoNumero  = utn_pedirNumeroFloatSinMaxMin(&numeroDos, 2, "Por favor, ingrese el numero para Operando B...", "-----ERROR. Dato invalido-----");

							if(utn_comprobarEstadoDeOperacion(estadoSegundoNumero) == 0 && banderaParaRealizarOperaciones == 0)
							{
								banderaParaRealizarOperaciones = 2;
								banderaOperarNuevamente = 0;
							}
							else
							{
								if(estadoSegundoNumero < 0)
								{
									estadoSegundoNumero = estadoActualNumeros;
								}
							}
							break;

						case 3:

							if(utn_comprobarEstadoDeOperacion(banderaOperarNuevamente)==0)
							{
								//La unica forma de realizar las operaciones, es que utn_comprobarNumeroUnoYNumeroDos() retorne 0.
								//Para que eso suceda, ambos estados (numero uno y numero dos) deben haber sido inicializados.
								 estadoOperacion = utn_comprobarNumeroUnoYNumeroDos(estadoPrimerNumero, estadoSegundoNumero);

								 if(utn_comprobarEstadoDeOperacion(estadoOperacion) == 0)
								 {
									 estadoOperacion = utn_realizarOperaciones(numeroUno, numeroDos, listaResutadosOperaciones, CANTIDAD_RESULTADOS_OPERACIONES);

									//Si el programa detecta que hay un error, no puede realizar operaciones,
									//por lo tanto tampoco puede mostrar los resultados.
									//Solo se podrian ingresar numeros pero no operar con ellos, por lo
									//que piede sentido continuar el programa. Se cierra con la opcion 5.
									if(utn_comprobarEstadoDeOperacion(estadoOperacion) != 0)
									{
										opcion = CERRAR_APLICACION;
									}

									 //Si no hubo problemas con la funcion utn_realizarOperaciones(),
									 //la variable estadoOperacion sera 0, y se informara
									 //que se realizaron las operaciones.
									 if(estadoOperacion == 0)
									 {
										 printf("\n\t<--Operaciones realizadas. Ya se pueden informar los resultados (opcion 4).-->\n");
										 banderaParaRealizarOperaciones = 0;
										 //Aqui se asigna 0 en la bandera de operaciones, habilitando la muestra de resultados.
									 }

									 banderaOperarNuevamente = 3;
									 //En el codigo de errores, el 3 indica que ya se realizaron los calculos.
									 //Para volver a calcular se debe actualizar uno o ambos operandos.
									 //De esta forma se evita calcular nuevamente si no se actualizaron los operandos.
								}
							}
							break;

						case 4:
							//Para mostrar los resultados, la bandera de operaciones DEBE estar en 0.
							//El unico sector donde la bandera se asigna en 0, es en la opcion 3.
							//Es decir, primero debe pasar por la opcion 3, para luego mostrar los resultados.
							if(utn_comprobarPosibilidadDeMostrarResultados(banderaParaRealizarOperaciones)==0)
							{
								estadoOperacion = utn_imprimirResultados(numeroUno, numeroDos, listaResutadosOperaciones, CANTIDAD_RESULTADOS_OPERACIONES);
								utn_comprobarEstadoDeOperacion(estadoOperacion);
							}
							break;
					}
				}
			}
		}while( opcion != CERRAR_APLICACION);
 	}


	printf("\n\t<--Fin del Programa-->");

	return EXIT_SUCCESS;
}

