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

#include <iostream>
#ifndef NODOBINARIO_H
#define NODOBINARIO_H

template <class T>
class NodoBinario
{
    private:
        T Elemento;
        NodoBinario<T> *izq;
        NodoBinario<T> *der;
	public:
		NodoBinario(T newElem){this->Elemento = newElem , this->izq = NULL , this->der = NULL;};
		NodoBinario(T newElem , NodoBinario<T> *izq , NodoBinario<T> *der){this->Elemento = newElem , this->izq = izq , this->der = der;};
        void setElemento(T newElem){this->Elemento = newElem;};
        void setIzq(NodoBinario<T> *newElem){this->izq = newElem;};
		void setDer(NodoBinario<T> *newElem){this->der = newElem;};
		NodoBinario<T> * getIzq(){return this->izq;};
		NodoBinario<T> * getDer(){return this->der;};
		T getElemento(){return Elemento;};

};
#endif