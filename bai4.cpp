#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

class sach {
  protected:
    int masach; char tensach[20];
  public:
    friend class dmsach;
    friend class sachmuon;
    void nhapbp(){
      cout<<"\nma sach:"; cin>>masach;
      fflush(stdin);
      cout<<"ten sach:"; cin.getline(tensach,20);
    }
    void xemmh(){ cout<<"\n"<<masach<<" "<<tensach; }
};
class dmsach{
  sach a[100]; int tssach;
  public:
    void nhapbp(){
      cout<<"Tong so sach:"; cin>>tssach;
      for (int i = 0; i < tssach; i++)
        a[i].nhapbp();
    }
    void xemmh(){
      cout<<"\nDanh muc sach:";
      for (int i = 0; i < tssach; i++)
        a[i].xemmh();
    }
    sach xemten(int ms){
      for(int i=0;i<tssach;i++){
        if(ms==a[i].masach) return a[i];
      }
    }
};
class sachmuon: public sach {
  int soluong;
  public:
    friend class phieumuon;
    void nhapbp(dmsach d){
      cout<<"\nma sach:"; cin>>masach;
      sach x=d.xemten(masach);
      strcpy(tensach,x.tensach);
      cout<<"so luong:"; cin>>soluong;
    }
    void xemmh(){ sach::xemmh(); cout<<" "<<soluong; }
};
class phieumuon {
  long sophieu,tongsoluong,tssachmuon;
  sachmuon b[100];
  public: 
    void nhapbp(dmsach d){
      tongsoluong=0;
      cout<<"\nso phieu:"; cin>>sophieu;
      cout<<"\ntong so sach muon:"; cin>>tssachmuon;
      for (int i = 0; i < tssachmuon; i++){
        b[i].nhapbp(d); 
        tongsoluong+=b[i].soluong;
      }
    }
    void xemmh(){
      cout<<"\nso phieu muon:"<<sophieu;
      cout<<"\nTong so luong:"<<tongsoluong;
      for (int i = 0; i < tssachmuon; i++)
        b[i].xemmh();
    }
    void ghitep(){
   	  fstream fg("phieumuon.dat",ios::out|ios::binary|ios::app);
      fg.write(reinterpret_cast <char *> (this),sizeof(phieumuon));
      fg.close();
    }
};
void doctep(phieumuon e[], int &tong){
  fstream fd("phieumuon.dat",ios::in|ios::binary);
  phieumuon x; tong=0;
  while(1){
    fd.read(reinterpret_cast <char *> (&x),sizeof(phieumuon));
    if(!fd) break;
    tong++;
    e[tong-1]=x;
  }
  fd.close();
}
int main(){
  dmsach d; d.nhapbp(); d.xemmh();
  // sach x1 = d.xemten(3); x1.xemmh();
  // sachmuon x2; x2.nhapbp(d); x2.xemmh();
  phieumuon e; e.nhapbp(d); e.xemmh();
  e.ghitep(); 
  phieumuon f[100]; 
  int tong;
  doctep(f,tong);
  for (int i = 0; i < tong; i++)
    f[i].xemmh();
  cout<<endl;
  system("pause");
}