#include "BaseDeDatos.h"
#include "Driver.cpp"
//#include "tabla.h"

using namespace aed2;

// /////////////////////////////////////////////////////////FUNCION AUXILIAR MOSTRAR REGISTRO
// void mostrarReg(Driver::Registro reg){
// 			Driver::Registro::Iterador pepe = reg.CrearIt();
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
	cout<< "IN-CHECKPOINTOH" << endl;
		while(it.HaySiguiente()){ 
			cout << it.SiguienteClave() << endl;
			if(!(r2.Definido((it.SiguienteClave())))){
				return false;
			}else{
				if(!((r2.Significado(it.SiguienteClave())) == it.SiguienteSignificado())){
					return false;
				}
			}
			it.Avanzar();
		}
		cout<< "OUT-CHECKPOINTOH" << endl;
		return true; //devuelve true si r1 esta contenido en r2 (hangyaku no lelouch)
}
///////////////////////////////////////////////////FUNCION AUXILIAR REGISTROS CONTENIDOS

/////////////////////////////////////////////////////////////////////////////////////////CONSTRUCTORES
BaseDeDatos::BaseDeDatos(){
	Dicc<NombreTabla, tuplaAux> d = Dicc<NombreTabla, tuplaAux>();
	Conj<NombreTabla> t = Conj<NombreTabla>();

	arbolTablas = d;
	tablaM = "empty";
	nTablas = t;
	vacio = Conj<Driver::Registro>();
}
BaseDeDatos::~BaseDeDatos(){}

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
//		Driver::Registro* reg1 = new Driver::Registro(r1);
//		Driver::Registro* reg2 =  Driver::Registro(r2);

//		registroTablaUno = *reg1;
//		registroTablaDos = *reg2;
		registroTablaUno = r1;
		registroTablaDos = r2;
		registroJoin = i;
	}


BaseDeDatos::tuplaCambios::tuplaCambios(NombreTabla n, Driver::Registro reg, bool a){
    	nTabla = n;
		r = reg;
		agregar  = a;
    }

	
/////////////////////////////////////////////////////////////////////////////////////////FUNCIONES

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

	bool r; 

	if (((arbolTablas.Significado(t1)).dicJoin).Definido(t2)){
		r = ((((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).principal);
	}else{ r = false; }

	return r;
};


void BaseDeDatos::agregarTabla(Tabla& t){
	Tabla* p = &t;
	tuplaAux a = tuplaAux(p);
	nTablas.AgregarRapido(t.nombreDeLaTabla());

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

	Conj<Driver::Registro> regsit1 = ((*te1).registros());
	Conj<Driver::Registro> regsit2 = ((*te2).registros());

	Conj<Driver::Registro>::Iterador it1 = regsit1.CrearIt();
	Conj<Driver::Registro>::Iterador it2 = regsit2.CrearIt();


	// Dicc<String, tuplaUnion> indiceS;
	// Dicc<Nat, tuplaUnion> indiceN;

	Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
	while(it1.HaySiguiente()){
		Driver::Registro regvacio = Driver::Registro();
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
				Driver::Registro registroUnido = unirRegistros(((tj->indiceS).Significado(((it2.Siguiente()).Significado(c)).dameString())).registroTablaUno, it2.Siguiente());
				Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);	
				((tj->indiceS).Significado(((it2.Siguiente()).Significado(c)).dameString())).registroJoin = iteradorJoin;
			}else{
				Driver::Registro regvacio = Driver::Registro();
				tuplaUnion tu = tuplaUnion(regvacio, it2.Siguiente(), v);
				(tj->indiceS).Definir(((it2.Siguiente()).Significado(c)).dameString(), tu);
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
				(tj->indiceN).Definir(((it2.Siguiente()).Significado(c)).dameNat(), tu);
			}
		}
		it2.Avanzar();
	};
}


