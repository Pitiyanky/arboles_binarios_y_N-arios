/*
Copyright © 2023 Jesus Machado

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation
files (the “Software”), to deal in the Software without restriction, including without limitation the rights to use, copy,
modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software
is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

This code was developed as an assessment for the University of Carabobo. The author is Jesus Machado and can be contacted at jesusdmpianist@hotmail.com.
 */

#ifndef ARBOL_B
#define ARBOL_B
#include "NodoBinario.hpp"
#include <list>
#include <climits>

using namespace std;
template <class T> class ArbolB
{
    private:
        NodoBinario<T> *raiz;
	public:
		ArbolB(){raiz = NULL;};
		ArbolB(NodoBinario<T> *a){this->raiz = a;};
		ArbolB(T e , ArbolB<T> hi , ArbolB<T> hd);
		ArbolB(const ArbolB<T> &);
		~ArbolB();
		void cargarPreIn(list<T> & ,  list<T> &);
		void cargarPostIn(list<T> & ,  list<T> &);
		int getMayorElemento();
		int getMenorElemento();
        list<T> preOrden();
		list<T> inOrden();
		list<T> postOrden();
		list<T> porNiveles();
		int altura();
		int numNodos();
		bool esABB();
		T 	getRaiz(){return this->raiz->getElemento();};
		bool esNulo(){return this->raiz == NULL;};
        bool esHoja(){return (this->raiz!=NULL && this->raiz->getIzq() == NULL && this->raiz->getDer() == NULL);};
        bool esAVL();
		ArbolB<T> obtHijoIzq();
		ArbolB<T> obtHijoDer();
		list<T> BFS_niveles(int n , int m);
		void operator = (const ArbolB<T> &l);
		int diametro();
		bool completo();
		bool lleno();
		bool isomorfo(ArbolB<T> &);
		void setHijoIzq(ArbolB<T> &);
		void setHijoDer(ArbolB<T> &);
        void setRaiz(T e){this->raiz->setElemento(e);};
        bool operator == (const ArbolB<T> &);
    private:
        void esAVL(NodoBinario<T> *,int &, int, int, bool &AVL);
        bool iguales(NodoBinario<T> * , NodoBinario<T> *);
        void copiar(NodoBinario<T> *&a , NodoBinario<T> &b);
        void vaciar(NodoBinario<T> *);
        void menor(NodoBinario<T> * ,int &);
        void mayor(NodoBinario<T> * ,int &);
        void preOrden(NodoBinario<T> * , list<T> &);
        void inOrden(NodoBinario<T> * ,list<T> &);
        void postOrden(NodoBinario<T> * , list<T> &);
        int altura(NodoBinario<T> *);
        bool esABB(NodoBinario<T> * , int minimo ,int maximo);
        int numNodos(NodoBinario<T> *);
        bool completo(NodoBinario<T> * );
        bool isomorfo(NodoBinario<T> * , NodoBinario<T> *);
        NodoBinario<T> * copiarNodos(NodoBinario<T> *a);
        NodoBinario<T> * leerPreOrdenInOrden( list<T> & ,  list<T> &);
        NodoBinario<T> * leerPostOrdenInOrden( list<T> & ,  list<T> &);
        int re_di(NodoBinario<T> * , int &);
};



template <class T>
void ArbolB<T>:: setHijoIzq(ArbolB<T> &a)
{
    // Este método asigna el subárbol izquierdo de este árbol binario con una copia de otro árbol binario dado como parámetro.
    // Recibe una referencia al otro árbol binario a copiar.
    // Utiliza un método auxiliar que recibe un puntero a un nodo raíz y devuelve una copia de ese nodo y sus subárboles.
    // Si este árbol está vacío, no hace nada.
    // Si este árbol tiene un nodo raíz, llama al método auxiliar con el nodo raíz del otro árbol y asigna el resultado al subárbol izquierdo de este árbol.
	if(this->raiz == NULL){
        return;
    }else{
        this->raiz->getIzq() = this->copiarNodos(a.raiz);
    }

}
template <class T>

void ArbolB<T>:: setHijoDer(ArbolB<T> &a)
{
    // Este método asigna el subárbol derecho de este árbol binario con una copia de otro árbol binario dado como parámetro.
    // Recibe una referencia al otro árbol binario a copiar. // Utiliza un método auxiliar que recibe un puntero a un nodo raíz y devuelve una copia de ese nodo y sus subárboles.
    // Si este árbol está vacío, no hace nada.
    // Si este árbol tiene un nodo raíz, llama al método auxiliar con el nodo raíz del otro árbol y asigna el resultado al subárbol derecho de este árbol
	if(this->raiz == NULL){
        return;
    }else{
        this->raiz->getDer() = this->copiarNodos(a.raiz);
    }

}
template <class T>
ArbolB<T>::ArbolB(T e , ArbolB<T> hi , ArbolB<T> hd)
{
    // Este constructor crea un nuevo árbol binario con un valor dado y dos subárboles dados como parámetros.
    // Recibe un valor de tipo T para el nodo raíz y dos referencias a otros árboles binarios para los subárboles izquierdo y derecho.
    // Utiliza un método auxiliar que recibe un puntero a un nodo raíz y devuelve una copia de ese nodo y sus subárboles.
    // Crea un nuevo nodo con el valor dado y las copias de los nodos raíz de los subárboles dados y lo asigna al nodo raíz de este árbol
	this->raiz = new NodoBinario<T>(e , this->copiarNodos(hi.raiz) ,this->copiarNodos(hd.raiz));
}

