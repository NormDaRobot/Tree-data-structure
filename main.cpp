#include <iostream>
#include <cstdlib>
#include <queue>
#include "arbin.h"
#include "abb.h"
#include "Excep_Ej6.h"

// Recorridos

template <typename T>
void inorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        inorden(a, a.subIzq(r));
        cout << r.observar() << " ";
        inorden(a, a.subDer(r));
    }
}

template <typename T>
void preorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        cout << r.observar() << " ";
        preorden(a, a.subIzq(r));
        preorden(a, a.subDer(r));
    }
}

template <typename T>
void postorden(const Arbin<T>& a, const typename Arbin<T>::Iterador& r) {
    if (!r.arbolVacio()) {
        postorden(a, a.subIzq(r));
        postorden(a, a.subDer(r));
        cout << r.observar() << " ";
    }
}

template <typename T>
void anchura(const Arbin<T>& a) {
    if (!a.esVacio()) {
        queue<typename Arbin<T>::Iterador> c;
        typename Arbin<T>::Iterador ic = a.getRaiz();
        c.push(ic);
        while (!c.empty()) {
             ic = c.front();
             c.pop();
             cout << ic.observar() << " ";
             if (!a.subIzq(ic).arbolVacio())
                c.push(a.subIzq(ic));
             if (!a.subDer(ic).arbolVacio())
                c.push(a.subDer(ic));
        }
    }
}


/***************************************************************************/
/****************************** EJERCICIOS *********************************/
/***************************************************************************/
//Ejercicio 1
//Dado un árbol binario, escribir una función que devuelva el número de hojas de dicho árbol.
template <typename T>
int numHojas(const Arbin<T> a)
{
    if(a.esVacio())
    {
        return 0;
    }

    return numHojas(a, a.getRaiz());
}

template <typename T>
int numHojas(const Arbin<T> a, const typename Arbin<T>::Iterador& r)
{
    if(r.arbolVacio()) return 0;

    if (a.subIzq(r).arbolVacio() && a.subDer(r).arbolVacio()) return 1;

    return numHojas(a, a.subIzq(r)) + numHojas(a, a.subDer(r));
}

/****************************************************************************/
//Ejercicio 2
//Diseñar una función que, dado un árbol binario A, devuelva una copia simétrica del mismo. Para el árbol
//A de la Figura 1, el árbol simétrico que devolvería la función sería el árbol B de la Figura 1.
template <typename T>
Arbin<T> simetrico(const Arbin<T> a)
{
    if (a.esVacio()) {
        return Arbin<T>();
    }

    return simetrico(a, a.getRaiz());
}

template <typename T>
Arbin<T> simetrico(const Arbin<T> a, const typename Arbin<T>::Iterador& r)
{
    if(r.arbolVacio()) {
        return Arbin<T>();
    }

    return Arbin<T>(r.observar(), simetrico(a, a.subDer(r)), simetrico(a, a.subIzq(r)));
}


/****************************************************************************/
//Ejercicio 3
/*Realizar un procedimiento que a partir de un árbol binario, muestre por pantalla los elementos de los
nodos visitados mediante un recorrido en zigzag, comenzando por un sentido dado (‘I’ para subárbol
izquierdo, ‘D’ para subárbol derecho):*/

template <typename T>
void recorridoZigzag( const Arbin<T>& a, char sentido )
{
    if(a.esVacio()) {
        cout << "Este arbol esta vacio.";
    } else {
        cout << a.getRaiz().observar();

        recorridoZigzag(a, a.getRaiz(), sentido);
    }
}

template <typename T>
void recorridoZigzag( const Arbin<T>& a, const typename Arbin<T>::Iterador& r, char sentido )
{
    if(r.arbolVacio())
    {
        cout << "FIN";
    }
    else if(sentido == 'I')
    {
        if (!a.subIzq(r).arbolVacio())
        {
            cout << "->" << a.subIzq(r).observar();
            recorridoZigzag(a, a.subIzq(r), 'D');
        }
    }
    else if(sentido == 'D')
    {
        if (!a.subDer(r).arbolVacio())
        {
            cout << "->" << a.subDer(r).observar();
            recorridoZigzag(a, a.subDer(r), 'I');
        }
    }
}

/******************************************************************************/
//Ejercicio 4
/*Un árbol binario está compensado si, para cada nodo interno del árbol, la diferencia entre el número de
nodos de sus hijos es menor o igual que 1. Escribir una función que devuelva verdadero si un árbol está
compensado y falso en caso contrario. Se entiende que el árbol vacío y las hojas están compensados.*/
template <typename T>
bool compensado(Arbin<T> a)
{
    if(a.esVacio())
    {
        return true;
    }
    return compensado(a, a.getRaiz());
}

template <typename T>
int tamano(const Arbin<T>& a, const typename Arbin<T>::Iterador& r)
{
    if (!r.arbolVacio()) {
        return (tamano(a, a.subIzq(r)) + tamano(a, a.subDer(r)) + 1);
    }

    return 0;
}

