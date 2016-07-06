// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
#include "Driver.cpp"
/*
#include "Driver.h"
#include "mini_test.h"
#include "DicNat.h"
#include "Dato.h"
*/
#include <string>
#include <iostream>
/*
void ejemplo_simple()
{
  aed2::Driver bd;
  ASSERT_EQ(bd.tablas().Cardinal(), 0);

  aed2::Conj<aed2::Columna> columnas_personas;

  aed2::Columna columna_dni;
  columna_dni.nombre = "DNI";
  columna_dni.tipo = aed2::NAT;

  aed2::Columna columna_nombre;
  columna_nombre.nombre = "nombre";
  columna_nombre.tipo = aed2::STR;

  aed2::Columna columna_apellido;
  columna_nombre.nombre = "apellido";
  columna_nombre.tipo = aed2::STR;

  columnas_personas.Agregar( columna_dni );
  columnas_personas.Agregar( columna_nombre );
  columnas_personas.Agregar( columna_apellido );

  aed2::Conj<aed2::NombreCampo> columnas_clave_personas;
  columnas_clave_personas.Agregar("DNI");

  bd.crearTabla("personas", columnas_personas, columnas_clave_personas);
  ASSERT_EQ(bd.tablas().Cardinal(), 1);

  aed2::Driver::Registro persona;
  persona.Definir("DNI", aed2::Driver::Dato(1));
  persona.Definir("nombre", aed2::Driver::Dato("Juan"));
  persona.Definir("apellido", aed2::Driver::Dato("Perez"));

  bd.insertarRegistro("personas", persona);

  // ...
}
*/
/*
void testDicNat(){
   aed2::DicNat<int, int> dn;
    ASSERT_EQ(dn.Vacio(), true);

    dn.Definir(10, 1);
    dn.Definir(4, 2);
    dn.Definir(15, 9);
    dn.Definir(16, 3);
    dn.Definir(13, 3);
    dn.Definir(14, 3);
    dn.Definir(7, 3);
    dn.Definir(8, 3);
    dn.Definir(5, 3);
    dn.Definir(6, 3);

    ASSERT_EQ(dn.Vacio(), false);
    ASSERT_EQ(dn.CantClaves(), 10);
    ASSERT_EQ(dn.Definido(10), true);
    ASSERT_EQ(dn.Significado(4), 2);
    ASSERT_EQ(dn.Min(), 4);
    ASSERT_EQ(dn.Max(), 16);

    dn.Borrar(10);
    ASSERT_EQ(dn.CantClaves(), 9);
    ASSERT_EQ(dn.Definido(10), false);

    dn.Borrar(16);
    ASSERT_EQ(dn.Max(), 15);

}
*/

