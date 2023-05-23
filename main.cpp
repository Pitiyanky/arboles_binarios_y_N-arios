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
#include <ostream>
#include <string>
#include <sstream>
#include <limits>
#include "arbolB.hpp"
#include "ArbolN.hpp"

//Leer los datos
struct persona{
    std::string ID;
    bool esNeph;
    //Sobrecarga de operadores del struct
    bool operator==(const persona& perComp) const {
        return ID == perComp.ID && esNeph == perComp.esNeph;
    }

    bool operator!=(const persona& perComp) const {
        return (ID != perComp.ID || esNeph != perComp.esNeph);
    }
};

//Struct caso de prueba, para almacenar a las personas que se buscaran en el arbol y el carbol con sus respectivos recorridos
struct CasoDePrueba {
    struct persona per1, per2;
    std::list<struct persona> Orden;
    std::list<struct persona> inOrden;
    std::string primerOrden;


};


//Funcion lee el archivo por entrada estandar y regresa un caso de prueba
//No recibe nada por parametros
//Devuelve un struct con las personas y los recorridos
CasoDePrueba leerCasoDePrueba() {
    //Declaracion de variables
    CasoDePrueba caso;
    std::string linea;
    std::string persona;
    std::string raza;
    std::list<struct persona> listaAux;
    std::istringstream iss;
    std::string aux;
    string orden;
    struct persona auxPersona;
    //Fin de declaracion de variables
    //Leemos la primera linea
    std::getline(std::cin, linea);
    iss.str(linea);
    //Leemos a la primera persona
    std::getline(iss, persona, '-');
    caso.per1.ID = persona;
    iss>>raza;
    caso.per1.esNeph = (raza == "N");
    //ignoramos el espacio
    iss.ignore();
    //leemos a la segunda persona
    std::getline(iss, persona, '-');
    caso.per2.ID = persona;
    iss>>raza;
    caso.per2.esNeph = (raza == "N");
    //Limpiamos el iss
    iss.clear();
    //Leemos las listas
    //Son dos listas una en el orden de entrada y otra en inorden, la lista de orden de entrada siempre ira de primera
    for(int i = 0; i < 2; i++){
        //Leemos el primer orden
        std::getline(std::cin, linea);
        iss.str(linea);
        std::getline(iss, orden, ' ');
        //Asignamos el orden al caso de entrada
        if(i == 0){
            caso.primerOrden = orden;
        }
        //Leemos la lista, un ejemplo de la lista seria este: alvaro-N marian-M vero-M
        //leera el nombre solamente que estara hasta "-" y despues la raza
        while(std::getline(iss, aux, '-')){
            auxPersona.ID = aux;
            iss>>raza;
            auxPersona.esNeph = (raza == "N");
            //ignoramos el espacio en blanco de cada linea
            iss.ignore();
            listaAux.push_back(auxPersona);
        }
        //Comprobamos cual lista es y la asignamos
        if(i == 0){
            caso.Orden = listaAux;
        }else{
            caso.inOrden = listaAux;
        }
        //vaciamos la lista y el iss para comenzar de nuevo
        listaAux.clear();
        iss.clear();
    }
    return caso;
}
//Fin de leer los datos
//Resolucion de taller

// La función buscarLCA toma como parámetros un árbol binario de búsqueda (arbol),
// y dos estructuras de tipo persona (per1 y per2) y devuelve el ancestro común más bajo (LCA) de per1 y per2 en el árbol.
ArbolB<struct persona> buscarLCA(ArbolB<struct persona> arbol, struct persona per1, struct persona per2){
    // Si el árbol es nulo, devuelve el árbol nulo
    if(arbol.esNulo()){
        return arbol;
    } else {
        // Si la raíz del árbol es igual a per1 o per2, devuelve el árbol
        if(arbol.getRaiz() == per1 || arbol.getRaiz() == per2){
            return arbol;
        } else {
            // Busca el LCA en el subárbol izquierdo
            ArbolB<struct persona> arbolIzq = buscarLCA(arbol.obtHijoIzq(), per1, per2);
            // Busca el LCA en el subárbol derecho
            ArbolB<struct persona> arbolDer = buscarLCA(arbol.obtHijoDer(), per1, per2);
            // Si ambos subárboles tienen un LCA no nulo, devuelve el árbol actual
            if(!arbolIzq.esNulo() && !arbolDer.esNulo()){
                return arbol;
            }
            // Si solo uno de los subárboles tiene un LCA no nulo, devuelve ese subárbol
            if(arbolIzq.esNulo()){
                return arbolDer;
            } else {
                return arbolIzq;
            }
        }
    }
}

