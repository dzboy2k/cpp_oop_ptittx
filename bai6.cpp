#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class hang {
  protected:
    string tenhang; long dongia;
  public:
    friend class hangnhap;
    friend class banggia;
    friend int main();
    void nhapbp() {
      cin.ignore();
      cout<<"\nten hang:"; getline(cin, tenhang);
      cout<<"\ndon gia:"; cin>>dongia; 
    }
    void xemmh()  {
      cout<<"\n"<<tenhang<<"---"<<dongia;
    }
};
class banggia {
  private: 
    hang a[100]; int tshang;
  public:
    void nhapbp(){
      cout<<"\ntong so hang:"; cin>>tshang; 
      for (int i = 0; i < tshang; i++) a[i].nhapbp();
    }
    void xemmh(){ 
      for (int i = 0; i < tshang; i++) a[i].xemmh();
    }
    hang xemgia(string tenhang){
      for (int i = 0; i < tshang; i++)
        if(tenhang.compare(a[i].tenhang)==0) return a[i];
    }
};
class hangnhap:hang{
  private:
    long soluongnhap, thanhtien;
  public: 
    friend class phieunhap;
    void nhapbp(banggia g){
      cin.ignore();
      cout<<"\nten hang:"; cin>>tenhang;
      hang g1 = g.xemgia(tenhang); 
      dongia = g1.dongia;
      cout<<"so luong nhap:"; cin>>soluongnhap;
      thanhtien=soluongnhap*dongia;
    }
    void xemmh(){
      hang::xemmh();
      cout<<"---"<<soluongnhap<<"---"<<thanhtien;
    }
};
class phieunhap{
  private:
    long sophieu, tongtien, tshangnhap; hangnhap b[100];
  public:
    void nhapbp(banggia g){
      tongtien=0;
      cout<<"\nso phieu:"; cin>>sophieu;
      cout<<"\ntong so hang nhap:"; cin>>tshangnhap;
      for (int i = 0; i < tshangnhap; i++){
        b[i].nhapbp(g);
        tongtien+=b[i].thanhtien;
      }
    }
    void xemmh(){
      cout<<"\nso phieu:"<<sophieu;
      cout<<"\ntong tien:"<<tongtien;
      cout<<"\ntong so hang nhap:"<<tshangnhap;
      for (int i = 0; i < tshangnhap; i++)
        b[i].xemmh();
    }
    void ghitep(){
   	  fstream fg("phieunhap.dat",ios::out|ios::binary|ios::app);
      fg.write(reinterpret_cast <char *> (this),sizeof(phieunhap));
      fg.close();
    }
};
void doctep(phieunhap e[], int &tong){
  fstream fd("phieunhap.dat",ios::in|ios::binary);
  phieunhap x; tong=0;
  while(1){
    fd.read(reinterpret_cast <char *> (&x),sizeof(phieunhap));
    if(!fd) break;
    tong++;
    e[tong-1]=x;
  }
  fd.close();
}
main(){
  banggia b; b.nhapbp(); b.xemmh(); 
  // cin.ignore();
  // string tenhang1; cout<<"\nten hang:"; cin>>tenhang1;
  // hang h = b.xemgia(tenhang1); cout<<"\ngia:"<<h.dongia;
  phieunhap h; h.nhapbp(b); h.xemmh();
  cout<<"\ndoc ghi tep";
  h.ghitep(); 
  phieunhap f[100]; 
  int tong;
  doctep(f,tong);
  for (int i = 0; i < tong; i++)
    f[i].xemmh();
  cout<<endl;
  system("pause");
}