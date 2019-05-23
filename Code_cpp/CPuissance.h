
#include <armadillo>
#include <cassert>
#include <iostream>
#include <vector>
using namespace arma;

class CPuissance {
	private :

	vec Puissances;

	public :

	CPuissance();
	~CPuissance();
	vec getPuissance(vec _Puissances);
	void setPuissance(vec _Puissances);
	vec idx2angles(int idx);
	vec my_mean(Mat<double> mics);
	void CalculPuissance(int angle,vec mic0, vec mic1, vec mic2, vec mic3, vec mic4, vec mic5, vec mic6, vec mic7);
	vec Direction(Mat<double> MIC0, Mat<double> MIC1, Mat<double> MIC2, Mat<double> MIC3, Mat<double> MIC4, Mat<double> MIC5, Mat<double> MIC6, Mat<double> MIC7);

};