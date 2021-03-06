    #include <iostream>
    #include "Tipos.h"
    #include "aed2/Dicc.h"
    #include "DicNat.h"         //ABB INCLUIDO
    #include "DicString.h"      //TRIE INCLUIDO
    #include "aed2/Lista.h"
    #include "aed2/TiposBasicos.h"
    #include "aed2/Conj.h"
    #include "Registro.h"
    #include "Dato.h"

    using namespace aed2;
    using namespace std;



	class tuplaIt {

        public:
        tuplaIt();
        tuplaIt(Conj<Registro>::Iterador c, Lista<tuplaIt>::Iterador o);

        void cambiarCR(Conj<Registro>::Iterador c);
        void cambiarOA(Lista<tuplaIt>::Iterador o);
		Conj<Registro>::Iterador CR();
		Lista<tuplaIt>::Iterador OA();


        private:
        Conj<Registro>::Iterador cr;
        Lista<tuplaIt>::Iterador oa;
    };



class Tabla {

      public:
        Tabla(const NombreTabla&, const Conj<Columna>&, const Conj<NombreCampo>&);
        Tabla(const Tabla&);
        ~Tabla();
//        bool operator==(const Tabla&) const;
        Conj<Registro> registros() const;
        void agregarRegistro(const Registro&);
        void quitarRegistro(const Registro);
        void indexar(const NombreCampo);
        Conj<NombreCampo> claves() const;
        Conj<NombreCampo> campos() const;
        Conj<NombreCampo> indices() const;
        bool tipoCampo(const NombreCampo) const;
        Dato minimo(const NombreCampo) const;
        Dato maximo(const NombreCampo) const;
        Nat accesos() const;
        Registro regCriterio() const;
        Conj<Registro> obtenerDeIndice(bool, const Nat, const String);
        NombreCampo campoDicNat() const;
        NombreCampo campoDicString() const;
        NombreTabla nombreDeLaTabla() const;
        bool tieneIndiceNat() const;
        bool tieneIndiceString() const;
        void mostrarTabla();

      private:

        Tabla& operator=(const Tabla& otra) {                     //?
        assert(false);
        return *this;
        }