// La función distanciaNephilim toma como parámetros un árbol binario de búsqueda (arbol),
// una estructura de tipo persona (per), una referencia a un entero (distancia) y una referencia a un entero (conteoNeph).
// La función busca el nodo per en el árbol y calcula la distancia desde la raíz hasta per y el número de nodos Nephilim en el camino.
// Los resultados se guardan en las variables distancia y conteoNeph.
void distanciaNephilim(ArbolB<struct persona> arbol, struct persona per, int &distancia, int &conteoNeph){
    // Si el árbol es nulo, establece distancia en -1 y conteoNeph en 0
    if(arbol.esNulo()) {
        distancia = -1;
        conteoNeph = 0;
    } else {
        // Si la raíz del árbol es igual a per, establece distancia en 0 y aumenta conteoNeph si la raíz es un Nephilim
        if(arbol.getRaiz() == per){
            if (arbol.getRaiz().esNeph){
                conteoNeph += 1;
            }
        } else {
            // Busca el nodo per en los subárboles izquierdo y derecho
            int distanciaAux = distancia+ 1;
            int conteo = conteoNeph;
            if (arbol.getRaiz().esNeph) {
                conteo += 1;
            }
            distanciaNephilim(arbol.obtHijoIzq(), per, distanciaAux, conteo);
            if (distanciaAux != -1) {
                // Si se encuentra el nodo per en el subárbol izquierdo, actualiza distancia y conteoNeph
                distancia = distanciaAux;
                conteoNeph = conteo;
            } else {
                // Si no se encuentra el nodo per en el subárbol izquierdo, busca en el subárbol derecho
                distanciaAux = distancia + 1;
                conteo = conteoNeph;
                if (arbol.getRaiz().esNeph) {
                    conteo += 1;
                }
                distanciaNephilim(arbol.obtHijoDer(), per, distanciaAux, conteo);
                if (distanciaAux != -1) {
                    // Si se encuentra el nodo per en el subárbol derecho, actualiza distancia y conteoNeph
                    distancia = distanciaAux;
                    conteoNeph = conteo;
                } else {
                    // Si no se encuentra el nodo per en ninguno de los subárboles, establece distancia en -1 y conteoNeph en 0
                    distancia = -1;
                    conteoNeph = 0;
                }
            }
        }
    }
}

// La función calcularNSE toma como parámetros un árbol binario de búsqueda (arbol) y dos estructuras de tipo persona (per1 y per2).
// La función calcula el NSE (Nephilim Separation Estimate) entre per1 y per2 en el árbol y devuelve el resultado como un float.
float calcularNSE(ArbolB<struct persona> arbol, struct persona per1, struct persona per2){
    // Busca el ancestro común más bajo (LCA) de per1 y per2 en el árbol
    ArbolB<struct persona> LCA = buscarLCA(arbol, per1, per2);
    // Inicializa las variables para almacenar la distancia y el número de nodos Nephilim en el camino desde el LCA hasta per1 y per2
    int distanciaPer1 = 0;
    int distanciaPer2 = 0;
    int conteoNephPer1 = 0;
    int conteoNephPer2 = 0;
    int sumaConteo;
    if(LCA.getRaiz().esNeph){
        sumaConteo = -1;
    }else{
        sumaConteo = 0;
    }
    // Calcula la distancia y el número de nodos Nephilim en el camino desde el LCA hasta per1 y per2
    distanciaNephilim(LCA, per1, distanciaPer1, conteoNephPer1);
    distanciaNephilim(LCA, per2, distanciaPer2, conteoNephPer2);
    /*std::cout<<"dis1:"<<distanciaPer1<<std::endl;
    std::cout<<"dis2:"<<distanciaPer2<<std::endl;
    std::cout<<"Conteo1:"<<conteoNephPer1<<std::endl;
    std::cout<<"Conteo2:"<<conteoNephPer2<<std::endl;*/
    // Si no se encuentra per1 o per2 en el árbol, devuelve -1
    sumaConteo = sumaConteo + conteoNephPer1 + conteoNephPer2;
    if(distanciaPer1 == -1 || distanciaPer2 == -1) {
        return -1;
    } else {
        // Calcula y devuelve el NSE como la suma de los nodos Nephilim en los caminos desde el LCA hasta per1 y per2 dividido por la suma de las distancias
        return (float) (sumaConteo) / (distanciaPer1 + distanciaPer2 );
    }
}
//fin de la solucion