template <class T>
bool ArbolB<T>::isomorfo(NodoBinario<T> *arbolA , NodoBinario<T> *arbolB)
{
    // Este método devuelve si dos árboles binarios son isomorfos, es decir, si tienen la misma forma pero pueden tener diferentes valores en sus nodos.
    // Recibe dos punteros a los nodos raíz de los árboles a comparar.
    // Utiliza un enfoque recursivo para verificar si los subárboles izquierdo y derecho de cada nodo son isomorfos entre sí, o si se pueden obtener intercambiando los subárboles izquierdo y derecho de uno de los nodos.
    // Si ambos árboles son nulos, devuelve verdadero.
    // Si uno de los árboles es nulo y el otro no, devuelve falso.
    // Si ambos árboles tienen nodos no nulos, llama al método recursivamente con las combinaciones de subárboles correspondientes y devuelve el resultado lógico de las llamadas.

	if(arbolA == NULL && arbolB == NULL){
        return true;
    }else{
        if((arbolA == NULL && arbolB != NULL) || (arbolA != NULL && arbolB == NULL)){
            return false;
        }else{
            return isomorfo(arbolA->getIzq() , arbolB->getDer()) && isomorfo(arbolA->getIzq() , arbolB->getDer()) || isomorfo(arbolB->getIzq() , arbolB->getIzq()) && isomorfo(arbolA->getDer() , arbolB->getDer());
        }
    }

}

template <class T>
bool ArbolB<T>::isomorfo(ArbolB<T> &a)
{
    // Este método devuelve si este árbol binario es isomorfo a otro árbol binario dado como parámetro.
    // Recibe una referencia al otro árbol binario a comparar.
    // Utiliza el método auxiliar recursivo que recibe dos punteros a los nodos raíz de los árboles a comparar y verifica si son isomorfos entre sí.
    // Llama al método auxiliar con los nodos raíz de este árbol y del otro árbol y devuelve el resultado.
	return this->isomorfo(this->raiz , a.raiz);
}

template <class T>
bool ArbolB<T>::lleno()
{   // Este método devuelve si el árbol binario está lleno, es decir, si todos sus niveles están llenos y no hay ningún nodo con un solo hijo o sin hijos.
    // Utiliza dos métodos auxiliares que calculan el número de nodos y la altura del árbol o subárbol dado un nodo raíz.
    // Compara el número de nodos con la fórmula 2^h - 1, donde h es la altura del árbol, que es el número máximo de nodos que puede tener un árbol binario de altura h.
	return this->numNodos(this->raiz) == (1 << this->altura(this->raiz)) - 1; // 2^h - 1
}

template <class T>
bool ArbolB<T>::completo()
{
    // Este método devuelve si el árbol binario está completo, es decir, si todos sus niveles están llenos excepto posiblemente el último, y los nodos del último nivel están alineados a la izquierda.
    // Utiliza un método auxiliar recursivo que recibe el nodo raíz del árbol o subárbol y verifica si cumple con la condición de completitud.
    // Si el árbol está vacío, devuelve verdadero.
	return this->completo(this->raiz);
}

template <class T>
bool ArbolB<T>::completo(NodoBinario<T> *base)
{
    /*
    Este método verifica y devuelve si el árbol binario está completo, es decir, si todos sus niveles están llenos excepto posiblemente el último, y los nodos del último nivel están alineados a la izquierda.
    Utiliza un recorrido en anchura o BFS (Breadth-First Search) para visitar los nodos del árbol por niveles y comprobar si hay algún nodo con un solo hijo o sin hijos antes de llegar al último nivel.
    Si el árbol está vacío, devuelve verdadero.
    @return verdadero si el árbol está completo, falso en caso contrario
     */

	if(base == NULL || (base->getIzq() == NULL && base->getDer() == NULL)){
        return true;
    }else{
        if((base->getIzq() != NULL && base->getDer() == NULL) || (base->getIzq()== NULL && base->getDer() != NULL)){
            return false;
        }else{
            return completo(base->getIzq()) && completo(base->getDer());
        }
    }

}

template <class T>
int ArbolB<T>::re_di(NodoBinario<T> *base , int &mejor)
{
    /*
    Este método calcula y devuelve el diámetro del árbol binario, es decir, la longitud del camino más largo entre dos nodos del árbol.
    Utiliza un enfoque recursivo para obtener la altura de cada subárbol y luego compararla con el diámetro máximo actual.
    El diámetro de un subárbol es la suma de las alturas de sus subárboles izquierdo y derecho más uno.
    Si el árbol está vacío, devuelve cero.
    @return: el diámetro del árbol binario
     */
	if(base == NULL){
        return 0;
    }else{
        int getIzq =re_di(base->getIzq() , mejor);
        int getDer =re_di(base->getDer() , mejor);
        mejor = max(mejor , getIzq + getDer);
        return max(getIzq , getDer) + 1;
    }
}

template <class T>
int ArbolB<T>::diametro()
{
    // Este método calcula el diámetro de un árbol binario
    // El diámetro es la longitud del camino más largo entre dos hojas del árbol
    // El método usa una función auxiliar re_di que recibe la raíz del árbol y una variable por referencia que almacena el mejor diámetro encontrado hasta el momento
    // La función re_di devuelve la altura del subárbol que tiene como raíz al nodo pasado como parámetro
    // La función re_di actualiza el mejor diámetro si la suma de las alturas de los subárboles izquierdo y derecho es mayor que el valor actual
    // El método devuelve el valor del mejor diámetro al final
	int mejor = 0;
	this->re_di(this->raiz , mejor);
	return mejor;
}

