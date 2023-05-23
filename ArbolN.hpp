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
#ifndef ARBOLN_H
#define ARBOLN_H
#include <list>
#include <queue>
#include "NodoArbol.hpp"
#include <sstream>

using namespace std;
template <class T>
class ArbolN //Arboles N-arios
{
    struct NodeInfo {
        NodoArbol<T>* node;
        int level;
        int position;
        NodeInfo(NodoArbol<T>* node, int level, int position) : node(node), level(level), position(position) {}
    };

    NodoArbol<T> *raiz;

	public:
		ArbolN(const ArbolN<T> &);
		ArbolN(){this->raiz = NULL;};
		ArbolN(T e , list<ArbolN<T> > arboles);
        ArbolN(T e){this->raiz = new NodoArbol<T>(e);};
		bool esNulo(){return this->raiz == NULL;};
		T GetRaiz(){return this->raiz->getElemento();};
		list< ArbolN<T> > hijos();
		void insertarSubarbol(ArbolN &);
		void eliminarSubarbol(int );
        list<T> Preorden();
        list<T> Inorden();
        list<T> Postorden();
        list<T> porNiveles();
		~ArbolN();
        void copiar(ArbolN<T> &);
        void buscaPadreInsertaHijo(T , T);
        void leerTaller(T &);
    private:
        void buscaPadreInsertaHijo(NodoArbol<T> * , T , T, bool &);
        void destruirNodos(NodoArbol<T> *);
        NodoArbol<T> * copiarNodos(NodoArbol<T> *);
        void recorridoPreorden(NodoArbol<T> *, list<T> &);
        void recorridoInorden(NodoArbol<T> *, list<T> &);
        void recorridoPostorden(NodoArbol<T> *, list<T> &);
};

template<class T>
void ArbolN<T>::leerTaller(T &Primo) {
    /*Este metodo Lee Archivos de este formato:
     * Maria 3 Luis Ana Jose
     * Luis 2 Miguel Jesus
     * Ana 1 Patricia
     * Jose 3 Andreina Alejandra Carlos
     * Jesus 2 Diana Brittany
     * Alejandra 3 Jennifer Elizabeth Fernando
     * Fernando 2 Juan Pedro
     * *** Jesus
*/
    //El metodo asume que los datos vienen ordenados por niveles, en caso contrario no funcionara
    //El metodo asume que el último dato es el nodo que se desea buscar
    //El metodo asume que el archivo termina con *** y el dato que se desea buscar
    //En caso de que los datos no vengan ordenados por niveles, deberá usar el metodo buscaPadreInsertaHijo() en insertarlos uno a uno
    //El metodo usa la entrada estandar
    //El metodo recibe como parametro por referencia dato de tipo T y lo modifica con el dato que se desea buscar
    list<NodoArbol<T> *> auxList;
    NodoArbol<T> *hijoIzq, *auxHijo, *padre;
    bool raizColocada = false;
    string linea;
    T hijo, nombre;
    int i, cantHijos;
    while (getline(cin, linea) && linea.compare(0,3,"***") != 0) { //Leemos la linea y verificamos que no sea el final del archivo
        stringstream ss(linea);
        ss >> nombre;
        ss >> cantHijos;
        for (i = 0; i < cantHijos; i++) { //Leemos los hijos de la linea y los insertamos en la lista
            ss >> hijo;
            auxHijo = new NodoArbol<T>(hijo);
            if (i == 0) { //Si es el primer hijo, lo colocamos como hijo izquierdo
                hijoIzq = auxHijo;
            } else { //Si no es el primer hijo, lo colocamos como hermano derecho del ultimo hijo
                auxList.back()->setHerDer(auxHijo);
            }
            auxList.push_back(auxHijo); //Insertamos el hijo en la lista
        }
        if (!raizColocada) { //Si la raiz no ha sido colocada, la colocamos
            this->raiz = new NodoArbol<T>(nombre, hijoIzq);
            raizColocada = true;
        } else { //Si la raiz ya fue colocada, buscamos el padre y le insertamos el hijo

            while (!auxList.empty() && auxList.front()->getElemento() != nombre) {
                auxList.pop_front();
            }
            if (!auxList.empty()) { //Si la lista no está vacia, el padre fue encontrado
                padre = auxList.front();
                padre->setHijoIzq(hijoIzq);
            }
        }

    }
    Primo = linea.substr(4); //Leemos el nombre del primo
}



