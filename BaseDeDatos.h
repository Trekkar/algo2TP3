//ESTA VERSION ESTA ULTRA ARCHI MEGA BETA. NO COMPILA NADA
//FALTAN LOS TIPOS, DICCIONARIOS, TODO.
//Revisar tipos. Referencia y por copia.

#include Tipos.h
#include Driver.h
#include Conj.h
#include Dicc.h
#include Lista.h


class BaseDeDatos
{

public:
	BaseDeDatos();
	~BaseDeDatos();
	void agregarTabla(const Tabla& t);
	void insertarEntrada(const Registro& r, char t);
	void borrar(const Registro& r, char t);
	void generarVIstaJoin(const char t1, const char t2, const char c);
	const_Iterador vistaJoin(const char t1, const char t2);
	void borrarJoin(const char t1, const char t2);
	const_Iterador tablas();
	Tabla dameTabla(const char t);
	bool hayJoin(const char t1, const char t2);
	char campoJoin(const char t1, const char t2);
	char tablaMaxima(); //devuelve el nombre de la tabla con mayor acceso (tablaM)
	Conj<Registro>& buscar(const Registro& crit, const char t);

	


private:
	DicString<tuplaAux> arbolTablas;
	char tablaM;
	Conj<char> nombreTablas;

	struct tuplaAux{
		tabla Tabla;
		Conj<char> nombresJoins;
		DicString<nodoJoin> Joins;	
	};

	struct nodoJoin{
		bool principal?;
		tuplaJoin* p;
	};

	struct tuplaJoin{
		char cJoin;
		Conj<registros> vistaJoin;
		indiceSAux indiceS;
		indiceNAux indiceN;
		Lista<tuplaCambios> modificaciones; //ESTO TENDRIA QUE SER UNA COLA! Pero no esta implementada, asique usamos Lista
		const_Iterador nombreJoin; //Apunta al nombre de la tabla (de tuplaAux). Creo que esto ya no tiene mas uso, al no ser reciproco
	};

	struct indiceSAux{
		DicString<tuplaUnion> d;
		bool v;
	};

	struct indiceNAux{
		DicNat<dato, tuplaUnion>  d; //DicNat toma dos parámetros, no?
		bool v;
	};

	struct tuplaUnion{
		registro registroTablaUno;
		registro registroTablaDos;
		const_Iterador registroJoin;
	};

	struct tuplaCambios{
		char nombreTabla;
		registro registro;
		bool agregar?;	
	};

};



