#include "BaseDeDatos.h"
#include "Driver.cpp"
//#include "tabla.h"

using namespace aed2;

/////////////////////////////////////////////////////////FUNCION AUXILIAR UNIR REGISTROS
Driver::Registro unirRegistros(const Driver::Registro& a, const Driver::Registro& b){
	Driver::Registro res = Driver::Registro();
	Driver::Registro::const_Iterador itA = a.CrearIt();
	Driver::Registro::const_Iterador itB = b.CrearIt();
	while(itA.HaySiguiente()){
		res.Definir(itA.SiguienteClave(), itA.SiguienteSignificado());
		itA.Avanzar();
	}

	while(itB.HaySiguiente()){
			if(!res.Definido(itB.SiguienteClave())){
			res.Definir(itB.SiguienteClave(), itB.SiguienteSignificado());
			}
		itB.Avanzar();
	}
	return res;
};
/////////////////////////////////////////////////////////FUNCION AUXILIAR UNIR REGISTROS

/////////////////////////////////////////////////////////FUNCION AUXILIAR REGISTRO VACIO
bool registroVacio(const Driver::Registro& r){
	bool res = true;
	Driver::Registro::const_Iterador it = r.CrearIt();
		if(it.HaySiguiente()){
			res = false;
		}
	return res;
};
/////////////////////////////////////////////////////////FUNCION AUXILIAR REGISTRO VACIO

///////////////////////////////////////////////////FUNCION AUXILIAR REGISTROS CONTENIDOS
bool registrosContenidos(const Driver::Registro& r1, const Driver::Registro& r2){
	Driver::Registro::const_Iterador it = r1.CrearIt();
		while(it.HaySiguiente()){ 
			if(!(r2.Definido((it.SiguienteClave())))){
				return false;
			}else{
				if((r2.Significado((it.SiguienteClave()))) != it.SiguienteSignificado()){
					return false;
				}
			}
			it.Avanzar();
		}
		return true; //devuelve true si r1 esta contenido en r2 (hangyaku no lelouch)
}
///////////////////////////////////////////////////FUNCION AUXILIAR REGISTROS CONTENIDOS

int main()
{
  Driver::Registro r;

  return 0;
}


BaseDeDatos::BaseDeDatos(){
	Dicc<NombreTabla, tuplaAux> d = Dicc<NombreTabla, tuplaAux>();
	Conj<NombreTabla> t = Conj<NombreTabla>();

	arbolTablas = d;
	tablaM = "empty";
	nTablas = t;
	vacio = Conj<Driver::Registro>();

}

BaseDeDatos::tuplaAux::tuplaAux(Tabla* t){
 	Conj<NombreTabla> c = Conj<NombreTabla>();
 	Dicc<NombreTabla, nodoJoin> d = Dicc<NombreTabla, nodoJoin>();

 	tab = t;
 	nombresJoins = c;
 	dicJoin = d;

 }

BaseDeDatos::nodoJoin::nodoJoin(tuplaJoin* t, bool v){
 	principal = v;
 	p = t;
 }

BaseDeDatos::tuplaJoin::tuplaJoin(NombreCampo c, TipoCampo t, Conj<NombreTabla>::Iterador t1, Conj<NombreTabla>::Iterador t2){
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
	nombreJoint1 = t1;
	nombreJoint2 = t2;


 }


BaseDeDatos::tuplaUnion::tuplaUnion(Driver::Registro r1, Driver::Registro r2, Conj<Driver::Registro>::Iterador i){
		registroTablaUno = r1;
		registroTablaDos = r2;
		registroJoin = i;
	}

BaseDeDatos::tuplaCambios::tuplaCambios(NombreTabla n, Driver::Registro reg, bool a){
    	nTabla = n;
		r = reg;
		agregar  = a;
    }

	
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


void BaseDeDatos::agregarTabla(Tabla& t){
	Tabla* p = &t;
	tuplaAux a = tuplaAux(p);
	nTablas.Agregar(t.nombreDeLaTabla());

	arbolTablas.Definir(t.nombreDeLaTabla(), a);
};