void BaseDeDatos::insertarEntrada(const Driver::Registro& r, NombreTabla t){
	Tabla* t1 = (arbolTablas.Significado(t)).tab;
	Tabla* tm; 
	if (tablaM != "empty"){
		tm = (arbolTablas.Significado(tablaM)).tab;
	}
	Conj<NombreTabla>::Iterador it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();
	
	tuplaCambios cam = tuplaCambios(t, r, true);
	
	while(it.HaySiguiente()){
		tuplaJoin* a = (((arbolTablas.Significado(t)).dicJoin).Significado(it.Siguiente())).p;
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

void BaseDeDatos::borrar(const Driver::Registro& r, NombreTabla t){
	Tabla* t1 = (arbolTablas.Significado(t)).tab;
	Tabla* tm;
	if (tablaM != "empty"){
		tm = (arbolTablas.Significado(tablaM)).tab;
	}
	cout << "ENTRA A BUSCAR"<< endl;
	Conj<Driver::Registro> todos = buscar(r, t);
	cout << "SALIO DEL BUSCAR"<< endl;
	Conj<Driver::Registro>::Iterador itbuscar = todos.CrearIt();
	Conj<NombreTabla>::Iterador it = ((arbolTablas.Significado(t)).nombresJoins).CrearIt();

	while(itbuscar.HaySiguiente()){
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

Conj<Driver::Registro>::const_Iterador BaseDeDatos::vistaJoin(const NombreTabla t1, const NombreTabla t2){
	tuplaJoin* tj = (((arbolTablas.Significado(t1)).dicJoin).Significado(t2)).p;
	Lista<tuplaCambios>::Iterador it = (tj->modificaciones).CrearIt();

	while(it.HaySiguiente()){
//	cout << "NUEVA ITERACION" << endl;		

			if((it.Siguiente()).agregar){																		//CASO AGREGAR
//				cout << "agregar" << endl;

				if(((it.Siguiente()).nTabla) == t1){															//CASO TABLA1
//					cout << "tabla1" << endl;
					
					if(tj->indiceSValido){																		//CASO INDICE STRING
//						cout << "indice string" << endl;

						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

						if((tj->indiceS).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
//							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceS).Significado(parametro)).registroTablaUno = (it.Siguiente()).r;
							Driver::Registro registroUnido = unirRegistros(((it.Siguiente()).r), ((tj->indiceS).Significado(parametro)).registroTablaDos);
							Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceS).Significado(parametro)).registroJoin = iteradorJoin;

						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
//							cout << "no esta definido para la otra tabla" << endl;
							Driver::Registro regvacio = Driver::Registro();
							Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion((it.Siguiente()).r, regvacio, v);
							(tj->indiceS).Definir(parametro, tu);
						}	

					}else{	
																										//CASO INDICE NAT
//						cout << "indice nat" << endl;

						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

						if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
//							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceN).Significado(parametro)).registroTablaUno = (it.Siguiente()).r;
							Driver::Registro registroUnido = unirRegistros(((it.Siguiente()).r), ((tj->indiceN).Significado(parametro)).registroTablaDos);
							Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceN).Significado(parametro)).registroJoin = iteradorJoin;

						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
//							cout << "no esta definido para la otra tabla" << endl;
							Driver::Registro regvacio = Driver::Registro();
							Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion((it.Siguiente()).r, regvacio, v);
							(tj->indiceN).Definir(parametro, tu);
						}
					}

				}else{																							//CASO TABLA2
//					cout << "tabla2" << endl;

					if(tj->indiceSValido){																		//CASO INDICE STRING
//						cout << "indice string" << endl;

						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

						if((tj->indiceS).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
//							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceS).Significado(parametro)).registroTablaDos = (it.Siguiente()).r;
							Driver::Registro registroUnido = unirRegistros(((tj->indiceS).Significado(parametro)).registroTablaUno, ((it.Siguiente()).r));
							Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceS).Significado(parametro)).registroJoin = iteradorJoin;

						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
//							cout << "no esta definido para la otra tabla" << endl;
							Driver::Registro regvacio = Driver::Registro();
							Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion(regvacio, (it.Siguiente()).r, v);
							(tj->indiceS).Definir(parametro, tu);
						}	

					}else{																						//CASO INDICE NAT
//						cout << "indice nat" << endl;
						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

						if((tj->indiceN).Definido(parametro)){													//CASO ESTA DEFINIDO (para la otra tabla)
//							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceN).Significado(parametro)).registroTablaDos = (it.Siguiente()).r;
							((tj->indiceN).Significado(parametro));
							Driver::Registro registroUnido = unirRegistros(((tj->indiceN).Significado(parametro)).registroTablaUno, ((it.Siguiente()).r));
							Conj<Driver::Registro>::Iterador iteradorJoin = (tj->vistaJoin).AgregarRapido(registroUnido);
							((tj->indiceN).Significado(parametro)).registroJoin = iteradorJoin;

						}else{																					//CASO NO ESTA DEFINIDO (para la otra tabla)
//							cout << "no esta definido para la otra tabla" << endl;
							Driver::Registro regvacio = Driver::Registro();
							Conj<Driver::Registro>::Iterador v = vacio.CrearIt();
							tuplaUnion tu = tuplaUnion(regvacio, (it.Siguiente()).r, v);
							(tj->indiceN).Definir(parametro, tu);
						}
					}
				}

			}else{																								//CASO BORRAR
//				cout << "borrar" << endl;

				if(((it.Siguiente()).nTabla) == t1){															//CASO TABLA1
//					cout << "tabla1" << endl;
					
					if(tj->indiceSValido){																		//CASO INDICE STRING
//						cout << "indice string" << endl;

						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();

//							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceS).Significado(parametro)).registroTablaUno = Driver::Registro();
							Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceS).Significado(parametro)).registroJoin;
							if(iteradorJoin.HaySiguiente()){													//CASO SI ESTAN UNIDOS
								iteradorJoin.EliminarSiguiente();
							}else{
								((tj->indiceS).Borrar(parametro));
							}	

					}else{																						//CASO INDICE NAT
						cout << "indice nat" << endl;

						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();

//							cout << "esta definido para la otra tabla" << endl;
							((tj->indiceN).Significado(parametro)).registroTablaUno = Driver::Registro();
							Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceN).Significado(parametro)).registroJoin;
							if(iteradorJoin.HaySiguiente()){													//CASO SI ESTAN UNIDOS
								iteradorJoin.EliminarSiguiente();
							}else{
								((tj->indiceN).Borrar(parametro));
							}

					}

				}else{																							//CASO TABLA2
//					cout << "tabla2" << endl;

					if(tj->indiceSValido){																		//CASO INDICE STRING
//						cout << "indice string" << endl;
						String parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameString();
						((tj->indiceS).Significado(parametro)).registroTablaDos = Driver::Registro();
						Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceS).Significado(parametro)).registroJoin;
							if(iteradorJoin.HaySiguiente()){													//CASO SI ESTAN UNIDOS
								iteradorJoin.EliminarSiguiente();
							}else{
								((tj->indiceS).Borrar(parametro));
							}

					}else{																						//CASO INDICE NAT
//						cout << "indice nat" << endl;
						Nat parametro = (((it.Siguiente()).r).Significado(tj->cJoin)).dameNat();
						((tj->indiceN).Significado(parametro)).registroTablaDos = Driver::Registro();
						Conj<Driver::Registro>::Iterador iteradorJoin = ((tj->indiceN).Significado(parametro)).registroJoin;
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

		return (tj->vistaJoin).CrearIt();
};

