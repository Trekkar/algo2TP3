#ifndef DIC_STRING_H_
#define DIC_STRING_H_

#include <iostream>
#include <string>
#include "ModulosBasicos/aed2.h"
#include "Tipos.h"
//using namespace aed2;
using namespace std;

template <class T>
class DicString
{
	public:
		
		DicString();
		
		~DicString();
		
		//DicString(const DicString<T>&);
		
		void Definir(String s, T a);
		
		void Borrar(String s);
		
		bool Definido(String s);
		
		bool Vacio();
		
		int cantClaves();
		
		T& Significado(String s);
		
		const String MaxClave();
		
		const String MinClave();
		
		const T& Min();
		
		const T& Max();
	
		//bool operator==(const DicString<T>&) const;
		
	private:
		
		struct Nodo{
			Vector<Nodo*> h;
			char letra;
			T* significado;
			int cant;
			
			Nodo(Vector<Nodo*> v,char c, T* s) : h(v), letra(c), significado(s), cant(0)
			{}
			
			/*Nodo(Vector<Nodo*> v, char c, T* s, int ca): letra(c), cant(ca)
			{
				significado = NULL;
				if(s != NULL)
				{
					significado = new T(*s);
				}
				int i = 0;
				while(i < v.Longitud())
				{
					if(v[i] == NULL)
					{
						h.AgregarAtras(NULL);
					}
					else
					{
						T* a = NULL;
						if(v[i]->significado != NULL)
						{
							a = new T(*v[i]->significado);
						}
						Nodo* nuevo = new Nodo(v[i]->h,v[i]->letra,a,v[i]->cant);
						h.AgregarAtras(nuevo);
					}
					i++;
				}
				
			}
			*/
			~Nodo()
			{
				if(significado != NULL)
				{
					T* a = significado;
					significado = NULL;
					delete a;
				}
				int i = 0;
				while(i < h.Longitud())
				{
					if(h[i] != NULL)
					{
						Nodo* aux = h[i];
						h[i] = NULL;
						delete aux;
					}
					i++;
				}
				
			}
			
			
		};
				
		const Nat Ord(const char &a);
		
		Vector<Nodo*> hijos;
		int cantidad;
		String minClave;
		T* minSig;
		String maxClave;
		T* maxSig;
};

// divide los chars a-z por 97, siendo 97 el valor de 'a'  en ASCII 
template <class T>
const Nat DicString<T>::Ord(const char& a)
{
	return (Nat)a;
}



template <class T>
DicString<T>::DicString() : hijos(Vector<Nodo*>()), cantidad(0), minClave(" "), minSig(NULL), maxClave(" "), maxSig(NULL)
{}


template <class T>
DicString<T>::~DicString()
{
	
	//cout << "cleaning time" << endl;
	maxSig = NULL;
	minSig = NULL;
	int i = 0;
	while(i < hijos.Longitud())
	{
		if(hijos[i] != NULL)
		{
			Nodo* a = hijos[i];
			hijos[i] = NULL;
			delete a;
		}
		i++;
	}
	cantidad = 0;
	
}

/*template <class T>
DicString<T>::DicString(const DicString<T>& otra)
{
	maxClave = otra.maxClave;
	minClave = otra.minClave;
	cantidad = otra.cantidad;
	
	int i = 0;
	while(i < hijos.Longitud())
	{
		if(hijos[i] == NULL)
		{
			hijos.AgregarAtras(NULL);
		}
		else
		{
			T* a = NULL;
			if(hijos[i]->significado != NULL)
			{
				a = new T(*hijos[i]->significado);
			}
			Nodo* nuevo = new Nodo(otra.hijos[i]->h,otra.hijos[i]->letra, a,otra.hijos[i]->cant);
			hijos.AgregarAtras(nuevo);
		}
		i++;
	}
	
}
*/