// La función leerCasoDePrueba lee un caso de prueba de la entrada estándar y lo devuelve como una estructura de tipo CasoDePrueba.
// La función solveTaller lee casos de prueba de la entrada estándar y resuelve cada uno de ellos.
void solveTaller(){
    // Lee el número de casos de prueba
    int n, i;
    cin >> n;
    // Inicializa las variables para almacenar cada caso de prueba y el árbol
    struct CasoDePrueba caso;
    ArbolB<struct persona> arbol;
    std::list<struct persona> listaAux;
    // Procesa cada caso de prueba
    for(i = 0; i < n; i++){
        // Ignora el resto de la línea actual
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // Lee el caso de prueba
        caso = leerCasoDePrueba();
        // Si el primer orden es PREORDEN, carga el árbol a partir de las listas de preorden e inorden
        if(caso.primerOrden == "PREORDEN"){
            arbol.cargarPreIn(caso.Orden, caso.inOrden);
        } else {
            // Si el primer orden es POSTORDEN, carga el árbol a partir de las listas de postorden e inorden
            arbol.cargarPostIn(caso.Orden, caso.inOrden);
        }
        // Calcula y muestra el NSE entre per1 y per2 en el árbol
        std::cout << calcularNSE(arbol, caso.per1, caso.per2) << std::endl;
    }
}
//funcion main
int main()
{
    //solveTaller() algoHace
    solveTaller();
    //solveTaller() algoHizo
	return 0;
}