Conj<Driver::Registro> BaseDeDatos::buscar(const Driver::Registro& r, NombreTabla t){
	Conj<Driver::Registro> conjRegistros = ((*(arbolTablas.Significado(t).tab)).registros());
	Conj<Driver::Registro>::Iterador itRegistros = conjRegistros.CrearIt();
	Conj<NombreCampo> conjCampos = ((*(arbolTablas.Significado(t).tab)).indices());
	Conj<NombreCampo>::Iterador itIndices = conjCampos.CrearIt();
	Conj<Driver::Registro> res = Conj<Driver::Registro>();
	
	cout << "PRIMER WHILE" << endl;

		while(itIndices.HaySiguiente()){							//este while solo se hace para acelerar la complejidad en algunos casos
			if(r.Definido(itIndices.Siguiente())){
				Driver::Registro reg = (*(arbolTablas.Significado(t).tab)).obtenerDeIndice(false,0,itIndices.Siguiente());
					if(registrosContenidos(r, reg)){
						(res).Agregar(reg);
					}
				return (res);
			}
		itIndices.Avanzar();
		}

	cout << "SEGUNDO WHILE" << endl;

		while(itRegistros.HaySiguiente()){ 							//este while funciona siempre, pero tarda mas
			if(registrosContenidos(r, itRegistros.Siguiente())){
				(res).Agregar(itRegistros.Siguiente());
			}

		itRegistros.Avanzar();
		}

	return (res);
};