template <class T>
void ArbolN<T>:: buscaPadreInsertaHijo(T padre, T hijo){
    // Este método es una envoltura que llama al método recursivo buscaPadreInsertaHijo con el nodo raíz del árbol
    // Recibe como parámetros el elemento del nodo padre y el elemento del nodo hijo
    // Si el arbol esta vacio, asume que el padre sera la raiz y le asignara hijo como hijo izquierdo, en caso contrario no encontrara al padre y no hara nada
    bool insertado = false;
    if(this->raiz==NULL){
        this->raiz = new NodoArbol<T>(padre,new NodoArbol<T>(hijo));
    }else{
        buscaPadreInsertaHijo(this->raiz, padre, hijo, insertado);
    }

}
template <class T>
void ArbolN<T>::buscaPadreInsertaHijo(NodoArbol<T> *raiz, T padre, T hijo, bool &insertado) {
    // Este método busca un nodo con un elemento dado (padre) en un árbol n-ario y le inserta un nuevo nodo como hijo
    // Recibe como parámetros un puntero al nodo raíz del árbol, el elemento del nodo padre y el elemento del nodo hijo
    // Si el nodo padre tiene hijo izquierdo, se inserta el nuevo como hijo izquierdo y el hijo izquierdo se le asigna como hermano derecho al nuevo nodo
    // Si el nodo padre no tiene hijo izquierdo, se inserta el nuevo nodo como hijo izquierdo
    // Si el nodo padre no se encuentra en el árbol, no se hace nada
    if(raiz != NULL && !insertado){ //Si el árbol no está vacío
        if(raiz->getElemento() == padre){ //Si el elemento del nodo raíz es igual al elemento del nodo padre
            if(raiz->getHijoIzq() == NULL){ //Si el nodo padre no tiene hijo izquierdo
                raiz->setHijoIzq(new NodoArbol<T>(hijo)); //Se inserta el nuevo nodo como hijo izquierdo
            }else{//Si el nodo padre tiene hijo izquierdo
                NodoArbol<T> *aux =  new NodoArbol<T>(hijo);
                aux->setHerDer(raiz->getHijoIzq());// Se asigna el hijo izquierdo como hermano derecho del nuevo hijo
                raiz->setHijoIzq(aux);//Se inserta el nuevo nodo como hijo izquierdo de la raiz
            }
        }else{
            buscaPadreInsertaHijo(raiz->getHijoIzq(), padre, hijo, insertado);//Se busca el nodo padre en el hijo izquierdo
            buscaPadreInsertaHijo(raiz->getHerDer(), padre, hijo, insertado);//Se busca el nodo padre en el hermano derecho
        }
    }
}

template <class T>
ArbolN<T>::ArbolN(const ArbolN<T> &a)
{
    // Este Metodo recibe como parámetro una referencia constante a otro árbol n-ario del mismo tipo de dato.
    // El Metodo crea un nuevo árbol n-ario que es una copia exacta del árbol pasado como parámetro.
    // Para ello, llama a un Metodo auxiliar que recibe un nodo del árbol original y devuelve un nuevo nodo con el mismo elemento y la misma estructura de hijos y hermanos.
    // El Metodo asigna el resultado del Metodo auxiliar a la raíz del nuevo árbol.
	this->raiz = this->copiarNodos(a.raiz);
}

template<class T>
list<T> ArbolN<T>::porNiveles(){
    // Este Metodo devuelve una lista con los elementos del árbol n-ario recorridos por niveles, de izquierda a derecha.
    // Para ello, utiliza una lista auxiliar de nodos, donde se van insertando los nodos del árbol según se van visitando.
    // El Metodo comienza insertando la raíz del árbol en la lista de nodos, si no es NULL.
    // Luego, mientras la lista de nodos no esté vacía, se extrae el primer nodo de la lista y se inserta su elemento en la lista de resultado.
    // Después, se obtiene el hijo izquierdo del nodo extraído y se recorre su lista de hermanos derechos, insertando cada uno de ellos en la lista de nodos.
    // De esta forma, se garantiza que los nodos del mismo nivel se visiten antes que los del nivel inferior.
    // El Metodo devuelve la lista de resultado con los elementos del árbol ordenados por niveles.
    list<NodoArbol<T> *> listaNodos;
    list<T> listaResult;
    NodoArbol<T> *aux;
    if(this->raiz != NULL){
        listaNodos.push_back(this->raiz);
        while(!listaNodos.empty()){
            aux =  listaNodos.front();
            listaNodos.pop_front();
            listaResult.push_back(aux->getElemento());
            aux = aux->getHijoIzq();
            while(aux != NULL){
                listaNodos.push_back(aux);
                aux = aux->getHerDer();
            }
        }
    }
    return listaResult;
}


