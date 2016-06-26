#include "BaseDeDatos.h"

using namespace aed2;

int main()
{
  Driver::Registro r;

  return 0;
}


BaseDeDatos::BaseDeDatos(): 
	arbolTablas(aed2::Dicc::Dicc()), tablaM(NULL), nTablas(aed2::Conj::Conj())
{}

// BaseDeDatos::tuplaAux::tuplaAux(Tabla t):
// 	tab(t), nombresJoins(conj()), j(Dicc())
// {}

// BaseDeDatos::nodoJoin::nodoJoin():
// 	//Modificar. Siempre se va a crear por referencia.
// {}

// BaseDeDatos::tuplaJoin::tuplaJoin():
// 	//Modificar. Siempre se va a crear por referencia.
// {}


// BaseDeDatos::indiceSAux::indiceSAux():
// 	//Modificar. Siempre se va a crear por referencia.
// {}

// BaseDeDatos::indiceNAux::indiceNAux():
// 	//Modificar. Siempre se va a crear por referencia.
// {}

// BaseDeDatos::tuplaUnion::tuplaUnion():
// 	//Modificar. Siempre se va a crear por referencia.
// {}

// BaseDeDatos::tuplaCambios::tuplaCambios():
// 	//Modificar. Siempre se va a crear por referencia.
// {}