template <class T>
void DicString<T>::Definir(String s, T a)
{
	Nat j = 0;
	Vector<Nodo*> vecbase;
	while(j < 256)
	{
		vecbase.AgregarAtras(NULL);
		j++;
	}
	if(cantidad  == 0)
	{
		hijos = vecbase;
	}
	if(hijos[Ord(s[0])] == NULL)
	{
		Nodo* nuevo = new Nodo(vecbase,s[0],NULL);
		hijos[Ord(s[0])] = nuevo;
	}
	Nat i = 0;
	Nodo* actual = hijos[Ord(s[0])];
	//cout << "entro al while" << endl;
	//cout << "letra " << actual->letra << endl;
	while(i < s.length()-1)
	{
		//cout << "ciclo: " << i << endl;
		if(actual->h[Ord(s[i+1])] == NULL)
		{
			actual->cant = actual->cant + 1;
			Vector<Nodo*> vec = Vector<Nodo*>(vecbase);
			Nodo* nuevo = new Nodo(vec,s[i+1],NULL);
			actual->h[Ord(s[i+1])] = nuevo;
			actual = actual->h[Ord(s[i+1])];
		}
		else
		{
			actual = actual->h[Ord(s[i+1])];
		}
		i += 1;
		//cout << "letra " << actual->letra << endl;
	}
	//cout << "Longitud h: " << actual->h.Longitud() << endl;
	//cout << "sali del while" << ", indice " << i << endl;
	//cout << "letra " << actual->letra << endl;
	
	if(actual->significado != NULL)
	{
		//cout << "estoy remplazando" << endl;
		T* aux = actual->significado;
		actual->significado = NULL;
		cantidad -= 1;
		delete aux;
	}
	actual->significado = new T(a);
	cantidad += 1;
	if(cantidad > 1)
	{
		if(s > maxClave)
		{
			maxClave = s;
			maxSig = actual->significado;
		}
		if(s < minClave)
		{
			minClave = s;
			minSig = actual->significado;
		}
	}
	else
	{
		maxClave = s;
		minClave = s;
		maxSig = actual->significado;
		minSig = actual->significado;
	}
	
	//cout << "defini" << endl;
}

template <class T>
void DicString<T>::Borrar(String s)
{
	if(Definido(s))
	{
		int i = 0;
		Nodo* actual = hijos[Ord(s[0])];
		Nodo* desdeAca = NULL;
		int ultimaLetra = Ord(s[0]);
		//cout << "busco lo que quiero borrar. Letra :" << actual->letra << endl;
		while(i < s.length()-1)
		{
			if(actual->cant > 1 && actual->h[Ord(s[i+1])]->cant == 1)
			{
				desdeAca = actual;
				ultimaLetra = Ord(s[i]);
			}
			if(actual->cant == 1 && actual->h[Ord(s[i+1])]->cant == 1 && actual->significado != NULL)
			{
				desdeAca = actual;
				ultimaLetra = Ord(s[i]);
			}
			actual = actual->h[Ord(s[i+1])];
			i++;
			//cout << "estoy en letra: " << actual->letra << endl;
		}
	//	cout << "termine la busqueda. Letra: " << actual->letra << endl;
		//cout << "desdeAca. Letra: " << desdeAca->letra << endl;
		T* aux = actual->significado;
		actual->significado = NULL;
		delete aux;
		cantidad--;
		//cout << "ultima letra: " << (char)ultimaLetra << endl;
		if(desdeAca != NULL)
		{
			//cout << "desdeAca no es nulo" << endl;
			Nodo* aux = desdeAca->h[ultimaLetra];
			//cout << "letra aux: " <<aux->letra << endl;
			desdeAca->h[ultimaLetra] = NULL;
			delete aux;	
		}
		else
		{
		//	cout << "desdeAca es nulo" << endl;
			if(actual->cant == 0)
			{
				Nodo* aux = hijos[ultimaLetra];
		//		cout << " aux: " << aux->letra << endl;
				hijos[ultimaLetra] = NULL;
				delete aux;
			}
		}
		//cout << "elimine " << endl;
		
		
		if(s == minClave)
		{
			if(cantidad == 1)
			{
				//cout << "me quedo 1 clave" << endl;
				minClave = maxClave;
				minSig = maxSig;
			}
			else if(cantidad == 0)
			{
				maxClave = " ";
				minClave = " ";
				minSig = NULL;
				maxSig = NULL;
			}
			else
			{
				//cout << "tengo que remplazar al minimo" << endl;
				String resmin;
				int k = 0;
				while(hijos[k] == NULL /*&& k < hijos.Longitud() && hijos[k]->cant < 1*/)
				{
					//cout << "estoy en el while" << endl;
					k++;
				}
				//cout << "encontre donde empezar" << endl;
				Nodo* actual2 = hijos[k];
				//cout << "actual: " << actual2->letra << endl;
				if(actual2->significado != NULL)
				{
					//cout << "encontre mi minimo" << endl;
					minClave = actual2->letra;
					minSig = actual2->significado;
				} 
				else
				{
					while(actual2->significado == NULL)
					{
						//cout << "entre al while" << endl;
						int j = 0;
						resmin.push_back(actual2->letra);
						while(actual2->h[j] == NULL)
						{
							//cout << "while 2" << endl;
							j++;
						}
						//cout << "pido siguiente" << endl;
 						actual2 = actual2->h[j];
 						//cout << "obtuve el siguiente" << endl;
					}
					//cout << "sali del while" << endl;
					resmin.push_back(actual2->letra);
					minClave = resmin;
					minSig = actual2->significado;
				}				
			}
			
		}


		else if(s == maxClave)
		{
			if(cantidad == 1)
			{
				//cout << "me quedo 1 clave" << endl;
				maxClave = minClave;
				maxSig = minSig;	
			}
			else if(cantidad == 0)
			{
				maxClave = " ";
				minClave = " ";
				minSig = NULL;
				maxSig = NULL;
			}
			else
			{
				//cout << "tengo que reemplazar al maximo" << endl;
				String resmax;
				int j = 255;
				while(hijos[j]==NULL /*&& j>=0 && hijos[i]->cant < 1*/)
				{
					j--;
				}
				Nodo* actual3 = hijos[j];
				while(actual3->cant != 0)
				{
					int k = 255;
					resmax.push_back(actual3->letra);
					while(actual3->h[k] == NULL)
					{
						k--;
					}	 
					actual3 = actual3->h[k];
				}
				resmax.push_back(actual3->letra);
				maxClave = resmax;
				maxSig = actual3->significado;
				}
				//cout << "termine" << endl;
			
		}
	}
}


