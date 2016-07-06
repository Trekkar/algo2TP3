// compilar usando:
//   g++ -o tests tests.cpp Driver.cpp <lista de archivos *.cpp propios>

#include "Driver.h"
#include "mini_test.h"
#include "DicNat.h"
#include "Dato.h"

#include <string>
#include <iostream>

/*void ejemplo_simple()
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
void testDato(){

    aed2::Dato a = aed2::Dato(1);
    aed2::Dato b = aed2::Dato(1);
    aed2::Dato c = aed2::Dato("ian");
    aed2::Dato d = aed2::Dato("ian");
    aed2::Dato e = aed2::Dato(2);

    ASSERT_EQ(a==b,true);
    ASSERT_EQ(c==d,true);/**/
    ASSERT_EQ(a.esNat(),true);
    ASSERT_EQ(c.esString(),true);
    ASSERT_EQ(a<e,true);
     ASSERT_EQ(e>a,true);



}

int main(int argc, char **argv)
{
  RUN_TEST( testDicNat );
  RUN_TEST( testDato );

  /********************************************************************
   * TODO: escribir casos de test exhaustivos para todas              *
   * las funcionalidades de cada módulo.                              *
   * La interacción con el TAD principal se debe hacer exclusivamente *
   * a través de la interfaz del driver.                              *
   ********************************************************************/

	return 0;
}
