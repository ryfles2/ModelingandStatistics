#include <iostream.h>
#include <fstream.h>
#include <math.h>

void makro()
{


  // wczytanie danych

  Int_t n=2000,i,j ;

 Float_t x1[2000];

  ifstream d;

   //d.open("density");
   d.open("C:\\out.txt");

   for(i=0;i<2000;i=i+1)
     {
       //d>>x1[i]>>x2[i]>>x3[i]>>x4[i]>>x5[i];

// operacje na danych

      // x6[i]=x1[i]+8.*x4[i];
	  d>>x1[i];


      }
   d.close();
   
  

   // deklarowanie histogramu "jednowymiarowego"  .... liczba klas, przedzia≈?

   TH1F *im1 = new TH1F("im1","Liczba dni potrzebnych na zostanie inøynierem ",50,1000.,1700.);
	//TH1F *im2 = new TH1F("im1","Jednowymiarowy Generator Liczb Losowych",10,0.,10.);
   //TH1F *im2 = new TH1F("im2","Dwuwymiarowy Generator Liczb Losowych",10,0.,1.);

//iml->draw();
  // TH2F *imd2 = new TH2F("imd2","Dwuwymiarowy Generator Liczb Losowych",10,0.,1.,10,0.,1.);

      for(i=0;i<2000;i=i+1)
        { 
	  im1->Fill(x1[i]);
	 
	}

    /*for(j=0;j<50;j=j+1)
      {
          imd2->Fill(x2[j],y2[j]);
	}*/
         
    //skalowanie histogramu

    /*      float scale_const=0.25;
           im2->Scale(scale_const);
    */
    ///stworzenie canwy do rysunku
//TCanvas *test = new TCanvas("test");
/*test->SetFillColor(0);
// podzial na 2 pady
test->Divide(2,1); 
// przejscie do pada z niumerem 2
 test->cd(1);

         im2->Draw();

      TH1F im3=8.* (*im2);*/

      // opcje rysowania histogramu
   im1->SetFillColor(2);
   im1->SetFillStyle(3002);
 //test->cd(1);
        // im1->Draw();
	 // narysowanie dwoch histogramowna jednym rysunku
	// im2->Draw("same");


	 // nowa canwa do rysowania

//Canvas *test2 = new TCanvas("test2");
// tlo biale ?? 
//test2->SetFillColor(0);
//dzielenie na pady

//Dopasowywanie funkcji do danych ( fitowanie)
//def funkcji do fitowania
//TF1 *ff1 = new TF1("ff1","[0]*exp(-(x-[1])/[2])",6.,10.);

// ustalenie parametr√≥w 9 w tej byly trzy parametry
//ff1->SetParameters(1.0,3.0,5.0);

 //fitowane 


//cos na temat statystyki
//ok np gStyle->SetOptStat(111);
//test2->Divide(2,1); 
 //test2->cd(1);
 // opcje draw : lego, box, cont4z
		
        im1->Draw();
		//im1->Fit(ff1);
		
	//test2->cd(2);
	//im2->Draw();
      //  imd2->Draw("lego");

	//test2->cd(3);
     //   imd2->Draw("box");

	//test2->cd(4);
      //  imd2->Draw("cont4z");
}
/*
TCanvas *test3 = new TCanvas("test3","test3");
// tlo biale ?? 
test3->SetFillColor(0);
// rysowanie funkcji

   //   TF3 *fun3z = new TF3("fun3z", "x+y*y-sin(z)-3.", -1, +1, -2, +2, -3, +3);
   TF3 *fun3z = new TF3("fun3z", "x*x+y*y+z*z-4.", -2, +2, -2, +2, -2, +2);
 
   fun3z->Draw("surf2z");

//Wykresy Dane z pliku....Lub wpisywane z listy polece≈? (kilka punkt√≥w)

// z pliku
Float_t x1[80],x2[80],x3[80],x4[80],x5[80],x6[80],x7[80],x8[80],x9[80],y[80],y1[80];
 Float xx1[80],xx2[80];
  ifstream d;

   d.open("tot_ph");
   for(i=0;i<6;i=i+1)
     {
       d>>x1[i]>>x2[i]>>x3[i]>>x4[i]>>x5[i]>>x6[i]>>x7[i]>>x8[i]>>x9[i]>>y[i]>>y1[i];
// operacje na danych
       xx1[i]=x8[i]/1000.;
       xx2[i]=x9[i]/1000.;
      }
   d.close();
//z listy polecen 
Int_t n=6,i ;

  Float_t erx[80];
  for(Int_t i=0;i<n;i++){erx[i]=0.;}

//tworzenie wykresu z danych - wykres bez bled√≥w
 
TGraph *gr3 =new TGraph(n,x1,xx1);

// opcje wykresu lini(typ, kolor, grybosc lini) i punktow(typ wielkosc) 

 gr3->SetLineColor(3);
 gr3->SetLineWidth(2);
 gr3->SetLineStyle(1);

 gr3->SetMarkerColor(3);
 gr3->SetMarkerStyle(21),
 gr3->SetMarkerSize(2);

 //rysowanie na domyslnej canwie c1 ‚?? a aby by≈?y osie. L. polaczone liniƒ?, P ‚?? zazanczone punkty

  gr3->Draw("ALP");}

//tworzenie wykresow z bledami

TGraph *gr =new TgraphErrors(n,x1,x2,erx,x3);

 gr->SetLineColor(1);
 gr->SetMarkerColor(1);
 gr->SetMarkerStyle(3),
 gr->SetMarkerSize(2);
 gr->SetLineStyle(1);
 gr->SetLineWidth(2);
  gr->Draw("ALP");


//Opcje Draw()
//Draw(ap) - os i punkty"
 gr->Draw("Ap");

//Draw(al) - os i laczenie punktow odcinkami
 gr1->Draw("Al");

//Draw(alp)-os, punkty oraz laczenie punktow odcinkami
 gr2->Draw("Alp");

//Draw(acp) - os, punkty oraz z interpolacja typu cubic spline
 gr4->Draw("Acp");


//Dopasowywanie funkcji do danych ( fitowanie)
//def funkcji do fitowania
TF1 *ff1 = new TF1("ff1","[0]*pow(x,[1])*exp(-[2]*x)",0,1000);

// ustalenie parametr√≥w 9 w tej byly trzy parametry
ff1->SetParameters(0.1,2.,0.01);

 //fitowane 
gr1->Fit(ff1);
}
*/