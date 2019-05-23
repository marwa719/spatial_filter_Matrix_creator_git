

#ifndef CMIC_H
#define CMIC_H
//#include <armadillo>
//#include "CMatrice.h"
#include <string>
#include <iostream>
#include <fstream>
#include <armadillo>
using namespace std;
using namespace arma;

class CMic {
  private :

    Mat<double> _mics;
    int _Fe;
    int _nbr_ech;
  public :
    CMic();
    CMic(int Fe, int duree);
    ~CMic();
    int get_nbr_ech();
    int getFe();
    void setFe(int Fe);
    void setnbr_ech(int nbr_ech);
    void setMics(Mat<double> mics);
    Mat<double> Create_tab(string _mic1, string _mic2, string _mic3, string _mic4, string _mic5, string _mic6, string _mic7, string _mic8);
};

#endif // CMICS_H
