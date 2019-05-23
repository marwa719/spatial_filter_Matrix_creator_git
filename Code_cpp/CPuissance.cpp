#include "CPuissance.h"
#include <iostream>
#include <vector>
#define pi 3.14

CPuissance::CPuissance(){
	Puissances = zeros<vec>(120);


}

CPuissance::~CPuissance(){

}

vec CPuissance::getPuissance(vec _Puissances){

	return _Puissances;

}

void CPuissance::setPuissance(vec _Puissances){

	Puissances = _Puissances;

}


vec CPuissance::my_mean(Mat<double> mics){
	vec signal_mean = zeros<vec>(mics.n_rows);
	for (int i =0; i< mics.n_rows; i++){
		signal_mean(i) = (mics.col(0))(i) + (mics.col(1))(i) + (mics.col(2))(i) + (mics.col(3))(i) + (mics.col(4))(i) + (mics.col(5))(i) + (mics.col(6))(i)+ (mics.col(7))(i);


	}
	return signal_mean/(mics.n_rows);
}

void CPuissance::CalculPuissance(int angle,vec mic0, vec mic1, vec mic2, vec mic3, vec mic4, vec mic5, vec mic6, vec mic7){
	Mat<double> MICS = zeros(mic0.n_elem,8);
	MICS.col(0) = mic0;
	MICS.col(1) = mic1;
	MICS.col(2) = mic2;
	MICS.col(3) = mic3;
	MICS.col(4) = mic4;
	MICS.col(5) = mic5;
	MICS.col(6) = mic6;
	MICS.col(7) = mic7;

	vec signal_out =  my_mean(MICS);
    double puissance= (double)var(signal_out);
    Puissances(angle) = puissance;
}

vec CPuissance::idx2angles(int idx){
	vec phi_t = linspace<vec>(0,pi/2,4);
    vec teta_t = linspace<vec>(0,2*pi,30);
	vec Angles = zeros<vec>(2);
	Angles(0) = phi_t(idx%4);
	Angles(1) = teta_t(floor(idx/4));
	return Angles;
}

vec CPuissance::Direction(Mat<double> MIC0, Mat<double> MIC1, Mat<double> MIC2, Mat<double> MIC3, Mat<double> MIC4, Mat<double> MIC5, Mat<double> MIC6, Mat<double> MIC7){
	vec phi_t = linspace<vec>(0,pi/2,4);
    vec teta_t = linspace<vec>(0,2*pi,30);
	for (int k =0; k< (phi_t.n_elem)*(teta_t.n_elem); k++){

		CalculPuissance(k, MIC0.col(k), MIC1.col(k), MIC2.col(k), MIC3.col(k), MIC4.col(k), MIC5.col(k), MIC6.col(k), MIC7.col(k));
		
	}
	int idx_m= Puissances.index_max();
	cout << "Puissance max : " << Puissances(idx_m) << endl;
	
	return idx2angles(idx_m);


}