        NombreTabla nombreT;                                      //nombre: STRING
        Registro registroCrit;                            //RegistroCrit: Registro
        Conj<NombreCampo> camposT;                                //campos: CONJ(CAMPO)
        Conj<NombreCampo> camposClave;                            //camposClave: CONJ(CAMPO)
        Conj<Registro> registrosT;                        //Registros: CONJ(Registro)
        DicNat<Nat, Lista<tuplaIt> > DicIndiceN;                    //DicIndiceN: DICCIONARIO(NAT,CONJ(tuplaIt))
        NombreCampo CamIndiceN;                                   //CamIndiceN: STRING
        bool EstaIndiceN;                                         //EstaIndiceN: BOOL
        DicString< Lista<tuplaIt> > DicIndiceS;                 //DicIndiceS: DICCIONARIO(STRING,CONJ(tuplaIt))
        NombreCampo CamIndiceS;                                   //CamIndiceS: STRING
        bool EstaIndiceS;                                         //EstaIndiceS: BOOL
        Dato minDatoNat;                                  //minDatoNat: Dato
        Dato minDatoString;                               //minDatoString: Dato
        Dato maxDatoNat;                                  //maxDatoNat: Dato
        Dato maxDatoString;                               //maxDatoString: Dato
        Nat accesosT;                                             //accesos: NAT
        Lista<tuplaIt> Vacio;                                     //ad-hoc
    };



        //ALGORITMOS:

    	tuplaIt::tuplaIt() {}

        tuplaIt::tuplaIt(Conj<Registro>::Iterador c, Lista<tuplaIt>::Iterador o) : cr(c), oa(o) {}

        void tuplaIt::cambiarCR(Conj<Registro>::Iterador c){
        	cr = c;
        }

        void tuplaIt::cambiarOA(Lista<tuplaIt>::Iterador o){
        	oa = o;
        }

        Conj<Registro>::Iterador tuplaIt::CR(){
        	return cr;
        }

		Lista<tuplaIt>::Iterador tuplaIt::OA(){
			return oa;
		}

        Tabla::Tabla(const NombreTabla& nombre, const Conj<Columna>& columnas, const Conj<NombreCampo>& claves) :
        nombreT(nombre), camposClave(Conj<NombreCampo>()), registrosT(Conj<Registro>()),
        DicIndiceN(DicNat<Nat, Lista<tuplaIt> >()), CamIndiceN("null"), EstaIndiceN(false),
        DicIndiceS(DicString< Lista<tuplaIt> >()), CamIndiceS("null"), EstaIndiceS(false),
        minDatoNat(Dato(0)), minDatoString(Dato("null")), maxDatoNat(Dato(0)), maxDatoString(Dato("null")),
        accesosT(0), Vacio(Lista<tuplaIt>()) {

        Conj<Columna>::const_Iterador actual = columnas.CrearIt();
        	while(actual.HaySiguiente()){
        		NombreCampo c = (actual.Siguiente()).nombre;
        		camposT.Agregar(c);
        		if((actual.Siguiente()).tipo == NAT){
                    registroCrit.Definir(c, Dato(1));
        		}else{
        			registroCrit.Definir(c, Dato("null"));
        		}

        		actual.Avanzar();

        	}

        Conj<NombreCampo>::const_Iterador claIt = claves.CrearIt();
        	while(claIt.HaySiguiente()){
        		camposClave.AgregarRapido(claIt.Siguiente());
        		claIt.Avanzar();
        	}

        //PERDON, ES UN ASCO, LO SE, PERO GCC ESTA EMPECINADO EN NO COMPILAR

/*        registroCrit = Dicc<NombreCampo, Dato>();
        camposT = Conj<NombreCampo>();

        nombreT = nombre;
        camposClave = claves;
        registrosT = Conj<Registro>();
        DicIndiceN = Dicc<Nat, Conj<tuplaIt> >();
        CamIndiceN = "null";
        EstaIndiceN = false;
        DicIndiceS = Dicc<String, Conj<tuplaIt> >();
        CamIndiceS = "null";
        EstaIndiceS = false;
        minDatoNat = Dato(0);
        minDatoString = Dato("null");
        maxDatoNat = Dato(0);
        maxDatoString = Dato("null");
        accesosT = 0;
        Vacio = Conj<tuplaIt>();
        */
        }

 //       Tabla::Tabla(const Tabla& t) {}


        Lista<tuplaIt>::Iterador Agregar(Lista<tuplaIt>& lista, tuplaIt& tupla){
        	Lista<tuplaIt>::Iterador res = lista.CrearIt();
        	res.AgregarComoSiguiente(tupla);
        	return res;
        }




        Tabla::~Tabla() {}

