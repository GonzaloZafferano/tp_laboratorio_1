#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this= NULL;
    this = (LinkedList*) malloc (sizeof(LinkedList));

    if(this != NULL)
    {
    	this->size = 0;
    	this->pFirstNode = NULL;
    }
    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 * \param LinkedList* this - Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = this->size;
    }
    return returnAux;
}

/** \brief  Obtiene un nodo de la lista
 * \param LinkedList* this - Puntero a la lista
 * \param int nodeIndex - Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	int i;
	Node* pNodo = NULL;

	if(this != NULL && nodeIndex >=0 && nodeIndex < ll_len(this))
	{
		pNodo = this->pFirstNode;

		for(i = 0; i < nodeIndex; i++)
		{
			pNodo = pNodo->pNextNode;
		}
	}
    return pNodo;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 * \param LinkedList* this - Puntero a la lista
 * \param int nodeIndex - Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}

/** \brief Agrega y enlaza un nuevo nodo a la lista
 * \param LinkedList* this -  Puntero a la lista
 * \param int nodeIndex - Ubicacion donde se agregara el nuevo nodo
 * \param  void* pElement - Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
static int addNode(LinkedList* this, int nodeIndex, void* pElement)
{
	Node* pNodoNuevo;
	Node* pNodoAnterior;
    int returnAux = -1;

    if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
    {
    	pNodoNuevo = (Node*) malloc(sizeof(Node));
    	if(pNodoNuevo != NULL)
    	{
			if(nodeIndex == 0)
			{
				pNodoNuevo->pNextNode = this->pFirstNode;
				this->pFirstNode = pNodoNuevo;
			}
			else
			{
				pNodoAnterior = getNode(this, nodeIndex-1);
				if(pNodoAnterior != NULL)
				{
					pNodoNuevo->pNextNode = pNodoAnterior->pNextNode;
					pNodoAnterior->pNextNode = pNodoNuevo;
				}
			}
			this->size++;
			pNodoNuevo->pElement = pElement;
			returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param LinkedList* this - Puntero a la lista
 * \param int nodeIndex - Ubicacion donde se agregara el nuevo nodo
 * \param  void* pElement - Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int test_addNode(LinkedList* this, int nodeIndex, void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}

/** \brief  Agrega un elemento a la lista
 * \param LinkedList* this - Puntero a la lista
 * \param void* pElement - Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(!addNode(this, ll_len(this), pElement))
    	{
			returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 * \param LinkedList* this - Puntero a la lista
 * \param int index - Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 */
void* ll_get(LinkedList* this, int index)
{
	Node* pNodo;
    void* returnAux = NULL;
    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
    	pNodo = getNode(this, index);
    	if(pNodo != NULL)
    	{
			returnAux = (void*) pNodo->pElement;
    	}
    }
    return returnAux;
}


/** \brief Modifica un elemento de la lista
 * \param LinkedList* this - Puntero a la lista
 * \param int index - Ubicacion del elemento a modificar
 * \param void* pElement - Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int ll_set(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;
    Node* pNode;
    if(this != NULL)
    {
    	pNode = getNode(this, index);
    	if(pNode != NULL)
    	{
    		pNode->pElement = pElement;
    		returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Elimina un elemento de la lista
 * \param LinkedList* this - Puntero a la lista
 * \param int index - Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 */
int ll_remove(LinkedList* this, int index)
{
    int returnAux = -1;
    Node* pNode;
    Node* pNodoAnterior;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
    	pNode = getNode(this, index);
    	if(pNode != NULL)
    	{
			if(index == 0)
			{
				this->pFirstNode = pNode->pNextNode;
			}
			else
			{
				pNodoAnterior = getNode(this, index-1);
				if(pNodoAnterior != NULL)
				{
					pNodoAnterior->pNextNode = pNode->pNextNode;
				}
			}
			free(pNode);
			this->size--;
			returnAux = 0;
    	}
    }
    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 * \param LinkedList* this - Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 */
int ll_clear(LinkedList* this)
{
	int i;
    int returnAux = -1;
    int len;
    if(this != NULL)
    {
    	len = ll_len(this);
    	for( i = 0 ; i < len; i++)
    	{
    		ll_remove(this, 0);
    	}
    	returnAux = 0;
    }
    return returnAux;
}

/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(!ll_clear(this))
    	{
			free(this);
			returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 * \param LinkedList* this - Puntero a la lista
 * \param void* pElement - Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
	int i;
	void* pElementoEnLista;
    int returnAux = -1;
    if(this != NULL)
    {
    	for(i = 0 ; i < ll_len(this); i++)
    	{
    		pElementoEnLista = ll_get(this, i);
    		if(pElementoEnLista == pElement)
    		{
				returnAux = i;
				break;
    		}
    	}
    }
    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 * \param LinkedList* this - Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
    {
    	if(!ll_len(this))
    	{
    		returnAux = 1;
    	}
    	else
    	{
    		if(ll_len(this) > 0)
    		{
    			returnAux = 0;
    		}
    	}
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param LinkedList* this -  Puntero a la lista
 * \param int index - Ubicacion donde se agregara el nuevo elemento
 * \param void* pElement - Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
    	if(!addNode(this, index, pElement))
    	{
			returnAux = 0;
    	}
    }
    return returnAux;
}

