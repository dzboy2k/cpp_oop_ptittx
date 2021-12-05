#include<iostream>
#include<string>
#include<fstream>
using namespace std;

class hang {
  protected:
    string tenhang; long dongia;
  public:
    friend class hangban;
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
class hangban:hang{
  private:
    long soluong, thanhtien;
  public: 
    friend class hoadon;
    void nhapbp(banggia g){
      cin.ignore();
      cout<<"\nten hang:"; cin>>tenhang;
      hang g1 = g.xemgia(tenhang); 
      dongia = g1.dongia;
      cout<<"so luong:"; cin>>soluong;
      thanhtien=soluong*dongia;
    }
    void xemmh(){
      hang::xemmh();
      cout<<"---"<<soluong<<"---"<<thanhtien;
    }
};
class hoadon{
  private:
    long sohoadon, tongtien, tshangban; hangban b[100];
  public:
    void nhapbp(banggia g){
      tongtien=0;
      cout<<"\nso hoa don:"; cin>>sohoadon;
      cout<<"\ntong so hang ban:"; cin>>tshangban;
      for (int i = 0; i < tshangban; i++){
        b[i].nhapbp(g);
        tongtien+=b[i].thanhtien;
      }
    }
    void xemmh(){
      cout<<"\nso hoa don:"<<sohoadon;
      cout<<"\ntong tien:"<<tongtien;
      cout<<"\ntong so hang ban:"<<tshangban;
      for (int i = 0; i < tshangban; i++)
        b[i].xemmh();
    }
    void ghitep(){
   	  fstream fg("hoadon.dat",ios::out|ios::binary|ios::app);
      fg.write(reinterpret_cast <char *> (this),sizeof(hoadon));
      fg.close();
    }
};
void doctep(hoadon e[], int &tong){
  fstream fd("hoadon.dat",ios::in|ios::binary);
  hoadon x; tong=0;
  while(1){
    fd.read(reinterpret_cast <char *> (&x),sizeof(hoadon));
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
  hoadon h; h.nhapbp(b); h.xemmh();
  cout<<"\ndoc ghi tep";
  h.ghitep(); 
  hoadon f[100]; 
  int tong;
  doctep(f,tong);
  for (int i = 0; i < tong; i++)
    f[i].xemmh();
  cout<<endl;
  system("pause");
}