template <class T>
void ArbolB<T>::operator = (const ArbolB<T> &l)
{
    // Este operador sobrecarga el operador = para asignar un árbol binario a otro
    // El operador recibe como parámetro una referencia constante a otro árbol binario
    // El operador llama a una función auxiliar copiarNodos que recibe la raíz del otro árbol y devuelve una copia de sus nodos
    // El operador asigna el resultado de la función copiarNodos a la raíz del árbol actual
	this->raiz = this->copiarNodos(l.raiz);
}
template <class T>
bool ArbolB<T>::operator == (const ArbolB<T> &arbol2)
{
    // Este operador sobrecarga el operador == para comparar dos árboles binarios
    // El operador recibe como parámetro una referencia constante a otro árbol binario
    // El operador llama a una función auxiliar iguales que recibe la raíz del otro árbol y devuelve si los dos árboles son iguales
    return this->iguales(this->raiz , arbol2.raiz);
}
template <class T>
bool ArbolB<T>::iguales(NodoBinario<T> *arbol1 , NodoBinario<T> *arbol2){
    /*
     * Este método verifica y devuelve si dos árboles binarios son iguales, es decir, si tienen la misma estructura y los mismos valores en los nodos.
     * Utiliza un enfoque recursivo para comparar los nodos de los dos árboles.
     * Si los dos árboles están vacíos, devuelve verdadero.
     * Si uno de los dos árboles está vacío, devuelve falso.
     * Si los dos árboles no están vacíos, devuelve verdadero si los valores de los nodos son iguales y los subárboles izquierdo y derecho son iguales.
     */
    if(arbol1 == NULL && arbol2 == NULL){
        return true;
    }else{
        if(arbol1 == NULL || arbol2 == NULL){
            return false;
        }else{
            return arbol1->getElemento() == arbol2->getElemento() && iguales(arbol1->getIzq() , arbol2->getIzq()) && iguales(arbol1->getDer() , arbol2->getDer());
        }
    }
}
template <class T>
list<T> ArbolB<T>::BFS_niveles(int n , int m)
{
    /*
    Este método realiza un recorrido en anchura o BFS (Breadth-First Search) del árbol binario y devuelve una lista con los valores de los nodos agrupados por niveles.
    Utiliza una cola auxiliar para almacenar los nodos del árbol y visitarlos en el orden de su nivel, de izquierda a derecha.
    Utiliza una variable para llevar el control del número de nodos en cada nivel y otra para almacenar los valores de los nodos en una lista temporal.
    Si el árbol está vacío, devuelve una lista vacía.
    @return: una lista de listas con los valores de los nodos en recorrido BFS agrupados por niveles
     */

	list<int> pos;
	list<NodoBinario<T> *> niv;
	int aux_pos;
	NodoBinario<T> *aux;
	list<T> re;

	niv.push_back(this->raiz);
	pos.push_back(0);
	while(!niv.empty() && pos.front() <= m)
	{
		aux = niv.front();
		niv.pop_front();
		aux_pos = pos.front();
		pos.pop_front();
		if(aux_pos >= n && aux_pos <= m)
			re.push_back(aux->getElemento());
		if(aux->getIzq() != NULL)
		{
			niv.push_back(aux->getIzq());
			pos.push_back(aux_pos + 1);
			
		}
		if(aux->getDer() != NULL)
		{
			niv.push_back(aux->getDer());
			pos.push_back(aux_pos + 1);
		}
	}
	return re;
}
template <class T>
ArbolB<T>::~ArbolB()
{
    // Este es el destructor del árbol binario
    // El destructor llama a una función auxiliar vaciar que recibe la raíz del árbol y libera la memoria de todos sus nodos
    // La función vaciar recorre el árbol en postorden y elimina cada nodo después de eliminar sus hijos
	this->vaciar(this->raiz);
}

template <class T>
void ArbolB<T>::vaciar(NodoBinario<T>* a)
{
    /*
    Este método elimina todos los nodos del árbol binario y lo deja vacío.
    Utiliza un enfoque recursivo para eliminar primero los subárboles izquierdo y derecho de cada nodo y luego el nodo mismo.
    Si el árbol ya está vacío, no hace nada.
     */
	if(a == NULL){
        return;
    }else{
        vaciar(a->getIzq());
        vaciar(a->getDer());
        delete a;

    }
}

template <class T>
void ArbolB<T>::cargarPreIn(list<T> &pre ,  list<T> &in)
{
    // Este método carga un árbol binario a partir de dos listas que contienen el recorrido preorden e inorden del árbol
    // El método recibe como parámetros dos referencias a listas de tipo T que almacenan los datos de los nodos en preorden e inorden
    // El método vacía el árbol actual llamando a una función auxiliar vaciar que recibe la raíz del árbol y libera la memoria de todos sus nodos
    // El método crea dos listas auxiliares que copian el contenido de las listas originales
    // El método llama a una función recursiva leerPreOrdenInOrden que recibe las listas auxiliares y devuelve la raíz del árbol reconstruido
    // El método asigna el resultado de la función leerPreOrdenInOrden a la raíz del árbol actual
	this->vaciar(this->raiz);
	list<T> aux_a , aux_b;
	aux_a = pre;
	aux_b = in;
	this->raiz = leerPreOrdenInOrden(aux_a , aux_b);
}

template <class T>
void ArbolB<T>::cargarPostIn(list<T> &post ,  list<T> &in)
{
    // Este método carga un árbol binario a partir de dos listas que contienen el recorrido postorden e inorden del árbol
    // El método recibe como parámetros dos referencias a listas de tipo T que almacenan los datos de los nodos en postorden e inorden
    // El método vacía el árbol actual llamando a una función auxiliar vaciar que recibe la raíz del árbol y libera la memoria de todos sus nodos
    // El método crea dos listas auxiliares que copian el contenido de las listas originales
    // El método llama a una función recursiva leerPostOrdenInOrden que recibe las listas auxiliares y devuelve la raíz del árbol reconstruido
    // El método asigna el resultado de la función leerPostOrdenInOrden a la raíz del árbol actual
	this->vaciar(this->raiz);
	list<T> aux_a , aux_b;
	aux_a = post;
	aux_b = in;
	this->raiz = leerPostOrdenInOrden(aux_a , aux_b);
}

template <class T>
ArbolB<T> ArbolB<T>::obtHijoIzq()
{
    // Este método devuelve el subárbol izquierdo del árbol binario
    // El método crea un nuevo árbol binario auxiliar
    // El método verifica si la raíz del árbol actual es nula, en cuyo caso asigna nulo a la raíz del árbol auxiliar
    // Si no, el método llama a una función auxiliar copiarNodos que recibe el nodo izquierdo de la raíz del árbol actual y devuelve una copia de sus nodos
    // El método asigna el resultado de la función copiarNodos a la raíz del árbol auxiliar
    // El método devuelve el árbol auxiliar
	ArbolB<T> aux;
	if(this->raiz == NULL) 
		aux.raiz = NULL;
	else
		aux.raiz = this->copiarNodos(this->raiz->getIzq());
	return aux;
}

