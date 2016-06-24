//ESTA VERSION ESTA ULTRA ARCHI MEGA BETA. NO COMPILA NADA
//FALTAN LOS TIPOS, DICCIONARIOS, TODO.
//Revisar tipos. Referencia y por copia.
#ifndef BASEDEDATOS_H_
#define BASEDEDATOS_H_

#include "Tipos.h"
#include "Driver.h"
#include "aed2/Dicc.h"
#include "aed2/Lista.h" //(incluido en diccionario)


class BaseDeDatos
{

public:
	BaseDeDatos();
	~BaseDeDatos();
	void agregarTabla(const Tabla& t);
	void insertarEntrada(const Registro& r, NombreTabla t);
	void borrar(const Registro& r, NombreTabla t);
	void generarVistaJoin(const NombreTabla t1, const NombreTabla t2, const NombreCampo c);
	const_Iterador vistaJoin(const NombreTabla t1, const NombreTabla t2);
	void borrarJoin(const NombreTabla t1, const NombreTabla t2);
	const_Iterador tablas();
	Tabla dameTabla(const NombreTabla t);
	bool hayJoin(const NombreTabla t1, const NombreTabla t2);
	NombreCampo campoJoin(const NombreTabla t1, const NombreTabla t2);
	NombreTabla tablaMaxima(); //devuelve el nombre de la tabla con mayor acceso (tablaM)
	Conj<Registro>& buscar(const Registro& crit, const NombreTabla t);

	


private:
	DicString<tuplaAux> arbolTablas;
	NombreTabla tablaM;
	Conj<NombreTabla> nTablas;

	struct tuplaAux{
		Tabla tab;
		Conj<NombreTabla> nombresJoins;
		DicString<nodoJoin> j;

		tuplaAux(Tabla t);
	};

	struct nodoJoin{
		bool principal;
		tuplaJoin* p;

		nodoJoin();
	};

	struct tuplaJoin{
		NombreCampo cJoin;
		Conj<Registro> vistaJoin;
		indiceSAux indiceS;
		indiceNAux indiceN;
		Lista<tuplaCambios> modificaciones; //ESTO TENDRIA QUE SER UNA COLA! Pero no esta implementada, asique usamos Lista
		const_Iterador nombreJoin; //Apunta al nombre de la tabla (de tuplaAux). Creo que esto ya no tiene mas uso, al no ser reciproco

		tuplaJoin();
	};

	struct indiceSAux{
		DicString<tuplaUnion> d;
		bool v;

		indiceSAux();
	};

	struct indiceNAux{
		DicNat<dato, tuplaUnion>  d; //DicNat toma dos parámetros, no?
		bool v;

		indiceNAux();
	};

	struct tuplaUnion{
		Registro registroTablaUno;
		Registro registroTablaDos;
		const_Iterador registroJoin;

		tuplaUnion();
	};

	struct tuplaCambios{
		char nTabla;
		Registro r;
		bool agregar;

		tuplaCambios();	
	};

};


#endif // BASEDEDATOS_H_


