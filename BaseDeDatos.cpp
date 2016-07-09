#include "BaseDeDatos.h"
//#include "Driver.cpp"
//#include "tabla.h"

using namespace aed2;

// /////////////////////////////////////////////////////////FUNCION AUXILIAR MOSTRAR REGISTRO
// void mostrarReg(Registro reg){
// 			Registro::Iterador pepe = reg.CrearIt();
// 			cout << "** MUESTRO REGISTRO **" << endl;
// 			int i = 1;
// 			while(pepe.HaySiguiente()){
// 				cout << i << ")";
// 				cout << "    " << pepe.SiguienteClave() << ":";
// 				if((pepe.SiguienteSignificado()).esNat()){
// 					cout << "        " << (pepe.SiguienteSignificado()).dameNat() << endl;
// 				}else{
// 					cout << "        " <<(pepe.SiguienteSignificado()).dameString() << endl;
// 				}
// 				pepe.Avanzar();
// 				i++;
// 			}
// 			cout << "     ** FIN **" << endl;
// 		}

/////////////////////////////////////////////////////////FUNCION AUXILIAR UNIR REGISTROS
Registro unirRegistros(const Registro& a, const Registro& b){
	Registro res = Registro();
	Registro::const_Iterador itA = a.CrearIt();
	Registro::const_Iterador itB = b.CrearIt();
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
bool registroVacio(const Registro& r){
	bool res = true;
	Registro::const_Iterador it = r.CrearIt();
		if(it.HaySiguiente()){
			res = false;
		}
	return res;
};
/////////////////////////////////////////////////////////FUNCION AUXILIAR REGISTRO VACIO

///////////////////////////////////////////////////FUNCION AUXILIAR REGISTROS CONTENIDOS
bool registrosContenidos(const Registro& r1, const Registro& r2){
	Registro::const_Iterador it = r1.CrearIt();
		while(it.HaySiguiente()){
//			cout << it.SiguienteClave() << endl;
			if(!(r2.Definido((it.SiguienteClave())))){
				return false;
			}else{
				if(!((r2.Significado(it.SiguienteClave())) == it.SiguienteSignificado())){
					return false;
				}
			}
			it.Avanzar();
		}
		return true; //devuelve true si r1 esta contenido en r2 (hangyaku no lelouch)
}
///////////////////////////////////////////////////FUNCION AUXILIAR REGISTROS CONTENIDOS

/////////////////////////////////////////////////////////////////////////////////////////CONSTRUCTORES
BaseDeDatos::BaseDeDatos(){
	DicString<tuplaAux> d = DicString<tuplaAux>();
	Conj<NombreTabla> t = Conj<NombreTabla>();

	arbolTablas = d;
	tablaM = "empty";
	nTablas = t;
	vacio = Conj<Registro>();
}
BaseDeDatos::~BaseDeDatos(){
Conj<NombreTabla>::const_Iterador it = nTablas.CrearIt();
	while(it.HaySiguiente()){
 	
 		//ITERADOR DE LOS NOMBRES CON LOS QUE HIZO JOIN 
		Conj<NombreTabla> nombres = (arbolTablas.Significado(it.Siguiente())).nombresJoins;
		Conj<NombreTabla>::const_Iterador itJoin = nombres.CrearIt();
		
		while(itJoin.HaySiguiente()){
			
			//((((arbolTablas.Significado(it.Siguiente()))).dicJoin).Significado(itJoin.Siguiente())).principal
			if (hayJoin(it.Siguiente(), itJoin.Siguiente())){
				if (hayJoin(itJoin.Siguiente(), it.Siguiente())){
					
					borrarJoin(itJoin.Siguiente(), it.Siguiente());
				}else{
					
				borrarJoin(it.Siguiente(), itJoin.Siguiente());	
				}
			}
			itJoin.Avanzar();	
		}
		it.Avanzar();
	}	

	Conj<NombreTabla>::const_Iterador it2 = nTablas.CrearIt();
	while(it2.HaySiguiente()){
 	delete((arbolTablas.Significado(it2.Siguiente())).tab);
 	it2.Avanzar();
 	}
	
}

BaseDeDatos::tuplaAux::tuplaAux(Tabla* t){
 	Conj<NombreTabla> c = Conj<NombreTabla>();
 	DicString<nodoJoin> d = DicString<nodoJoin>();

 	tab = t;
 	nombresJoins = c;
 	dicJoin = d;

 }

BaseDeDatos::nodoJoin::nodoJoin(tuplaJoin* t, bool v){
 	principal = v;
 	p = t;
 }

BaseDeDatos::tuplaJoin::tuplaJoin(NombreCampo c, TipoCampo t, Conj<NombreTabla>::Iterador t1, Conj<NombreTabla>::Iterador t2){
 	Conj<Registro> a = Conj<Registro>();
 	DicString<tuplaUnion> i = DicString<tuplaUnion>();
 	DicNat<Nat, tuplaUnion> j = DicNat<Nat, tuplaUnion>();
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


BaseDeDatos::tuplaUnion::tuplaUnion(Registro r1, Registro r2, Conj<Registro>::Iterador i){
//		Registro* reg1 = new Registro(r1);
//		Registro* reg2 =  Registro(r2);

//		registroTablaUno = *reg1;
//		registroTablaDos = *reg2;
		registroTablaUno = r1;
		registroTablaDos = r2;
		registroJoin = i;
	}


BaseDeDatos::tuplaCambios::tuplaCambios(NombreTabla n, Registro reg, bool a){
    	nTabla = n;
		r = reg;
		agregar  = a;
    }


/////////////////////////////////////////////////////////////////////////////////////////FUNCIONES

Conj<NombreTabla>::const_Iterador BaseDeDatos::tablas(){
	return nTablas.CrearIt();
};

 NombreTabla BaseDeDatos::tablaMaxima() const{
	return tablaM;
};

Tabla& BaseDeDatos::dameTabla(const NombreTabla t) const{
	//tuplaAux a = arbolTablas.Significado(t);
	NombreTabla nombre = t;
	Tabla* res = ((arbolTablas.Significado(nombre)).tab);
	return *res;
};

 NombreCampo BaseDeDatos::campoJoin(const NombreTabla t1, const NombreTabla t2) const{
	tuplaJoin* a = (((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).p;

	return a->cJoin;
};

 bool BaseDeDatos::hayJoin(const NombreTabla t1, const NombreTabla t2) const {

	bool r;

	if (((arbolTablas.Significado(t1)).dicJoin).Definido(t2)){
		r = ((((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).principal);
	}else{
    	 cout << "ESTO TIENE QUE SER UN CERO---> " << ((arbolTablas.Significado(t1)).nombresJoins).Pertenece(t2) << endl;
		 r = false; }

	return r;
};


void BaseDeDatos::agregarTabla(Tabla& t){
	Tabla* p = &t;
	tuplaAux a = tuplaAux(p);
	nTablas.AgregarRapido(t.nombreDeLaTabla());

	arbolTablas.Definir(t.nombreDeLaTabla(), a);
};

void BaseDeDatos::borrarJoin(const NombreTabla t1, const NombreTabla t2){
	if (hayJoin(t2, t1))
	{
		((arbolTablas.Significado(t1)).dicJoin).Significado(t2).principal = false;
	}else{

		tuplaJoin* a = (((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).p;
		(a->nombreJoint1).EliminarSiguiente(); //WARNING! SI SE INDEFINE BORRANDO UN ELEMENTO EXPLOTA TODO!
		(a->nombreJoint2).EliminarSiguiente();
		delete a;
		((arbolTablas.Significado(t1)).dicJoin).Borrar(t2);
		((arbolTablas.Significado(t2)).dicJoin).Borrar(t1);

	}
	// tuplaJoin* b = (((arbolTablas.Significado(t2)).dicJoin).Significado(t1)).p;
	// //WARNING! SI SE INDEFINE BORRANDO UN ELEMENTO EXPLOTA TODO!
	// delete b;
	//
}

void BaseDeDatos::generarVistaJoin(const NombreTabla t1, const NombreTabla t2, const NombreCampo c){
	//Conj<NombreTabla>::Iterador c2 = ((arbolTablas.Significado(t1)).nombresJoins).AgregarRapido(t2);
	//Conj<NombreTabla>::Iterador c1 = ((arbolTablas.Significado(t2)).nombresJoins).AgregarRapido(t1);
	Tabla* te1 = (arbolTablas.Significado(t1)).tab;
	Tabla* te2 = (arbolTablas.Significado(t2)).tab;
 	

	TipoCampo tc;
	if ((*te1).tipoCampo(c))
	{
		tc = NAT;
	}else{
		tc = STR;

	};

	if (hayJoin(t2, t1))
	{
		((arbolTablas.Significado(t1)).dicJoin).Significado(t2).principal = true;
	} else {
		Conj<NombreTabla>::Iterador c2 = ((arbolTablas.Significado(t1)).nombresJoins).AgregarRapido(t2);
		Conj<NombreTabla>::Iterador c1 = ((arbolTablas.Significado(t2)).nombresJoins).AgregarRapido(t1);

		tuplaJoin* tj = new tuplaJoin(c, tc, c1, c2);

		nodoJoin nj1 = nodoJoin(tj, true);
		nodoJoin nj2 = nodoJoin(tj, false);

		(((arbolTablas.Significado(t1)).dicJoin).Definir(t2, nj1));
		(((arbolTablas.Significado(t2)).dicJoin).Definir(t1, nj2));

		Conj<Registro> regsit1 = ((*te1).registros());
		Conj<Registro> regsit2 = ((*te2).registros());

		Conj<Registro>::Iterador it1 = regsit1.CrearIt();
		Conj<Registro>::Iterador it2 = regsit2.CrearIt();

		// Dicc<String, tuplaUnion> indiceS;
		// Dicc<Nat, tuplaUnion> indiceN;

		Conj<Registro>::Iterador v = vacio.CrearIt();
		while(it1.HaySiguiente()){
			Registro regvacio = Registro();
			tuplaUnion tu = tuplaUnion(it1.Siguiente(), regvacio, v);

			if (tc == STR){
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
				Registro registroUnido = unirRegistros(((tj->indiceS).Significado(((it2.Siguiente()).Significado(c)).dameString())).registroTablaUno, it2.Siguiente());
				Conj<Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
				((tj->indiceS).Significado(((it2.Siguiente()).Significado(c)).dameString())).registroJoin = iteradorJoin;
			}else{
				Registro regvacio = Registro();
				tuplaUnion tu = tuplaUnion(regvacio, it2.Siguiente(), v);
				(tj->indiceS).Definir(((it2.Siguiente()).Significado(c)).dameString(), tu);
			}

		}else{

			if((tj->indiceN).Definido(((it2.Siguiente()).Significado(c)).dameNat())){
				((tj->indiceN).Significado(((it2.Siguiente()).Significado(c)).dameNat())).registroTablaDos = it2.Siguiente();
				Registro registroUnido = unirRegistros(((tj->indiceN).Significado(((it2.Siguiente()).Significado(c)).dameNat())).registroTablaUno, it2.Siguiente());
				Conj<Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
				((tj->indiceN).Significado(((it2.Siguiente()).Significado(c)).dameNat())).registroJoin = iteradorJoin;
			}else{
				Registro regvacio = Registro();
				tuplaUnion tu = tuplaUnion(regvacio, it2.Siguiente(), v);
				(tj->indiceN).Definir(((it2.Siguiente()).Significado(c)).dameNat(), tu);
			}
		}
		it2.Avanzar();
		};
	}
}


void BaseDeDatos::insertarEntrada(const Registro r, const NombreTabla& t){
	Tabla* t1 = (arbolTablas.Significado(t)).tab;
	Tabla* tm;
	if (tablaM != "empty"){
		tm = (arbolTablas.Significado(tablaM)).tab;
	}
	Conj<NombreTabla>::Iterador it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();

	tuplaCambios cam = tuplaCambios(t, r, true);

	while(it.HaySiguiente()){
		tuplaJoin* a = (((arbolTablas.Significado(t)).dicJoin).Significado(it.Siguiente())).p;
		cout << "INSERTASTE ALGO EN LA TABLA!" << endl;
		cout << it.Siguiente() << endl;
		(a->modificaciones).AgregarAtras(cam);
		it.Avanzar();
	}

	(*t1).agregarRegistro(r); //SE AGREGA AHORA, NO?

	if (tablaM == "empty"){
		tablaM = t;
	} else if ((*t1).accesos() > (*tm).accesos()){
		tablaM = t;
	}
}

void BaseDeDatos::borrar(const Registro& r, NombreTabla t){
	Tabla* t1 = (arbolTablas.Significado(t)).tab;
	Tabla* tm;
	if (tablaM != "empty"){
		tm = (arbolTablas.Significado(tablaM)).tab;
	}
	//cout << "ENTRA A BUSCAR"<< endl;
	Conj<Registro> todos = buscar(r, t);
	//cout << "SALIO DEL BUSCAR"<< endl;
	Conj<Registro>::Iterador itbuscar = todos.CrearIt();
	Conj<NombreTabla>::Iterador it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();

	while(itbuscar.HaySiguiente()){
		//cout << "SE VA A BORRAR EL REGISTRO: " << endl;
		//mostrarReg(itbuscar.Siguiente());
		(*t1).quitarRegistro(itbuscar.Siguiente());

		it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();
		while(it.HaySiguiente()){
		tuplaJoin* a = (((arbolTablas.Significado(t)).dicJoin).Significado(it.Siguiente())).p;
		tuplaCambios cam = tuplaCambios(t, itbuscar.Siguiente(), false);
		(a->modificaciones).AgregarAtras(cam);
		it.Avanzar();
		}

		itbuscar.Avanzar();
	}

	if (tablaM == "empty"){
		tablaM = t;
	} else if ((*t1).accesos() > (*tm).accesos()){
		tablaM = t;
	}

}

/*
//ES UN COPY PASTE DE BORRAR, LO HACE SOLAMENTE PARA UN REGISTRO
void BaseDeDatos::borrarRegistro(const Registro& r, NombreTabla t){

	Tabla* t1 = (arbolTablas.Significado(t)).tab;
	Tabla* tm;
	if (tablaM != "empty"){
		tm = (arbolTablas.Significado(tablaM)).tab;
	}

		(*t1).quitarRegistro(r);

		Conj<NombreTabla>::Iterador it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();
		
		while(it.HaySiguiente()){
		tuplaJoin* a = (((arbolTablas.Significado(t)).dicJoin).Significado(it.Siguiente())).p;
		tuplaCambios cam = tuplaCambios(t, r, false);
		(a->modificaciones).AgregarAtras(cam);
		it.Avanzar();
		}

	if (tablaM == "empty"){
		tablaM = t;
	} else if ((*t1).accesos() > (*tm).accesos()){
		tablaM = t;
	}

}
*/

Conj<Registro> BaseDeDatos::vistaJoin(const NombreTabla t1, const NombreTabla t2){
	tuplaJoin* tj = (((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).p;
	Lista<tuplaCambios>::Iterador it = (tj->modificaciones).CrearIt();

	while(it.HaySiguiente()){
	cout << "NUEVA ITERACION" << endl;

			if((it.Siguiente()).agregar){																		//CASO AGREGAR
				cout << "agregar" << endl;

				if(((it.Siguiente()).nTabla) == t1){															//CASO TABLA1
					cout << "tabla1" << endl;

					if(tj->indiceSValido){																		//CASO INDICE STRING
						cout << "indice string" << endl;

						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

						if((tj->indiceS).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceS).Significado(parametro)).registroTablaUno = (it.Siguiente()).r;
							Registro registroUnido = unirRegistros(((it.Siguiente()).r), ((tj->indiceS).Significado(parametro)).registroTablaDos);
							Conj<Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceS).Significado(parametro)).registroJoin = iteradorJoin;

						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
							cout << "no esta definido para la otra tabla" << endl;
							Registro regvacio = Registro();
							Conj<Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion((it.Siguiente()).r, regvacio, v);
							(tj->indiceS).Definir(parametro, tu);
						}

					}else{
																										//CASO INDICE NAT
						cout << "indice nat" << endl;

						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

						cout << parametro << endl;

						if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceN).Significado(parametro)).registroTablaUno = (it.Siguiente()).r;
							Registro registroUnido = unirRegistros(((it.Siguiente()).r), ((tj->indiceN).Significado(parametro)).registroTablaDos);
							Conj<Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceN).Significado(parametro)).registroJoin = iteradorJoin;
						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
							cout << "no esta definido para la otra tabla" << endl;
							Registro regvacio = Registro();
							Conj<Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion((it.Siguiente()).r, regvacio, v);
							(tj->indiceN).Definir(parametro, tu);
						}
					}

				}else{																							//CASO TABLA2
					cout << "tabla2" << endl;

					if(tj->indiceSValido){																		//CASO INDICE STRING
						cout << "indice string" << endl;

						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

						if((tj->indiceS).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceS).Significado(parametro)).registroTablaDos = (it.Siguiente()).r;
							Registro registroUnido = unirRegistros(((tj->indiceS).Significado(parametro)).registroTablaUno, ((it.Siguiente()).r));
							Conj<Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceS).Significado(parametro)).registroJoin = iteradorJoin;

						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
							cout << "no esta definido para la otra tabla" << endl;
							Registro regvacio = Registro();
							Conj<Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion(regvacio, (it.Siguiente()).r, v);
							(tj->indiceS).Definir(parametro, tu);
						}

					}else{																						//CASO INDICE NAT
						cout << "indice nat" << endl;
						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

						if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceN).Significado(parametro)).registroTablaDos = (it.Siguiente()).r;
							Registro registroUnido = unirRegistros(((tj->indiceN).Significado(parametro)).registroTablaUno, ((it.Siguiente()).r));
							Conj<Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceN).Significado(parametro)).registroJoin = iteradorJoin;
						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
							cout << "no esta definido para la otra tabla" << endl;
							Registro regvacio = Registro();
							Conj<Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion(regvacio, (it.Siguiente()).r, v);
							(tj->indiceN).Definir(parametro, tu);
						}
					}
				}

			}else{																								//CASO BORRAR
				cout << "borrar" << endl;

				if(((it.Siguiente()).nTabla) == t1){															//CASO TABLA1
					cout << "tabla1" << endl;

					if(tj->indiceSValido){																		//CASO INDICE STRING
						cout << "indice string" << endl;

						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceS).Significado(parametro)).registroTablaUno = Registro();
							Conj<Registro>::Iterador iteradorJoin = ((tj->indiceS).Significado(parametro)).registroJoin;
							if(iteradorJoin.HaySiguiente()){													//CASO SI ESTAN UNIDOS
								iteradorJoin.EliminarSiguiente();
							}else{
								((tj->indiceS).Borrar(parametro));
							}

					}else{																						//CASO INDICE NAT
						cout << "indice nat" << endl;

						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceN).Significado(parametro)).registroTablaUno = Registro();
							Conj<Registro>::Iterador iteradorJoin = ((tj->indiceN).Significado(parametro)).registroJoin;
							if(iteradorJoin.HaySiguiente()){													//CASO SI ESTAN UNIDOS
								iteradorJoin.EliminarSiguiente();
							}else{
								((tj->indiceN).Borrar(parametro));
							}

					}

				}else{																							//CASO TABLA2
					cout << "tabla2" << endl;

					if(tj->indiceSValido){																		//CASO INDICE STRING
						cout << "indice string" << endl;
						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();
						((tj->indiceS).Significado(parametro)).registroTablaDos = Registro();
						Conj<Registro>::Iterador iteradorJoin = ((tj->indiceS).Significado(parametro)).registroJoin;
							if(iteradorJoin.HaySiguiente()){													//CASO SI ESTAN UNIDOS
								iteradorJoin.EliminarSiguiente();
							}else{
								((tj->indiceS).Borrar(parametro));
							}

					}else{																						//CASO INDICE NAT
						cout << "indice nat" << endl;
						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();
						((tj->indiceN).Significado(parametro)).registroTablaDos = Registro();
						Conj<Registro>::Iterador iteradorJoin = ((tj->indiceN).Significado(parametro)).registroJoin;
							if(iteradorJoin.HaySiguiente()){													//CASO SI ESTAN UNIDOS
								iteradorJoin.EliminarSiguiente();
							}else{
								((tj->indiceN).Borrar(parametro));
							}
					}
				}
			}
		it.Avanzar();
		};


		tj->modificaciones = Lista<tuplaCambios>();

		Conj<Registro> conjuntoregistros = Conj<Registro>(tj->vistaJoin);
		return conjuntoregistros;
};

