//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include<iostream.h>
#include<fstream.h>
#include<math.h>
#include<Math.hpp>
#include "Unit5.h"
#define n 1001
#define N 10
#define m 30
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{


}


//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender)
{



double B[N] = {0.286, 0.106, -0.077, -0.039, -0.048, -0.013, 0.082, 0.087, -0.085, 0.014};
double Rv[N] = {0.46, 0.3, 0, -0.2, -0.24, -0.14, 0, 0.05, 0.02, 0};
double Re[N] = {0.95, 0.69, 0.37, 0.05, -0.19, -0.37, -0.43, -0.36, -0.14, -0.05};
double Rx[N][N], Xt[1001],Yt[1001];
double kor[n];
AnsiString q;
char symb;
ifstream infile("Lb7_11_s.prn");
for(int i=0;infile;)
 {
 infile.get(symb);
 if ((symb>='0' && symb<='9') || symb=='.'||symb=='-')
 {   if(symb=='.') {symb=',';};
     q=q+symb;
  }
  else if(q.Length()>=2)
     {kor[i]=StrToFloat(q);
      q=""; i++;
     }}


     double zav[n];
AnsiString q2;
char symb2;
ifstream infile2("Lb7_11_z.prn");
for(int i=0;infile2;)
 {
 infile2.get(symb2);
 if ((symb2>='0' && symb2<='9') || symb2=='.'||symb2=='-')
 {   if(symb2=='.') {symb2=',';};
     q2=q2+symb2;
  }
  else if(q2.Length()>=2)
     {zav[i]=StrToFloat(q2);
      q2=""; i++;
     }}


 //======Matrix R===============
int s, a=-1;
for (int i=0;i<=N;i++){
a++;
for (int j=0;j<=N;j++) {
s=abs(j-a);
Rx[i][j] = Rv[s] + Re[s];

 }
}
for (int i=0;i<=N;i++){
for (int j=0;j<=N;j++) {
StringGrid1->Cells[i][j]=Rx[i][j];
            }
        }


//===Kor signal============
 for(int i=0;i<=152;i++)
 Series3->Add(kor[i],i);
  //===zavada==============
 for(int i=0;i<=152;i++)
Series4->Add(zav[i],i);
 //===input signal
 for(int i=0;i<=1001;i++){
 Xt[i]=kor[i]+zav[i];


}
//====OUTPUT SIGNAL============
   double sum,korel_summ=0,v,Y[101],Y2[101];
for(int t=0;t<=1001;t++){
 sum=0;
 for (int j=0;j<=10;j++){
 sum+=B[j]*Xt[t-j];
 }
 Yt[t]=sum;
korel_summ+=Yt[t];
}
v=0.001*korel_summ;
for(int i=0;i<=150;i++){
Series8->Add(Yt[i],i);
Series7->Add(Xt[i],i);
}
  for(int i=0;i<=151;i++){
 Series5->Add(kor[i],i);
  Series13->Add(Yt[i],i);

}
//Korel function==============

  for(int t=0;t<=10;t++)
   {
    sum=0;
   for(int k=1;k<1000-t;k++) {
   sum+=(Yt[k]-v)*(Yt[k+t]-v);
   }
   Y[t]=(1.0/(n-t))*sum;
    Series10->Add(Y[t],t);
    }

 //Duspertion

 double d;
 d=Y[0];
 Label1->Caption = d;

//Impulse Reaction=============
Xt[0]=1;
   for(int i=1;i<=150;i++){
 Xt[i]=0;
}
 for(int t=0;t<=50;t++){
 sum=0;
 for (int j=0;j<=10;j++){
 sum=B[j]*Xt[t-j];

 }
 Yt[t]=sum;

 Series1->Add(Yt[t],t);

}

  //usefull signal============
  for(int i=0;i<=9;i++){
Series2->Add(Rv[i],i);
  Series11->Add(Rv[i],i);
    Series12->Add(Y[i],i);
}
 for(int i=0;i<=9;i++){
 Series9->Add(Rx[i][0],i);

}


}
//---------------------------------------------------------------------------




