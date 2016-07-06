#include "Driver.h"
#include "BaseDeDatos.cpp"
#include <iostream>

bool aed2::operator == (const aed2::Columna& c1, const aed2::Columna& c2)
{
  return c1.nombre == c2.nombre and c1.tipo == c2.tipo;
}

using namespace aed2;

////////////////////////////////////////////////////////////////////////////////
// Dato
////////////////////////////////////////////////////////////////////////////////

/*
Driver::Dato::Dato(const aed2::Nat& x)
  : tipo_( NAT ), nat_( x )
{}

Driver::Dato::Dato(const aed2::String& x)
  : tipo_( STR ), str_( x )
{}

bool Driver::Dato::esNat() const
{
  return tipo_ == NAT;
}

bool Driver::Dato::esString() const
{
  return tipo_ == STR;
}

TipoCampo Driver::Dato::tipo() const
{
  return tipo_;
}

const aed2::Nat& Driver::Dato::dameNat() const
{
  assert( esNat() );
  return nat_;
}

const aed2::String& Driver::Dato::dameString() const
{
  assert( esString() );
  return str_;
}

bool Driver::Dato::operator == (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ == otro.nat_ ) or
    ( tipo_ == STR and str_ == otro.str_ )
  );
}

bool Driver::Dato::operator != (const Dato& otro) const
{
  return not (*this == otro);
}

*/
////////////////////////////////////////////////////////////////////////////////
// Base de datos
////////////////////////////////////////////////////////////////////////////////

Driver::Driver()
{
  b = BaseDeDatos();
}

Driver::~Driver()
{
}

////////////////////////////////////////////////////////////////////////////////
// Tablas
////////////////////////////////////////////////////////////////////////////////

void Driver::crearTabla(const NombreTabla& nombre, const aed2::Conj<Columna>& columnas, const aed2::Conj<NombreCampo>& claves)
{
//  cout << "crearTabla" << endl;
  Tabla* t =  new Tabla(nombre, columnas, claves);
  b.agregarTabla(*t);
}

void Driver::insertarRegistro(const NombreTabla& tabla, const Registro& registro)
{
//  cout << "insertarRegistro" << endl;
  NombreTabla t = tabla;
  Registro r = Registro(registro);
  b.insertarEntrada(r, t);
}

void Driver::borrarRegistro(const NombreTabla& tabla, const NombreCampo& columna, const Dato& valor)
{
  Registro reg = Registro();
  reg.Definir(columna,valor);
  b.borrar(reg, tabla);
}

aed2::Conj<Columna> Driver::columnasDeTabla(const NombreTabla& tabla) const
{
  Conj<Columna> res = Conj<Columna>();
  Conj<NombreCampo> cam = (b.dameTabla(tabla)).campos();
  Conj<NombreCampo>::const_Iterador itCam = cam.CrearIt();
  while(itCam.HaySiguiente()){
    NombreCampo nom = itCam.Siguiente();
    TipoCampo tipoc;
      if((b.dameTabla(tabla)).tipoCampo(nom)){
        tipoc = NAT;
      }else{
        tipoc = STR;
      }

    Columna col;
    col.nombre = nom;
    col.tipo = tipoc;

    res.AgregarRapido(col);
    itCam.Avanzar();
  }

  return res;
}

aed2::Conj<NombreCampo> Driver::columnasClaveDeTabla(const NombreTabla& tabla) const
{
  Conj<NombreCampo> res = (b.dameTabla(tabla)).claves();
  return res;
}

aed2::Conj<Registro> Driver::registrosDeTabla(const NombreTabla& tabla) const
{
  Conj<Registro> res = (b.dameTabla(tabla)).registros();
  return res;
}

aed2::Nat Driver::cantidadDeAccesosDeTabla(const NombreTabla& tabla) const
{
  Nat res = (b.dameTabla(tabla)).accesos();
  return res;
}

Dato Driver::minimo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  Dato res = (b.dameTabla(tabla)).minimo(columna);
  return res;
}

Dato Driver::maximo(const NombreTabla& tabla, const NombreCampo& columna) const
{
  Dato res = (b.dameTabla(tabla)).maximo(columna);
  return res;
}

aed2::Conj<Registro> Driver::buscar(const NombreTabla& tabla, const Registro& criterio) const
{
  Conj<Registro> res = b.buscar(criterio, tabla);
  return res;
}

aed2::Conj<NombreTabla> Driver::tablas() const
{
 Conj<NombreTabla> res = b.nombresTablas();
 return res;
}

NombreTabla Driver::tablaMaxima() const
{
  b.MostrarBaseDeDatos();
  return b.tablaMaxima();
}

////////////////////////////////////////////////////////////////////////////////
// Indices
////////////////////////////////////////////////////////////////////////////////

bool Driver::tieneIndiceNat(const NombreTabla& tabla) const
{
  return (b.dameTabla(tabla)).tieneIndiceNat();
}

bool Driver::tieneIndiceString(const NombreTabla& tabla) const
{
  return (b.dameTabla(tabla)).tieneIndiceString();
}

NombreCampo Driver::campoIndiceNat(const NombreTabla& tabla) const
{
  NombreCampo cam = (b.dameTabla(tabla)).campoDicNat();
  return cam;
}

NombreCampo Driver::campoIndiceString(const NombreTabla& tabla) const
{
  NombreCampo cam = (b.dameTabla(tabla)).campoDicString();
  return cam; 
}

void Driver::crearIndiceNat(const NombreTabla& tabla, const NombreCampo& campo)
{
  (b.dameTabla(tabla)).indexar(campo);
}

void Driver::crearIndiceString(const NombreTabla& tabla, const NombreCampo& campo)
{
  (b.dameTabla(tabla)).indexar(campo);
}

////////////////////////////////////////////////////////////////////////////////
// Joins
////////////////////////////////////////////////////////////////////////////////

bool Driver::hayJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  bool res;
  res = b.hayJoin(tabla1, tabla2);
  return res;
}

NombreCampo Driver::campoJoin(const NombreTabla& tabla1, const NombreTabla& tabla2) const
{
  NombreCampo cam = b.campoJoin(tabla1, tabla2);
  return cam; 
}

void Driver::generarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2, const NombreCampo& campo)
{
  b.generarVistaJoin(tabla1, tabla2, campo);
}

void Driver::borrarVistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)
{
  b.borrarJoin(tabla1, tabla2);
}

aed2::Conj<Registro> Driver::vistaJoin(const NombreTabla& tabla1, const NombreTabla& tabla2)/* const*/
{
  
  return b.vistaJoin(tabla1, tabla2);

}

/*
int main()
{
  cout << "driver" << endl;
	return 0;
}
*/