void BaseDeDatos::MostrarBaseDeDatos(){
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

/////////////////////////////////////////////////////////////////////////////////////////MAIN

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
	  Driver::Registro Runo;
	  Driver::Dato Dunoa = Driver::Dato("Emiliano");
	  Runo.Definir(uno,Dunoa);

	  Driver::Dato Ddosa = Driver::Dato(21);
	  Runo.Definir(dos,Ddosa);	  

	  Driver::Dato Dtresa = Driver::Dato("Aiko");
	  Runo.Definir(tres,Dtresa);

	  ////////////////////////////////////////////////REGISTRO 2:
	  Driver::Registro Rdos;
	  Driver::Dato Dunob = Driver::Dato("Lucas");
	  Rdos.Definir(uno,Dunob);

	  Driver::Dato Ddosb = Driver::Dato(20);
	  Rdos.Definir(dos,Ddosb);   

	  Driver::Dato Dtresb = Driver::Dato("Yuno");
	  Rdos.Definir(tres,Dtresb);

	  ////////////////////////////////////////////////REGISTRO 3:
	  Driver::Registro Rtres;
	  Driver::Dato Dunoc = Driver::Dato("Luis");
	  Rtres.Definir(uno,Dunoc);

	  Driver::Dato Ddosc = Driver::Dato(23);
	  Rtres.Definir(dos,Ddosc);   

	  Driver::Dato Dtresc = Driver::Dato("Mikasa");
	  Rtres.Definir(tres,Dtresc);

	 ////////////////////////////////////////////////REGISTRO 4:
	  Driver::Registro Rcuatro;
	  Driver::Dato Dunod = Driver::Dato("Peter");
	  Rcuatro.Definir(uno,Dunod);

	  Driver::Dato Ddosd = Driver::Dato(17);
	  Rcuatro.Definir(dos,Ddosd);    

	  Driver::Dato Dtresd = Driver::Dato("Yuno");
	  Rcuatro.Definir(tres,Dtresd);

	  ////////////////////////////////////////////////REGISTRO 5:
	  Driver::Registro Rcinco;
	  Driver::Dato Dunoe = Driver::Dato("Ian");
	  Rcinco.Definir(uno,Dunoe);

	  Driver::Dato Ddose = Driver::Dato(18);
	  Rcinco.Definir(dos,Ddose);    

	  Driver::Dato Dtrese = Driver::Dato("Misa");
	  Rcinco.Definir(tres,Dtrese);

///////////////////////////////////////////////////BASEDEDATOS:
  BaseDeDatos b;
  b.agregarTabla(pepito);
  b.insertarEntrada(Rdos, nombre);
  b.insertarEntrada(Rtres, nombre);
  b.insertarEntrada(Rcuatro, nombre);
  b.insertarEntrada(Rcinco, nombre);

  
  Tabla& esta = b.dameTabla(b.tablaMaxima());
  //cout << esta.accesos() << endl;
  b.borrar(Rtres, nombre);
  b.borrar(Rdos, nombre);
  //cout << esta.accesos() << endl;


  NombreTabla name = "LaTablaTWO";
  Tabla jose = Tabla(name,columna,claves);

   ////////////////////////////////////////////////REGISTRO 1:
  Driver::Registro R2uno;
  Driver::Dato D2unoa = Driver::Dato("Mariano");
  R2uno.Definir(uno,D2unoa);

  Driver::Dato D2dosa = Driver::Dato(21);
  R2uno.Definir(dos,D2dosa);	  

  Driver::Dato D2tresa = Driver::Dato("Aiko");
  R2uno.Definir(tres,D2tresa);

  ////////////////////////////////////////////////REGISTRO 2:
  Driver::Registro R2dos;
  Driver::Dato D2unob = Driver::Dato("Esteban");
  R2dos.Definir(uno,D2unob);

  Driver::Dato D2dosb = Driver::Dato(20);
  R2dos.Definir(dos,D2dosb);   

  Driver::Dato D2tresb = Driver::Dato("Yuno");
  R2dos.Definir(tres,D2tresb);

////////////////////////////////////////////////REGISTRO 3:
  Driver::Registro R2tres;
  Driver::Dato D2unoc = Driver::Dato("Luis");
  R2tres.Definir(uno,D2unoc);

  Driver::Dato D2dosc = Driver::Dato(17);
  R2tres.Definir(dos,D2dosc);   

  Driver::Dato D2tresc = Driver::Dato("Aiko");
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

///////////////////////////////////////////////////BORRAR REGISTROS:
  //pepito.quitarRegistro(Rdos);
  //pepito.agregarRegistro(Rdos);

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

   b.insertarEntrada(R2tres, name);
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

  Driver::Registro Rigual;
  Driver::Dato paborrar = Driver::Dato("Yuno");
  Rigual.Definir(tres, paborrar);

  b.MostrarBaseDeDatos();
    cout << endl;
  	cout << endl;
  	cout<< "AHORA BORRO" << endl;
 	cout << endl;
 	cout << endl;
	cout << endl;
  	cout << endl;
  	cout << endl;
  b.borrar(Rigual, nombre);
  	cout << endl;
  	cout << endl;
  	cout<< "AHORA VUELVO A MOSTRAR" << endl;
 	cout << endl;
 	cout << endl;
	cout << endl;
  	cout << endl;
  	cout << endl;
  b.MostrarBaseDeDatos();
  	cout << endl;
  	cout << endl;
  	cout<< "VISTAJOIN AHORA TIENE" << endl;
  Conj<Driver::Registro>::const_Iterador itvista = b.vistaJoin(nombre, name);
  while(itvista.HaySiguiente()){
  		mostrarReg((itvista.Siguiente()));
  		itvista.Avanzar();
  }

 	cout << endl;
 	cout << endl;
	cout << endl;
  	cout << endl;
  	cout << endl;






  //b.MostrarBaseDeDatos();


/////////////////////////////////////////////////MUESTRO TABLA:
  //pepito.mostrarTabla();


  return 0;
}