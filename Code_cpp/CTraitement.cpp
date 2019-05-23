#include "CTraitement.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
using namespace std;
using namespace arma ;

const double pi = 3.14;
const double R  = 0.0525000;  //rayon de la carte
const double V    = 340;  // vitesse du son dans l'air


void CTraitement :: setmic(CMic *_microphone){
  microphone = _microphone;
}

void CTraitement :: setecart_ech(Mat<double> _ecart_ech){
  ecart_ech = _ecart_ech;
}


CTraitement :: CTraitement(CMic *_microphone) {
  setmic(_microphone);
  setecart_ech(zeros(1,8));
}

CTraitement :: ~CTraitement() {

}

Mat<double> CTraitement :: calcul_ecart_ech(double theta_s, double phi_s){
   Mat<double> theta_i = zeros(1,8) ;
   theta_i(0) = -3*pi/8;
   theta_i(1) = -pi/8;
   theta_i(2) = pi/8 ;
   theta_i(3) = 3*pi/8;
   theta_i(4) = 5*pi/8;
   theta_i(5) = 7*pi/8;
   theta_i(6) = 9*pi/8;
   theta_i(7) = 11*pi/8;

   Mat<double> tau = zeros(1,8) ;

   for ( int i = 0; i < 8; i++){
      
      // Formule purement géométrique
      
      tau(i) = (R/V)*sin(phi_s)*(cos(theta_s - theta_s)- cos(theta_i(i) - theta_s)); // j'ai mis theta_o = theta_s
      ecart_ech(i) = tau(i)* (microphone->getFe());

  }

     double decalage = ceil(abs(ecart_ech.max())) ;
     for ( int i = 0; i < 8; i++){
        ecart_ech(i) = decalage - ecart_ech(i) ;
     }
   return ecart_ech;
}

