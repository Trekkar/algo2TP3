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

  Driver::Dato Ddosd = Driver::Dato(20);
  Rcuatro.Definir(dos,Ddosd);    

  Driver::Dato Dtresd = Driver::Dato("Shitsu");
  Rcuatro.Definir(tres,Dtresd);

  ////////////////////////////////////////////////REGISTRO 5:
  Driver::Registro Rcinco;
  Driver::Dato Dunoe = Driver::Dato("Ian");
  Rcinco.Definir(uno,Dunoe);

  Driver::Dato Ddose = Driver::Dato(18);
  Rcinco.Definir(dos,Ddose);    

  Driver::Dato Dtrese = Driver::Dato("Misa");
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

  cout << "termina" << endl;
  return 0;

}
