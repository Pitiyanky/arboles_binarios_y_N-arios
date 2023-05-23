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


#ifndef NODOARBOL_H
#define NODOARBOL_H

template <class T>
class NodoArbol
{
    private:
        T Elemento;
        NodoArbol<T> *hijoIzq;
        NodoArbol<T> *herDer;

	public:
		NodoArbol (T a){this->Elemento = a , this->hijoIzq = NULL , this->herDer = NULL;};
        NodoArbol (T a, NodoArbol<T> *hijoIzq){this->Elemento = a , this->hijoIzq = hijoIzq , this->herDer = NULL;};
		NodoArbol (T a , NodoArbol<T> *hijoIzq , NodoArbol<T> *herDer){this->Elemento = a , this->hijoIzq = hijoIzq , this->herDer = herDer;};
		void setHijoIzq(NodoArbol<T> *a){this->hijoIzq = a;};
		void setHerDer(NodoArbol<T> *a){this->herDer = a;};
		NodoArbol<T> * getHijoIzq(){return this->hijoIzq;};
		NodoArbol<T> * getHerDer(){return this->herDer;};
		T getElemento(){return Elemento;};
        void setElemento(T a){this->Elemento = a;};
};
#endif