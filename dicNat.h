#ifndef DICNAT_H_INCLUDED
#define DICNAT_H_INCLUDED



namespace aed2
{


    template<class K, class S>
    class DicNat
    {
    
    public:

    DicNat();
    ~DicNat();
    void Definir(const K clave, const S significado);
    bool Definido(const K& clave) const;
    S& Significado(const K& clave) const;
    void Borrar(const K& clave);
    bool Vacio() const;
    const S& Max() const;
    const S& Min() const;
    Nat CantClaves() const;



        private:

    struct nodo {

        K clave;
        nodo* izq;
        nodo* der;
        S significado;

        nodo(K c, S s) : clave(c), izq(NULL), der(NULL), significado(s) {}
        ~nodo(){
            delete izq;
            delete der;
        }

         };

        nodo* prim;
        Nat cant;

    };

template<class K, class S>
DicNat<K,S>::DicNat(): prim(NULL), cant(0){
}

template<class K, class S>
DicNat<K,S>::~DicNat(){
    delete this->prim;
}

template<class K, class S>
void DicNat<K,S>::Definir(const K c, const S s){
if (this->cant == 0){
       nodo* n = new nodo(c,s);
    this->prim = n;
    this->cant++;
     }else{
        nodo* actual = this->prim;
        bool noLoDefini = true;
        while (noLoDefini == true){

            if (c==actual->clave){
                actual->significado = s;
                noLoDefini = false;

                }else{
                if (c<actual->clave) {
                        if (actual->izq!=NULL){
                            actual = actual->izq;

                        }else{
                            nodo* n = new nodo(c,s);
                            actual->izq = n;
                            this->cant++;
                            noLoDefini = false;
                        }

                   }else{
                       if (actual->der!=NULL){
                            actual = actual->der;
                        }
                        else{
                            nodo* n = new nodo(c,s);
                            actual->der = n;
                            this->cant++;
                            noLoDefini = false;
                        }
                    }
            }
        }
    }
}

template<class K, class S>
bool DicNat<K,S>::Definido(const K& c) const{
    if (this->cant==0){
     return false;
    }
    else {
        bool res;
        nodo* actual = this->prim;
        bool estoyBuscando = true;

        while (estoyBuscando==true){
            if (c==actual->clave){
                res = true;
                estoyBuscando = false;
            }
            else{
                if(c<actual->clave){
                    if(actual->izq!=NULL){
                        actual=actual->izq;
                    }
                    else{
                        res = false;
                        estoyBuscando=false;
                    }
                }
                else {
                    if(actual->der!=NULL){
                        actual=actual->der;
                    }
                    else{
                        res = false;
                        estoyBuscando=false;
                    }
                }
            }

        }
        return res;
    }
}

template<class K, class S>
S& DicNat<K,S>::Significado(const K& c)const{

        nodo* actual = this->prim;
        bool noEncontre = true;

        while (noEncontre==true){
            if (c==actual->clave){
                noEncontre = false;
            }
            else{
                if(c<actual->clave){
                        actual=actual->izq;
                    }
                else {
                        actual=actual->der;
                    }
                }
            }
    return actual->significado;
}

template<class K, class S>
void DicNat<K,S>::Borrar(const K& c){

        nodo* actual = this->prim;
        bool izquierda;

        if(this->cant == 1){
            this->prim = NULL;
            delete actual;
        }
       else{
            nodo* padre = actual;
            bool noEncontre = true;

            while(noEncontre==true){
                padre = actual;
                if(c<actual->clave){
                    actual = actual->izq;
                    izquierda = true;

                    if(c==actual->clave){
                        noEncontre = false;
                    }
                }else{
                    if(c>actual->clave){
                        actual = actual->der;
                        izquierda = false;
                    }
                    if(c==actual->clave){
                        noEncontre = false;
                    }
                }
            }
            if(actual->izq==NULL && actual->der==NULL){
                if(izquierda == true){
                    padre->izq = NULL;
                    delete actual;
                }
                else{
                    padre->der = NULL;
                    delete actual;
                    }
            }else{
                    if(actual->izq!=NULL && actual->der==NULL){
                        if(izquierda==true){
                            padre->izq = actual->izq;
                            actual->izq = NULL;
                            delete actual;
                        }
                        else{
                        padre->der = actual->izq;
                        actual->izq = NULL;
                        delete actual;
                        }
                    }else{
                        if(actual->izq==NULL && actual->der!=NULL){
                            if(izquierda==true){
                            padre->izq = actual->der;
                            actual->der = NULL;
                            delete actual;
                            }
                            else{
                            padre->der = actual->der;
                            actual->der = NULL;
                            delete actual;
                            }
                        }else{
                            if(actual->izq!=NULL && actual->der!=NULL){

                            bool izquierdaheredero = true;
                            nodo* padreheredero = actual;
                            nodo* heredero = actual->izq;

                            while(heredero->der!=NULL){
                                izquierdaheredero = false;
                                padreheredero = heredero;
                                heredero = heredero->der;
                            }
                        actual->clave = heredero->clave;
                        actual->significado = heredero->significado;
                        if(heredero->izq==NULL){
                            if(izquierdaheredero==true){
                                padreheredero->izq = NULL;
                                delete heredero;
                            }
                            else{
                                padreheredero->der = NULL;
                                delete heredero;
                            }
                        }
                    else{
                        if(izquierdaheredero==true){
                            padreheredero->izq = heredero->izq;
                            heredero->izq = NULL;
                            delete heredero;
                        }
                        else{
                            padreheredero->der = heredero->izq;
                            heredero->izq = NULL;
                            delete heredero;
                            }
                        }
                    }
                }
            }
        }
    }
this->cant--;
}


template<class K, class S>
bool DicNat<K,S>::Vacio() const{
    if(this->cant==0){
        return true;
    }
    else{
        return false;
    }
}

template<class K, class S>
const S& DicNat<K,S>::Max()const{

        nodo* actual = this->prim;

        while (actual->der!=NULL){
                        actual=actual->der;
                    }

    return actual->significado;
}

template<class K, class S>
const S& DicNat<K,S>::Min()const{

        nodo* actual = this->prim;

        while (actual->izq!=NULL){
                        actual=actual->izq;
                    }

    return actual->significado;
}

template<class K, class S>
Nat DicNat<K,S>::CantClaves()const{
    return this->cant;
}

}

#endif // DICNAT_H_INCLUDED