template <class T>
ArbolB<T> ArbolB<T>::obtHijoDer()
{
    // Este método devuelve el subárbol derecho del árbol binario
    // El método crea un nuevo árbol binario auxiliar
    // El método verifica si la raíz del árbol actual es nula, en cuyo caso asigna nulo a la raíz del árbol auxiliar
    // Si no, el método llama a una función auxiliar copiarNodos que recibe el nodo derecho de la raíz del árbol actual y devuelve una copia de sus nodos
    // El método asigna el resultado de la función copiarNodos a la raíz del árbol auxiliar
    // El método devuelve el árbol auxiliar
	ArbolB<T> aux;
	if(this->raiz == NULL) 
		aux.raiz = NULL;
	else
		aux.raiz = this->copiarNodos(this->raiz->getDer());
	return aux;
}

template <class T>
ArbolB<T>::ArbolB(const ArbolB<T> &a)
{
    // Este es el constructor copia del árbol binario
    // El constructor recibe como parámetro una referencia constante a otro árbol binario
    // El constructor llama a una función auxiliar copiarNodos que recibe la raíz del otro árbol y devuelve una copia de sus nodos
    // El constructor asigna el resultado de la función copiarNodos a la raíz del árbol actual
	this->raiz = copiarNodos(a.raiz);
}

template <class T>
NodoBinario<T>* ArbolB<T>::copiarNodos(NodoBinario<T> *a)
{
    /*
    Este método crea y devuelve una copia del árbol binario original.
    Utiliza un enfoque recursivo para crear un nuevo nodo con el mismo valor que el nodo actual y luego copiar sus subárboles izquierdo y derecho.
    Si el árbol está vacío, devuelve nulo.
    @return: un puntero a una copia del árbol binario original
     */

	if(a == NULL){
        return NULL;
    }else{
        NodoBinario<T> *getIzq = this->copiarNodos(a->getIzq());
        NodoBinario<T> *getDer = this->copiarNodos(a->getDer());
        return new NodoBinario<T>(a->getElemento(), getIzq, getDer);
    }
}

template <class T>
void ArbolB<T>::copiar(NodoBinario<T> *&a , NodoBinario<T> &b)
{
    // Este método copia los nodos de un árbol binario a otro
    // El método recibe como parámetros dos referencias a nodos binarios: una por referencia y otra por valor
    // El método asigna a la primera referencia el resultado de llamar a una función auxiliar copiarNodos que recibe la segunda referencia y devuelve una copia de sus nodos
	a = copiarNodos(b);
}

template <class T>
list<T> ArbolB<T>::porNiveles()
{
    /*
    Este método devuelve una lista con los valores de los nodos del árbol binario en recorrido por niveles.
    Utiliza una cola auxiliar para almacenar los nodos del árbol y visitarlos en el orden de su nivel, de izquierda a derecha.
    Si el árbol está vacío, devuelve una lista vacía.
    @return: una lista con los valores de los nodos en recorrido por niveles
     */
	list< NodoBinario<T>* > aux;
	list<T> listResult;
	aux.push_back((this->raiz));
	while(!aux.empty())
	{
		listResult.push_back(aux.front()->getElemento());
		if(aux.front()->getIzq() != NULL)
			aux.push_back(aux.front()->getIzq());
		if(aux.front()->getDer() != NULL)
			aux.push_back(aux.front()->getDer());
		aux.pop_front();
	}
	return listResult;
}
template <class T>

NodoBinario<T> * ArbolB<T>::leerPostOrdenInOrden( list<T> &post ,  list<T> &in)
{
    /*
    Este método construye un árbol binario a partir de dos listas dadas que representan el recorrido en postorden y en inorden del árbol.
    Asume que las listas no son nulas, tienen el mismo tamaño y contienen valores únicos.
    Utiliza un enfoque recursivo para encontrar el nodo raíz a partir de la lista de postorden y luego divide la lista de inorden en subárboles izquierdo y derecho según el valor del nodo raíz.
    Devuelve el nodo raíz del árbol construido o nulo si las listas están vacías o son inválidas.
    @post: una lista de valores de nodos en recorrido en postorden
    @in: una lista de valores de nodos en recorrido en inorden
    @return el nodo raíz del árbol construido o nulo
     */

	if(post.empty() && in.empty()){
        return NULL;
    }

	if(post.size() == 1){
        return new NodoBinario<T>(post.front(), NULL, NULL);
    }

	list<T> inOrdenIzq , inOrdenDer , postOrdenIzq , postOrdenDer;
	T val = post.back();
	post.pop_back();

	while(in.front() != val)
	{
		inOrdenIzq.push_back(in.front());
		postOrdenIzq.push_back(post.front());
		in.pop_front();
		post.pop_front();
	}
	in.pop_front();

	while(!in.empty())
	{
		inOrdenDer.push_back(in.front());
		postOrdenDer.push_back(post.front());
		in.pop_front();
		post.pop_front();
	}
	
	return new NodoBinario<T>(val , leerPostOrdenInOrden( postOrdenIzq, inOrdenIzq),leerPostOrdenInOrden( postOrdenDer, inOrdenDer));

}
template <class T>

NodoBinario<T> * ArbolB<T>::leerPreOrdenInOrden(list<T> &pre , list<T> &in)
{
    /*
    Este método construye un árbol binario a partir de dos listas dadas que representan el recorrido en preorden y en inorden del árbol.
    Asume que las listas no son nulas, tienen el mismo tamaño y contienen valores únicos.
    Utiliza un enfoque recursivo para encontrar el nodo raíz a partir de la lista de preorden y luego divide la lista de inorden en subárboles izquierdo y derecho según el valor del nodo raíz.
    Devuelve el nodo raíz del árbol construido o nulo si las listas están vacías o son inválidas.
    @pre: una lista de valores de nodos en recorrido en preorden
    @in: una lista de valores de nodos en recorrido en inorden
    @return el nodo raíz del árbol construido o nulo */

	if(pre.empty() && in.empty()){
        return NULL;
    }

	if(pre.size() == 1){
        return new NodoBinario<T>(pre.front(), NULL, NULL);
    }

	list<T> inOrdenIzq , inOrdenDer , preOrdenIzq , preOrdenDer;
	T val = pre.front();
	pre.pop_front();
	while(in.front() != val)
	{
		inOrdenIzq.push_back(in.front());
		preOrdenIzq.push_back(pre.front());
		in.pop_front();
		pre.pop_front();
	}
	in.pop_front();
	while(!in.empty())
	{
		inOrdenDer.push_back(in.front());
		preOrdenDer.push_back(pre.front());
		in.pop_front();
		pre.pop_front();
	}
	
	return new NodoBinario<T>(val , leerPreOrdenInOrden( preOrdenIzq, inOrdenIzq),leerPreOrdenInOrden( preOrdenDer, inOrdenDer));
}