//        bool operator==(const Tabla&) const;

        Conj<Registro> Tabla::registros() const {
            return registrosT;
        }

        bool registrosIguales(const Registro& a, const Registro& b){
        	if(a.CantClaves() != b.CantClaves()){
        		return false;
        	}

        	Registro::const_Iterador itA = a.CrearIt();
        	Registro::const_Iterador itB = b.CrearIt();

        	while(itA.HaySiguiente()){
        		if(!(itA.SiguienteClave() == itB.SiguienteClave())){
        			return false;
        		}
        		if(!(itA.SiguienteSignificado() == itB.SiguienteSignificado())){
        			return false;
        		}
        		itA.Avanzar();
        		itB.Avanzar();
        	}

        	return true;

        }

        void Tabla::agregarRegistro(const Registro& r) {
            accesosT++;
            Conj<Registro>::Iterador it = registrosT.Agregar(r);
            Lista<tuplaIt>::Iterador itVac = Vacio.CrearIt();

            if((!EstaIndiceN) && (EstaIndiceS)){
//        cout << "SOLO INDICE STR" << endl;
                tuplaIt tupla = tuplaIt(it, itVac);
                if(!(DicIndiceS.Definido((r.Significado(CamIndiceS)).dameString()))){
                    Lista<tuplaIt> conjVac = Lista<tuplaIt>();
                    DicIndiceS.Definir((r.Significado(CamIndiceS)).dameString(), conjVac);
                }

                Agregar((DicIndiceS.Significado((r.Significado(CamIndiceS)).dameString())), tupla);
                minDatoString = DicIndiceS.MinClave();    // CUANDO ESTE LISTO TRIE
                maxDatoString = DicIndiceS.MaxClave();      //CUANDO ESTE LISTO TRIE
            }

            if((EstaIndiceN) && (!EstaIndiceS)){
//        cout << "SOLO INDICE NAT" << endl;
                tuplaIt tupla = tuplaIt(it, itVac);
                if(!(DicIndiceN.Definido((r.Significado(CamIndiceN)).dameNat()))){
                    Lista<tuplaIt> conjVac = Lista<tuplaIt>();
                    DicIndiceN.Definir((r.Significado(CamIndiceN)).dameNat(), conjVac);
                }

                Agregar((DicIndiceN.Significado((r.Significado(CamIndiceN)).dameNat())), tupla);
                minDatoNat = DicIndiceN.Min();
                maxDatoNat = DicIndiceN.Max();
            }

            if((EstaIndiceN) && (EstaIndiceS)){
//        cout << "AMBOS INDICES" << endl;
                tuplaIt tuplaN = tuplaIt(it, itVac);
                if(!(DicIndiceN.Definido((r.Significado(CamIndiceN)).dameNat()))){
                    Lista<tuplaIt> conjVac = Lista<tuplaIt>();
                    DicIndiceN.Definir((r.Significado(CamIndiceN)).dameNat(), conjVac);
                }

                Lista<tuplaIt>::Iterador actual = Agregar((DicIndiceN.Significado((r.Significado(CamIndiceN)).dameNat())), tuplaN);

                tuplaIt tuplaS = tuplaIt(it, actual);
                if(!(DicIndiceS.Definido((r.Significado(CamIndiceS)).dameString()))){
                    Lista<tuplaIt> conjVac = Lista<tuplaIt>();
                    DicIndiceS.Definir((r.Significado(CamIndiceS)).dameString(), conjVac);
                }

                Lista<tuplaIt>::Iterador vecino = Agregar((DicIndiceS.Significado((r.Significado(CamIndiceS)).dameString())), tuplaS);

                (actual.Siguiente()).cambiarOA(vecino);

                 minDatoNat = DicIndiceN.Min();
                 maxDatoNat = DicIndiceN.Max();
                 minDatoString = DicIndiceS.MinClave();
                 maxDatoString = DicIndiceS.MaxClave();



                //minDatoNat = max(DicIndiceN);     CUANDO ESTE LISTO ABB
                //maxDatoNat = min(DicIndiceN);     CUANDO ESTE LISTO ABB
                //minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
            }
        }

        void Tabla::quitarRegistro(const Registro r) {
        	accesosT++;
        	if(EstaIndiceN){
        		Nat valor = (r.Significado(CamIndiceN)).dameNat();
        		Lista<tuplaIt>::Iterador it = (DicIndiceN.Significado(valor)).CrearIt();
        			while((it.HaySiguiente()) && !(registrosIguales((((it.Siguiente()).CR()).Siguiente()), r))){
        				it.Avanzar();
        		}

        		if(((it.Siguiente()).OA()).HaySiguiente()){
        		((it.Siguiente()).OA()).EliminarSiguiente();

        		String valorString = (r.Significado(CamIndiceS)).dameString();

        			if((DicIndiceS.Significado(valorString)).EsVacia()){
        				DicIndiceS.Borrar(valorString);
        			}

                minDatoString = DicIndiceS.MinClave();
                maxDatoString = DicIndiceS.MaxClave();
        		}


        		((it.Siguiente()).CR()).EliminarSiguiente();
        		it.EliminarSiguiente();

        		if((DicIndiceN.Significado(valor)).EsVacia()){
        			DicIndiceN.Borrar(valor);
        		}

                minDatoNat = DicIndiceN.Min();
                maxDatoNat = DicIndiceN.Max();

        	}else{
        		if(EstaIndiceS){
        		String valor = (r.Significado(CamIndiceS)).dameString();
        		Lista<tuplaIt>::Iterador it = (DicIndiceS.Significado(valor)).CrearIt();
        			while((it.HaySiguiente()) && !(registrosIguales((((it.Siguiente()).CR()).Siguiente()), r))){
        				it.Avanzar();
        			}
        			((it.Siguiente()).CR()).EliminarSiguiente();
        			it.EliminarSiguiente();

        		if((DicIndiceS.Significado(valor)).EsVacia()){
        			DicIndiceS.Borrar(valor);
        		}

                minDatoString = DicIndiceS.MinClave();
                maxDatoString = DicIndiceS.MaxClave();

        		}else{
        			Conj<Registro>::Iterador it = registrosT.CrearIt();
        			while((it.HaySiguiente()) && !(registrosIguales((it.Siguiente()), r))){
        				it.Avanzar();
        			}
        			it.EliminarSiguiente();
        		}
        	}
        }


        void Tabla::indexar(const NombreCampo c) {
        	Conj<Registro>::Iterador it = registrosT.CrearIt();
        	if((registroCrit.Significado(c)).esNat()){

        		if(!EstaIndiceS){
        			while(it.HaySiguiente()){
        				Nat actual = ((it.Siguiente()).Significado(c)).dameNat();
        					if(!(DicIndiceN.Definido(actual))){
								DicIndiceN.Definir(actual, Lista<tuplaIt>());
        					}
        				Lista<tuplaIt>::Iterador vac = Vacio.CrearIt();
        				tuplaIt tup = tuplaIt(it, vac);
        				Agregar(DicIndiceN.Significado(actual), tup);
        				it.Avanzar();
        			}

        		}else{

        			while(it.HaySiguiente()){
        				Nat actual = ((it.Siguiente()).Significado(c)).dameNat();
        				String vecino = ((it.Siguiente()).Significado(CamIndiceS)).dameString();
        				Lista<tuplaIt>::Iterador vecinoIt = (DicIndiceS.Significado(vecino)).CrearIt();
        					while(!registrosIguales(((vecinoIt.Siguiente()).CR()).Siguiente(),it.Siguiente())){
        						vecinoIt.Avanzar();
        					}

        					if(!(DicIndiceN.Definido(actual))){
								DicIndiceN.Definir(actual, Lista<tuplaIt>());
        					}
        				tuplaIt tup = tuplaIt(it, vecinoIt);
        				Lista<tuplaIt>::Iterador actualIt = Agregar(DicIndiceN.Significado(actual), tup);
        				(vecinoIt.Siguiente()).cambiarOA(actualIt);
        				it.Avanzar();
        			}

        		}
                EstaIndiceN = true;
        		CamIndiceN = c;
                minDatoNat = DicIndiceN.Min();
                maxDatoNat = DicIndiceN.Max();

        	}else{

        		if(!EstaIndiceN){
        			    while(it.HaySiguiente()){
        				String actual = ((it.Siguiente()).Significado(c)).dameString();
        					if(!(DicIndiceS.Definido(actual))){
								DicIndiceS.Definir(actual, Lista<tuplaIt>());
        					}

        				Lista<tuplaIt>::Iterador vac = Vacio.CrearIt();
        				tuplaIt tup = tuplaIt(it, vac);
        				Agregar(DicIndiceS.Significado(actual), tup);
        				it.Avanzar();
        			}
        		}else{

						while(it.HaySiguiente()){
        				String actual = ((it.Siguiente()).Significado(c)).dameString();
        				Nat vecino = ((it.Siguiente()).Significado(CamIndiceN)).dameNat();
        				Lista<tuplaIt>::Iterador vecinoIt = (DicIndiceN.Significado(vecino)).CrearIt();
        					while(!registrosIguales(((vecinoIt.Siguiente()).CR()).Siguiente(),it.Siguiente())){
        						vecinoIt.Avanzar();
        					}

        					if(!(DicIndiceS.Definido(actual))){
								DicIndiceS.Definir(actual, Lista<tuplaIt>());
        					}
        				tuplaIt tup = tuplaIt(it, vecinoIt);
        				Lista<tuplaIt>::Iterador actualIt = Agregar(DicIndiceS.Significado(actual), tup);
        				(vecinoIt.Siguiente()).cambiarOA(actualIt);
        				it.Avanzar();
        			}

        		}
                EstaIndiceS = true;
        		CamIndiceS = c;
                minDatoString = DicIndiceS.MinClave();     // CUANDO ESTE LISTO TRIE
                maxDatoString = DicIndiceS.MaxClave();     //CUANDO ESTE LISTO TRIE
        		//minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
        	}
        }

        Conj<NombreCampo> Tabla::claves() const{
            return camposClave;
        }

        Conj<NombreCampo> Tabla::campos() const{
            return camposT;
        }

        Conj<NombreCampo> Tabla::indices() const{
            Conj<NombreCampo> res = Conj<NombreCampo>();
            if(EstaIndiceN){
                res.Agregar(CamIndiceN);
            }
            if(EstaIndiceS){
                res.Agregar(CamIndiceS);
            }
            return res;
        }

        bool Tabla::tipoCampo(const NombreCampo c) const {
            return (registroCrit.Significado(c)).esNat();
        }

        Dato Tabla::minimo(const NombreCampo c) const {
            if((CamIndiceN == c) && EstaIndiceN){
                return minDatoNat;
            }else{
                return minDatoString;
            }
        }

        Dato Tabla::maximo(const NombreCampo c) const {
            if((CamIndiceN == c) && EstaIndiceN){
                return maxDatoNat;
            }else{
                return maxDatoString;
            }
        }

        Nat Tabla::accesos() const{
            return accesosT;
        }

        Registro Tabla::regCriterio() const{
            return registroCrit;
        }

        NombreCampo Tabla::campoDicNat() const{
            return CamIndiceN;
        }

        NombreCampo Tabla::campoDicString() const{
            return CamIndiceS;
        }

        Conj<Registro> Tabla::obtenerDeIndice(bool indiceNat, const Nat n, const String s){
            Conj<Registro> res = Conj<Registro>();
            //true == indice nat
            //false == indice string
            if(indiceNat){
            //	cout << "ACA NAT" << endl;
                Lista<tuplaIt> hola = (DicIndiceN.Significado(n));
                Lista<tuplaIt>::Iterador it = hola.CrearIt();
                while(it.HaySiguiente()){
                	res.AgregarRapido(((it.Siguiente()).CR()).Siguiente());
                	it.Avanzar();
                }
            }else{
            //	cout << "ACA STRING" << endl;
                Lista<tuplaIt> chau = (DicIndiceS.Significado(s));
              //  cout << "ACA STRING SALE" << endl;
                Lista<tuplaIt>::Iterador it = chau.CrearIt();
                //cout << "ACA STRING SALE2" << endl;
                while(it.HaySiguiente()){
                	res.AgregarRapido(((it.Siguiente()).CR()).Siguiente());
                	it.Avanzar();
                }
            }
            return res;
        }

        NombreTabla Tabla::nombreDeLaTabla() const{
        	return nombreT;
        }

        bool Tabla::tieneIndiceNat() const{
        	return EstaIndiceN;
        }

        bool Tabla::tieneIndiceString() const{
        	return EstaIndiceS;
        }

        void mostrarReg(Registro reg){
			Registro::Iterador pepe = reg.CrearIt();
			cout << "** MUESTRO REGISTRO **" << endl;
			int i = 1;
			while(pepe.HaySiguiente()){
				cout << i << ")";
				cout << "    " << pepe.SiguienteClave() << ":";
				if((pepe.SiguienteSignificado()).esNat()){
					cout << "        " << (pepe.SiguienteSignificado()).dameNat() << endl;
				}else{
					cout << "        " <<(pepe.SiguienteSignificado()).dameString() << endl;
				}
				pepe.Avanzar();
				i++;
			}
			cout << "     ** FIN **" << endl;
		}

