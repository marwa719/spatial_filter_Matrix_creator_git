#ifndef CTRAITEMENT_H_
#define CTRAITEMENT_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <iostream>
#include <fstream>
#include "CMic.h"
using namespace std;

class CTraitement {
 private :
    CMic *microphone;
    Mat<double> ecart_ech;

 public :

    CTraitement(CMic *_microphone);
    ~CTraitement();

    void setmic(CMic *_microphone);
    void setecart_ech(Mat<double> _ecart_ech);
    Mat<double> calcul_ecart_ech(double theta_s, double phi_s);
   // Mat<double> estimation(Mat<double> puissance);
};
#endif // CTRAITEMENT_H_
