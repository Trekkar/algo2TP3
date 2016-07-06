#ifndef DATO_H_INCLUDED
#define DATO_H_INCLUDED

#include "Tipos.h"
#include "aed2/Conj.h"
#include "aed2/TiposBasicos.h"

 namespace aed2
{

 class Dato
    {
      public:

        Dato(const aed2::Nat& x);
        Dato(const aed2::String& x);

        bool esNat() const;
        bool esString() const;
        TipoCampo tipo() const;

        const aed2::Nat& dameNat() const;
        const aed2::String& dameString() const;

        bool operator == (const Dato& otro) const;
        bool operator != (const Dato& otro) const;
        bool operator  < (const Dato& otro) const;
        bool operator  > (const Dato& otro) const;

      private:

        TipoCampo tipo_;

        aed2::Nat nat_;
        aed2::String str_;
    };

Dato::Dato(const aed2::Nat& x)
  : tipo_( NAT ), nat_( x )
{}

Dato::Dato(const aed2::String& x)
  : tipo_( STR ), str_( x )
{}

bool Dato::esNat() const
{
  return tipo_ == NAT;
}

bool Dato::esString() const
{
  return tipo_ == STR;
}

TipoCampo Dato::tipo() const
{
  return tipo_;
}

const aed2::Nat& Dato::dameNat() const
{
  assert( esNat() );
  return nat_;
}

const aed2::String& Dato::dameString() const
{
  assert( esString() );
  return str_;
}

bool Dato::operator == (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ == otro.nat_ ) or
    ( tipo_ == STR and str_ == otro.str_ )
  );
}

bool Dato::operator < (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ < otro.nat_ ) or
    ( tipo_ == STR and str_ < otro.str_ )
  );
}

bool Dato::operator > (const Dato& otro) const
{
  return tipo_ == otro.tipo_ and (
    ( tipo_ == NAT and nat_ > otro.nat_ ) or
    ( tipo_ == STR and str_ > otro.str_ )
  );
}


bool Dato::operator != (const Dato& otro) const
{
  return not (*this == otro);
}

}
#endif // DATO_H_INCLUDED
