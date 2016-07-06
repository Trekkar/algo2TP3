//ESTA VERSION ESTA ULTRA ARCHI MEGA BETA. NO COMPILA NADA
//FALTAN LOS TIPOS, DICCIONARIOS, TODO.
//Revisar tipos. Referencia y por copia.
#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

// #include "Tipos.h"
// #include "Driver.h"
// #include "aed2/Dicc.h"
// #include "aed2/Lista.h" //(incluido en diccionario)
// #include "aed2/TiposBasicos.h"
#include "tabla.h"

 //fake tabla para compilar
//typedef bool indiceNAux;
//typedef bool indiceSAux;

//TYPOS ROBADOS/////////////////////////////////////////////////////////////////////////////

// typedef unsigned int Nat;
// typedef std::string String;
// typedef String NombreTabla;
// typedef String NombreCampo;

// typedef aed2::Dicc<NombreCampo, Dato> Registro;
// enum TipoCampo { NAT, STR };

// typedef struct {NombreCampo nombre; TipoCampo tipo;} Columna;
// bool operator == (const Columna& c1, const Columna& c2);

//TYPOS ROBADOS/////////////////////////////////////////////////////////////////////////////
using namespace aed2;

class BaseDeDatos
{


public:
	BaseDeDatos();
	~BaseDeDatos();
	void agregarTabla(Tabla& t);
	void insertarEntrada(const Registro, const NombreTabla&);
	void borrar(const Registro& r, NombreTabla t);
	//void borrarRegistro(const Registro& r, NombreTabla t);
	void generarVistaJoin(const NombreTabla t1, const NombreTabla t2, const NombreCampo c);
	Conj<Registro>::const_Iterador vistaJoin(const NombreTabla t1, const NombreTabla t2);
	void borrarJoin(const NombreTabla t1, const NombreTabla t2);
	Conj<NombreTabla>::const_Iterador tablas();
	Conj<NombreTabla> nombresTablas() const;
	Tabla& dameTabla(const NombreTabla t) const;
	bool hayJoin(const NombreTabla t1, const NombreTabla t2) const;
	NombreCampo campoJoin(const NombreTabla t1, const NombreTabla t2) const;
	NombreTabla tablaMaxima() const; //devuelve el nombre de la tabla con mayor acceso (tablaM)
	Conj<Registro> buscar(const Registro& crit, const NombreTabla t) const;
	void MostrarBaseDeDatos() const;


 private:
 	//Las estructuras estan declaradas en orden inverso. Empiezo por las de mas bajo nivel hasta la del mas alto...
 	//...esto es para que, al compilar, las detecte.

 	struct tuplaCambios{
		NombreTabla nTabla;
		Registro r;
		bool agregar;

		tuplaCambios(NombreTabla n, Registro reg, bool a);
	};

	struct tuplaUnion{
		Registro registroTablaUno;
		Registro registroTablaDos;
		Conj<Registro>::Iterador registroJoin;

		tuplaUnion(Registro r1, Registro r2, Conj<Registro>::Iterador i);
	};



	struct tuplaJoin{
		NombreCampo cJoin;
		Conj<Registro> vistaJoin;
		DicString<tuplaUnion> indiceS;
		bool indiceSValido;
		DicNat<Nat, tuplaUnion> indiceN;
		bool indiceNValido;
		Lista<tuplaCambios> modificaciones; //ESTO TENDRIA QUE SER UNA COLA! Pero no esta implementada, asique usamos Lista
		Conj<NombreTabla>::Iterador nombreJoint1;
		Conj<NombreTabla>::Iterador nombreJoint2;

		tuplaJoin(NombreCampo c, TipoCampo t, Conj<NombreTabla>::Iterador t1, Conj<NombreTabla>::Iterador t2);
	};


	struct nodoJoin{
		bool principal;
		tuplaJoin* p;

		nodoJoin(tuplaJoin* t, bool v);
	};

 	struct tuplaAux{
		Tabla* tab; //puse un puntero porque no tenemos operador =
		Conj<NombreTabla> nombresJoins;
		DicString<nodoJoin> dicJoin;
		//DicString<nodoJoin> j;

		tuplaAux(Tabla* t);
	};

 	DicString<tuplaAux> arbolTablas;
 	//DicString<tuplaAux> arbolTablas;
 	NombreTabla tablaM;
 	Conj<NombreTabla> nTablas;
 	Conj<Registro> vacio;

};

//}; //end namespace Driver

#endif // BASEDEDATOS_H_