Conj<Registro> BaseDeDatos::buscar(const Registro& r, const NombreTabla t) const{
	Tabla* latabla = (arbolTablas.Significado(t)).tab;
	Conj<Registro> conjRegistros = ((*(arbolTablas.Significado(t).tab)).registros());
	Conj<Registro>::Iterador itRegistros = conjRegistros.CrearIt();
	Conj<NombreCampo> conjCampos = ((*(arbolTablas.Significado(t).tab)).indices());
	Conj<NombreCampo>::Iterador itIndices = conjCampos.CrearIt();
	Conj<Registro> res = Conj<Registro>();

	//cout << "PRIMER WHILE" << endl;

		while(itIndices.HaySiguiente()){							//este while solo se hace para acelerar la complejidad en algunos casos

			if(r.Definido(itIndices.Siguiente())){
				if((*latabla).tipoCampo(itIndices.Siguiente())){
					//cout<< "ENTRO ACA, EL CAMPO ES NAT" << endl;
					Conj<Registro> reg = (*(arbolTablas.Significado(t).tab)).obtenerDeIndice(true,((r).Significado(itIndices.Siguiente()).dameNat()),"null");
					Conj<Registro>::const_Iterador itReg = reg.CrearIt();
					while(itReg.HaySiguiente()){
						if(registrosContenidos(r, itReg.Siguiente())){
						(res).Agregar(itReg.Siguiente());
						}
					itReg.Avanzar();
					}
					return res;
				}else{
					Conj<Registro> reg = (*(arbolTablas.Significado(t).tab)).obtenerDeIndice(false,0,((r).Significado(itIndices.Siguiente())).dameString());
					Conj<Registro>::const_Iterador itReg = reg.CrearIt();
					while(itReg.HaySiguiente()){
						if(registrosContenidos(r, itReg.Siguiente())){
							(res).Agregar(itReg.Siguiente());
						}
					itReg.Avanzar();
					}
					return res;
				}
			}
			itIndices.Avanzar();
		}

	//cout << "SEGUNDO WHILE" << endl;

		while(itRegistros.HaySiguiente()){ 							//este while funciona siempre, pero tarda mas
			if(registrosContenidos(r, itRegistros.Siguiente())){
				(res).Agregar(itRegistros.Siguiente());
			}

		itRegistros.Avanzar();
		}

	return (res);
};