void BaseDeDatos::borrarJoin(const NombreTabla t1, const NombreTabla t2){
	tuplaJoin* a = (((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).p;
	(a->nombreJoint1).EliminarSiguiente(); //WARNING! SI SE INDEFINE BORRANDO UN ELEMENTO EXPLOTA TODO!
	(a->nombreJoint2).EliminarSiguiente(); 
	delete a;
	((arbolTablas.Significado(t1)).dicJoin).Borrar(t2);
	((arbolTablas.Significado(t2)).dicJoin).Borrar(t1); 


	// tuplaJoin* b = (((arbolTablas.Significado(t2)).dicJoin).Significado(t1)).p;
	// //WARNING! SI SE INDEFINE BORRANDO UN ELEMENTO EXPLOTA TODO!
	// delete b;
	// 
}

void BaseDeDatos::generarVistaJoin(const NombreTabla t1, const NombreTabla t2, const NombreCampo c){
	Conj<NombreTabla>::Iterador c2 = ((arbolTablas.Significado(t1)).nombresJoins).AgregarRapido(t2);
	Conj<NombreTabla>::Iterador c1 = ((arbolTablas.Significado(t2)).nombresJoins).AgregarRapido(t1);
	Tabla* te1 = (arbolTablas.Significado(t1)).tab;
	Tabla* te2 = (arbolTablas.Significado(t2)).tab;

	TipoCampo tc;
	if ((*te1).tipoCampo(c))
	{
		tc = NAT;
	}else{
		tc = STR;
	};

	tuplaJoin* tj = new tuplaJoin(c, tc, c1, c2);

	nodoJoin nj1 = nodoJoin(tj, true);
	nodoJoin nj2 = nodoJoin(tj, false);

	(((arbolTablas.Significado(t1)).dicJoin).Definir(t2, nj1));
	(((arbolTablas.Significado(t2)).dicJoin).Definir(t1, nj2));

	Conj<Driver::Registro>::Iterador it1 = ((*te1).registros()).CrearIt();
	Conj<Driver::Registro>::Iterador it2 = ((*te2).registros()).CrearIt();


	// Dicc<String, tuplaUnion> indiceS;
	// Dicc<Nat, tuplaUnion> indiceN;

	Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
	while(it1.HaySiguiente()){
		Driver::Registro regvacio = Driver::Registro();
		tuplaUnion tu = tuplaUnion(it1.Siguiente(), regvacio, v);

		if (tc == STR)
		{
			(tj->indiceS).Definir(((it1.Siguiente()).Significado(c)).dameString(), tu);
		}else{
			(tj->indiceN).Definir(((it1.Siguiente()).Significado(c)).dameNat(), tu);
		}
		it1.Avanzar();
	};

		while(it2.HaySiguiente()){
		if (tc == STR){	

			if((tj->indiceS).Definido(((it2.Siguiente()).Significado(c)).dameString())){
				((tj->indiceS).Significado(((it2.Siguiente()).Significado(c)).dameString())).registroTablaDos = it2.Siguiente();
				Driver::Registro registroUnido = unirRegistros(((tj->indiceS).Significado(((it2.Siguiente()).Significado(c)).dameString())).registroTablaUno, it2.Siguiente());
				Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);	
				((tj->indiceS).Significado(((it2.Siguiente()).Significado(c)).dameString())).registroJoin = iteradorJoin;
			}else{
				Driver::Registro regvacio = Driver::Registro();
				tuplaUnion tu = tuplaUnion(regvacio, it2.Siguiente(), v);
				(tj->indiceS).Definir(((it1.Siguiente()).Significado(c)).dameString(), tu);
			}

		}else{

			if((tj->indiceN).Definido(((it2.Siguiente()).Significado(c)).dameNat())){
				((tj->indiceN).Significado(((it2.Siguiente()).Significado(c)).dameNat())).registroTablaDos = it2.Siguiente();
				Driver::Registro registroUnido = unirRegistros(((tj->indiceN).Significado(((it2.Siguiente()).Significado(c)).dameNat())).registroTablaUno, it2.Siguiente());
				Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);	
				((tj->indiceN).Significado(((it2.Siguiente()).Significado(c)).dameNat())).registroJoin = iteradorJoin;
			}else{
				Driver::Registro regvacio = Driver::Registro();
				tuplaUnion tu = tuplaUnion(regvacio, it2.Siguiente(), v);
				(tj->indiceN).Definir(((it1.Siguiente()).Significado(c)).dameNat(), tu);
			}
		}
		it2.Avanzar();
	};
}


