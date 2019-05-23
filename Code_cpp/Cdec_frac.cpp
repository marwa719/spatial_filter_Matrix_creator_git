#include "Cdec_frac.h"
#include <armadillo>
#include <cassert>
#include <iostream>
#include <vector>
#include <complex>

using namespace arma;
const double pi = 3.14;

Cdec_frac :: Cdec_frac(int num_mic, CTraitement* _T )
{
    reset();
    setphi_t();
    setteta_t();
    setTraitement(_T);
    setdec_frac(num_mic);
}


Cdec_frac ::~Cdec_frac()
{}

void Cdec_frac::reset(){
  setxnd2_1();
  setxnd2_2();
  setxnd2_3();
  setxn_1();
  setxn_2();
}

void Cdec_frac :: setxnd2_1(){
    xnd2_1  = 0;
 

}

void Cdec_frac :: setxnd2_2(){
    xnd2_2 = 0;
}

void Cdec_frac :: setxnd2_3(){
    xnd2_3 = 0;

}

void Cdec_frac :: setxn_1(){
    xn_1 = 0;

}

void Cdec_frac :: setxn_2(){
    xn_2 = 0;

}

void Cdec_frac:: setTraitement(CTraitement* _T){
    T = _T;
}

void Cdec_frac :: setphi_t(){
  phi_t  = linspace<vec>(0,pi/2,4);
}


void Cdec_frac :: setteta_t(){
  teta_t  = linspace<vec>(0,2*pi,30);
}

// Calcule les décalages fractionnaires pour un micro selon toutes les directions 

void Cdec_frac :: setdec_frac(int num_mic){  
    
    dec_frac = zeros<vec>(phi_t.n_elem*teta_t.n_elem);
    for(int t = 0; t < teta_t.n_elem; t++){
        for(int p = 0; p < phi_t.n_elem; p++){
            dec_frac(phi_t.n_elem*t+p) = T->calcul_ecart_ech(teta_t(t), phi_t(p))(num_mic) - floor(T->calcul_ecart_ech( teta_t(t), phi_t(p))(num_mic));
        }
    }

}

vec Cdec_frac :: getdec_frac(){
  return dec_frac;
}

// FIltre de Farrow

vec Cdec_frac ::step(const vec x_elt, double teta, double phi )  
{
    vec y_elt = zeros<vec>(x_elt.n_elem);

    vec xnd2 = x_elt * 0.5;

  

    for(int li = 0; li<x_elt.n_elem; li++){
          y_elt(li)  = this->dec_frac(phi_t.n_elem*teta+phi) * ((xnd2(li) - this->xnd2_1 - this->xnd2_2 + this->xnd2_3* this->dec_frac(phi_t.n_elem*teta+phi)+  (this->xn_1) + this->xnd2_1 - xnd2(li) - this->xnd2_2 - this->xnd2_3)) + this->xn_2;

          this->xn_2 = this->xn_1;

          this->xn_1 = x_elt(li);

          this->xnd2_3 = this->xnd2_2;
          this->xnd2_2 = this->xnd2_1;
          this->xnd2_1 = xnd2(li);
    }
    reset();

    return y_elt;
  }