void BaseDeDatos::MostrarBaseDeDatos() const{
	cout << "**BIENVENIDO AL VISUALIZADOR DE BASE DE DATOS**" << endl;
	cout << endl;
	cout << "LAS TABLAS QUE EXISTENTES SON:" <<endl;
	Conj<NombreTabla>::const_Iterador ITOBA = nTablas.CrearIt();
	cout << "{ " ;
	while(ITOBA.HaySiguiente()){

   		cout << (ITOBA).Siguiente() << " " ;
   		ITOBA.Avanzar();
   }
   		cout << "}" << endl;

   		cout << endl;
   		cout << endl;

	Conj<NombreTabla>::const_Iterador ITAB = nTablas.CrearIt();

  while(ITAB.HaySiguiente()){
  		Tabla* t1 = (arbolTablas.Significado((ITAB).Siguiente())).tab;
  		(*t1).mostrarTabla();
		cout << endl;
  		cout << endl;

  		Conj<NombreTabla> hizoJoinCon = (arbolTablas.Significado((*t1).nombreDeLaTabla())).nombresJoins;
  		Conj<NombreTabla>::Iterador itHizoJoinCon = hizoJoinCon.CrearIt();

  		if(itHizoJoinCon.HaySiguiente()){
			cout << "HIZO JOINS CON: " << endl;
			while(itHizoJoinCon.HaySiguiente()){
				cout << itHizoJoinCon.Siguiente() << " SOBRE EL CAMPO ";
				NombreCampo campoDelJoin = (*((((arbolTablas.Significado((*t1).nombreDeLaTabla())).dicJoin).Significado(itHizoJoinCon.Siguiente())).p)).cJoin;

				cout << campoDelJoin << endl;
				itHizoJoinCon.Avanzar();
			}

  		}else{
  			cout << "NO HIZO JOINS" << endl;
  		}


  		cout << endl;
  		cout << endl;
  		cout << endl;
  		ITAB.Avanzar();
  }
  cout << endl;
  cout <<"LA TABLA MAXIMA ES: " <<  tablaM << endl;

}