template <class T>
int ArbolB<T>::getMayorElemento()
{
    // Este método devuelve el mayor elemento de un árbol binario
    // El método declara una variable entera mayor e inicializa con el valor mínimo posible
    // El método llama a una función auxiliar mayor que recibe la raíz del árbol y la variable mayor por referencia
    // La función mayor recorre el árbol en preorden y compara cada elemento con la variable mayor, actualizando su valor si encuentra uno más grande
    // El método devuelve el valor de la variable mayor al final
    int mayor=INT_MIN;
	mayor( this->raiz ,mayor);
	return mayor;
}

template <class T>
void ArbolB<T>::mayor(NodoBinario<T> * ptrRaiz,int &mayor)
{
    // Este método recorre el árbol en inorden y compara cada elemento con la variable mayor, actualizando su valor si encuentra uno más grande
    // El método recibe como parámetros un puntero a un nodo binario y una referencia a una variable entera mayor
    // El método verifica si el puntero es nulo, en cuyo caso termina la recursión
    // Si no, el método compara el elemento del nodo con la variable mayor y lo asigna si es más grande
    // El método llama recursivamente a la función mayor con el hijo izquierdo y el hijo derecho del nodo
	if(ptrRaiz == NULL){
        return;
    }else{
        if(ptrRaiz->getElemento()>mayor){
            mayor=ptrRaiz->getElemento();
        }
        mayor(ptrRaiz->getIzq() , mayor);
        mayor(ptrRaiz->getDer() , mayor);
    }

}

template <class T>
int ArbolB<T>::getMenorElemento()
{
    // Este método devuelve el menor elemento de un árbol binario
    // El método declara una variable entera menor e inicializa con el valor máximo posible
    // El método llama a una función auxiliar menor que recibe la raíz del árbol y la variable menor por referencia
    // La función menor recorre el árbol en preorden y compara cada elemento con la variable menor, actualizando su valor si encuentra uno más pequeño
    // El método devuelve el valor de la variable menor al final
    int menor=INT_MAX;
	menor( this->raiz ,menor);
	return menor;
}

template <class T>
void ArbolB<T>::menor(NodoBinario<T> * ptrRaiz,int &menor)
{
    // Este método recorre el árbol en inorden y compara cada elemento con la variable menor, actualizando su valor si encuentra uno más pequeño
    // El método recibe como parámetros un puntero a un nodo binario y una referencia a una variable entera menor
    // El método verifica si el puntero es nulo, en cuyo caso termina la recursión
    // Si no, el método compara el elemento del nodo con la variable menor y lo asigna si es más pequeño
    // El método llama recursivamente a la función menor con el hijo izquierdo y el hijo derecho del nodo
	if(ptrRaiz == NULL){
        return;
    }else{
        if(ptrRaiz->getElemento()<menor){
            menor=ptrRaiz->getElemento();
        }
        menor(ptrRaiz->getIzq() , menor);
        menor(ptrRaiz->getDer() , menor);
    }

}
template <class T>
void ArbolB<T>::preOrden(NodoBinario<T> * ptrRaiz, list<T> &listaResult)
{
    // Este método recorre el árbol en preorden y agrega cada elemento a la lista
    // El método recibe como parámetros un puntero a un nodo binario y una referencia a una lista de tipo T
    // El método verifica si el puntero es nulo, en cuyo caso termina la recursión
    // Si no, el método agrega el elemento del nodo a la lista
    // El método llama recursivamente a la función preOrden con el hijo izquierdo y el hijo derecho del nodo
    if(ptrRaiz == NULL){
        return;
    }else{
        listaResult.push_back(ptrRaiz->getElemento());
        preOrden(ptrRaiz->getIzq() , listaResult);
        preOrden(ptrRaiz->getDer() , listaResult);
    }
}

template <class T>
list<T> ArbolB<T>::preOrden()
{
    // Este método devuelve una lista con los elementos de un árbol binario en preorden
    // El método declara una lista vacía de tipo T
    // El método llama a una función auxiliar preOrden que recibe la raíz del árbol y la lista por referencia
    // La función preOrden recorre el árbol en preorden y agrega cada elemento a la lista
    // El método devuelve la lista al final
    list<T> a;
    preOrden(this->raiz , a);
    return a;
}

template <class T>
list<T> ArbolB<T>::inOrden()
{
    // Este método devuelve una lista con los elementos de un árbol binario en inorden
    // El método declara una lista vacía de tipo T
    // El método llama a una función auxiliar inOrden que recibe la raíz del árbol y la lista por referencia
    // La función inOrden recorre el árbol en inorden y agrega cada elemento a la lista
    // El método devuelve la lista al final
	list<T> b;
	inOrden(this->raiz , b);
	return b;
}

template <class T>
void ArbolB<T>::inOrden(NodoBinario<T> *ptrRaiz ,list<T> &listResult)
{
    // Este método recorre el árbol en inorden y agrega cada elemento a una lista
    // El método recibe como parámetros un puntero a un nodo binario y una referencia a una lista de tipo T
    // El método verifica si el puntero es nulo, en cuyo caso termina la recursión
    // Si no, el método llama recursivamente a la función inOrden con el hijo izquierdo del nodo
    // El método agrega el elemento del nodo a la lista usando el método push_back
    // El método llama recursivamente a la función inOrden con el hijo derecho del nodo
	if(ptrRaiz == NULL){
        return;
    }else{
        inOrden(ptrRaiz->getIzq() , listResult);
        listResult.push_back(ptrRaiz->getElemento());
        inOrden(ptrRaiz->getDer() , listResult);
    }

}