template <typename T>
bool compensado(Arbin<T> a, const typename Arbin<T>::Iterador& r)
{
    if (r.arbolVacio()) return true;

    int dif = tamano(a, a.subDer(r)) - tamano(a, a.subIzq(r));

    if(dif >= -1  && dif <= 1) return compensado(a, a.subDer(r)) && compensado(a, a.subIzq(r));
    else
    {
        return false;
    }
}

/*****************************************************************************/
//Ejercicio 5
/*Cada nodo de un árbol binario A almacena una letra. La concatenación de las mismas, en cada camino
que va desde la raíz a una hoja representa una palabra. Realizar una función que visualice todas las
palabras almacenadas en un árbol binario A.*/
template <typename T>
void palabras(Arbin<T> a)
{
    if (!a.esVacio())
    {
        char p[a.altura()];

        palabras(a, a.getRaiz(), p, 0);
    }
    else
    {
        cout << "El arbol esta vacio.";
    }
}

template <typename T>
void palabras(Arbin<T> a, const typename Arbin<T>::Iterador& r, char p[], int pos)
{
    if(!r.arbolVacio())
    {
        p[pos] = r.observar();

        if (!a.subIzq(r).arbolVacio())
        {
            palabras(a, a.subIzq(r), p, pos + 1);
        }
        if (!a.subDer(r).arbolVacio())
        {
            palabras(a, a.subDer(r), p, pos + 1);
        }
        if (a.subDer(r).arbolVacio() && a.subIzq(r).arbolVacio())
        {
            p[pos] = r.observar();
            for (int i = 0; i <= pos; i++)
            {
                cout << p[i];
            }
            cout << ".\n";
        }
    }
}

/******************************************************************************/
//Ejercicio 6
/*Sea a un árbol de búsqueda binario de enteros positivos y x un número entero positivo. Se
pide escribir una función que dados a y x devuelva el siguiente elemento mayor que x
almacenado en el árbol. En caso de que x no tenga un elemento mayor en el árbol a debe
lanzar una excepción. El elemento x puede estar en el árbol o no.*/
int siguienteMayor(const ABB<int>& a, const typename Arbin<int>::Iterador& r, int x)
{
    if (r.observar() <= x)
        if (!a.subDer(r).arbolVacio())
            return siguienteMayor(a, a.subDer(r), x);
        else
            throw NoHaySiguienteMayor();
    if (!a.subIzq(r).arbolVacio())
        try
        {
            return siguienteMayor(a, a.subIzq(r), x);
        }
        catch(NoHaySiguienteMayor)
        {
            return r.observar();
        }

    else
        return r.observar();
}

int siguienteMayor(const ABB<int>& a, int x)
{
    if (!a.esVacio())
        return siguienteMayor(a, a.getRaiz(), x);
    else
        throw NoHaySiguienteMayor();
}


/******************************************************************************/
//Ejercicio 7
/*Realizar una función que devuelva la posición de un elemento en un ABB (desde 1 hasta el número de
nodos del árbol) según un recorrido en inorden de dicho árbol, pero sin tener que procesar a posteriori
el resultado de dicho recorrido. Si el elemento no está en el árbol, la función devolverá 0.*/
int posicionInorden(const ABB<int>& a, const typename Arbin<int>::Iterador& r, int x, int& k)
{
    if (!r.arbolVacio())
    {
        int izq = posicionInorden(a, a.subIzq(r), x, k);

        if (izq != -1)
            return izq;

        k++;
        if (x == r.observar())
            return k;

        posicionInorden(a, a.subDer(r), x, k);
    }
    else
        return -1;
}

int posicionInorden(const ABB<int>& a, int x)
{
    if (!a.esVacio())
    {
        int k = 0;
        return posicionInorden(a, a.getRaiz(), x, k);
    }
    else
        return -1;
}

/******************************************************************************/
//Ejercicio 8
/*Sea a un árbol binario de enteros. Denominamos suma de un camino a la suma de los
valores de los nodos que forman un camino que vaya desde la raíz del árbol a una de sus
hojas. Se pide escribir una función booleana que dado a y un valor entero devuelva cierto si
dicho valor coincide con alguna suma de camino en dicho árbol y falso si no coincide con
ninguna. Para un árbol vacío la función haySumaCamino devolverá cierto para un valor de
suma 0 y falso en cualquier otro caso.*/
bool haySumaCamino(const Arbin<int>& a, const typename Arbin<int>::Iterador& r, int suma, int total)
{
    if (!r.arbolVacio())
    {
        total += r.observar();

        if (total == suma && (a.subDer(r).arbolVacio() && a.subIzq(r).arbolVacio()))
            return true;
        else
        {
            return (haySumaCamino(a, a.subIzq(r), suma, total) ||
                    haySumaCamino(a, a.subDer(r), suma, total));
        }
    }

    return false;
}

