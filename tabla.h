    #include <iostream>
    #include "Tipos.h"
    #include "aed2/Dicc.h"
    #include "aed2/Lista.h"
    #include "aed2/TiposBasicos.h"
    #include "aed2/Conj.h"
    #include "Driver.h"
    using namespace aed2;



	class tuplaIt {
        
        public:
        tuplaIt();
        tuplaIt(Conj<Driver::Registro>::Iterador c, Lista<tuplaIt>::Iterador o);
        
        void cambiarCR(Conj<Driver::Registro>::Iterador c);
        void cambiarOA(Lista<tuplaIt>::Iterador o);
		Conj<Driver::Registro>::Iterador CR();
		Lista<tuplaIt>::Iterador OA();


        private:
        Conj<Driver::Registro>::Iterador cr;
        Lista<tuplaIt>::Iterador oa;
    };



class Tabla {

      public:
        Tabla(const NombreTabla&, const Conj<Columna>&, const Conj<NombreCampo>&);
        Tabla(const Tabla&);
        ~Tabla();
        void mostrarTabla() const;
//        bool operator==(const Tabla&) const;
        Conj<Driver::Registro> registros() const;
        void agregarRegistro(const Driver::Registro&);
        void quitarRegistro(const Driver::Registro);
        void indexar(const NombreCampo);
        NombreTabla nombre() const;
        Conj<NombreCampo> claves() const;
        Conj<NombreCampo> campos() const;
        Conj<NombreCampo> indices() const;
        bool tipoCampo(const NombreCampo) const;
        Driver::Dato minimo(const NombreCampo) const;
        Driver::Dato maximo(const NombreCampo) const;
        Nat accesos() const;
        Driver::Registro regCriterio() const;
        NombreCampo campoDicNat() const;
        NombreCampo campoDicString() const;
        Dicc<Nat, Lista<tuplaIt> > dicNat() const;
        Dicc<String, Lista<tuplaIt> > dicString() const;
        NombreTabla nombreDeLaTabla() const;

      private:

        Tabla& operator=(const Tabla& otra) {                     //?
        assert(false);
        return *this;
        }



