#include "BaseDeDatos.h"
#include "Driver.cpp"
//#include "tabla.h"

using namespace aed2;

int main()
{
  Driver::Registro r;

  return 0;
}


BaseDeDatos::BaseDeDatos() 
	//arbolTablas(aed2::Dicc::Dicc()), tablaM(NULL), nTablas(aed2::Conj::Conj())
{
	Dicc<NombreTabla, tuplaAux> d = Dicc<NombreTabla, tuplaAux>();
	Conj<NombreTabla> t = Conj<NombreTabla>();

	arbolTablas = d;
	tablaM = "empty";
	nTablas = t;

}

BaseDeDatos::tuplaAux::tuplaAux(Tabla* t)
 // 	tab(t), nombresJoins(conj()), j(Dicc())
 {
 	Conj<NombreTabla> c = Conj<NombreTabla>();
 	Dicc<NombreTabla, nodoJoin> d = Dicc<NombreTabla, nodoJoin>();


 	tab = t;
 	nombresJoins = c;
 	dicJoin = d;

 }

BaseDeDatos::nodoJoin::nodoJoin(tuplaJoin* t, bool v)
// 	//Modificar. Siempre se va a crear por referencia.
 {
 	principal = v;
 	p = t;
 }

BaseDeDatos::tuplaJoin::tuplaJoin(NombreCampo c, TipoCampo t)
// 	//Modificar. Siempre se va a crear por referencia.
 {
 	Conj<Driver::Registro> a = Conj<Driver::Registro>();
 	Dicc<String, tuplaUnion> i = Dicc<String, tuplaUnion>();
 	Dicc<Nat, tuplaUnion> j = Dicc<Nat, tuplaUnion>();
 	Lista<tuplaCambios> l = Lista<tuplaCambios>();

 	cJoin = c;
	vistaJoin = a;
	indiceS = i;
	indiceN = j;
	modificaciones = l;
	if (t == NAT){
		indiceSValido = false;
		indiceNValido = true;
	}else if (t == STR){
		indiceSValido = true;
		indiceNValido = false;
	};

 }


// BaseDeDatos::tuplaUnion::tuplaUnion():
// 	//Modificar. Siempre se va a crear por referencia.
// {}

// BaseDeDatos::tuplaCambios::tuplaCambios():
// 	//Modificar. Siempre se va a crear por referencia.
// {}

	// void insertarEntrada(const Driver::Registro& r, NombreTabla t);
	// void borrar(const Driver::Registro& r, NombreTabla t);
	// void generarVistaJoin(const NombreTabla t1, const NombreTabla t2, const NombreCampo c);
	// Conj<Driver::Registro>::const_Iterador vistaJoin(const NombreTabla t1, const NombreTabla t2);
	// void borrarJoin(const NombreTabla t1, const NombreTabla t2);
	// Conj<Driver::Registro>& buscar(const Driver::Registro& crit, const NombreTabla t);


Conj<NombreTabla>::const_Iterador BaseDeDatos::tablas(){

	return nTablas.CrearIt();
};

NombreTabla BaseDeDatos::tablaMaxima(){
	return tablaM;
};

Tabla& BaseDeDatos::dameTabla(const NombreTabla t){
	//tuplaAux a = arbolTablas.Significado(t);
	return (*(arbolTablas.Significado(t)).tab);
};

NombreCampo BaseDeDatos::campoJoin(const NombreTabla t1, const NombreTabla t2){
	tuplaJoin* a = (((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).p;

	return a->cJoin;
};

bool BaseDeDatos::hayJoin(const NombreTabla t1, const NombreTabla t2){

	bool r = (((arbolTablas.Significado(t1)).dicJoin).Definido(t2));
	return r;
};

// void agregarTabla(const Tabla& t);

void BaseDeDatos::agregarTabla(Tabla& t){
	Tabla* p = &t;
	tuplaAux a = tuplaAux(p);
	nTablas.Agregar(t.nombreDeLaTabla());

	arbolTablas.Definir(t.nombreDeLaTabla(), a);

};






