template <class T>
list<T> ArbolB<T>::postOrden()
{
    // Este método devuelve una lista con los elementos de un árbol binario en postorden
    // El método declara una lista vacía de tipo T
    // El método llama a una función auxiliar postOrden que recibe la raíz del árbol y la lista por referencia
    // La función postOrden recorre el árbol en postorden y agrega cada elemento a la lista
    // El método devuelve la lista al final
	list<T> listResult;
	postOrden(this->raiz , listResult);
	return listResult;
}

template <class T>
void ArbolB<T>::postOrden(NodoBinario<T> *ptrRaiz , list<T> &listResult)
{
    // Este método recorre el árbol en postorden y agrega cada elemento a una lista
    // El método recibe como parámetros un puntero a un nodo binario y una referencia a una lista de tipo T
    // El método verifica si el puntero es nulo, en cuyo caso termina la recursión
    // Si no, el método llama recursivamente a la función postOrden con el hijo izquierdo y el hijo derecho del nodo
    // El método agrega el elemento del nodo a la lista usando el método push_back
	if(ptrRaiz == NULL){
        return;
    }else{
        postOrden(ptrRaiz->getIzq() , listResult);
        postOrden(ptrRaiz->getDer() , listResult);
        listResult.push_back(ptrRaiz->getElemento());
    }

}

template <class T>
int ArbolB<T>::altura()
{
    // Este método devuelve la altura de un árbol binario
    // El método llama a una función auxiliar altura que recibe la raíz del árbol y devuelve un valor entero
    // La función altura calcula la altura del árbol usando la recursión y el máximo entre las alturas de los subárboles izquierdo y derecho
    // El método devuelve el valor de la función altura al final
	return altura(this->raiz);
}

template <class T>
int ArbolB<T>::altura(NodoBinario<T> *a)
{
    // Este método calcula la altura de un árbol binario usando la recursión y el máximo entre las alturas de los subárboles izquierdo y derecho
    // El método recibe como parámetro un puntero a un nodo binario
    // El método verifica si el puntero es nulo, en cuyo caso devuelve cero
    // Si no, el método llama recursivamente a la función altura con el hijo izquierdo y el hijo derecho del nodo
    // El método suma uno al máximo de los valores devueltos por las llamadas recursivas y lo devuelve
	if(a == NULL){
        return 0;
    }else{
        return 1 + max(altura(a->getIzq()) , altura(a->getDer()));
    }

}
template <class T>
int ArbolB<T>::numNodos()
{
    // Este método devuelve el número de nodos de un árbol binario
    // El método llama a una función auxiliar numNodos que recibe la raíz del árbol y devuelve un valor entero
    // La función numNodos calcula el número de nodos del árbol usando la recursión y la suma de los números de nodos de los subárboles izquierdo y derecho
    // El método devuelve el valor de la función numNodos al final
	return numNodos(this->raiz);	
}

template <class T>
int ArbolB<T>::numNodos(NodoBinario<T> *a)
{
	if(a == NULL){
        return 0;
    }else{
        return 1 + numNodos(a->getIzq()) + numNodos(a->getDer());
    }
}

template <class T>
bool ArbolB<T>::esABB()
{
    // Esta función verifica si el árbol binario es un árbol binario de búsqueda (ABB).
    // Para ello, llama a una función auxiliar que recibe la raíz del árbol y los límites
    // inferior y superior del rango de valores permitidos para cada nodo.
    // La función auxiliar devuelve verdadero si el árbol cumple con la propiedad de ABB,
    // es decir, si el valor de cada nodo está entre los límites correspondientes y si
    // los subárboles izquierdo y derecho también son ABB.
	return esABB(this->raiz , INT_MIN , INT_MAX);
}

