
#include "Cdec_entier.h"
const double pi = 3.1415;

using namespace arma;

Cdec_entier::Cdec_entier( CMic* _M, CTraitement* _T, int num_mic){
  
    setReg(zeros<vec>(8));
    setmic(_M);
    setTraitement(_T);
    setphi_t();
    setteta_t();    
    setdec_entier(num_mic);
}

Cdec_entier::~Cdec_entier(){

}
void Cdec_entier :: setphi_t(){
  phi_t  = linspace<vec>(0,pi/2,4);
}

void Cdec_entier :: setteta_t(){
  teta_t  = linspace<vec>(0,2*pi,30);
}

void Cdec_entier:: setReg(vec _reg){
    reg = _reg;
}

void Cdec_entier:: setmic(CMic* _mic){
    mic = _mic;
}

void Cdec_entier:: setTraitement(CTraitement* _T){
    T = _T;
}

void Cdec_entier:: setdec_entier(int num_mic){

  dec_entier = zeros<vec>(teta_t.n_elem*phi_t.n_elem);
  for(int t = 0; t < teta_t.n_elem; t++){
    for(int p = 0; p < phi_t.n_elem; p++){
      dec_entier(phi_t.n_elem*t+p) = floor(T->calcul_ecart_ech( teta_t(t), phi_t(p))(num_mic));
    }
  }

}

// Renvoie une matrice (nb_ech*nb_directions) contenant un signal décalé selon toutes les directions (theta, phi)

Mat<double> Cdec_entier:: decalage_entier(vec mics){

  Mat<double> mic_dec = zeros(mics.n_elem, phi_t.n_elem*teta_t.n_elem);

  for(int t = 0; t < teta_t.n_elem; t++){
    for(int p = 0; p < phi_t.n_elem; p++){

       for(int li = 0; li<mics.n_elem; li++){
          reg(0) = mics(li);
          mic_dec(li,phi_t.n_elem*t+p ) = reg(dec_entier(phi_t.n_elem*t+p));  // 4*t+p va de 0 à 119
          reg(span(1, 7))= reg(span(0, 6));

          
       }
       reg = zeros<vec>(8);

    }
  }
     return mic_dec ;
}
