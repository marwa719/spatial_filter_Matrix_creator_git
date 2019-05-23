
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
//#ifndef CDEC_ENTIER_H_
//#define CDEC_ENTIER_H_

#include <armadillo>
#include <vector>
#include <iostream>
#include <fstream>
#include "CMic.h"
#include "CTraitement.h"
using namespace std;
using namespace arma;


class Cdec_entier {
  private :
      vec  reg;
      vec  dec_entier;
      vec phi_t;
      vec teta_t;
      CTraitement* T;
      CMic* mic;

  public :
      Cdec_entier(CMic* _M, CTraitement* _T, int num_mic);
      ~Cdec_entier();
      void setphi_t();
      void setteta_t();
      void setdec_entier(int num_mic);
      void setReg(vec _reg);
      void setmic(CMic* _mic);
      void setTraitement(CTraitement* _T);
      Mat<double> decalage_entier(vec mics);
};
//#endif // CDEC_ENTIER_H_