/*                      MOSTRAR INDICES, PERO USA ITERADOR A DICCIONARIO

        void mostrarIndiceN(Dicc<Nat, Lista<tuplaIt> > indice){
            Dicc<Nat, Lista<tuplaIt> >::Iterador pepe = indice.CrearIt();
            cout << "**** MUESTRO INDICE NAT ****" << endl;
            int i = 1;
            while(pepe.HaySiguiente()){
                cout << i << ")";
                cout << "CLAVE '" << pepe.SiguienteClave() << "' APUNTA A REGISTRO/S:" << endl;
                Lista<tuplaIt>::Iterador it = (pepe.SiguienteSignificado()).CrearIt();
                    int j = 1;
                    while(it.HaySiguiente()){
                        cout << "   MUESTRO PARA " << i << ") EL NUMERO " << j << ")" << endl;
                        mostrarReg(((it.Siguiente()).CR()).Siguiente());
                            if(((it.Siguiente()).OA()).HaySiguiente()){
                                cout << "(APUNTA A OTRO ARBOL)" << endl;
                            }else{
                                cout << "(NO APUNTA A OTRO ARBOL)" << endl;
                            }
                        it.Avanzar();
                        j++;
                        }
                pepe.Avanzar();
                i++;
            }
            cout << "      **** FIN ****" << endl;
        }

        void mostrarIndiceS(Dicc<String, Lista<tuplaIt> > indice){
            Dicc<String, Lista<tuplaIt> >::Iterador pepe = indice.CrearIt();
            cout << "**** MUESTRO INDICE STRING ****" << endl;
            int i = 1;
            while(pepe.HaySiguiente()){
                cout << i << ")";
                cout << "CLAVE '" << pepe.SiguienteClave() << "' APUNTA A REGISTRO/S:" << endl;
                Lista<tuplaIt>::Iterador it = (pepe.SiguienteSignificado()).CrearIt();
                    int j = 1;
                    while(it.HaySiguiente()){
                        cout << "   MUESTRO PARA " << i << ") EL NUMERO " << j << ")" << endl;
                        mostrarReg(((it.Siguiente()).CR()).Siguiente());
                            if(((it.Siguiente()).OA()).HaySiguiente()){
                                cout << "(APUNTA A OTRO ARBOL)" << endl;
                            }else{
                                cout << "(NO APUNTA A OTRO ARBOL)" << endl;
                            }
                        it.Avanzar();
                        j++;
                        }
                pepe.Avanzar();
                i++;
            }
            cout << "      **** FIN ****" << endl;
        }
*/
//                 MOSTRAR INDICES SIN USAR ITERADOR A DICCIONARIO