//"Lo que he logrado ha sido gracias al trabajo y la práctica, cualquier persona con un don natural tolerable y capacidad, también puede lograrlo."
//Johann Sebastian Bach (1685-1750) Compositor alemán.
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&#%%%%##@###%%%%%%%&%%%&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&&&%##(/((((####(#/(%%%%%%####@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&&&%##(/((##%&&@@&%%#%#(##%%((/(%&%&%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&%##%%#%&&&@&&&%@&&&&%%%##(####((##(/#/%(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&@&@@%#&&&&&&#%%%%#%%####/(/*****/(((%%%##//#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&%####&&&%&(#(/##%%&&&&&&&%&%%%%%%##(///##(%#((%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&%&&&&&&@##(((#%&&@@@@@@@@@@@&&&&&&&%%##(/*#%##((/#@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&%%%#%##%(///(#&@@@@@@@@@@@@@@@&&&&&&%&%#((/,(%#(((//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&%&%%%##%&%#/*%&@@@@@@@@@@@@@@@@@&&&&&%%%%#(/*,%%&%#((/@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@#(%&%&%#&%%/((&&&@@@@@@@@@@@@@@@&&@&&&%&&%#%#/*(%&@&&%//%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%###(((#&&%#//*&&&@@@@@@@@@@@@@@@@&&&&&&&&&&&%#///&&&&%#/(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@%((//%&&(%&&&#(*%&@&@@@@@@@@@@@@@&&%%@&&@&&%##**,**/&%%(((##@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@&&%%%%%%((%%%#///%&&&&&%%#/*,/((%%#%#%@&%%#*,,(%#/,***#%&##((%@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@@@@@@@@@&@&&&&#%%##(((/&&&&##*#&&%%%%&&@@@@&&&%**%&@&#,/#,,,**//..,((%%%%#(@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@@&&&&@@&%&&%&%%##%/*%%&&%(&&&#(%&&&&&##*.,.,*((##&&&&@&**%%%##/,*/*,*(%&&%(/*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@@@&%#%&&%&#%#%%&#(/(%#%%%((##&%((*&&&@&@@&@&&@&&%(%@@&&&@%,*####(/%#*..*(%#/*/**@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@@@%%&%&&%#((###########&(((#&&%&#*/*#&&@@@@@@@@&&&@@@@@&&&&&&/*#&&%%##/*.(%%%%#,,,*@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@@@@%&&%%%#&(#%#(##(#((%#(//*%%#%(##/*/*%&&&@@@@@@@@@@@@@@%%&&&@@&(*#&&%#((/ .#&&%//*(&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@&&%#%&%%#%%(%###(#(/##(((/#&&&%**%%%(*/%&&%@&&@@@@@@@&%#*#%%%%%%%* ,%%%%(/* ..#%#(.,,/&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@@&@&%%###%((#%((((#(//(%%%%%&/**,*###(/,#&&&&&&&&&&&&&%(#&@@@&%(,.. /(##%#(*, .,,,*..,*#&&&&&&@&&@@&@@&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@&&&&##%###(####(((##(##(%#(#*//*(%%##*/,(%%%&%%%&&&&%%#%%%%&&%%%(%#((/(%%#(*.,,/(/(,///#&&&&%&&&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@@&&&&%%%%#(#(#(((#(((/##((#(/,*&&(/%((((**##%%##%%%%%%%%#/(%(*., . (#/,,#%#//..,/(,//,*#%%&%%&&%&&&&&&%&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@@@&@@%%%#(%##%####/#//(#((#((#//((((%&&&(((,(#######%%%%%##%&@@@@@&%(/,.**/#//*,.*/(#,*//%%&%%&&%&%&%&&%%%&&&&@&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@&&&&%#%##%##(%((((((((#(##((((&&%(/(*///((*/,*(####%##%%%###&&&&&%#%%%##((((*/*..////*.((%&%%&%%%&%%%&%%&&&&%&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@&@&%&##%#(#(#%(#(#(#(#(//(#((#(%%#(%(//,*,/,,*/(#((/(((#%%%##&&@@@@@@@&%#(////,/,,,,*.,%&%%%%%%%%%%%%%%&&&&&%&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@&&%%#%(%#%%(#(((%#(((//(#((/(#//(((*#/**((,,#&&&((%##%%#(####%%%&&&@&%#(///*/*,,,.,,*/#&&%%%&%###&&%%%&%&%&&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@&&%&%##%%%#####(((#(/((/(((((//(%#(((//,,*.,, ,@@&@@((####%#%%%((*(/#******(/.,*////(((%%%%%#%%%%%&%%&%%&%%&%&&%&&&&&@@@@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@@@&&&&%%######((((#(((#((#/##((/////*,,*,.,***,,.%&@@@@@@&/(((##(####(/////*,,,,*,,,.###%%#&%%%%%#&%%%&&%%&&%&&%&&&&&&&@&@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@&@&&&%#%%#(%###/(/(#//((((#((((*/**/**,*,*****,,,**&@&@@@@@@&&&&&&&%&%#(##(**,.,*,,,,,..*%&&&&%%%%&%%%%%#%%%&&&%%%&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@
//@@@@&&%%%&#(%&(&#(/(##(*/(((//(/#(*/*,*/.*****,**///,*.*,.&@%@@&@@@@@@@&&%%%####///*.,,.,*.... .,/%%&&%#&%%&%%%%%%%%%&%&&&&&&&&@@@@@@@@@@@@@@@@@@@@@@@
//@@@@@&&&@####%###(#(##(///(*(/(///,***,/*/*,,.,*,*,**,*,/,,,*&&@@&@@%&&%%%%%#&&@%%(*.,*/,..**.,,*,.,*#%&&&%%%%%%%%%&&&&%&&%&&&@@@@@@@@@@@@@@@@@@@@@@@@
//@@@@&&%&#%&%#%%#(#(/*/(////**/*/**//*,*,,,***.,,*,,*,,/***,,.,/*@@&@@@@@@@@@@@@&(&%(*,..,.,.,*.,,*..,,,./&&%%&#%%%%&%&%%&&%&&&&@@@@@@@@@@@@@@@@@@@@@@@
//@@@&&@&&%&(##%#(((//#/((//********,,..*/*/**, ,**,,,,,*,***,,*,.,/@@@@@@@@@@@@@@@%#%*....**,/**..,.,.,*....(&%#%%%%%%%%%&&&&&&&&&@@@@@@@@@@@@@@@@@@@@@
//@@@&%&%&&%##&#(/((//////*/,*//,*******/.*,/,,,,,*,,,.,,,,,*/,,/,*..,(@@@@@@@@@@@@@##,,,.,* .*,,,.,*, .*.   ..(%%%%%%%%&%&&%&&&&&&@@@@@@@@@@@@@@@@@@@@@
//@@@@@&%%&%####/#(//////,.*,*/*/**,,*,,**,/*/,..**,,.*,,...*,(***,,,., ,@@@@@@@@@&&@%#*  ,.,.,*,/,*,*,, ..,, .,.#%&%#%%%%%&&%&&&&&&@@@@@@@@@@@@@@@@@@@@
//@@@@&%&&&%%###%(//,,,***,****,*/*,*,., ...*,**..,*.,*,,***,**(**,**,, ,...@@@@@@@@@&#/ .. *.*,*,,****,,..,.*.  *,&&%%#&%%&%&%&&&&@@@@@@@@@@@@@@@@@@@@@