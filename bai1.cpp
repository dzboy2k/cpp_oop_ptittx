#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class canbo
{
  protected:
    char hoten[30]; long luongcoban;
  public:
    friend class bangluong;
    friend class danhsach;
    void nhapbp(){
      cout<<"ten: "; cin>>hoten;
      cout<<"luong co ban: "; cin>>luongcoban;
    }
    void xemmh(){ cout<<"\n"<<hoten<<" "<<luongcoban; }
};
class danhsach {
  canbo a[100]; long tscanbo;
  public:
    friend class bangluong;
    void nhapbp(){
      cout<<"Tong so cb:"; cin>>tscanbo;
      for (int i = 0; i < tscanbo; i++) a[i].nhapbp();
    }
    void xemmh(){
      cout<<"danh sach can bo:";
      for (int i = 0; i < tscanbo; i++) a[i].xemmh();
    }
    void sapxepgiam(){
      for (int i = 0; i < tscanbo-1; i++)
        for (int j = i+1; j < tscanbo; j++)
          if(a[i].luongcoban < a[j].luongcoban) swap(a[i], a[j]);
    }
};
class luongcb : public canbo {
  long ngaycong, luong;
  public:
    friend class bangluong;
    void nhapbp(){
      canbo::xemmh(); 
      cout<<" - ngay cong:"; cin>>ngaycong;
      luong=luongcoban+ngaycong*50000;
    }
    void xemmh(){
      canbo::xemmh();
      cout<<" "<<ngaycong<<" "<<luong;
    }
};
class bangluong {
  long thang, tongluong, tscanbo;
  luongcb b[100];
  public:
    bangluong(){};
    bangluong(danhsach d){
      tscanbo = d.tscanbo;
      for (int i = 0; i < tscanbo; i++)
      {
        strcpy(b[i].hoten, d.a[i].hoten);
        b[i].luongcoban = d.a[i].luongcoban; 
      }
    };
    void nhapbp(){
      cout<<"\nnhap thang:"; cin>>thang;
      for(int i=0;i<tscanbo;i++){
        b[i].nhapbp();
        tongluong+=b[i].luong;
      }
    }
    void xemmh(){
      cout<<"\nBang luong thang "<<thang<<endl;
      cout<<"Tong luong "<<tongluong;
      for (int i = 0; i < tscanbo; i++) b[i].xemmh();
    }
    void ghitep(){
   	  fstream fg("bangluong.dat",ios::out|ios::binary|ios::app);
      fg.write(reinterpret_cast <char *> (this),sizeof(bangluong));
      fg.close();
    }
};
void doctep(bangluong e[],long &tong){
	fstream fd("bangluong.dat",ios::in|ios::binary);
	bangluong x;tong=0;
	while (1){
    fd.read(reinterpret_cast <char *> (&x),sizeof(bangluong));
			if (!fd) break;
			++tong;
      e[tong-1]=x;	
		}
		fd.close();
}
main(){
  danhsach d; d.nhapbp(); 
  d.sapxepgiam(); d.xemmh();
  bangluong e(d);
  e.nhapbp(); e.xemmh();
  cout<<endl;
  e.ghitep();
  bangluong m[100];long tong;
  cout<<"\n==Sau khi doc tep=="<<endl;
  doctep(m,tong);
  for(int i=0;i<tong;i++)
    m[i].xemmh();
  cout<<endl;
  system("pause");
}