template<class T>
void ArbolN<T>::recorridoPostorden(NodoArbol<T> *ptrRaiz, list<T> &listaResult){
    // Este Metodo recibe como parámetros un puntero a un nodo del árbol y una referencia a una lista donde se van a insertar los elementos del árbol.
    // El Metodo visita los nodos del árbol en el siguiente orden: primero los hijos de izquierda a derecha, y luego el padre.
    // Para ello, utiliza un Metodo recursivo que verifica si el nodo actual es NULL. Si no lo es, obtiene su hijo izquierdo y recorre su lista de hermanos derechos,
    // llamando al Metodo recursivo para cada uno de ellos. Luego, inserta el elemento del nodo actual en la lista de resultado.
    NodoArbol<T> *aux; // Nodo auxiliar
    if(ptrRaiz != NULL){
        aux = ptrRaiz->getHijoIzq();
        while(aux != NULL){
            recorridoPostorden(aux);
            aux = aux->getHerDer();
        }
        listaResult.push_back(ptrRaiz->getElemento());
    }
}

template<class T>
list<T> ArbolN<T>::Postorden(){
    // Este Metodo crea una lista vacía donde se van a insertar los elementos del árbol.
    // Luego, llama al Metodo auxiliar recorridoPostorden, pasando como parámetros la raíz del árbol y la lista creada.
    // El Metodo auxiliar se encarga de visitar los nodos del árbol en postorden y de insertar sus elementos en la lista.
    // Finalmente, la Metodo devuelve la lista con los elementos del árbol ordenados en postorden.
    list<T> listaResult;
    recorridoPostorden(this->raiz);
    return listaResult;
}

template <class T>
void ArbolN<T>::recorridoPreorden(NodoArbol<T> *ptrRaiz, list<T> &listaResult){
    // Este Metodo recibe como parámetros un puntero a un nodo del árbol y una referencia a una lista donde se van a insertar los elementos del árbol.
    // El Metodo visita los nodos del árbol en el siguiente orden: primero el padre, y luego los hijos de izquierda a derecha.
    // Para ello, utiliza un Metodo recursivo que verifica si el nodo actual es NULL. Si no lo es, inserta su elemento en la lista de resultado y obtiene su hijo izquierdo.
    // Luego, recorre su lista de hermanos derechos, llamando al Metodo recursivo para cada uno de ellos.
    NodoArbol<T> *aux;
    if(ptrRaiz != NULL){
        listaResult.push_back(ptrRaiz->getElemento());
        aux = ptrRaiz->getHijoIzq();
        while(aux != NULL){
            recorridoPreorden(aux,listaResult);
            aux = aux->getHerDer();
        }
    }
}

template<class T>
list<T> ArbolN<T>::Preorden(){
    // Este método devuelve una lista con los elementos del árbol n-ario recorridos en preorden.
    // Para ello, crea una lista vacía donde se van a insertar los elementos del árbol.
    // Luego, llama al método auxiliar recorridoPreorden, pasando como parámetros la raíz del árbol y la lista creada.
    // El método auxiliar se encarga de visitar los nodos del árbol en preorden y de insertar sus elementos en la lista.
    // Finalmente, el método devuelve la lista con los elementos del árbol ordenados en preorden.
    list<T> listaResult;
    recorridoPreorden(this->raiz,listaResult);
    return listaResult;
}

template <class T>
void ArbolN<T>::recorridoInorden(NodoArbol<T> *ptrRaiz, list<T> &listaResult){
    // Este método realiza un recorrido inorden de un árbol n-ario y almacena los elementos visitados en una lista
    // Recibe como parámetros un puntero al nodo raíz del árbol y una referencia a la lista donde se guardarán los elementos
    // Utiliza un puntero auxiliar para recorrer los hermanos derechos de cada nodo
    NodoArbol<T> *aux;
    if(ptrRaiz != NULL){
        recorridoInorden(ptrRaiz->getHijoIzq());
        listaResult.push_back(ptrRaiz->getElemento());
        aux = ptrRaiz->getHijoIzq()->getHerDer();
        while(aux != NULL){
            recorridoInorden(aux,listaResult);
            aux = aux->getHerDer();
        }
    }
}

template<class T>
list<T> ArbolN<T>::Inorden(){
    // Este método devuelve una lista con los elementos del árbol n-ario recorridos en inorden.
    // Para ello, crea una lista vacía donde se van a insertar los elementos del árbol.
    // Luego, llama al método auxiliar recorridoInorden, pasando como parámetro la raíz del árbol.
    // El método auxiliar se encarga de visitar los nodos del árbol en inorden y de insertar sus elementos en la lista.
    // Finalmente, el método devuelve la lista con los elementos del árbol ordenados en inorden.
    list<T> listaResult;
    recorridoInorden(this->raiz,listaResult);
    return listaResult;
}