bool haySumaCamino(const Arbin<int>& a, int suma)
{
    if (!a.esVacio())
        return haySumaCamino(a, a.getRaiz(), suma, 0);
    else if (suma == 0)
        return true;
    else
        return false;
}


/****************************************************************************/
/****************************************************************************/
int main(int argc, char *argv[])
{
    Arbin<char> A('t', Arbin<char>('m', Arbin<char>(),
                                        Arbin<char>('f', Arbin<char>(), Arbin<char>())),
                       Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>()));

    Arbin<char> B('t', Arbin<char>('n', Arbin<char>(),
                                        Arbin<char>('d', Arbin<char>('e', Arbin<char>(), Arbin<char>()),
                                                         Arbin<char>())),
                       Arbin<char>('m', Arbin<char>('f', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>('n', Arbin<char>(), Arbin<char>())));

    Arbin<char> D('t', Arbin<char>('k', Arbin<char>('d', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>()),
                       Arbin<char>('m', Arbin<char>(),
                                        Arbin<char>('f', Arbin<char>(), Arbin<char>())));

    Arbin<char> E('o', Arbin<char>('r', Arbin<char>(),
                                        Arbin<char>('o', Arbin<char>(), Arbin<char>())),
                       Arbin<char>('l', Arbin<char>('a', Arbin<char>(), Arbin<char>()),
                                        Arbin<char>('e', Arbin<char>(), Arbin<char>())));

    Arbin<int> F(2, Arbin<int>(7, Arbin<int>(2, Arbin<int>(), Arbin<int>()),
                                  Arbin<int>(6, Arbin<int>(5, Arbin<int>(), Arbin<int>()),
                                                Arbin<int>(11, Arbin<int>(), Arbin<int>()))),
                    Arbin<int>(5, Arbin<int>(),
                                  Arbin<int>(9, Arbin<int>(),
                                                  Arbin<int>(4, Arbin<int>(), Arbin<int>()))));

    ABB<int> BB6, BB7;


    // NUMERO HOJAS //
    cout << "Num. hojas del arbol B: " << numHojas(B) << endl;
    cout << "Num. hojas del arbol E: " << numHojas(E) << endl << endl;

    // COPIA SIMETRICA //
    Arbin<char> C = simetrico(B);
    cout << "Recorrido en inorden del arbol B: " << endl;
    inorden(B, B.getRaiz());
    cout << endl << "Recorrido en inorden del arbol C: " << endl;
    inorden(C, C.getRaiz());
    cout << endl << endl;


    // RECORRIDO EN ZIG-ZAG //
    cout << "Recorrido en zigzag I de B:\n";
    recorridoZigzag(B, 'I');
    cout << endl;
    cout << "Recorrido en zigzag D de C:\n";
    recorridoZigzag(C, 'D');
    cout << endl << endl;

    // COMPENSADO //
    cout << "Esta A compensado?:";
    cout << (compensado(A) ? " SI" : " NO") << endl;
    cout << "Esta B compensado?:";
    cout << (compensado(B) ? " SI" : " NO") << endl << endl;

    // PALABRAS DE UN ARBOL //
    cout << "PALABRAS DE A:\n";
    palabras(E);
    cout << "PALABRAS DE B:\n";
    palabras(B);
    cout << endl;

    // SIGUIENTE MAYOR
    BB6.insertar(8); BB6.insertar(3); BB6.insertar(10); BB6.insertar(1); BB6.insertar(6);
    BB6.insertar(14); BB6.insertar(4); BB6.insertar(7); BB6.insertar(13);
    try
    {
        cout << "Siguiente mayor en BB6 de 5: " << siguienteMayor(BB6, 5) << endl;
        cout << "Siguiente mayor en BB6 de 8: " << siguienteMayor(BB6, 8) << endl;
        cout << "Siguiente mayor en BB6 de 13: " << siguienteMayor(BB6, 13) << endl;
        cout << "Siguiente mayor en BB6 de 14: " << siguienteMayor(BB6, 14) << endl;
    }
    catch(const NoHaySiguienteMayor& e)
    {
        cout << e.Mensaje() << endl << endl;
    }

    // POSICION INORDEN //
    BB7.insertar(5); BB7.insertar(1); BB7.insertar(3); BB7.insertar(8); BB7.insertar(6);
    cout << "Posicion Inorden en BB7 de 3: ";
    cout << posicionInorden(BB7, 3);
    cout << endl << "Posicion Inorden en BB7 de 8: ";
    cout << posicionInorden(BB7, 8);
    cout << endl << "Posicion Inorden en BB7 de 7: ";
    cout << posicionInorden(BB7, 7);
    cout << endl << endl;

    // SUMA CAMINO
    cout << "Hay un camino de suma 26 en F?:";
    cout << (haySumaCamino(F, 26) ? " SI" : " NO") << endl;
    cout << "Hay un camino de suma 9 en F?:";
    cout << (haySumaCamino(F, 9) ? " SI" : " NO") << endl;


    system("PAUSE");
    return 0;
}
