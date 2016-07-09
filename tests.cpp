// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>
#include "Driver.cpp"
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
  Driver b = Driver();

NombreCampo campos1 [5] = {"nombre", "edad", "superheroe", "lu", "pelicula"};
String valoresCampo11 [5] = {"lucas", "ian", "franco", "emiliano", "clark"};
Nat valoresCampo21 [5] = {31, 14, 23, 16, 14};
String valoresCampo31 [5] = {"raven", "shazam", "nightwing", "zee", "superman"};
Nat valoresCampo41 [5] = {155, 100, 255, 354, 14};
String valoresCampo51 [5] = {"dosmiluno", "avatar", "warcraft", "avatar", "dory"};

Conj<Columna> columnas1 = Conj<Columna>();
Columna col;
int i = 0;
while(i < 5){
  col.nombre = campos1[i];
    if((i % 2) == 0){
      col.tipo = STR;
    }else{
      col.tipo = NAT;
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
  while(i<3){
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
Nat valoresCampo22 [5] = {100, 255, 138, 354, 64};
String valoresCampo32 [5] = {"tetraedro", "piramide", "cilindro", "esfera", "cubo"};
Nat valoresCampo42 [5] = {64, 2, 128, 4096, 1024};
String valoresCampo52 [5] = {"kripton", "xenon", "radon", "neon", "helio"};
Nat valoresCampo62 [5] = {39, 40, 42, 40, 45};
String valoresCampo72 [5] = {"lannister", "martell", "ulryden", "payne", "baelish"};
Nat valoresCampo82 [5] = {1, 6, 6, 7, 6};

Conj<Columna> columnas2 = Conj<Columna>();
i = 0;
while(i < 8){
  col.nombre = campos2[i];
    if((i % 2) == 0){
      col.tipo = STR;
    }else{
      col.tipo = NAT;
    }
  columnas2.AgregarRapido(col);
  i++;
}
Conj<NombreCampo> claves2 = Conj<NombreCampo>();
claves2.AgregarRapido("lu");
claves2.AgregarRapido("banda");
NombreTabla nombreSegunda = "segunda";

b.crearTabla(nombreSegunda, columnas2, claves2);
 
i = 0;
j = 0;
  while(i<4){
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



//////////////////////////////////////////////////////////////////////////////////////////////////////TESTS

//TEST 1:

  cout << "TEST 1:" << endl;

  //Crear indice nat, en este caso libreta universitaria

  NombreCampo lu = "lu";
  b.crearIndiceNat(nombrePrimera, lu);

  //Como se agregaron como registros todos los elementos del array "valoresCampo41" excepto los dos ultimos, 
  //a saber, los elementos {155, 100, 255}, el minimo deberia ser 100

  cout << "EL MINIMO ES: " << (b.minimo(nombrePrimera,lu)).dameNat() << endl;

  r = Registro();
  r.Definir(campos1[0], valoresCampo11[4]);
  r.Definir(campos1[1], valoresCampo21[4]);
  r.Definir(campos1[2], valoresCampo31[4]);
  r.Definir(campos1[3], valoresCampo41[4]);
  r.Definir(campos1[4], valoresCampo51[4]);
  b.insertarRegistro(nombrePrimera, r);

  //Ahora agregue un registro cuyo valor en el campo 'lu' es 14, el nuevo minimo deberia ser ese

  cout << "EL MINIMO ES: " << (b.minimo(nombrePrimera,lu)).dameNat() << endl;

  //Ahora voy a borrar el registro que agregue antes, por lo que el minimo deberia ser ahora 100 nuevamente

  b.borrarRegistro(nombrePrimera, lu, Dato(14));
  cout << "EL MINIMO ES: " << (b.minimo(nombrePrimera,lu)).dameNat() << endl;

 // b.insertarRegistro(nombrePrimera, r);
 
//TEST 2:

  cout << endl;
  cout << "TEST 2:" << endl;

  //Del test anterior queda que el maximo es 255. Por lo que ahora

  cout << "EL MAXIMO ES: " << (b.maximo(nombrePrimera,lu)).dameNat() << endl;

  r = Registro();
  r.Definir(campos1[0], valoresCampo11[3]);
  r.Definir(campos1[1], valoresCampo21[3]);
  r.Definir(campos1[2], valoresCampo31[3]);
  r.Definir(campos1[3], valoresCampo41[3]);
  r.Definir(campos1[4], valoresCampo51[3]);
  b.insertarRegistro(nombrePrimera, r);

  //Ahora agruegue un registro que en 'lu' lleva 354. Este deberia ser el nuevo maximo

  cout << "EL MAXIMO ES: " << (b.maximo(nombrePrimera,lu)).dameNat() << endl;

  //Lo borro, por lo que ahora vuelve a ser 255 el maximo

  b.borrarRegistro(nombrePrimera, lu, Dato(354));
  cout << "EL MAXIMO ES: " << (b.maximo(nombrePrimera,lu)).dameNat() << endl;

  //b.insertarRegistro(nombrePrimera, )
 



//TEST 3:
  cout << endl;
  cout << "TEST 3:" << endl;

  NombreCampo gasnoble = "gasnoble";
  b.crearIndiceString(nombreSegunda, gasnoble);

  //El gas noble minimo deberia ser krypton, ya que entre mas cerca de la letra "a" este, menor sera. 

  cout << "EL MINIMO ES: " << (b.minimo(nombreSegunda,lu)).dameString() << endl;

    r = Registro();
    r.Definir(campos2[0], valoresCampo12[4]);
    r.Definir(campos2[1], valoresCampo22[4]);
    r.Definir(campos2[2], valoresCampo32[4]);
    r.Definir(campos2[3], valoresCampo42[4]);
    r.Definir(campos2[4], valoresCampo52[4]);
    r.Definir(campos2[5], valoresCampo62[4]);
    r.Definir(campos2[6], valoresCampo72[4]);
    r.Definir(campos2[7], valoresCampo82[4]);
    b.insertarRegistro(nombreSegunda, r);

  //Ahora agrego un registro con el gas noble helio, deberia ser el minimo porque h < k

  cout << "EL MINIMO ES: " << (b.minimo(nombreSegunda,lu)).dameString() << endl;

  //Voy a borrarlo, y krypton deberia ser el menor nuevamente

  b.borrarRegistro(nombreSegunda, gasnoble, Dato("helio"));
  cout << "EL MINIMO ES: " << (b.minimo(nombreSegunda,lu)).dameString() << endl;  




//TEST 4:
  cout << endl;
  cout << "TEST 4:" << endl;


  //hago join primera-segunda
  b.generarVistaJoin(nombrePrimera, nombreSegunda, lu);
  //Chequeo que existe uno y no el otro
  cout << "Tiene que mostrar un 1 ---> " << b.hayJoin(nombrePrimera, nombreSegunda) << endl;
  cout << "Tiene que mostrar un 0 ---> " << b.hayJoin(nombreSegunda, nombrePrimera) << endl;
  //hago join segunda-primera
  b.generarVistaJoin(nombreSegunda, nombrePrimera, lu);
  //chequeo que ambos joins 
  cout << "Tiene que mostrar un 1 ---> " << b.hayJoin(nombrePrimera, nombreSegunda) << endl;
  cout << "Tiene que mostrar un 1 ---> " << b.hayJoin(nombreSegunda, nombrePrimera) << endl;
  //borro el join segunda-primera
  b.borrarVistaJoin(nombreSegunda, nombrePrimera);
  //quedo solo el primer join
  cout << "Tiene que mostrar un 1 ---> " << b.hayJoin(nombrePrimera, nombreSegunda) << endl;
  cout << "Tiene que mostrar un 0 ---> " << b.hayJoin(nombreSegunda, nombrePrimera) << endl;
  //borro el primer join
  b.borrarVistaJoin(nombrePrimera, nombreSegunda);
  //no quedo ningun join
  cout << "Tiene que mostrar un 0 ---> " << b.hayJoin(nombrePrimera, nombreSegunda) << endl;
  cout << "Tiene que mostrar un 0 ---> " << b.hayJoin(nombreSegunda, nombrePrimera) << endl;


  //CHEQUEO QUE NO HAYA NOMBRES EN LOS JOINS






//TEST 5:
  cout << endl;
  cout << "TEST 5:" << endl;

  //Hago un join y muestro su vista join.
  b.generarVistaJoin(nombrePrimera, nombreSegunda, lu);
  Conj<Registro> vista = b.vistaJoin(nombrePrimera, nombreSegunda);
  Conj<Registro>::Iterador it = vista.CrearIt();
  cout << "Muestro el Join: " << endl;
    while(it.HaySiguiente()){
        mostrarReg(it.Siguiente());
        it.Avanzar();
    }


//Agrego un registro nuevo, asi se genera un nuevo registro en la vista join
  cout << "Agrego un registro DE L.U 155" << endl;
    Registro h = Registro();
    h.Definir(campos2[0], valoresCampo12[4]);
    h.Definir(campos2[1], Dato(155));
    h.Definir(campos2[2], valoresCampo32[4]);
    h.Definir(campos2[3], valoresCampo42[4]);
    h.Definir(campos2[4], valoresCampo52[4]);
    h.Definir(campos2[5], valoresCampo62[4]);
    h.Definir(campos2[6], valoresCampo72[4]);
    h.Definir(campos2[7], valoresCampo82[4]);
    b.insertarRegistro(nombreSegunda, h);

  cout  << "Ahora el join debe tener un nuevo registro" <<  endl;

  Conj<Registro> vista2 = b.vistaJoin(nombrePrimera, nombreSegunda);
  Conj<Registro>::Iterador it2 = vista2.CrearIt();
  cout << "Muestro el Join: " << endl;
    while(it2.HaySiguiente()){
        mostrarReg(it2.Siguiente());
        it2.Avanzar();
    } 


  //Borro todo y me quedo con el join vacio  
  cout  << "Ahora borro todos los registros para que el join me quede vacio" <<  endl;
  b.borrarRegistro(nombreSegunda, lu, Dato(100));
  b.borrarRegistro(nombreSegunda, lu, Dato(155));  
  b.borrarRegistro(nombreSegunda, lu, Dato(255));

 // b.tablaMaxima();
  
 // cout << "CHECK" << endl;


  Conj<Registro> vista3 = b.vistaJoin(nombrePrimera, nombreSegunda);
  Conj<Registro>::Iterador it3 = vista3.CrearIt();
  cout << "Muestro el Join: " << endl;
    if (!(it3.HaySiguiente())){
      
      cout << "JOIN VACIO!" << endl;
    
    }else{
      while(it3.HaySiguiente()){
          mostrarReg(it3.Siguiente());
          it3.Avanzar();
      }
    } 

    //b.tablaMaxima();

  return 0;
}