template <class T>
void ArbolN<T>::eliminarSubarbol(int pos)
{
    // Este Metodo recibe como parámetro un entero que indica la posición del hijo a eliminar, contando desde la izquierda.
    // El Metodo verifica si el árbol no está vacío y si la posición es válida.
    // Si la posición es 1, se elimina el hijo izquierdo de la raíz y se enlaza la raíz con el hermano derecho del hijo eliminado.
    // Si la posición es mayor que 1, se busca el nodo anterior al hijo a eliminar, recorriendo la lista de hermanos derechos desde el hijo izquierdo de la raíz.
    // Si se encuentra el nodo anterior, se elimina el hijo correspondiente y se enlaza el nodo anterior con el hermano derecho del hijo eliminado.
    // Luego, se desconecta el subárbol eliminado del resto del árbol y se llama a un Metodo auxiliar que libera la memoria de los nodos del subárbol.
    NodoArbol<T> *elim = NULL; // Nodo a eliminar
    if(!this->raiz->esNulo()){ // Si el árbol no está vacío

        if(pos == 1){ // Si la posición es 1
            elim = this->raiz->getHijoIzq(); // Se obtiene el hijo izquierdo de la raíz
            this->raiz->setIzq(this->raiz->getHijoIzq()->getHerDer()); // Se enlaza la raíz con el hermano derecho del hijo eliminado
        }else{ // Si la posición es mayor que 1
            int i;
            NodoArbol<T> *aux;
            aux = this->raiz->getHijoIzq(); // Se obtiene el hijo izquierdo de la raíz
            for(i = 2; i < pos - 1 && aux != NULL; i++){ // Se busca el nodo anterior al hijo a eliminar
                aux = aux->getHerDer(); // Se avanza al siguiente hermano derecho
            }

            if(aux != NULL){ // Si se encuentra el nodo anterior
                elim = aux->getHerDer(); // Se obtiene el hijo a eliminar
                aux->setDer(aux->getHerDer()->getHerDer()); // Se enlaza el nodo anterior con el hermano derecho del hijo eliminado
            }
        }
        elim->setDer(NULL); // Se desconecta el subárbol eliminado del resto del árbol
        this->destruirNodos(elim); // Se llama al Metodo auxiliar que libera la memoria de los nodos del subárbol
    }
}


template <class T>
list<ArbolN<T> > ArbolN<T>::hijos()
{
    // Este método devuelve una lista con los subárboles hijos del árbol n-ario actual.
    // Para ello, verifica si el árbol tiene algún hijo izquierdo. Si lo tiene, recorre la lista de hermanos derechos desde el hijo izquierdo,
    // copiando cada nodo y sus descendientes en un nuevo árbol auxiliar, y añadiendo ese árbol a la lista de resultado.
    // Si el árbol no tiene ningún hijo izquierdo, devuelve una lista vacía.
	list< ArbolN<T> > result;

    if(this->raiz->getHijoIzq() != NULL) // Si el árbol tiene algún hijo izquierdo
    {
        NodoArbol<T> *aux; // Nodo auxiliar
        ArbolN<T> arbolAux; // Árbol auxiliar
        aux = this->raiz->getHijoIzq(); // Se obtiene el hijo izquierdo
        while(aux != NULL) // Se recorre la lista de hermanos derechos
        {
            arbolAux.raiz = this->copiarNodos(aux); // Se copia el nodo actual y sus descendientes en un nuevo árbol
            result.push_back(arbolAux); // Se añade el árbol a la lista de resultado
            aux = aux->getHerDer(); // Se avanza al siguiente hermano derecho
        }
    }
    return result; // Se devuelve la lista de resultado
}


template <class T>
void ArbolN<T>::copiar(ArbolN<T> &a)
{
    // Este método copia el contenido de otro árbol n-ario en el árbol actual.
    // Para ello, recibe como parámetro una referencia a otro árbol n-ario del mismo tipo de dato.
    // El método llama a una función auxiliar que recibe un nodo del árbol original y devuelve un nuevo nodo con el mismo elemento y la misma estructura de hijos y hermanos.
    // El método asigna el resultado de la función auxiliar a la raíz del árbol actual.
	this->raiz = this->copiarNodos(a.raiz);
}


template <class T>
ArbolN<T>::~ArbolN()
{
    // Este metodo libera la memoria ocupada por los nodos del árbol.
    // Para ello, obtiene la raíz del árbol y llama a una función auxiliar que recibe un nodo del árbol y libera su memoria y la de sus descendientes.
	NodoArbol<T> *aux = this->raiz;  // Se obtiene la raíz del árbol
	this->destruirNodos(aux); // Se llama a la función auxiliar
}


template <class T>
void ArbolN<T>::destruirNodos(NodoArbol<T> *ptrRaiz)
{
    // Este método libera la memoria ocupada por un nodo del árbol y sus descendientes.
    // Para ello, recibe como parámetro un puntero a un nodo del árbol.
    // El método verifica si el nodo es NULL. Si no lo es, llama recursivamente al mismo método para liberar la memoria de sus hermanos derechos y de sus hijos izquierdos.
    // Luego, elimina el nodo actual con el operador delete
	if(ptrRaiz != NULL){  // Si el nodo no es NULL
        if(ptrRaiz->getHerDer() != NULL){ // Si tiene algún hermano derecho
            this->destruirNodos(ptrRaiz->getHerDer()); // Se llama al método recursivo para liberar su memoria
        }
        if(ptrRaiz->getHijoIzq() != NULL){ // Si tiene algún hijo izquierdo
            this->destruirNodos(ptrRaiz->getHijoIzq()); // Se llama al método recursivo para liberar su memoria
        }
        delete ptrRaiz; // Se elimina el nodo actual
    }

}