Conj<NombreTabla> BaseDeDatos::nombresTablas() const{
	return nTablas;
}

/////////////////////////////////////////////////////////////////////////////////////////MAIN
/*
int main()
{

  NombreCampo uno = "Nombre";
  NombreCampo dos = "Edad";
  NombreCampo tres = "Waifu";

  ///////////////////////////////////////////////Columnas
  Columna Cuno;
  Cuno.tipo = STR;
  Cuno.nombre = uno;

  Columna Cdos;
  Cdos.tipo = NAT;
  Cdos.nombre = dos;

  Columna Ctres;
  Ctres.tipo = STR;
  Ctres.nombre = tres;

  Conj<Columna> columna = Conj<Columna>();
  columna.Agregar(Cuno);
  columna.Agregar(Cdos);
  columna.Agregar(Ctres);

  Conj<NombreCampo> claves = Conj<NombreCampo>();
  claves.Agregar(uno);
  claves.Agregar(dos);

//////////////////////////////////////////////////Tabla
  NombreTabla nombre = "LaTablaONE";
	  Tabla pepito = Tabla(nombre,columna,claves);
	 // NombreTabla a = pepito.nombreDeLaTabla();

	 ////////////////////////////////////////////////REGISTRO 1:
	  Registro Runo;
	  Dato Dunoa = Dato("Emiliano");
	  Runo.Definir(uno,Dunoa);

	  Dato Ddosa = Dato(21);
	  Runo.Definir(dos,Ddosa);

	  Dato Dtresa = Dato("Yuno");
	  Runo.Definir(tres,Dtresa);

	  ////////////////////////////////////////////////REGISTRO 2:
	  Registro Rdos;
	  Dato Dunob = Dato("Lucas");
	  Rdos.Definir(uno,Dunob);

	  Dato Ddosb = Dato(20);
	  Rdos.Definir(dos,Ddosb);

	  Dato Dtresb = Dato("Aiko");
	  Rdos.Definir(tres,Dtresb);

	  ////////////////////////////////////////////////REGISTRO 3:
	  Registro Rtres;
	  Dato Dunoc = Dato("Luis");
	  Rtres.Definir(uno,Dunoc);

	  Dato Ddosc = Dato(23);
	  Rtres.Definir(dos,Ddosc);

	  Dato Dtresc = Dato("Mikasa");
	  Rtres.Definir(tres,Dtresc);

	 ////////////////////////////////////////////////REGISTRO 4:
	  Registro Rcuatro;
	  Dato Dunod = Dato("Peter");
	  Rcuatro.Definir(uno,Dunod);

	  Dato Ddosd = Dato(17);
	  Rcuatro.Definir(dos,Ddosd);

	  Dato Dtresd = Dato("Yuno");
	  Rcuatro.Definir(tres,Dtresd);

	  ////////////////////////////////////////////////REGISTRO 5:
	  Registro Rcinco;
	  Dato Dunoe = Dato("Ian");
	  Rcinco.Definir(uno,Dunoe);

	  Dato Ddose = Dato(18);
	  Rcinco.Definir(dos,Ddose);

	  Dato Dtrese = Dato("Misa");
	  Rcinco.Definir(tres,Dtrese);

///////////////////////////////////////////////////BASEDEDATOS:
  BaseDeDatos b;
  b.agregarTabla(pepito);
  b.insertarEntrada(Runo, nombre);
  b.insertarEntrada(Rdos, nombre);
  b.insertarEntrada(Rtres, nombre);
  b.insertarEntrada(Rcuatro, nombre);
  b.insertarEntrada(Rcinco, nombre);


  Tabla& esta = b.dameTabla(nombre);
  //cout << esta.accesos() << endl;
 // b.borrar(Rtres, nombre);
 // b.borrar(Rdos, nombre);
  //cout << esta.accesos() << endl;


  NombreTabla name = "LaTablaTWO";
	  Tabla jose = Tabla(name,columna,claves);

	   ////////////////////////////////////////////////REGISTRO 1:
	  Registro R2uno;
	  Dato D2unoa = Dato("Mariano");
	  R2uno.Definir(uno,D2unoa);

	  Dato D2dosa = Dato(21);
	  R2uno.Definir(dos,D2dosa);

	  Dato D2tresa = Dato("Aiko");
	  R2uno.Definir(tres,D2tresa);

	  ////////////////////////////////////////////////REGISTRO 2:
	  Registro R2dos;
	  Dato D2unob = Dato("Esteban");
	  R2dos.Definir(uno,D2unob);

	  Dato D2dosb = Dato(20);
	  R2dos.Definir(dos,D2dosb);

	  Dato D2tresb = Dato("Yuno");
	  R2dos.Definir(tres,D2tresb);

	  ////////////////////////////////////////////////REGISTRO 3:
	  Registro R2tres;
	  Dato D2unoc = Dato("Luis");
	  R2tres.Definir(uno,D2unoc);

	  Dato D2dosc = Dato(17);
	  R2tres.Definir(dos,D2dosc);

	  Dato D2tresc = Dato("Aiko");
	  R2tres.Definir(tres,D2tresc);
	  // cout << "LAS TABLAS QUE HAY SON: " << endl;

	  // Conj<NombreTabla>::const_Iterador itab = b.tablas();

	  // while(itab.HaySiguiente()){
	  // 		cout << (itab).Siguiente() << endl;
	  // 		itab.Avanzar();
	  // }

  b.agregarTabla(jose);
  b.insertarEntrada(R2uno, name);
  b.insertarEntrada(R2dos, name);
  b.insertarEntrada(R2tres, name);



/////////////////////////////////////////////////////INDEX:
  esta.indexar("Waifu");
  esta.indexar("Edad");

  // cout << "LAS TABLAS QUE HAY SON: " << endl;

  // Conj<NombreTabla>::const_Iterador itob = b.tablas();

  // while(itob.HaySiguiente()){
  // 		cout << (itob).Siguiente() << endl;
  // 		itob.Avanzar();
  // }

  // cout <<"LA TABLA MAXIMA ES: " <<  b.tablaMaxima() << endl;

  // cout<< endl;

  //b.MostrarBaseDeDatos();
  cout << "CHECKPOINT" << endl;
  cout << "HAY JOIN? " << b.hayJoin(nombre, name) << endl;
  cout << "CHECKPOINT" << endl;
  b.generarVistaJoin(nombre, name, dos);

  // cout << "CAMBIOS REGISTROS" << endl;


  // b.borrar(R2tres, name);
  // b.insertarEntrada(Runo, nombre);

  cout << "VISTAJOIN" << endl;

  b.vistaJoin(nombre,name);
  cout << "TIENE QUE MOSTRAR UN UNO: " << b.hayJoin(nombre, name) << endl;
  cout << "TIENE QUE MOSTRAR UN CERO: " << b.hayJoin(name, nombre) << endl;


  cout << "EL JOIN FUE HECHO CON DOS-NAT-EDAD:" <<  b.campoJoin(nombre, name) << endl;
	cout << endl;
  	cout << endl;
  	//cout<< "CHECKPOINT" << endl;
 	cout << endl;
 	cout << endl;
	cout << endl;
  	cout << endl;
  	cout << endl;
  	cout << endl;
 // b.borrarJoin(nombre, name);
  //cout << "TIENE QUE MOSTRAR UN CERO: " << b.hayJoin(nombre, name) << endl;
  //cout << "TIENE QUE MOSTRAR UN CERO: " << b.hayJoin(name, nombre) << endl;

  Registro Rigual;
  Dato paborrar = Dato("Yuno");
  Rigual.Definir(tres, paborrar);

 // b.MostrarBaseDeDatos();
    cout << endl;
  	cout << endl;
  	cout<< "AHORA BORRO" << endl;
 	cout << endl;
 	cout << endl;
	cout << endl;
  	cout << endl;
  	cout << endl;
  		//cout<< "QUE HAY EN VISTAJOIN HASTA AHORA" << endl;


  b.borrar(Rigual, nombre);
  	cout << endl;
  	cout << endl;
  	cout<< "AHORA VUELVO A MOSTRAR" << endl;
 	cout << endl;
 	cout << endl;
	cout << endl;
  	cout << endl;
  	cout << endl;
 // b.MostrarBaseDeDatos();
  	cout << endl;
  	cout << endl;

  /*	cout<< "VISTAJOIN AHORA TIENE" << endl;
  Conj<Registro>::const_Iterador itvista = b.vistaJoin(nombre, name);
  while(itvista.HaySiguiente()){
  		mostrarReg((itvista.Siguiente()));
  		itvista.Avanzar();
  }*/

/*  
  b.borrarJoin(nombre, name);
 	cout << endl;
 	cout << endl;
	cout << endl;
  	cout << endl;
  	cout << endl;


  b.MostrarBaseDeDatos();


/////////////////////////////////////////////////MUESTRO TABLA:
  //pepito.mostrarTabla();


  return 0;
}
*/
