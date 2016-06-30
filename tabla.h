    
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
        tuplaIt(const Conj<Driver::Registro>::Iterador c, const Conj<tuplaIt>::Iterador o);
        
        void cambiarCR(const Conj<Driver::Registro>::Iterador c);
        void cambiarOA(const Conj<tuplaIt>::Iterador o);

        private:
        Conj<Driver::Registro>::Iterador cr;
        Conj<tuplaIt>::Iterador oa;
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
        Dicc<Nat, Conj<tuplaIt> > dicNat() const;
        Dicc<String, Conj<tuplaIt> > dicString() const;

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
        Dicc<Nat, Conj<tuplaIt> > DicIndiceN;                     //DicIndiceN: DICCIONARIO(NAT,CONJ(tuplaIt))
        NombreCampo CamIndiceN;                                   //CamIndiceN: STRING
        bool EstaIndiceN;                                         //EstaIndiceN: BOOL
        Dicc<String, Conj<tuplaIt> > DicIndiceS;                  //DicIndiceS: DICCIONARIO(STRING,CONJ(tuplaIt))
        NombreCampo CamIndiceS;                                   //CamIndiceS: STRING
        bool EstaIndiceS;                                         //EstaIndiceS: BOOL
        Driver::Dato minDatoNat;                                  //minDriver::DatoNat: Driver::Dato
        Driver::Dato minDatoString;                               //minDriver::DatoString: Driver::Dato
        Driver::Dato maxDatoNat;                                  //maxDriver::DatoNat: Driver::Dato
        Driver::Dato maxDatoString;                               //maxDriver::DatoString: Driver::Dato
        Nat accesosT;                                             //accesos: NAT
        Conj<tuplaIt> Vacio;                                      //ad-hoc
    };



        //ALGORITMOS:

        tuplaIt::tuplaIt(const Conj<Driver::Registro>::Iterador c, const Conj<tuplaIt>::Iterador o) : cr(c), oa(o) {
        } 

        void tuplaIt::cambiarCR(const Conj<Driver::Registro>::Iterador c){
        cr = c;
        }

        void tuplaIt::cambiarOA(const Conj<tuplaIt>::Iterador o){
        oa = o;    
        }



        Tabla::Tabla(const NombreTabla& nombre, const Conj<Columna>& columnas, const Conj<NombreCampo>& claves) : 
        nombreT(nombre), camposClave(claves), registrosT(Conj<Driver::Registro>()), 
        DicIndiceN(Dicc<Nat, Conj<tuplaIt> >()), CamIndiceN("null"), EstaIndiceN(false), 
        DicIndiceS(Dicc<String, Conj<tuplaIt> >()), CamIndiceS("null"), EstaIndiceS(false),
        minDatoNat(Driver::Dato(0)), minDatoString(Driver::Dato("null")), maxDatoNat(Driver::Dato(0)), maxDatoString(Driver::Dato("null")), 
        accesosT(0), Vacio(Conj<tuplaIt>()) {

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
        
        Tabla::~Tabla() {}

        void Tabla::mostrarTabla() const {}
        
//        bool operator==(const Tabla&) const;
        
        Conj<Driver::Registro> Tabla::registros() const {
            return registrosT;
        }
        
        void Tabla::agregarRegistro(const Driver::Registro& r) {
            accesosT++;
            Conj<Driver::Registro>::Iterador it = registrosT.Agregar(r);
            Conj<tuplaIt>::Iterador itVac = Vacio.CrearIt();

            if((EstaIndiceN) && (!EstaIndiceS)){
                tuplaIt tupla = tuplaIt(it, itVac);
                if(!(DicIndiceS.Definido((r.Significado(CamIndiceS)).dameString()))){
                    Conj<tuplaIt> conjVac = Conj<tuplaIt>();
                    DicIndiceS.Definir((r.Significado(CamIndiceS)).dameString(), conjVac);
                }

                (DicIndiceS.Significado((r.Significado(CamIndiceS)).dameString())).AgregarRapido(tupla);
                //minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //TENGO QUE HACER DELETE DE TUPLAIT? CONJ LO COPIA O LO AGREGA DIRECTO?
            }

            if((!EstaIndiceN) && (EstaIndiceS)){
                tuplaIt tupla = tuplaIt(it, itVac);
                if(!(DicIndiceN.Definido((r.Significado(CamIndiceN)).dameNat()))){
                    Conj<tuplaIt> conjVac = Conj<tuplaIt>();
                    DicIndiceN.Definir((r.Significado(CamIndiceN)).dameNat(), conjVac);
                }

                (DicIndiceN.Significado((r.Significado(CamIndiceN)).dameNat())).AgregarRapido(tupla);
                //minDatoNat = max(DicIndiceN);     CUANDO ESTE LISTO ABB
                //maxDatoNat = min(DicIndiceN);     CUANDO ESTE LISTO ABB
            }

            if((EstaIndiceN) && (EstaIndiceS)){
                tuplaIt tuplaN = tuplaIt(it, itVac);
                if(!(DicIndiceN.Definido((r.Significado(CamIndiceN)).dameNat()))){
                    Conj<tuplaIt> conjVac = Conj<tuplaIt>();
                    DicIndiceN.Definir((r.Significado(CamIndiceN)).dameNat(), conjVac);
                }

                Conj<tuplaIt>::Iterador actual = (DicIndiceN.Significado((r.Significado(CamIndiceN)).dameNat())).AgregarRapido(tuplaN);

                tuplaIt tuplaS = tuplaIt(it, actual);
                if(!(DicIndiceS.Definido((r.Significado(CamIndiceS)).dameString()))){
                    Conj<tuplaIt> conjVac = Conj<tuplaIt>();
                    DicIndiceS.Definir((r.Significado(CamIndiceS)).dameString(), conjVac);
                }

                Conj<tuplaIt>::Iterador vecino = (DicIndiceS.Significado((r.Significado(CamIndiceS)).dameString())).AgregarRapido(tuplaS);

                (actual.Siguiente()).cambiarOA(vecino);

                //OJO, ESTOY ASUMIENDO QUE SI AGREGO UN ELEMENTO A UN CONJUNTO Y LE PREGUNTO "SIGUIENTE"
                //AL ITERADOR QUE ME DEVUELVE, ME VA A DEVOLVER EL ELEMENTO QUE ACABO DE AGREGAR

                //minDatoNat = max(DicIndiceN);     CUANDO ESTE LISTO ABB
                //maxDatoNat = min(DicIndiceN);     CUANDO ESTE LISTO ABB
                //minDatoString = max(DicIndiceS);      CUANDO ESTE LISTO TRIE
                //maxDatoString = min(DicIndiceS);      CUANDO ESTE LISTO TRIE
            }
        }
        
        void Tabla::quitarRegistro(const Driver::Registro) {}
        
        void Tabla::indexar(const NombreCampo) {}
        
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
        
        Dicc<Nat, Conj<tuplaIt> > Tabla::dicNat() const{
            return DicIndiceN;
        }
        
        Dicc<String, Conj<tuplaIt> > Tabla::dicString() const{
            return DicIndiceS;
        }