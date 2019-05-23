
#ifndef CDEC_FRAC_H
#define CDEC_FRAC_H
#include <armadillo>
#include <cassert>
#include <iostream>
#include <vector>
//#include "CMic.h"
//#include "CTraitement.h"
#include "Cdec_entier.h"
using namespace arma;

//template <typename R = double>
class  Cdec_frac
{
private:
	double xnd2_1;
	double xnd2_2;
	double xnd2_3;
	double xn_1;
	double xn_2;
    vec dec_frac;
    vec phi_t;
    vec teta_t;
	CMic* mic;
	CTraitement* T;

public:
	//Mat<double> mu;
	vec getdec_frac();
	void setxnd2_1();
	void setxnd2_2();
	void setxnd2_3();
	void setxn_1();
	void setxn_2();
	void reset();
	void setdec_frac(int num_mic);
	void setTraitement(CTraitement* _T);
	void setphi_t();
	void setteta_t();
	Cdec_frac(int num_mic, CTraitement* T);
	virtual ~Cdec_frac();
	vec step(const vec x_elt, double teta, double phi);
};

//#include "farrow_rc_naive.hxx"

#endif //CDEC_FRAC_H