void BaseDeDatos::insertarEntrada(const Driver::Registro& r, NombreTabla t){
	Tabla* t1 = (arbolTablas.Significado(t)).tab;
	Conj<NombreTabla>::Iterador it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();

	tuplaCambios cam = tuplaCambios(t, r, true);
	
	while(it.HaySiguiente()){
		tuplaJoin* a = (((arbolTablas.Significado(t)).dicJoin).Significado(it.Siguiente())).p;
		(a->modificaciones).AgregarAdelante(cam);
	}
	(*t1).agregarRegistro(r); //SE AGREGA AHORA, NO?
}

void BaseDeDatos::borrar(const Driver::Registro& r, NombreTabla t){
	Tabla* t1 = (arbolTablas.Significado(t)).tab;
	Conj<NombreTabla>::Iterador it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();

	tuplaCambios cam = tuplaCambios(t, r, false);
	
	while(it.HaySiguiente()){
		tuplaJoin* a = (((arbolTablas.Significado(t)).dicJoin).Significado(it.Siguiente())).p;
		(a->modificaciones).AgregarAdelante(cam);
	}
	(*t1).quitarRegistro(r); //SE BORRA AHORA, NO?
}

Conj<Driver::Registro>::const_Iterador BaseDeDatos::vistaJoin(const NombreTabla t1, const NombreTabla t2){
	tuplaJoin* tj = (((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).p;
	Lista<tuplaCambios>::Iterador it = (tj->modificaciones).CrearIt();

while(it.HaySiguiente()){
		
		if((it.Siguiente()).agregar){																		//CASO AGREGAR

			if(((it.Siguiente()).nTabla) == t1){															//CASO TABLA1
				
				if(tj->indiceSValido){																		//CASO INDICE STRING

					String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

					if((tj->indiceS).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceS).Significado(parametro)).registroTablaUno = (it.Siguiente()).r;
						Driver::Registro registroUnido = unirRegistros(((it.Siguiente()).r), ((tj->indiceS).Significado(parametro)).registroTablaDos);
						Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
						((tj->indiceS).Significado(parametro)).registroJoin = iteradorJoin;

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						Driver::Registro regvacio = Driver::Registro();
						Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
						tuplaUnion tu = tuplaUnion((it.Siguiente()).r, regvacio, v);
						(tj->indiceS).Definir(parametro, tu);
					}	

				}else{																						//CASO INDICE NAT

					Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

					if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceN).Significado(parametro)).registroTablaUno = (it.Siguiente()).r;
						Driver::Registro registroUnido = unirRegistros(((it.Siguiente()).r), ((tj->indiceN).Significado(parametro)).registroTablaDos);
						Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
						((tj->indiceN).Significado(parametro)).registroJoin = iteradorJoin;

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						Driver::Registro regvacio = Driver::Registro();
						Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
						tuplaUnion tu = tuplaUnion((it.Siguiente()).r, regvacio, v);
						(tj->indiceN).Definir(parametro, tu);
					}
				}

			}else{																							//CASO TABLA2

				if(tj->indiceSValido){																		//CASO INDICE STRING

					String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

					if((tj->indiceS).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceS).Significado(parametro)).registroTablaDos = (it.Siguiente()).r;
						Driver::Registro registroUnido = unirRegistros(((tj->indiceS).Significado(parametro)).registroTablaUno, ((it.Siguiente()).r));
						Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
						((tj->indiceS).Significado(parametro)).registroJoin = iteradorJoin;

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						Driver::Registro regvacio = Driver::Registro();
						Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
						tuplaUnion tu = tuplaUnion(regvacio, (it.Siguiente()).r, v);
						(tj->indiceS).Definir(parametro, tu);
					}	

				}else{																						//CASO INDICE NAT

					Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

					if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceN).Significado(parametro)).registroTablaDos = (it.Siguiente()).r;
						Driver::Registro registroUnido = unirRegistros(((tj->indiceN).Significado(parametro)).registroTablaUno, ((it.Siguiente()).r));
						Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
						((tj->indiceN).Significado(parametro)).registroJoin = iteradorJoin;

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						Driver::Registro regvacio = Driver::Registro();
						Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
						tuplaUnion tu = tuplaUnion(regvacio, (it.Siguiente()).r, v);
						(tj->indiceN).Definir(parametro, tu);
					}
				}
			}

		}else{																								//CASO BORRAR

			if(((it.Siguiente()).nTabla) == t1){															//CASO TABLA1
				
				if(tj->indiceSValido){																		//CASO INDICE STRING

					String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

					if(registroVacio(((tj->indiceS).Significado(parametro)).registroTablaDos)){				//CASO ESTA DEFINIDO (para la otra tabla, es decir, estan unidos)
						((tj->indiceS).Significado(parametro)).registroTablaUno = Driver::Registro();
						Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceS).Significado(parametro)).registroJoin;
						iteradorJoin.EliminarSiguiente();

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceS).Significado(parametro)).registroTablaUno = Driver::Registro();
					}	

				}else{																						//CASO INDICE NAT

					Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

					if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla, es decir, estan unidos)
						((tj->indiceN).Significado(parametro)).registroTablaUno = Driver::Registro();
						Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceN).Significado(parametro)).registroJoin;
						iteradorJoin.EliminarSiguiente();

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceN).Significado(parametro)).registroTablaUno = Driver::Registro();
					}
				}

			}else{																							//CASO TABLA2

				if(tj->indiceSValido){																		//CASO INDICE STRING

					String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

					if((tj->indiceS).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla, es decir, estan unidos)
						((tj->indiceS).Significado(parametro)).registroTablaDos = Driver::Registro();
						Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceS).Significado(parametro)).registroJoin;
						iteradorJoin.EliminarSiguiente();

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceS).Significado(parametro)).registroTablaDos = Driver::Registro();
					}	

				}else{																						//CASO INDICE NAT

					Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

					if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla, es decir, estan unidos)
						((tj->indiceN).Significado(parametro)).registroTablaDos = Driver::Registro();
						Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceN).Significado(parametro)).registroJoin;
						iteradorJoin.EliminarSiguiente();

					}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
						((tj->indiceN).Significado(parametro)).registroTablaDos = Driver::Registro();
					}
				}
			}
		}

	it.Avanzar();
	};

	return (tj->vistaJoin).CrearIt();
}

Conj<Driver::Registro>& BaseDeDatos::buscar(const Driver::Registro& r, NombreTabla t){
	Conj<Driver::Registro>::Iterador itRegistros = ((*(arbolTablas.Significado(t).tab)).registros()).CrearIt();
	Conj<NombreCampo>::Iterador itIndices = ((*(arbolTablas.Significado(t).tab)).indices()).CrearIt();
	Conj<Driver::Registro>* res = new Conj<Driver::Registro>();

		while(itIndices.HaySiguiente()){							//este while solo se hace para acelerar la complejidad en algunos casos
			if(r.Definido(itIndices.Siguiente())){
				Driver::Registro reg = (*(arbolTablas.Significado(t).tab)).obtenerDeIndice(false,0,itIndices.Siguiente());
					if(registrosContenidos(r, reg)){
						(*res).Agregar(reg);
					}
				return (*res);
			}
		itIndices.Avanzar();
		}

		while(itRegistros.HaySiguiente()){ 							//este while funciona siempre, pero tarda mas
			if(registrosContenidos(r, itRegistros.Siguiente())){
				(*res).Agregar(itRegistros.Siguiente());
			}

		itRegistros.Avanzar();
		}

	return (*res);
}

