template <class T>
bool ArbolB<T>::esABB(NodoBinario<T> *a ,int minimo ,int maximo)
{
    // Esta función recibe un nodo del árbol, el límite inferior y el límite superior del rango de valores permitidos para ese nodo.
    // La función devuelve verdadero si el nodo es NULL, lo que significa que el subárbol está vacío y por lo tanto es ABB.
    // Si el nodo no es NULL, la función verifica si el valor del nodo está entre los límites dados. Si no lo está, devuelve falso,
    // porque el subárbol no cumple con la propiedad de ABB.
    // Si el valor del nodo está entre los límites, la función llama recursivamente a sí misma para verificar los subárboles izquierdo y derecho,
    // pasando como nuevos límites el valor del nodo actual. Si ambos subárboles son ABB, la función devuelve verdadero. Si alguno de ellos no lo es,
    // devuelve falso.
	if(a == NULL){
        return true;
    }else{
        if(a->getElemento() < minimo || a->getElemento() > maximo){
            return false;
        }else{
            return esABB(a->getIzq() , minimo , a->getElemento()) && esABB(a->getDer() , a->getElemento() , maximo);
        }
    }
}
template<class T>
bool ArbolB<T>::esAVL(){
    // Esta función verifica si el árbol binario es un árbol AVL.
    // Para ello, llama a una función auxiliar que recibe la raíz del árbol y los límites
    // inferior y superior del rango de valores permitidos para cada nodo.
    // La función auxiliar devuelve verdadero si el árbol cumple con la propiedad de AVL,
    // es decir, si el valor de cada nodo está entre los límites correspondientes y si
    // los subárboles izquierdo y derecho también son AVL y el valor absoluto de la diferencia entre sus alturas es <= 1.
    // El método devuelve el valor de la función auxiliar al final.
    int altura;
    bool AVL = true;
    esAVL(this->raiz , altura , INT_MIN , INT_MAX , AVL);
    return AVL;
};
template <class T>
void ArbolB<T>::esAVL(NodoBinario<T> *ptrRaiz,int &altura, int minimo, int maximo, bool &AVL){
    // Esta función recibe un nodo del árbol, el límite inferior y el límite superior del rango de valores permitidos para ese nodo.
    // La función devuelve verdadero si el nodo es NULL, lo que significa que el subárbol está vacío y por lo tanto es AVL.
    // Si el nodo no es NULL, la función verifica si el valor del nodo está entre los límites dados. Si no lo está, devuelve falso,
    // porque el subárbol no cumple con la propiedad de AVL.
    // Si el valor del nodo está entre los límites, la función llama recursivamente a sí misma para verificar los subárboles izquierdo y derecho,
    // pasando como nuevos límites el valor del nodo actual. Si ambos subárboles son AVL, la función devuelve verdadero. Si alguno de ellos no lo es,
    // devuelve falso.
    if(ptrRaiz == NULL){
        altura = 0;
    }else{
        if(AVL){
            int alturaIzq, alturaDer;
            esAVL(ptrRaiz->getIzq(), alturaIzq, minimo, ptrRaiz->getElemento(), AVL);
            esAVL(ptrRaiz->getDer(), alturaDer, ptrRaiz->getElemento(), maximo, AVL);
            altura = 1 + max(alturaIzq, alturaDer);
            AVL = AVL && abs(alturaIzq - alturaDer) <= 1 && ptrRaiz->getElemento() > minimo && ptrRaiz->getElemento() < maximo;
        }
    }
}
#endif
// "Toda dificultad eludida se convertirá más tarde en un fantasma que perturbará nuestro reposo."
// Frederic Chopin (1810 - 1849) Compositor y pianista polaco.
//,,,,,.,................................................,,,,,,,,,,,,,,,,,,,,,,,,,.,,,,,,...........,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,,,,,,,,,,,,,,,,,,,
//,,,,,...................................................,,,,,,,...........,,,..............,..............,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,..........................................................,,,,.,,,................... ................,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,,.......................................................,,.................  ,,,,.,,,..  ................,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,,..................................................... ...........,.....,,,...,,,*****,....,. ..,,.......,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,,,,,............................................    ....  ......,,**,,,,,,,,,,*//**,,*,.....,.. ...........,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,,,,,.....................................      ..,*/****,,,....,,,,**//******,,,,..,,,*,,,,.     ............,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,,.................................,. .       ..///*,......  ..,***/(/*,,,... ...,...,**,,,..       ..,,......,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,,,..................................  .    ..,**,...   ....,,,,******,...,..,,...,. ........       .   ..,,,.,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//,,,,,,..................................     .,...,**,..    ..,***,*(/*........ ...,.  .                    .......,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*,,,,
//,,,,,,,................................     ....  ,**,.      .,**/**,.     ...,,.,......                      ....,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,******
//,,,,,,,...............................   .,,,,.. .,*,.      ,,,.......,*///(#%%%%%%#(///**,,*,,**/**,..  ..   ....,,,,.,,,,,,,,,,,,,,,,,,,,,,,,,******
//,,,................................... .,,,,,,. ....,,,.    .,,,,,*/(#%%&%%%&&&&&&%%%%%%%%%%%%%%#((((/,,.  .    ..,,,,,,,,,,,,,,,,,,,,,,,,,,,,,*******
//,,,,,................................  .,*,,,. ... .. .,....*/(#%%%%%&&&&&&&%&&&&&&&%%%%%%%#######(((//*,,  ..  ...,..,,,,,,,,,,,,,,,,,,,,,,*,********
//,,,,,............................,.   .,,,, .,...,.  .,*,,**//((#%%&&&&&&&&&&&&&&&&&&&%%%########((((((/*,,.     ...,..,,,,,,,,,,,,,,,,,,,************
//,,,,,.............................   ..,. ....  ...*/*,,,,**///(#%&&&&&&&&&&&&&&&&&&&%%%%%%####((((((///*,,,.     ..,,,,,,,,,,,,,,,,,,,,,*************
//,,,,,............................      . ..  ...,,,***,,,,**/(((%%&&&&&&&&&&&&&&&&&&&&&%%%%####((((((//***,,,      .,,,,,,,,,,,,,,,,,,,,,,,***********
//,,,,,,............................     .., ......,,********/*//(#%%&&&&&&&&&&&&&&&&&&&&&%%%#######(((((//**,,.     ...,,,,,,,,,,,,,,,,,,,,,,**********
//,,,,,,...........................      .,*.  ..  .,**,,,,,**//(##%%%%%%%%&&&&&&&&&&&&&&&&%%%%##(##(####(/*,,,*.   . .,,,.,,,,,,,,,,,,,,,**************
//,,,,,,,...,......................       ..   ..,*,..,,,,,,**/(#%%%%%%%%%%%%&&&&&&&&&&&&&&%%%%##(((#####((/*,**.    ... ...,,,,,,,,,,,,,***************
//,,,,,,,,,........................            .*//**,...,,**//(#%%%%%%%%%%%%%&&&&&&&&&&&&%%%%%##(((###((////////     .... ..,,,,,,,,,,*****************
//,,,,,,,,,..,,,,,,,,,,,.........     .....    .*/**..,..,***/(##%%%%%%%%%%%%%&&%%%#(//*****///(((((((((//*,,,...,.  .  ,,,,,,,,,,,,,,******************
//,,,,,,,,,....,,,,,,,,,...,....  .  ..         ,**,,/...,**/(#%%%%%%%%%%%%%%####(###(//*,,.....,*//(//,...,****,..      ,,,,,,,,,,,,,******************
//,,,,,,........,,,,,,,,..,...  .... .......    .   ,....,**/(#%%%&&&&%%%%%####%%%(//(,..,,.,,,*#&&%(*.  .,,. ...     . .,,,,,,,,,**********************
//,,,,,,...........,,,,,..... ..,,,,.                 .,,,,*/#%%%&%%%%&%%######/*/*(&*.,*,.*//%%&&&@&#../%*.,,,.. .  . .,,,,,,,*************************
//,,,,,,................... . . ,,,,,.     ..  ..   ..,,,***(#%%%%%%%%%%%%##((####&%%%###(///%&&&&&&@@%(,,**/*,... .   ..,,,,,,*************************
//,,,,,,......,,,,...........   .....    .. .,/,*////*,*,,*/((###%%%%%%%%%%%%&&&&&&%%%##(((#&&&&&&&&&@@&#**//***,,  . .,,,,,,,**************************
//,,,,,,..,..,,,,,...........          ,.    //#&&&@@&//*,/((((((####%%%%&&&&&&&&%%%%##(#%&@@&&&&&&&&&&@&#*//**,/,.  ....,,,,*************************//
//,,,,,,,,,,,,,,,............                %%&%&&&%* .*/%%#(((((((###%%%%&&&&%&%%%%%%&&&&&@@&&&&&&&&&&@&#//(/(/,. .*,,,*************************/**///
//,,,,,,,,,,,,,,........,,,...               %&@%&&%/.*(/(%%%(((((((((###%%%%%%%%%%%%%%&&&&&&&&&%%&&&&&&&&%(////*,,,,,,*****************************////
//,,,,,,,,,,,,,...........,.....             ,&&&%&#(&&&%,(#%#(((((((((((########%%%%%&&&&&&&%%%&&&&&&&&&&&%(*//*,,**,*,,***************************////
//,,,,,,,,,,,,,,,,......,......  ..        .,..(@%#&&&&&&%&##/(//(#((((#((#########%%%%%&&&&%#%%%%/,..,/(((/*,/*,,,,,******************************/////
//,,,,,,,,,,,,,,,,,...........  ....      .,,*,  /@@@&%&&@&&&(*/*//(((######((######%%%%%%&%%&@&/,(%#/**/*.,,*/*,,*,*******************************/////
//*,,,,,,,,,,,,,,,................    .,...,,**,..  ,(%&&@&&%(,/***(((#############%%%%%&&&&&&&&@@&&&&(*...,/***,***********************************////
//*,,,,,,,,,,,,,,,,,....,.........  .,..,,,*,,.. ..    .,,,.  .,*,*//((###########%%%%%&%&&&&&&&&&&&&&%&(,,*//*,,************************************///
//**,,,,,,,,,,,,,,,,,...,,,.......  ,**,,*,,,,...      .,*,,. ....,*,*/((#########%%%%%&&&%%&%%&&&&%##(/,.,,,**,,***********************************////
//,,,,,,,,,,,,,,,,,,,,,.,....,....  .,**,...,.          ,**//****,,,,,*/((########%%%%&%%&%#*,,*/((///***,..,/*,**************************//////***/////
//*,,,,,,,,,,,,,,,,,,,,,,,,,,..,,... ..,..,.            .//((#/***,,,,***/((#######%%%%%%#((#&&&&&&&%%#((*,.,,,,************///**************///////////
//*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,...     .              */(#%%#(/**,,,,***///(((#####%#####%%&%%%%%#(*,,.....,*************/////***********////////////
//*,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..                  *(#%%%%%#///*,,,,***///((((((#####%%%&%%%##(/*.......**************////////******/***//////////
//***,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..,.      ......./##%%%%%%##((//**,,,,***/////((##%%%&&&&&&&&&&&#(*,.****************/////*******///////////////
//***,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,,.,,,....... ./##%#%%%%%%##((///***,,,,,,**//((#%%&&&&@@@@&%%#(, *,**************************/******/////////
//****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..   .,*(###%%%%%%%%%##(((///****,,,,,,***/(#%%%&%%%##(/*.,,***************************/*****/*/*****//
//,**,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..    (..*(##%%%%%%%&&%%###(//********,,,,...,,,*****,,,,..,*******************/*******////////////******
//****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,      %@#/#%%%%%%%%%&&&&%%#(//*,,,.,,,,,,,,,............*****************************///***////*//*******
//****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.  ..   &@@&@&%%%%%%%&%&&&%%%%(/**,..,................ ..  ,***************************//*****//********///
//******,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.,,  .    ..*&@@&&&@&%%%&&&&&&%%%#(****/(((*............    .,,,/*******************************/**********///
//******,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.  ...   ,... *%@@@&%%@@&&&&&%%%##/**/(#%###(/,.......,,..,,*(#%&%*********************////////**************
//******,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,..   ...   .,....... /&&&&%&@&&@&&&%%#######(((/*,.....****//#%%%&@&/,*************///////*///////**********///
//****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,...   .....   .,,.........   .*#&&@&&&&%%%%%%%%%%#%(*.,. /(#%%&&&@@#, .**************////////////////****/********
//****,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,.   .........    .,,.......... .    ./&@&&&%%%%%%%##(/,..%@@@&&%(*.       ,**/***********//////*///////***///*******
//****,,,,,,,,,,,,,,,,,,,,,,,,,,,.   ............    .,,........... ... .,   .%@&&&%%&&&#(/.                     ,********//***////////////*************
//,***,,,,,,,,,,,,,,,,,,,,,,,,,.................. .  .,,... . .........,*.   .  ................,,,,,*,.              .*///*//***//*///////***/*********
//***,,,,,,,,,,,,,,,,,,,,,,.      .................  .&@@@(..     ....,,.  .,,,..,......... ,.......,,**.                 .,**//////******/*************
//*,,,,,,,,,,,,,,,,,,,,.     . ...................... /&@@@@@@(.. ...,**********..,,....,.  ,,   .,,***,*                       .*////////**************
//**,,,,,,,,,,,.,,,,.      ........................... (@@@@@@@@@@(*,,**,,,,,,,,,..,*,..  ....,*.  .,*****                           .,,*//***/****/////
//****,,,,.,,,,,.   ................................... (@@@@@@@&*****,,**,,,,,/*....      ....  ......                                .....**//////////
//*,,,,,,,,,.          ............................,.... *@@@@@@@&*,**,,******..  .,. ..,,,.............                                  .......,//////
//,,,,,.. .          ........ ......................,,... ,@@@@@@@@@(,*/#%&@@&&&&&&%&&@&(...,.,,..,,..,./  ...                           ..  .  .....,*/
//,...              ................................,,... .,&@@@@@@@@@@@@@@&&&&&@@@@@@@@@@@%*....,,..,(&@&* ...    .                       .............
//.   .           ................................,,,,,..  .,&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&(/////#&&@&@@@/ ...                      ..................
//.......         ..........................,,....,,,.,,,.. ..%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@&%&&&@&@@@@@,...    ..                 .................