void testDriver(){
/*
  NombreCampo uno = "Nombre";
  NombreCampo dos = "Edad";
  NombreCampo tres = "Apellido";

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


  NombreTabla nombre = "primera";
  Tabla pepito = Tabla(nombre,columna,claves);

  NombreTabla a = pepito.nombreDeLaTabla();

 ////////////////////////////////////////////////REGISTRO 1:
  Registro Runo;
  Dato Dunoa = Dato("Emiliano");
  Runo.Definir(uno,Dunoa);

  Dato Ddosa = Dato(21);
  Runo.Definir(dos,Ddosa);

  Dato Dtresa = Dato("Galimberti");
  Runo.Definir(tres,Dtresa);

  ////////////////////////////////////////////////REGISTRO 2:
  Registro Rdos;
  Dato Dunob = Dato("Lucas");
  Rdos.Definir(uno,Dunob);

  Dato Ddosb = Dato(20);
  Rdos.Definir(dos,Ddosb);

  Dato Dtresb = Dato("Giorgi");
  Rdos.Definir(tres,Dtresb);

////////////////////////////////////////////////REGISTRO 3:
  Registro Rtres;
  Dato Dunoc = Dato("Luis");
  Rtres.Definir(uno,Dunoc);

  Dato Ddosc = Dato(23);
  Rtres.Definir(dos,Ddosc);

  Dato Dtresc = Dato("Novaresio");
  Rtres.Definir(tres,Dtresc);

 ////////////////////////////////////////////////REGISTRO 4:
  Registro Rcuatro;
  Dato Dunod = Dato("Peter");
  Rcuatro.Definir(uno,Dunod);

  Dato Ddosd = Dato(24);
  Rcuatro.Definir(dos,Ddosd);

  Dato Dtresd = Dato("Pettigrew");
  Rcuatro.Definir(tres,Dtresd);

  ////////////////////////////////////////////////REGISTRO 5:
  Registro Rcinco;
  Dato Dunoe = Dato("Ian");
  Rcinco.Definir(uno,Dunoe);

  Dato Ddose = Dato(30);
  Rcinco.Definir(dos,Ddose);

  Dato Dtrese = Dato("Celestino");
  Rcinco.Definir(tres,Dtrese);

///////////////////////////////////////////////////AGREGAR REGISTROS:
  pepito.agregarRegistro(Runo);
  pepito.agregarRegistro(Rdos);
  pepito.agregarRegistro(Rtres);
  pepito.agregarRegistro(Rcuatro);
  pepito.agregarRegistro(Rcinco);


  uno = "Alias";
  dos = "Edad";
  tres = "Superheroe";




  Columna CunoD;
  CunoD.tipo = STR;
  CunoD.nombre = "Alias";

  Columna CdosD;
  CdosD.tipo = NAT;
  CdosD.nombre = "Edad";

  Columna CtresD;
  CtresD.tipo = STR;
  CtresD.nombre = "Superheroe";

  Conj<Columna> columnaD = Conj<Columna>();
  columnaD.Agregar(Cuno);
  columnaD.Agregar(Cdos);
  columnaD.Agregar(Ctres);

  Conj<NombreCampo> clavesD = Conj<NombreCampo>();
  claves.Agregar(uno);
  claves.Agregar(tres);

 NombreTabla name = "segunda";
 Tabla segunda = Tabla(name,columnaD,clavesD);

	   ////////////////////////////////////////////////REGISTRO 1:
	  Registro R2uno;
	  Dato D2unoa = Dato("Canuto");
	  R2uno.Definir(uno,D2unoa);

	  Dato D2dosa = Dato(21);
	  R2uno.Definir(dos,D2dosa);

	  Dato D2tresa = Dato("Shazam");
	  R2uno.Definir(tres,D2tresa);

	  ////////////////////////////////////////////////REGISTRO 2:
	  Registro R2dos;
	  Dato D2unob = Dato("Colagusano");
	  R2dos.Definir(uno,D2unob);

	  Dato D2dosb = Dato(24);
	  R2dos.Definir(dos,D2dosb);

	  Dato D2tresb = Dato("Zee");
	  R2dos.Definir(tres,D2tresb);

	  ////////////////////////////////////////////////REGISTRO 3:
	  Registro R2tres;
	  Dato D2unoc = Dato("Cornamenta");
	  R2tres.Definir(uno,D2unoc);

	  Dato D2dosc = Dato(17);
	  R2tres.Definir(dos,D2dosc);

	  Dato D2tresc = Dato("Batwoman");
	  R2tres.Definir(tres,D2tresc);

Registro R2cuatro;
    Dato D2unod = Dato("Cornamenta");
    R2cuatro.Definir(uno,D2unoc);

    Dato D2dosd = Dato(17);
    R2cuatro.Definir(dos,D2dosc);

    Dato D2tresd = Dato("Aquaman");
    R2cuatro.Definir(tres,D2tresc);

  segunda.agregarRegistro(R2uno);
  segunda.agregarRegistro(R2dos);
  segunda.agregarRegistro(R2tres);
  segunda.agregarRegistro(R2cuatro);
  



    pepito.mostrarTabla();
    segunda.mostrarTabla();
*/

}