template <class T>
ArbolN<T>::ArbolN(T e , list< ArbolN <T> > arboles)
{
    // Este constructor crea un nuevo árbol n-ario a partir de un elemento y una lista de subárboles hijos.
    // Para ello, recibe como parámetros un elemento de tipo T y una referencia a una lista de árboles n-arios del mismo tipo de dato.
    // El constructor crea un nuevo nodo con el elemento dado y lo asigna a la raíz del árbol.
    // Luego, verifica si la lista de subárboles está vacía. Si no lo está, copia el primer subárbol de la lista y lo asigna al hijo izquierdo de la raíz.
    // Después, recorre el resto de la lista de subárboles, copiando cada uno de ellos y asignándolos a los hermanos derechos del hijo izquierdo de la raíz.
	NodoArbol<T> * aux;
	this->raiz = new NodoArbol<T>(e); // Se crea un nuevo nodo con el elemento dado y se asigna a la raíz
	if(!arboles.empty()) // Si la lista de subárboles no está vacía
	{
		this->raiz->setIzq(this->copiarNodos(arboles.front().raiz)); // Se copia el primer subárbol de la lista y se asigna al hijo izquierdo de la raíz
		arboles.pop_front(); // Se elimina el primer subárbol de la lista
		aux = this->raiz->getHijoIzq(); // Se obtiene el hijo izquierdo de la raíz
		while(!arboles.empty()) // Se recorre el resto de la lista de subárboles
		{
			aux->setHerDer(this->copiarNodos(arboles.front().raiz)); // Se copia el siguiente subárbol de la lista y se asigna al hermano derecho del nodo auxiliar
			aux = aux->getHerDer(); // Se avanza al siguiente hermano derecho
			arboles.pop_front(); // Se elimina el siguiente subárbol de la lista
		}
	}
}


template <class T>
NodoArbol<T> * ArbolN<T>::copiarNodos(NodoArbol<T> * ptrRaiz)
{
    // Este método devuelve una copia de los nodos de un árbol binario a partir de un puntero a la raíz

	if(ptrRaiz == NULL){ // Si el puntero es nulo, devuelve nulo
        return NULL;
    }else{
        // Si no, crea un nuevo nodo con el mismo elemento que el puntero
        // y llama recursivamente al método para copiar los subárboles izquierdo y derecho
        return new NodoArbol<T>(ptrRaiz->getElemento() ,
                                this->copiarNodos(ptrRaiz->getHijoIzq()) ,
                                this->copiarNodos(ptrRaiz->getHerDer()));
    }

}


template <class T>
void ArbolN<T>::insertarSubarbol(ArbolN<T> &subArbol)
{
    // Este método inserta un subárbol como hijo izquierdo de la raíz del árbol actual
    // Si la raíz ya tiene un hijo izquierdo, inserta el subárbol como hermano derecho del último hijo

    // Crea un puntero auxiliar que apunta a la raíz del árbol actual
	NodoArbol<T> *aux;
	aux = this->raiz;
	if(aux->getHijoIzq() == NULL){  // Si la raíz no tiene hijo izquierdo, inserta el subárbol como su hijo izquierdo

		aux->setHijoIzq(subArbol.raiz);

	}else{
        // Si la raíz tiene hijo izquierdo, recorre los hermanos derechos hasta encontrar el último
        while(aux->getHerDer() != NULL){
            aux = aux->getHerDer();
        }
        // Inserta el subárbol como hermano derecho del último hijo
        aux->setHerDer(subArbol.raiz);
    }

}

#endif

