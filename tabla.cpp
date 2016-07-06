#include "tabla.h"
#include "Driver.cpp"
using namespace std;

int main(){

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
  NombreTabla nombre = "tuvieja";
  Tabla pepito = Tabla(nombre,columna,claves);

  NombreTabla a = pepito.nombreDeLaTabla();

 ////////////////////////////////////////////////REGISTRO 1:
  Registro Runo;
  Dato Dunoa = Dato("Emiliano");
  Runo.Definir(uno,Dunoa);

  Dato Ddosa = Dato(21);
  Runo.Definir(dos,Ddosa);

  Dato Dtresa = Dato("Aiko");
  Runo.Definir(tres,Dtresa);

  ////////////////////////////////////////////////REGISTRO 2:
  Registro Rdos;
  Dato Dunob = Dato("Lucas");
  Rdos.Definir(uno,Dunob);

  Dato Ddosb = Dato(20);
  Rdos.Definir(dos,Ddosb);

  Dato Dtresb = Dato("Yuno");
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

  Dato Ddosd = Dato(20);
  Rcuatro.Definir(dos,Ddosd);

  Dato Dtresd = Dato("Yuno");
  Rcuatro.Definir(tres,Dtresd);

  ////////////////////////////////////////////////REGISTRO 5:
  Registro Rcinco;
  Dato Dunoe = Dato("Ian");
  Rcinco.Definir(uno,Dunoe);

  Dato Ddose = Dato(20);
  Rcinco.Definir(dos,Ddose);

  Dato Dtrese = Dato("Misa");
  Rcinco.Definir(tres,Dtrese);

///////////////////////////////////////////////////AGREGAR REGISTROS:
  pepito.agregarRegistro(Runo);
  pepito.agregarRegistro(Rdos);
  pepito.agregarRegistro(Rtres);
  pepito.agregarRegistro(Rcuatro);
  pepito.agregarRegistro(Rcinco);

///////////////////////////////////////////////////BORRAR REGISTROS:
  pepito.quitarRegistro(Rdos);
  pepito.agregarRegistro(Rdos);

/////////////////////////////////////////////////////INDEX:
  pepito.indexar("Waifu");
  pepito.indexar("Edad");


  //cout<< "CHECKPOINT" << endl;
/////////////////////////////////////////////////MUESTRO TABLA:
  pepito.mostrarTabla();


cout << endl;
cout << endl;
cout<< "CHECKPOINT" << endl;
cout << endl;
cout << endl;

  pepito.quitarRegistro(Rdos);
  pepito.quitarRegistro(Rtres);
  pepito.mostrarTabla();
  cout << "termina" << endl;
  return 0;

}