/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param LinkedList* this -  Puntero a la lista
 * \param int index - Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;

    if(this != NULL && index >=0 && index <= ll_len(this))
    {
		returnAux = ll_get(this, index);
		ll_remove(this, index);
    }
    return returnAux;
}

/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 * \param LinkedList* this -  Puntero a la lista
 * \param void* pElement - Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
	int i;
    int returnAux = -1;
    if(this != NULL)
    {
    	returnAux = 0;
    	for(i = 0; i < ll_len(this) ; i++)
    	{
    		if(ll_get(this, i) == pElement)
    		{
    			returnAux = 1;
    			break;
    		}
    	}
    }
    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 * \param LinkedList* this -  Puntero a la lista
 * \param LinkedList* this2 -  Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
	int i;
	void* pElemento;
    int returnAux = -1;
    if(this != NULL && this2 != NULL)
    {
    	returnAux = 0;
    	if(ll_len(this) >= ll_len(this2))
    	{
			returnAux = 1;
			for(i = 0; i < ll_len(this); i++)
			{
				pElemento = ll_get(this2, i);
				if(!ll_contains(this, pElemento))
				{
					returnAux = 0;
					break;
				}
			}
    	}
    }
    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 * \param LinkedList* this -  Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
	int i;
	int j = 0;
	void* pElemento;
    LinkedList* cloneArray = NULL;
    if(this != NULL)
    {
    	if(from >= 0 && from < to && to <= ll_len(this))
    	{
			cloneArray = ll_newLinkedList();
			if(cloneArray != NULL)
			{
				for(i = from; i < to; i++)
				{
					pElemento = ll_get(this, i);
					if(!addNode(cloneArray, j, pElemento))
					{
						j++;
					}
				}
			}
    	}
    }
    return cloneArray;
}

/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 * \param LinkedList* this -  Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;
    if(this != NULL)
    {
    	cloneArray = ll_subList(this, 0, ll_len(this));
    }
    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param LinkedList* this - Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas  o a la funcion es NULL, o
 *                       si el parametro Order es invalido. ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int i;
    int limite;
    int retornoFuncion;
    int banderaOrdenado;
    void* pElementoUno;
    void* pElementoDos;
    int returnAux = -1;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
		limite = ll_len(this);
		returnAux = 0;
		do
		{
			banderaOrdenado = 1;
			limite--;
			for(i = 0; i < limite; i++)
			{
				pElementoUno = ll_get(this, i);
				pElementoDos = ll_get(this, i+1);
				retornoFuncion = pFunc(pElementoUno, pElementoDos);

				if((order && retornoFuncion > 0 ) || (!order && retornoFuncion < 0 ))
				{
					ll_set(this, i, pElementoDos);
					ll_set(this, i+1, pElementoUno);
					banderaOrdenado = 0;
				}
			}
		}while(!banderaOrdenado);
    }
    return returnAux;
}

/** \brief Mapea los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param LinkedList* this - Puntero a la lista
 * \param int(*pFunc)(void*) - Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas o a la funcion es NULL
                        ( 0) Si pudo mapear por lo menos un elemento
 */
int ll_map(LinkedList* this, int(*pFunc)(void*))
{
	int retorno = -1;
	void* pAuxiliar;

	if(this != NULL && pFunc != NULL)
	{
		for(int i = 0; i < ll_len(this); i++)
		{
			pAuxiliar = ll_get(this, i);
			if(!pFunc(pAuxiliar))
			{
				retorno = 0;
			}
		}
	}
	return retorno;
}

/** \brief Filtra los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param LinkedList* this - Puntero a la lista
 * \param int(*pFunc)(void*) - Puntero a la funcion criterio
 * \return int Retorna  (-1) Error: si el puntero a la listas o a la funcion es NULL
                        ( 0) Si ok
 */
int ll_filter(LinkedList* this, int (*pFunc)(void*))
{
	int i;
	void* pAuxiliar;
	int retornoFuncionCriterio;
	int retorno = -1;

	if(this != NULL && pFunc != NULL)
	{
		for(i = ll_len(this)-1; i >= 0; i--)
		{
			pAuxiliar = ll_get(this, i);
			retornoFuncionCriterio = pFunc(pAuxiliar);
			if(!retornoFuncionCriterio)
			{
				retorno = ll_remove(this, i);
			}
		}
	}
	return retorno;
}