//"¡Actúa en vez de suplicar. Sacrifícate sin esperanza de gloria ni recompensa! Si quieres conocer los milagros, hazlos tú antes. Sólo así podrá cumplirse tu peculiar destino."
// Ludwig van Beethoven (1770-1827) Compositor alemán.
//*//*/(/*/*,****//,//***//*,,***,,***,,,,,*,,,,,,*,*,,,..,,...,....,,,..,,,,.,..,,,,,..,.,.,,,.,,..,.,.,,,*,,,,,,,,,,,,.,,,,,.,.,.,,,,,,..,,,,,,.,,.,,.
//(//(//*/***,,,,,/,,,,,,*,*,,,,*,,,,,,,.,..,............................,......../,,,........,....... .,,...............,..,.,...  ........... .......,
//%((****(**,,,,,,,**,,,,,,,,,,,,,,***,.,....,.....................,,  .*.,,,,,*,,**/*,,,**,,,,,.,.... .. ..... ..,. , ., .....,......... .. ...........
//#***,/******,*,,,(*,,,,,,*,,,.,*,,,,,.,,..,....,........,....../......******////*//(///*//**/,,,,.,....,.........,.*,.....,.............. ..........,.
//#/*,,.*,,//*,*,,,*,***,,.*,.........,..,...,..........,...../,,,*,,///*(((#(////(/**///**/*///******.,,........ .. .,. .,.. ....,. ......  .*. .....,
//(,,,,,.,,,**,,,,,,***,,,,,,,,.,.....,,. ,,...............*..,,**/(***/(#((//***/*,,***/*/**/*(((////*,,,*,... ... . .,...*,,*.  ...... .   ..........,
//(,****//**,**,,,,.,//*****,,,,..........,,,,....... .....,,,/**/(//**/((/*#,,,,*/,,/*,,,****/((/(/**/,,,,,,,  .....,.,.  ....  ..,.........,...,......
//(,,/(,**#/(**,,,,,,,,,***,,,,,.........................../,,*/((,*****/(**(*,,,,,***//((/((((((**/*/*,*,,,........ .,...,....*.,... ,....,.    ..  ...
// ,*./,/(/**,*,.,,,,.......,,,.......,.,...,.,. ... . . ..,/,**((//*//***#(/*,*,..*//**,*###%/((**,,..,,,*.*...... . ..   . .,,.....*.... ... . ... ...
//(.,,,(*,,*....,......,,................... .. ....,.....,,,(((**(////*/////((,,,,,,,,.,.,,*,#((/,*,,..**,.. .....  .  .,..  .....,.....,... ..,..  ..
//(,,,,.,,,,,..,....... ,,.....,,...,........,.........,,,,,,##(**////(#/(//*/,*,.,,.,.,..(**,/*((,.,.,.*,... ............ . ....,........... .. ,.  .,
//(,.,,*,,....,,*.,.... .....,...,..,........   ......*./,,//**(((((//**/(///*,,,,,,***///,,**((((*.,.,,.....   .......... .  .. ...*..... .. ..  . ...
//(....,............,,....,.................   ...  ,,*,,*,(/##((**,,,*//((((((#//((/(#/*/**,,*//,/*.**.,....... ...  ..... ., . . .......      . ......
// ,....,.....,..,................. . . ..... .. ...,,,**//**(/((,*(,*(%&&%###((((##(###(((/(/(/(,,,,*,*,,. ...,,,.*,//*..,,,.,,.. ..,..,.. . ... ..,.,.
// ...,...  ......,,............ .... ...... .. .   ,**,,,*/*/,//#//#&&@@&@&@@&&&%%###((((////(/,*,,**/,,.*,****,,,.**//*..,...... ..  ..  .  ..  .. .,.
//(.,.....,,.......,..... .......  . ..... .. .    ..,*,,,..,./((/(#&&&&&@@@&&&&&%&%%%###((//***,,,,./(/*/,**((////*,*.,,..*,.,,.. ,  . ... .    ..... .
//..,....*,. ..... .............  ... ..... .  ... ,,(/*,.,//*#%%%&&&&&&&&&&&&&&%%%%###(((///*,,,,.,.,(/(//*,..  .,,.,,,,, .,**,,*.....   ..,.    ...
//,............*,,,..... .....  ..    .......     . .,*(/,*,,(#%%%%%%&%&%&&&&%%%%%%####(((/****,,*,. ... ..,**, .   ,.,,,.  .,.*.   ..,...   .. .. .. .
//#,*,..,........,..........   . .. .  .. , ... ..  ,..,,*,/,,(###%%%&&%%%%%%%%&&%%##(///////,,,,,,,...,..*,,*,*,,. ..*.* .... .... ,    . .,       .. .
//(,,,........**.,... ..    .   .   . . . . .......**...,***,./(((##%%%###%#%%%%#(***.,*,**,,,,,,,,,,,*/*/*/,..*.., .     . .  .....   . . ....  .  ...
//(/*,..,...........,..  .  . ... .   .   ....,*.,***..*((/*/.,*,,,,****//(#(/*,,*,,,.    ..,,,,**,,,**/....  ..  .......  .. ...... .., .. . . .  ...,.
//(......,,,.. ,... .....  . ...     .    .. ..,*,/*,*/,(*/*,,,***,..  .,,*((/*,,,,,,/((##.,,*((//**,,,,,,,...  ..    ,.. .  . ...    ..,      .*. ....
// ....... .... . ..    .       . *  .,       ..,,,.,,,**//**(*,*/*//%#((((%&%(/**(((((/*((#%%((/*.,,,*,,,,..  .,      . . . .,       ..   ,./,..., ., .
// .....   . ....   .  .. ...                  .....,*,,,,*(#,,,,(%#(((##%##&&(///(########%#((/*,,,*,,*,,,..,,***...,,.  ....     .  , ,  *,,,...,..,.
// ....,..... .  ..             .                ..,,**,,//,,,,..(#%%###%#(#%%(/////(#%####(///**,,,*,,,. ,******// .      .. . . ,        ...,.,,,,,..
// .........    .... . ...   ... .   .  .         ..   ..*........((((###((#%%#(/((/*######(//**,*,***,..,**//((##%&..   .  .   . .. .... .,.,    ......
//*.......  . .. . ..  .   . .. .. .  .  ..              .. ,....,,/((###(((%%(//**,,*##((((/***(,*//,,,//((##%%&&&&,,..         .    .     .. , , , ..
// .,. ....   ...,... .... .  . ..  .          ..  ..   . .....,.,%((((((##(/**.*,,*(((#((((/*****//,,*(##%%&&@@@@@@%,,          .....  .    .. .*,,**,
// .,...  .... ..   ...... .*    .  . .    . .   .. . . . ....,.@@@&%(((((/(((((/*//*/****/(/*,***/,/#%&@@@@@@@@@@@@@**.. .  . .   .  ...    .. *,,....
//*.........  ... .   ..  ......          .. ...  ....    ...,(@@@&@@&(((/,*(((((##////(((/(**,,**/%&@@@@@@@@@@@@@@@&#*....  ..  .    . . ., ,,,,. ..,.
// ..... .. .,. . .  .. ..  . .. .    ...       ..  . .  ...,@@&@@@@@@@&(/((//*,,,,,,*/**///**,**%&@@@@@@@@@@@@@@@@@@&, ...  ..       ..        ., ...,
//*..,..  . ... .. .   .   , ..  .  ,,..  ..     ..  ..... .@@@&@@@@@@@@&#//((/##(/#(//////,,*/,&@@@@@@@@&@&@&&&#//*.,.....  . .     .  .    .  .   ..,
//*..   . ..      ..   .   *. ,.. ....   . ..   .. .. ..  .@@@@@@@@@@@@@&%%#*(/((//*/***,,/,,,#@@&*****,*,,,,,,,..,,.....  .. .     ..        .      .,
//*...     . ..  .  , ,.  ,     .. .    ..  .  .... ... .....,,,,,,..,,*,&%%%#(**//*/**,,,,,,&,/*****/**,,,,,,..,,,,.....    . .     .              .. .
//*...    .      * ., . . ...... .   ...  .   ..  .  .   ,.,,,,,.  ..**/***,###(/,,*//******(**,,**//,,,,,,,..,,,,,.........    .. . . ..        ..   .
// ........  , ., # , ..  . .    .    .  .   . . .    ......,,,.  ...***/*,,*,/((/********,**,,,*/*,,,,,,,..,.,.,.,.....  ...   ...... .            ..,.
// ,. .. .. ..... . . . . (*  ..  ....      .  .. .   ....,.,,.. . ..*****,*******,*****,,,*,,***,,,*,,,.,,.,,,......... .  ..   .   .          . .....
// ...  ....    ..   .    .(,.       .. .        .  .........,... . .*****************,*,,,*/*,*,,*,,,.,.,,,.,.,..,.......... .. .  .  *        . . . .
// ... ..  ..,,.,.. .    . .#*.  .....   ...    . ..........,...    .,**************,,.,,*,,,*,*,,,,*,,,,,,........,..... .. ... ... .            .....
// ....  .,,,....   .  .    .,#,  .        . .    ....,.....,,.....,****************,,,,,,,,,,,**.,.,,,,,,.....,..........,...   ,              ........
// ...*......,   .  ,. ...#%(/*(*, ..  ...       ...,.......,.....,**************,,,,,,***,,.,.*%(.,,..,...........,........  ,.          . ........ .
//(/..,....,*,,,,,*,,, .(#%%%&#/((,,*#%#((       ...........,.,..***************,,,,,,****,,,./%,,,,,...................... .            .. . ...... ...
//(..,...,.,...*,...,.(#%#/(%%%%#(*(%((/***..    ............,..,**************,,,**,,,*,,,,.%(,.,.,,,................ . ..             ....... .. .....
//*.,....,..*......,,.##%&&&%#/((%/#,,*,,***   ................. ************,,,,,,,***,. .(/*,..,............,..... . /.              ...  ............
// ..,.,*.,/,........(##*(#%##%%%(/*#*,**,,**   ,,,..............***********,,,,,,,*,,.../*#..,,.................   .,                ....,.............
//*...,,,,,*..,.,,./.(#%%&&#/*/(///**(,,/****. .,, .....,...,,...,*,*,**,,,,,,,,,,.....,*/,...,............. ...   .,              ..,..,..............
// ,,,@@&%#@@#/,,.*..(#((##%%(###(((/**//(***..,,, ...............,*,**,*,*,,,.,.,**,,,/,....,.,,.......,.....   ..               ....,.., . ... .......
//@@@@&&@&@@@@@&&@*@,*(#%%&#((********(/****.   ,. ..........,.... *,**,****,,,,,,,,*,,,........,............  ,                . . . .  ............,.
//@@,#,*@@%@%@@((#%@%*&%#@@#(////*,,****/*,.   .. . .  ..,........ ,**,**,,*,,,*,,,,,,............,... ....  ., . .,        .. *      . ...............
//#*@&@%#%#@/(((((((((( /(,%%&%###,***/**,..    .  ..  .,...........,*,*,****,,,**,,* ........,....,,....  ,,    ..     .         . .  .................
//@@#%%(@(((((((((((((((((##&//##*.%%@&#,. . ..  .. ........,........*****,,**,,,,,,....................  ,         .   .  .    ...  ........... .. .. .
//%#(@/(((((((((((((((((((((((((((#&#/*(##( /& .,(#&&&&&&&&&&%%%##/,..**,*,,***,,*,......,..............,   ... ,*      .  .       .  ... .    .  ..
//#&##(##((((((((((((((((((((((((((((((/(#%#//(###&%((((##%%#%%#####(/*,,,.,,..,,,,.... ...........  .,.    .   . . . ..          .   .      .
//%#((((((((((((((((((/((//////////(((//////(///(#%%%&%%%%%%#######(,,,,,,,,,.................,.... .      .. . . ..  .         .  ..          .   . .
//%####(((((((((((((((((((/((///**((/*//*/(############%###(((((((*,,,,,,./,...........  .......   . . .    .. ,    .                  .       .  ..
//%#((#####(#((((#(((((((((((((((///***,,****/*****,,/(&%%##((((/,**,,..,...... .,.,,....,,..... ..  . *  ... *,              . .                 . . .
//%((#(*##(###((#(##(*((((((((((((/(/////*,**/*//(((####%%#(///*,,,,,.*,.........*....... . .   .    ,  ,  ..        ...                            ....
//%((((((#(#,(((((/(((((((((((((((((/////*/**,***,,,*,/((((//**,,,,.. ..,.,........ ,.,..........   .  ,  . .  ,               .      .     .      . ..
//#,#((*(((((((((((/((///((/(((((/(//////*////,**/////(((((/,*,,,..........,.....,*  .,.  ....    ,.                         .        .  .         ...
//#(((((#((((*,*(.((/(///(((/((////*////*//////*,,,**,*///**,,....,,........ .,* ....  ..... ...   .....                   ..  .         .        .   .
//#(/(((((((/((((*/(//(/////////////*//*///////*****,,,,,,,,,.,.., ,..........   .,.........   ........ .. ...             .     .  .        .
//#/((((/(///((((//////////////////////////*//////*******/**,,. ...........   .  ... ,.... ........      ........ .  .              .    ..        .
//#//(/((//////(///////////////////////////////////*///*****,... ....... .     ................ ....   ....... ...  .       .  ...  ..  ...  ..        .
//((//***///////////*/////////////////////////////*////******,.... . .. .  .  ,.... .............. ... ..  . .    .   .         .       .    .   .     .
// ,  ,..,/////*/////////*/////////////////////*///////*/*****,,  ......    ...  .   ... .  .    ... .        ..  .     . .        ..   .      ..     ..
// ,,. ..,.... ,*////(/////////////////*///////*//////////*/*** ..   . ..  .   .  .     .       .    .. ... ..  ..     .                    .    . .  ..
// .... .   ..  ,.,.  .,////////////////////*/*///////////*,     .     .         .     .         ., . .  .. .          .    .  .      ..             ..
//*   . .... ,...    ..     ..,*//////*/////////////////*          .                               . .   .   ... .  .                ..     .  .  ...
// .....  . ..,, .. ,, .  ..,. ....  . ,,****////////*.          ..    .              .. . .     .          .    . .           . . .  .        .  ....
//*. .,.. .  ...,.,..... .. .. ......,   . . ,. . .   . ..      .      .         .        ..   . ..      ..  ..     .. .    ... . .      .        ..
// ...........,,.......,. ... ..,....       ,       ,..  .,.,,.. . ., .,.... . ..  ..    .  ..  .   .  ..   . .  . . .   .. ........... .   ..  ... . .
// ...... ...,. ...... ........... ..   .. ,...,.... ...  ,.... . ...,....  . .        ..  .    ,.. .. .  ..,  , ......   .....   . ....   .   .  ... ..