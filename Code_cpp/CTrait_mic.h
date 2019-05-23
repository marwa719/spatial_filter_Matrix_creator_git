

#ifndef CTRAIT_MIC_H_
#define CTRAIT_MIC_H_

#include "Cdec_frac.h"
//#include "CTraitment.h"
#include "CPuissance.h"
//#include "Passe-haut.h"

 class CTrait_mic {
private :
    /*Cdec_entier * dec_mic;
    Cdec_frac * dec_frac_mic;
    CPuissance * P_mic;*/
    CTraitement * T;
    CMic *M ;

public :
    CTrait_mic();
    ~CTrait_mic();
    vec traitement(Mat<double> TAB);

    /*void setdec_mic();
    void setdec_frac_mic();
    void setT_mic();
    void setP_mic();*/


 };




#endif