template <class T>
bool DicString<T>::Definido(String s)
{
	if(Vacio())
	{
		//cout << "No hay claves" << endl;
		return false;
	}
	else
	{
		//cout << "Busco la  clave" << endl;
		//if(s == maxClave || s == minClave)
		//{
			//cout << "la encontre entre el min o max" << endl;
		//	return true;
		//}
		//else
		//{
			int i = 0;
			Nodo* actual = hijos[Ord(s[0])];
			if(actual != NULL)
			{
				//cout << "entro al While" << endl;
				while(i < s.length()-1)
				{
					//cout << "letra: " << actual->letra << endl;
					actual = actual->h[Ord(s[i+1])];
					if(actual == NULL)
					{
						return false;
					}
					i++;
				}
				//cout << "sali del While en la letra: " << actual->letra << endl;
				if(actual->significado != NULL)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				return false;
			}
			
		//}
	}
}

template <class T>
bool DicString<T>::Vacio()
{
	return this->cantidad == 0;
}

template <class T>
int DicString<T>::cantClaves()
{
	return this->cantidad;
}

template <class T>
T& DicString<T>::Significado(String s)
{
	//	cout << "quiero Obtener: " << s << endl; 
		if(s == minClave)
		{
		//	cout << "era el minimo" << endl;;
			return *minSig;
		}
		else if (s == maxClave)
		{
		//	cout << "era el maximo" << endl; 
			return *maxSig;
		}
		else
		{
	//		cout << "lo busco en el dic" << endl;
			int i = 0;
			Nodo* actual = hijos[Ord(s[0])];
			//cout << "empiezo en la letra: " << actual->letra << endl;
			while(i < s.length()-1)
			{	
				actual = actual->h[Ord(s[i+1])];
				i++;
				//cout << "estoy en la letra: " << actual->letra << endl;
			}

		//	cout << "sali del while en el indice: " << i <<  " letra: " << actual->letra << endl;
			return *actual->significado;	
		}
	
	
}

template <class T>
const String DicString<T>::MaxClave()
{
	return maxClave;
}

template <class T>
const String DicString<T>::MinClave()
{
	return minClave;
}

template <class T>
const T& DicString<T>::Min()
{
	return *minSig;
}

template <class T>
const T& DicString<T>::Max()
{
	return *maxSig;
	
}

#endif
