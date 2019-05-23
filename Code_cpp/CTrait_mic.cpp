#include "CTrait_mic.h"

#define Fe  16000
#define time  0.037  //temps correspondant pour avoir 512 echantillons, soit la longueur de buffer.

CTrait_mic :: CTrait_mic(){
 M = new CMic(Fe, time); //set la fréquence d'échantillonnage et le temps d'acquisition des 8 signaux
 T = new CTraitement(M);  

}
CTrait_mic :: ~CTrait_mic(){
}


// Debut de la déclaration de la fonction filtre passe_haut

vec my_mean(Mat<double> mics){    
	vec signal_mean = zeros<vec>(mics.n_cols);
	double sum=0;
	for(int k=0; k< mics.n_cols; k++){
		sum =0;
		for (int i =0; i< mics.n_rows; i++){
			sum += (mics.col(k))(i);
		}
		signal_mean(k) = sum/mics.n_rows;

	}
	
	return signal_mean;
}

Mat<double> filtre (Mat<double> Mics){

	vec moy = my_mean(Mics);
	vec moyenne_mic = zeros<vec>(Mics.n_rows);
	for (int i =0; i< Mics.n_cols; i++){
		moyenne_mic = moy(i)*ones<vec>(Mics.n_rows);
		Mics.col(i) = Mics.col(i) - moyenne_mic;

	}
	return Mics;

}


//Fin de fonction passe_haut

vec CTrait_mic ::  traitement(Mat<double> TAB){  // La fonction traitement effectue toute la chaîne de traitement pour chaque buffer 512*8 arrivant en entrée
       
        TAB = filtre(TAB);  //Filtrage passe haut en amont
        
        //routine de traitement pour un micro : décalage entier puis décalage fractionnaire 
        
        
       // Micro 0 : 
       Cdec_entier *Dec0 = new Cdec_entier(M, T, 0);
       Mat<double> micd0 = Dec0->decalage_entier( TAB.col(0));
       Cdec_frac *Dec_frac0 = new Cdec_frac(0, T);
       Mat<double> micfrac0 = zeros(micd0.n_rows, micd0.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac0.col(4*t+p) = Dec_frac0->step(micd0.col(4*t+p), t, p);
          }
        }


      delete Dec0;
      delete Dec_frac0;

      // Micro 1 :
        Cdec_entier *Dec1 = new Cdec_entier(M, T, 1);
       Mat<double> micd1 = Dec1->decalage_entier( TAB.col(1));


       Cdec_frac *Dec_frac1 = new Cdec_frac(1, T);
       Mat<double> micfrac1 = zeros(micd0.n_rows, micd0.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac1.col(4*t+p) = Dec_frac1->step(micd1.col(4*t+p), t, p);
          }
        }


        delete Dec1;
        delete Dec_frac1;


        // Micro 2 :
         Cdec_entier *Dec2 = new Cdec_entier(M, T, 2);
       Mat<double> micd2 = Dec2->decalage_entier( TAB.col(2));


       Cdec_frac *Dec_frac2 = new Cdec_frac(2, T);
       Mat<double> micfrac2 = zeros(micd2.n_rows, micd2.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac2.col(4*t+p) = Dec_frac2->step(micd2.col(4*t+p), t, p);
          }
        }

        delete Dec2;
        delete Dec_frac2;


        // Micro 3:
              Cdec_entier *Dec3 = new Cdec_entier(M, T, 3);
       Mat<double> micd3 = Dec3->decalage_entier( TAB.col(3));

       Cdec_frac *Dec_frac3 = new Cdec_frac(3, T);
       Mat<double> micfrac3 = zeros(micd3.n_rows, micd3.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac3.col(4*t+p) = Dec_frac3->step(micd3.col(4*t+p), t, p);
          }
        }

        delete Dec3;
        delete Dec_frac3;

        // micro 4
        Cdec_entier *Dec4 = new Cdec_entier(M, T, 4);
        Mat<double> micd4 = Dec4->decalage_entier( TAB.col(4));

       Cdec_frac *Dec_frac4 = new Cdec_frac(4, T);
       Mat<double> micfrac4 = zeros(micd4.n_rows, micd4.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac4.col(4*t+p) = Dec_frac4->step(micd4.col(4*t+p), t, p);
          }
        }

        delete Dec4;
        delete Dec_frac4;

        //micro 5
        Cdec_entier *Dec5 = new Cdec_entier(M, T, 4);
        Mat<double> micd5 = Dec5->decalage_entier( TAB.col(5));

       Cdec_frac *Dec_frac5 = new Cdec_frac(5, T);
       Mat<double> micfrac5 = zeros(micd5.n_rows, micd5.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac5.col(4*t+p) = Dec_frac5->step(micd5.col(4*t+p), t, p);
          }
        }


        delete Dec5;
        delete Dec_frac5;

        //micro 6
        Cdec_entier *Dec6 = new Cdec_entier(M, T, 6);
        Mat<double> micd6 = Dec6->decalage_entier( TAB.col(6));

        Cdec_frac *Dec_frac6 = new Cdec_frac(6, T);
        Mat<double> micfrac6 = zeros(micd6.n_rows, micd6.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac6.col(4*t+p) = Dec_frac6->step(micd6.col(4*t+p), t, p);
          }
        }


        delete Dec6;
        delete Dec_frac6;

        //Micro 7
        Cdec_entier *Dec7 = new Cdec_entier(M, T, 7);
        Mat<double> micd7 = Dec7->decalage_entier( TAB.col(7));

        Cdec_frac *Dec_frac7 = new Cdec_frac(7, T);
        Mat<double> micfrac7 = zeros(micd7.n_rows, micd7.n_cols);
        for(int t = 0; t < 30; t++){
          for(int p = 0; p < 4; p++){
             micfrac7.col(4*t+p) = Dec_frac7->step(micd7.col(4*t+p), t, p);
          }
        }

        delete Dec7;
        delete Dec_frac7;
        delete M;
        delete T;
        
        
        // Ici on a alors les pavés direction(angles)/temps pour chaque micro. On procède alors au calcul de puissance pour chaque direction.

        CPuissance *P = new CPuissance();
        
        // La fonction CPuissance() renvoie alors le couple correpondant à la plus grande puissance
        
       vec couple = P->Direction(micfrac0, micfrac1, micfrac2, micfrac3, micfrac4, micfrac5, micfrac6, micfrac7) ;
       cout << "PHI " << couple(0)*180/3.14 << "°"<< endl << "THETA "<< couple(1)*180/3.14 << "°"<< endl;


     delete P;
     return couple;

 }
