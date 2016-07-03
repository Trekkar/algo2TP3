#include "tabla.h"
#include "Driver.cpp"
using namespace std;

int main(){

  NombreCampo uno = "mierda";
  NombreCampo dos = "sangre";
  NombreCampo tres = "vomito";
  
  Columna Cuno;
  Cuno.tipo = NAT;
  Cuno.nombre = uno;

  Columna Cdos;
  Cdos.tipo = STR;
  Cdos.nombre = dos;

  Columna Ctres;
  Ctres.tipo = NAT;
  Ctres.nombre = tres;

  Conj<Columna> columna = Conj<Columna>();
  columna.Agregar(Cuno);
  columna.Agregar(Cdos);
  columna.Agregar(Ctres);

  Conj<NombreCampo> claves = Conj<NombreCampo>();
  claves.Agregar(uno);
  claves.Agregar(dos);

  NombreTabla nombre = "tuvieja";
  Tabla pepito = Tabla(nombre,columna,claves);

  NombreTabla a = pepito.nombreDeLaTabla();

  Driver::Registro Runo;
  Driver::Dato Duno = Driver::Dato("hola");
  Runo.Definir(uno,Duno);

  Driver::Dato Ddos = Driver::Dato(3);
  Runo.Definir(dos,Ddos);	  

  Driver::Dato Dtres = Driver::Dato("chau");
  Runo.Definir(tres,Dtres);	    


  pepito.agregarRegistro(Runo);

  pepito.mostrarTabla();

  cout << "termina" << endl;
  return 0;

}