int main(int argc, char **argv)
{
  Driver b = Driver();

NombreCampo campos1 [5] = {"nombre", "edad", "superheroe", "lu", "pelicula"};
String valoresCampo11 [5] = {"lucas", "ian", "franco", "emiliano", "clark"};
Nat valoresCampo21 [5] = {31, 14, 23, 16, 14};
String valoresCampo31 [5] = {"raven", "shazam", "nightwing", "zee", "superman"};
Nat valoresCampo41 [5] = {64, 100, 255, 138, 144};
String valoresCampo51 [5] = {"dosmiluno", "avatar", "warcraft", "avatar", "dory"};

Conj<Columna> columnas1 = Conj<Columna>();
Columna col;
int i = 0;
while(i < 5){
  col.nombre = campos1[i];
    if((i % 2) == 0){
      col.tipo = NAT;
    }else{
      col.tipo = STR;
    }
  columnas1.AgregarRapido(col);
  i++;
}
Conj<NombreCampo> claves1 = Conj<NombreCampo>();
claves1.AgregarRapido("lu");
claves1.AgregarRapido("nombre");
NombreTabla nombrePrimera = "primera";

b.crearTabla(nombrePrimera, columnas1, claves1);


i = 0;
int j = 0;
Registro r = Registro();
  while(i<5){
        r = Registro();
        r.Definir(campos1[0], valoresCampo11[i]);
        r.Definir(campos1[1], valoresCampo21[i]);
        r.Definir(campos1[2], valoresCampo31[i]);
        r.Definir(campos1[3], valoresCampo41[i]);
        r.Definir(campos1[4], valoresCampo51[i]);
    b.insertarRegistro(nombrePrimera, r);
    i++;
  }

NombreCampo campos2 [8] = {"banda", "lu", "figura", "numerocuadrado", "gasnoble", "zapato", "house", "librohp"};
String valoresCampo12 [5] = {"ramones", "queen", "guns", "acdc", "beatles" };
Nat valoresCampo22 [5] = {100, 254, 138, 145, 64};
String valoresCampo32 [5] = {"tetraedro", "piramide", "cilindro", "esfera", "cubo"};
Nat valoresCampo42 [5] = {64, 2, 128, 4096, 1024};
String valoresCampo52 [5] = {"kripton", "xenon", "argon", "helio", "neon"};
Nat valoresCampo62 [5] = {39, 40, 42, 40, 45};
String valoresCampo72 [5] = {"lannister", "martell", "ulryden", "payne", "baelish"};
Nat valoresCampo82 [5] = {1, 6, 6, 7, 6};

Conj<Columna> columnas2 = Conj<Columna>();
i = 0;
while(i < 8){
  col.nombre = campos2[i];
    if((i % 2) == 0){
      col.tipo = NAT;
    }else{
      col.tipo = STR;
    }
  columnas2.AgregarRapido(col);
  i++;
}
Conj<NombreCampo> claves2 = Conj<NombreCampo>();
claves2.AgregarRapido("lu");
claves2.AgregarRapido("banda");
NombreTabla nombreSegunda = "segunda";

b.crearTabla(nombreSegunda, columnas2, claves2);


Conj<NombreTabla> tablas = b.tablas();
Conj<NombreTabla>::const_Iterador it = tablas.CrearIt();

while(it.HaySiguiente()){
cout << it.Siguiente() << endl;
it.Avanzar();  
}

 
i = 0;
j = 0;
/*
  while(i<5){
        r = Registro();
        r.Definir(campos2[0], valoresCampo12[i]);
        r.Definir(campos2[1], valoresCampo22[i]);
        r.Definir(campos2[2], valoresCampo32[i]);
        r.Definir(campos2[3], valoresCampo42[i]);
        r.Definir(campos2[4], valoresCampo52[i]);
        r.Definir(campos2[5], valoresCampo62[i]);
        r.Definir(campos2[6], valoresCampo72[i]);
        r.Definir(campos2[7], valoresCampo82[i]);
    b.insertarRegistro(nombreSegunda, r);
    i++;
  } 
*/
  return 0;
}
