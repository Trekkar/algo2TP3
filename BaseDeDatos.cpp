#include "BaseDeDatos.h"

BaseDeDatos::BaseDeDatos(): 
	arbolTareas(Dicc()), tablaM(NULL), nTablas(conj())
{}

BaseDeDatos::tuplaAux::tuplaAux(Tabla t):
	tab(t), nombresJoins(conj()), j(Dicc())
{}

BaseDeDatos::nodoJoin::nodoJoin():
	//Modificar. Siempre se va a crear por referencia.
{}

BaseDeDatos::tuplaJoin::tuplaJoin():
	//Modificar. Siempre se va a crear por referencia.
{}


BaseDeDatos::indiceSAux::indiceSAux():
	//Modificar. Siempre se va a crear por referencia.
{}

BaseDeDatos::indiceNAux::indiceNAux():
	//Modificar. Siempre se va a crear por referencia.
{}

BaseDeDatos::tuplaUnion::tuplaUnion():
	//Modificar. Siempre se va a crear por referencia.
{}

BaseDeDatos::tuplaCambios::tuplaCambios():
	//Modificar. Siempre se va a crear por referencia.
{}