void mostrarIndiceN(NombreCampo c, Conj<Registro>::Iterador itRegistros, DicNat<Nat, Lista<tuplaIt> >& DicIndiceN){
            cout << "**** MUESTRO INDICE NAT ****" << endl;
            int i = 1;
            while(itRegistros.HaySiguiente()){
                cout << i << ")";
                cout << "CLAVE '" << ((itRegistros.Siguiente()).Significado(c)).dameNat() << "' APUNTA A REGISTRO/S:" << endl;
                Lista<tuplaIt>::Iterador it = (DicIndiceN.Significado(((itRegistros.Siguiente()).Significado(c)).dameNat())).CrearIt();
                    int j = 1;
                    while(it.HaySiguiente()){
                        cout << "   MUESTRO PARA " << i << ") EL NUMERO " << j << ")" << endl;
                        mostrarReg(((it.Siguiente()).CR()).Siguiente());
                            if(((it.Siguiente()).OA()).HaySiguiente()){
                                cout << "(APUNTA A OTRO ARBOL)" << endl;
                            }else{
                                cout << "(NO APUNTA A OTRO ARBOL)" << endl;
                            }
                        it.Avanzar();
                        j++;
                        }
                itRegistros.Avanzar();
                i++;
            }
            cout << "      **** FIN ****" << endl;
        }

        void mostrarIndiceS(NombreCampo c, Conj<Registro>::Iterador itRegistros, DicString< Lista<tuplaIt> >& DicIndiceS){
            cout << "**** MUESTRO INDICE STRING ****" << endl;
            int i = 1;
            while(itRegistros.HaySiguiente()){
                cout << i << ")";
                cout << "CLAVE '" << ((itRegistros.Siguiente()).Significado(c)).dameString() << "' APUNTA A REGISTRO/S:" << endl;
                Lista<tuplaIt>::Iterador it = (DicIndiceS.Significado(((itRegistros.Siguiente()).Significado(c)).dameString())).CrearIt();
                    int j = 1;
                    while(it.HaySiguiente()){
                        cout << "   MUESTRO PARA " << i << ") EL NUMERO " << j << ")" << endl;
                        mostrarReg(((it.Siguiente()).CR()).Siguiente());
                            if(((it.Siguiente()).OA()).HaySiguiente()){
                                cout << "(APUNTA A OTRO ARBOL)" << endl;
                            }else{
                                cout << "(NO APUNTA A OTRO ARBOL)" << endl;
                            }
                        it.Avanzar();
                        j++;
                        }
                itRegistros.Avanzar();
                i++;
            }
            cout << "      **** FIN ****" << endl;
        }

        void Tabla::mostrarTabla() {
			cout << "** MUESTRO LA TABLA TITULADA " << nombreT << " **" << endl;
			cout << "CANTIDAD DE ACCESOS: " << accesosT << endl;

			Conj<NombreCampo>::const_Iterador camIt = camposT.CrearIt();

			cout << "SUS CAMPOS SON: " << endl;
			while(camIt.HaySiguiente()){
			NombreCampo camp = camIt.Siguiente();
			cout << camp;
			camIt.Avanzar();
				if(camIt.HaySiguiente()){
				cout << " - ";
				}
			}
			cout << endl;

			Conj<NombreCampo>::const_Iterador claIt = camposClave.CrearIt();

			cout << "DE ELLOS, SUS CAMPOS CLAVE SON: " << endl;

			while(claIt.HaySiguiente()){
			NombreCampo camp = claIt.Siguiente();
			cout << camp;
			claIt.Avanzar();
				if(claIt.HaySiguiente()){
				cout << " - ";
				}
			}

			cout << endl;
            cout << endl;

				if(!EstaIndiceN){
					cout << "NO TIENE INDICE SOBRE NATURALES" << endl;
				}else{
					cout << "TIENE INDICE SOBRE NATURALES" << endl;
					cout << "SU CAMPO ES " << CamIndiceN << endl;
					cout << "SU MAXIMO ES " << maxDatoNat.dameNat() << " Y SU MINIMO " << minDatoNat.dameNat() << endl;
                    cout << "EL INDICE SOBRE NATURALES ES DE LA FORMA: " << endl;
                    Conj<Registro>::Iterador iteradorDeRegistrosN = registrosT.CrearIt();
                    mostrarIndiceN(CamIndiceN, iteradorDeRegistrosN, DicIndiceN);
				}

            cout << endl;
            cout << endl;

				if(!EstaIndiceS){
					cout << "NO TIENE INDICE SOBRE STRING" << endl;
				}else{
					cout << "TIENE INDICE SOBRE STRING" << endl;
					cout << "SU CAMPO ES " << CamIndiceS << endl;
					cout << "SU MAXIMO ES " << maxDatoString.dameString() << " Y SU MINIMO " << minDatoString.dameString() << endl;
                    cout << "EL INDICE SOBRE STRING ES DE LA FORMA: " << endl;
                    Conj<Registro>::Iterador iteradorDeRegistrosS = registrosT.CrearIt();
                    mostrarIndiceS(CamIndiceS, iteradorDeRegistrosS, DicIndiceS);
				}

            cout << endl;
            cout << endl;

			    Conj<Registro>::const_Iterador regIt = registrosT.CrearIt();
				cout << "PASO A MOSTRAR LOS REGISTROS DE LA TABLA " << nombreT << ":" << endl;
			int j = 1;
				while(regIt.HaySiguiente()){
					cout << "  * REGISTRO Nro " << j << " *"<< endl;
					Registro r = regIt.Siguiente();
					mostrarReg(r);
					regIt.Avanzar();
                    j++;
				}

			cout << "** FIN DE LA TABLA " << nombreT << " **" << endl;

		}
