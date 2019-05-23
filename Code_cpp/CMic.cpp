#include "CMic.h"

using namespace arma;
using namespace std;

CMic :: CMic() {

}

CMic :: ~CMic() {

}

int CMic :: getFe() {
 return _Fe;
}

void CMic :: setFe(int Fe) {
  _Fe = Fe;
}

int CMic :: get_nbr_ech(){
 return _nbr_ech;
}

void CMic :: setnbr_ech(int nbr_ech){
   _nbr_ech = nbr_ech;
}


void CMic :: setMics(Mat<double> mics){
   _mics = mics;
}

CMic::CMic(int Fe, int duree)
{
    setFe(Fe);
    setnbr_ech(duree*Fe);
    setMics(zeros(_nbr_ech,8));

}

// Fonction utilisée pour récupérer des fichiers .raw stockés en local

Mat<double> CMic :: Create_tab(string _mic0, string _mic1, string _mic2, string _mic3, string _mic4, string _mic5, string _mic6, string _mic7)
{
    string tab[8];
    tab[0] = _mic0;
    tab[1] = _mic1;
    tab[2] = _mic2;
    tab[3] = _mic3;
    tab[4] = _mic4;
    tab[5] = _mic5;
    tab[6] = _mic6;
    tab[7] = _mic7;

    for (int i = 0; i < 8; i++){
        std::ifstream micstream;
        micstream.open(tab[i] , std::ifstream::binary);
        int16_t b;
      
        for (int j = 0; j < get_nbr_ech(); j++){
            micstream.read((char*)&b, sizeof(b));
            _mics(j,i) = (double)b;
            
        }
        micstream.close();
    }
    return _mics ;

}