        NombreTabla nombreT;                                      //nombre: STRING
        Driver::Registro registroCrit;                            //Driver::RegistroCrit: Driver::Registro
        Conj<NombreCampo> camposT;                                //campos: CONJ(CAMPO)
        Conj<NombreCampo> camposClave;                            //camposClave: CONJ(CAMPO)
        Conj<Driver::Registro> registrosT;                        //Driver::Registros: CONJ(Driver::Registro)
        Dicc<Nat, Lista<tuplaIt> > DicIndiceN;                     //DicIndiceN: DICCIONARIO(NAT,CONJ(tuplaIt))
        NombreCampo CamIndiceN;                                   //CamIndiceN: STRING
        bool EstaIndiceN;                                         //EstaIndiceN: BOOL
        Dicc<String, Lista<tuplaIt> > DicIndiceS;                  //DicIndiceS: DICCIONARIO(STRING,CONJ(tuplaIt))
        NombreCampo CamIndiceS;                                   //CamIndiceS: STRING
        bool EstaIndiceS;                                         //EstaIndiceS: BOOL
        Driver::Dato minDatoNat;                                  //minDriver::DatoNat: Driver::Dato
        Driver::Dato minDatoString;                               //minDriver::DatoString: Driver::Dato
        Driver::Dato maxDatoNat;                                  //maxDriver::DatoNat: Driver::Dato
        Driver::Dato maxDatoString;                               //maxDriver::DatoString: Driver::Dato
        Nat accesosT;                                             //accesos: NAT
        Lista<tuplaIt> Vacio;                                      //ad-hoc
    };



        //ALGORITMOS:

    	tuplaIt::tuplaIt() {}

        tuplaIt::tuplaIt(Conj<Driver::Registro>::Iterador c, Lista<tuplaIt>::Iterador o) : cr(c), oa(o) {} 

        void tuplaIt::cambiarCR(Conj<Driver::Registro>::Iterador c){
        	cr = c;
        }

        void tuplaIt::cambiarOA(Lista<tuplaIt>::Iterador o){
        	oa = o;    
        }

        Conj<Driver::Registro>::Iterador tuplaIt::CR(){
        	return cr;
        }

		Lista<tuplaIt>::Iterador tuplaIt::OA(){
			return oa;
		}

        Tabla::Tabla(const NombreTabla& nombre, const Conj<Columna>& columnas, const Conj<NombreCampo>& claves) : 
        nombreT(nombre), camposClave(claves), registrosT(Conj<Driver::Registro>()), 
        DicIndiceN(Dicc<Nat, Lista<tuplaIt> >()), CamIndiceN("null"), EstaIndiceN(false), 
        DicIndiceS(Dicc<String, Lista<tuplaIt> >()), CamIndiceS("null"), EstaIndiceS(false),
        minDatoNat(Driver::Dato(0)), minDatoString(Driver::Dato("null")), maxDatoNat(Driver::Dato(0)), maxDatoString(Driver::Dato("null")), 
        accesosT(0), Vacio(Lista<tuplaIt>()) {

        Conj<Columna>::const_Iterador actual = columnas.CrearIt();
        	while(actual.HaySiguiente()){
        		NombreCampo c = (actual.Siguiente()).nombre;
        		camposT.Agregar(c);
        		if((actual.Siguiente()).tipo == NAT){
        			registroCrit.Definir(c,Driver::Dato(1));
        		}else{
        			registroCrit.Definir(c,Driver::Dato("null"));
        		}

        		actual.Avanzar();
        		
        	}

        //PERDON, ES UN ASCO, LO SE, PERO GCC ESTA EMPECINADO EN NO COMPILAR

/*        registroCrit = Dicc<NombreCampo, Driver::Dato>();
        camposT = Conj<NombreCampo>();

        nombreT = nombre;
        camposClave = claves;
        registrosT = Conj<Driver::Registro>();
        DicIndiceN = Dicc<Nat, Conj<tuplaIt> >();
        CamIndiceN = "null";
        EstaIndiceN = false;
        DicIndiceS = Dicc<String, Conj<tuplaIt> >();
        CamIndiceS = "null";
        EstaIndiceS = false;
        minDatoNat = Driver::Dato(0);
        minDatoString = Driver::Dato("null");
        maxDatoNat = Driver::Dato(0);
        maxDatoString = Driver::Dato("null");
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

        void Tabla::mostrarTabla() const {}
        
//        bool operator==(const Tabla&) const;
        
        Conj<Driver::Registro> Tabla::registros() const {
            return registrosT;
        }

        bool registrosIguales(const Driver::Registro& a, const Driver::Registro& b){
        	if(a.CantClaves() != b.CantClaves()){
        		return false;
        	}

        	Driver::Registro::const_Iterador itA = a.CrearIt();
        	Driver::Registro::const_Iterador itB = b.CrearIt();

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
        
        void Tabla::agregarRegistro(const Driver::Registro& r) {
            accesosT++;
            Conj<Driver::Registro>::Iterador it = registrosT.Agregar(r);
            Lista<tuplaIt>::Iterador itVac = Vacio.CrearIt();

            if((EstaIndiceN) && (!EstaIndiceS)){
                tuplaIt tupla = tuplaIt(it, itVac);
                if(!(DicIndiceS.Definido((r.Significado(CamIndiceS)).dameString()))){
                    Lista<tuplaIt> conjVac = Lista<tuplaIt>();
                    DicIndiceS.Definir((r.Significado(CamIndiceS)).dameString(), conjVac);
                }

                Agregar((DicIndiceS.Significado((r.Significado(CamIndiceS)).dameString())), tupla);
                //minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //TENGO QUE HACER DELETE DE TUPLAIT? CONJ LO COPIA O LO AGREGA DIRECTO?
            }

            if((!EstaIndiceN) && (EstaIndiceS)){
                tuplaIt tupla = tuplaIt(it, itVac);
                if(!(DicIndiceN.Definido((r.Significado(CamIndiceN)).dameNat()))){
                    Lista<tuplaIt> conjVac = Lista<tuplaIt>();
                    DicIndiceN.Definir((r.Significado(CamIndiceN)).dameNat(), conjVac);
                }

                Agregar((DicIndiceN.Significado((r.Significado(CamIndiceN)).dameNat())), tupla);
                //minDatoNat = max(DicIndiceN);     CUANDO ESTE LISTO ABB
                //maxDatoNat = min(DicIndiceN);     CUANDO ESTE LISTO ABB
            }

            if((EstaIndiceN) && (EstaIndiceS)){
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

                //OJO, ESTOY ASUMIENDO QUE SI AGREGO UN ELEMENTO A UN CONJUNTO Y LE PREGUNTO "SIGUIENTE"
                //AL ITERADOR QUE ME DEVUELVE, ME VA A DEVOLVER EL ELEMENTO QUE ACABO DE AGREGAR

                //minDatoNat = max(DicIndiceN);     CUANDO ESTE LISTO ABB
                //maxDatoNat = min(DicIndiceN);     CUANDO ESTE LISTO ABB
                //minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
            }
        }
        
        void Tabla::quitarRegistro(const Driver::Registro r) {
        	accesosT++;
        	if(EstaIndiceN){
        		Nat valor = (r.Significado(CamIndiceS)).dameNat();
        		Lista<tuplaIt>::Iterador it = (DicIndiceN.Significado(valor)).CrearIt();
        			while((it.HaySiguiente()) && !(registrosIguales((((it.Siguiente()).CR()).Siguiente()), r))){
        				it.Avanzar();
        			}
        		if(((it.Siguiente()).OA()).HaySiguiente()){
        		((it.Siguiente()).OA()).EliminarSiguiente();
                //minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
        		}
        		((it.Siguiente()).CR()).EliminarSiguiente();
        		it.EliminarSiguiente();
                //minDatoNat = max(DicIndiceN);     CUANDO ESTE LISTO ABB
                //maxDatoNat = min(DicIndiceN);     CUANDO ESTE LISTO ABB
        	}else{
        		if(EstaIndiceS){
        		String valor = (r.Significado(CamIndiceS)).dameString();
        		Lista<tuplaIt>::Iterador it = (DicIndiceS.Significado(valor)).CrearIt();
        			while((it.HaySiguiente()) && !(registrosIguales((((it.Siguiente()).CR()).Siguiente()), r))){
        				it.Avanzar();
        			}
        			((it.Siguiente()).CR()).EliminarSiguiente();
        			it.EliminarSiguiente();
                //minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
        		}else{
        			Conj<Driver::Registro>::Iterador it = registrosT.CrearIt();
        			while((it.HaySiguiente()) && !(registrosIguales((it.Siguiente()), r))){
        				it.Avanzar();
        			}
        			it.EliminarSiguiente();
        		}
        	}
        }
        

        void Tabla::indexar(const NombreCampo c) {
        	Conj<Driver::Registro>::Iterador it = registrosT.CrearIt();
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
        				String vecino = ((it.Siguiente()).Significado(c)).dameString();
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

        		CamIndiceN = c;
        		//minDatoNat = max(DicIndiceN);     CUANDO ESTE LISTO ABB
                //maxDatoNat = min(DicIndiceN);     CUANDO ESTE LISTO ABB
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
        				Nat vecino = ((it.Siguiente()).Significado(c)).dameNat();
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
        		CamIndiceS = c;
        		//minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
        	}
        }
        
        NombreTabla Tabla::nombre() const{
            return nombreT;
        }

        Conj<NombreCampo> Tabla::claves() const{
            return camposClave;
        }
        
        Conj<NombreCampo> Tabla::campos() const{
            return camposT;
        }

        Conj<NombreCampo> Tabla::indices() const{
            Conj<NombreCampo>* res = new Conj<NombreCampo>;
            if(EstaIndiceN){
                res->Agregar(CamIndiceN);
            }
            if(EstaIndiceS){
                res->Agregar(CamIndiceS);   
            }
            return *res;
        }

        bool Tabla::tipoCampo(const NombreCampo c) const {
            return (registroCrit.Significado(c)).esNat();
        }

        Driver::Dato Tabla::minimo(const NombreCampo c) const {
            if((CamIndiceN == c) && EstaIndiceN){
                return minDatoNat;
            }else{
                return minDatoString;
            }
        }

        Driver::Dato Tabla::maximo(const NombreCampo c) const {
            if((CamIndiceN == c) && EstaIndiceN){
                return maxDatoNat;
            }else{
                return maxDatoString;
            }
        }
        
        Nat Tabla::accesos() const{
            return accesosT;
        }

        Driver::Registro Tabla::regCriterio() const{
            return registroCrit;
        }
        
        NombreCampo Tabla::campoDicNat() const{
            return CamIndiceN;
        }
        
        NombreCampo Tabla::campoDicString() const{
            return CamIndiceS;
        }
        
        Dicc<Nat, Lista<tuplaIt> > Tabla::dicNat() const{
            return DicIndiceN;
        }
        
        Dicc<String, Lista<tuplaIt> > Tabla::dicString() const{
            return DicIndiceS;
        }

        NombreTabla Tabla::nombreDeLaTabla() const{
        	return nombreT;
        }