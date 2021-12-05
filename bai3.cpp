#include<iostream>
#include<string.h>
#include<fstream>
using namespace std;

class sinhvien {
  private:
    long maso; char hoten[255];
  public:
    friend class lop;
    friend class bangdiem;
    void nhapbp(){
      cout<<"\nma so:"; cin>>maso;
      fflush(stdin);
      cout<<"\nho ten:"; cin.getline(hoten,255);
    }
    void xemmh(){
      cout<<"\n"<<maso<<"-"<<hoten;
    }
};
class lop {
  private:
    sinhvien a[100]; int tssinhvien;
  public:
    friend class bangdiem;
    void nhapbp(){
      cout<<"\ntong so sinh vien:"; cin>>tssinhvien;
      for(int i=0;i<tssinhvien;i++) a[i].nhapbp();
    }
    void xemmh(){
      cout<<"\ndanh sach sinh vien";
      for(int i=0;i<tssinhvien;i++) a[i].xemmh();
    }
    void sapxeptang(){
      for (int i = 0; i < tssinhvien-1; i++)
        for (int j = i+1; j < tssinhvien; j++)
          if(a[i].maso>a[j].maso) swap(a[i],a[j]);
    }
};
class diemsinhvien:sinhvien{
  private:
    int diemthi; char ketqua[100];
  public:
    friend class bangdiem;
    void nhapbp(){
      sinhvien::xemmh();
      cout<<"-diem thi:"; cin>>diemthi;
    }
    void xemmh(){
      if(diemthi>5) strcpy(ketqua,"Qua");
      else strcpy(ketqua,"Thi lai");
      sinhvien::xemmh();
      cout<<"-"<<diemthi<<"-"<<ketqua;
    }
};
class bangdiem{
  private:
    char monhoc[100];  int tsqua, tsthilai, tssinhvien; diemsinhvien b[100];
  public:
    bangdiem(){}
    bangdiem(lop l){
      tssinhvien = l.tssinhvien;
      for(int i=0;i<tssinhvien;i++){
        b[i].maso = l.a[i].maso;
        strcpy(b[i].hoten,l.a[i].hoten);
      }
    }
    void nhapbp(){
      fflush(stdin);
      cout<<"\nmon hoc:"; cin.getline(monhoc,100);
      for(int i=0;i<tssinhvien;i++)
        b[i].nhapbp();
    }
    void xemmh(){
      tsthilai=0, tsqua=0;
      for(int i=0;i<tssinhvien;i++)
        if(b[i].diemthi>5) tsthilai++;
        else tsqua++;
      cout<<"\nmon hoc:"<<monhoc; 
      cout<<"\ntong so sinh vien:"<<tssinhvien;
      cout<<"\ntong so sinh vien qua:"<<tsqua; 
      cout<<"\ntong so sinh vien thi lai:"<<tsthilai; 
      for(int i=0;i<tssinhvien;i++)b[i].xemmh();
    }
    void ghitep(){
   	  fstream fg("bangdiem.dat",ios::out|ios::binary|ios::app);
      fg.write(reinterpret_cast <char *> (this),sizeof(bangdiem));
      fg.close();
    }
};
void doctep(bangdiem d[],long &tong){
	fstream fd("bangdiem.dat",ios::in|ios::binary);
	bangdiem x;tong=0;
	while (1){
    fd.read(reinterpret_cast <char *> (&x),sizeof(bangdiem));
			if (!fd) break;
			++tong;
      d[tong-1]=x;	
		}
		fd.close();
}
main(){
  lop l; l.nhapbp();
  l.sapxeptang(); l.xemmh();
  bangdiem b(l); b.nhapbp(); b.xemmh();
  cout<<"\ndoc ghi tep";
  b.ghitep(); 
  // bangdiem d[100]; 
  // long tong;
  // doctep(d,tong);
  // for (int i = 0; i < tong; i++)
  //   d[i].xemmh();
  cout<<endl;
  system("pause");
}