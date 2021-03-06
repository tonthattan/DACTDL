#include "pch.h"
#include <iostream>
#include<stdio.h>
#include "math.h"
#include "conio.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include<fstream>
#include <string.h>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <string>
#pragma warning (disable 4996)
#define output "sach.OUT"
#define MAX 200
#define X 20
#define y 13
#include<vector>
using namespace std;

struct thongtin {
	char tensach[50];   // tên sách
	char tennxb[100];   //tên nhà xuất bản
	char tentacgia[50]; //tên tác giả
	int masach;         //mã sách
	int vitri;          //vị trí để sách
	int manxb;			//mã nhà xuất bản
	float giatien;      //giá tiền
	int namxb;			//năm xuất bản
	char theloai[50];	//thể loại
	int soluong;		//số lượng sách
	
};
struct quyensach
{
	thongtin dl;
	struct quyensach *next;
	
};
struct list
{
	quyensach *head;
	quyensach *tail;
};
struct docgia
{
	char tendocgia[50];		//tên độc giả
	int madocgia;			//mã độc giả
	char diachidg[50];		//địa chỉ
	int sdtdg;				//số điện thoại độc giả
	
};
struct quanly
{
	char ten[50];			//tên quản lý
	int maso;				//mã quản lý
	char diachi[50];		//địa chỉ quản lý
	int sdt;				//số điện thoại quản lý
};
//quanly ql;
//docgia b;
//thongtin x;
//quyensach *sach;
//list l;

//khai báo hàm
list l;
int n,N;
void AddHead(list &l, quyensach *p);
void AddTail(list &l, quyensach *p);
void CreateList(list &l);
quyensach *GetNode(thongtin a);
void GiaiPhong(list &l);
void XoaDau(list &l);
void xoacuoi(list &l);
void nhapql(quanly &a);
void nhapcacql(quanly a[MAX], int &n);
void nhapdocgia(docgia &a);
void nhapcacdg(docgia a[], int &n);
void nhapsach(thongtin &a);
void nhap(list &l, int n);
void them(list&l,int&n);
void xuattql();
void xuatql(quanly a);
void xuatcacql(quanly a[], int n);
void xuatttdg();
void xuatdg(docgia a);
void xuatcacdg(docgia a[], int n);
void inthongtinsach();
void insach(thongtin a);
void xuatlist(list l);
void chitietsach();
void chitietsach1(thongtin a);
void xuatchitietsach(list l);
void congviec();
void menuamuonsach();
void menuquanli();
void ms();
void muonsach(list &l, int x);
void trasach(list &l, int x);
int xoatheoten(list &L);
int xoatheomasach(list &L);
void xoatheogiatien(list &l);
void timtheomasach(list &l);
void timtheogiatien(list l);
void timtheomanxb(list l);
void timtheotensach(list l);
void Lietkevt(list l);
void lietketennxb(list l);
void Lietkenxb(list l);
void sachkocon(list l);
void SapXep(list &l, char phanloai);
void sapxepabc(list l);
int TinhTong(list l);
int Tinh(list l);
bool doctt(const char* filename, list &l);
void fix(char chuoi[]);
void ghi1(ofstream &fileout, thongtin sv);
void ghi(list l);
void timtheotheloaisach(list l);
void timtheotentacgia(list l);

//HÀM CƠ BẢN

/////////////////////////////////////////////////
//Thêm đầu
void AddHead(list &l, quyensach *p)
{
	// danh sách rỗng.
	if (l.head == NULL)
	{
		l.head = l.tail = p; // p vừa là đầu vừa là cuối.
	}
	else
	{
		p->next = l.head; // Cho p trỏ tới đầu danh sách
		l.head = p; // Cập nhật lại đầu danh sách
	}
}
//Thêm cuối
void AddTail(list &l, quyensach *p)
{
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else
	{
		l.tail->next = p;
		l.tail = p;
	}
}
//Tạo list
void CreateList(list &l)
{
	l.head = l.tail = NULL;
}
//Tạo node
quyensach *GetNode(thongtin a)
{
	quyensach *p = new quyensach;
	if (p == NULL)
	{
		return NULL;
	}
	p->dl = a;
	p->next = NULL;
	return p;
}
//Giải phóng bộ nhớ
void GiaiPhong(list &l)
{
	quyensach *p;
	while (l.head != NULL)
	{
		p = l.head; // Cho con trỏ p trỏ vào pHead
		l.head = l.head->next; // pHead được trỏ sang Node bên cạnh
		delete p; // giải phóng con trỏ
	}

}
//Xóa đầu
void XoaDau(list &l)
{
	if (l.head != NULL)
	{
		quyensach *p = l.head;
		l.head = l.head->next;
		delete p;
	}
}
//xóa cuối
void xoacuoi(list &l)
{
	quyensach *p = l.head; //khai báo con trỏ gán với node đầu của danh sách
	quyensach *q = l.tail; //khai báo con trỏ gán với node cuối của danh sách
	if (p == q) //Nếu danh sách chỉ có một node
	{
		l.head = l.tail = NULL;
		delete p;
	}
	else //Nếu không p chạy tới node cận cuối cùng
	{
		while (p->next != q) p = p->next;
		p->next = NULL; //p trỏ đến NULL
		l.tail = p; //Node cận cuối p trở thành node cuối
		delete q; //Xóa node cuối ban đầu
	}

}
//////////////////////////////////////////////////



//HÀM NHẬP
//>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<
//nhập thông tin của người quản lí
void nhapql(quanly &a)
{
	cin.ignore();
	cout << "Nhap ten nguoi quan ly: ";
	cin.getline(a.ten, 20);
	cout << "Nhap ma so nguoi quan ly: ";
	cin >> a.maso;
	cout << "Nhap so dien thoai: ";
	cin >> a.sdt;
	cout << "Nhap dia chi: ";
	cin.ignore();
	cin.getline(a.diachi, 100);
	cout << endl;
}
void nhapcacql(quanly a[MAX], int &n) 
{
	for (int i = 0; i < n; i++) 
	{
		cout << "nhap thong tin cua quan ly thu: " << i + 1 << endl;
		nhapql(a[i]);
	}
}
//nhập thông tin người mượn sách
void nhapdocgia(docgia &a)
{
	cin.ignore();
	cout << "Nhap ten nguoi muon : ";
	cin.getline(a.tendocgia, 9);
	cout << "Nhap ma so nguoi muon: ";
	cin >> a.madocgia;
	cout << "Nhap dia chi :";
	cin.ignore();
	cin.getline(a.diachidg, 100);
	cout << "Nhap so dien thoai:";
	cin >> a.sdtdg;

}
void nhapdocgia1(docgia &a)
{
	
	cout << "Nhap ma so nguoi tra: "; //Nhập mã độc giả
	cin >> a.madocgia;
	

}

void nhapcacdg(docgia a[], int &n)
{

	for (int i = 0; i < n; i++)
	{
		cout << "nhap thong tin cua doc gia thu: " << i + 1 << endl;
		nhapdocgia(a[i]);

	}

}
//nhập thông tin sách
void nhapsach(thongtin &a)
{
	CreateList(l);
	//congviec();
	doctt("sach.txt", l);
	cin.ignore();
	cout << "Nhap ten sach : ";
	cin.getline(a.tensach, 9);
	cout << endl;	
	
	cout << "nhap ma sach ";
	cin >> a.masach;


	cout << "Nhap nam xuat ban:";
	cin >> a.namxb;
	cout << "Nhap ten nxb: ";
	cin.ignore();
	cin.getline(a.tennxb, 100);
	cout << "Nhap ma nha xuat ban:";
	cin >> a.manxb;
	cout << "Nhap ten tac gia cua sach: ";
	cin.ignore();
	cin.getline(a.tentacgia, 50);
	cout << "Nhap vi tri cua sach:";
	cin >> a.vitri;
	cout << "Nhap gia tien cua sach: ";
	cin >> a.giatien;
	cout << "Nhap so cuon sach: ";
	cin >> a.soluong;
	cout << "Nhap the loai: ";
	cin.ignore();
	cin.getline(a.theloai, 50);
	cout << endl;
}
void nhap(list &l, int n)
{
	thongtin x[100];
	quyensach *p;
	for (int i = 1; i <= n; i++)
	{
		cout << "Nhap dau sach thu " << i << " :" << endl;
		nhapsach(x[i]);
		p = GetNode(x[i]);
		AddTail(l, p);
	}
}
//thêm sách
void them(list&l,int &n)
{
	
	thongtin x[100];
	quyensach *p;
	for (int i = 1; i <= n; i++)
	{
		cout << "Nhap sach thu " << i << " :" << endl;
		nhapsach(x[i]);
		p = GetNode(x[i]);
		AddTail(l, p);
	}
}
//>>>>>>>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<<<<<<<<<<<<



//HÀM XUẤT
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
//xuất các quản lý
void xuattql()
{
	cout << "thong tin nhan vien " << endl;
	cout << "======================================\n";
	cout << "ho va ten";
	
	cout << "-------ma so";
	
	cout << "-----------so dien thoai";
	
	cout << "---------dia chi";
	

}
void xuatql(quanly a) 
{
	
	cout.width(X);
	cout << left << a.ten;
	cout.width(18);
	cout << left << a.maso;
	cout.width(16);
	cout << left << a.sdt;
	cout.width(15);
	cout << left << a.diachi;
	cout.width(X);
	
}
void xuatcacql(quanly a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		xuatql(a[i]);
	}
}
//xuất độc giả
void xuatttdg() 
{
	cout << "thong tin doc gia " << endl;
	cout << "======================================\n";
	cout << "ho va ten";
	
	cout << "----------ma so";

	cout << "--------so dien thoai";
	
	cout << "--------dia chi";
	
}
void xuatdg(docgia a) 
{
	cout.width(X);
	cout << left << a.tendocgia;
	cout.width(18);
	cout << left << a.madocgia;
	cout.width(16);
	cout << left << a.sdtdg;
	cout.width(15);
	cout << left << a.diachidg;
	cout.width(X);

	cout << endl;
	
}
void xuatcacdg(docgia a[], int n) 
{
	for (int i = 0; i < n; i++)
	{
		cout << endl;
		xuatdg(a[i]);
	}
}
//in thông tin của sách
void inthongtinsach()
{
	int i = 10;
	cout << "thong tin sach " << endl;
	cout << "======================================" << endl;
	cout << "Ten sach";
	
	cout << "----Ma sach";
	cout << "------Vi tri";
	cout << "-------The loai";
	cout << "----------So luong";
	cout << "-------------Gia tien";


}
void insach(thongtin a)
{


	cout.width(y);
	cout << left << a.tensach;
	cout.width(y);
	cout << left << a.masach;
	cout.width(y);
	cout << left << a.vitri;
	cout.width(23);
	cout << left << a.theloai;
	cout.width(18);
	cout << left << a.soluong;
	cout.width(5);
	cout << left << a.giatien;

	cout << endl;
	cout.width(10);
}
void xuatlist(list l)
{
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		insach(p->dl);
	}
}
//in chi tiết
void chitietsach()
{
	cout << "thong tin chi tiet " << endl;
	cout << "======================================\n";
	cout << "Ten sach";	
	cout << "----Ma sach";
	cout << "-------Ten tac gia";
	cout << "-------Ten nxb";
	cout << "----------Ma nha xuat ban";
	cout << "------------Nam xuat ban ";
}
void chitietsach1(thongtin a)
{
	cout.width(13);
	cout << left << a.tensach;
	cout.width(14);
	cout << left << a.masach;
	cout.width(18);
	cout << left << a.tentacgia;
	cout.width(15);
	cout << left << a.tennxb;
	cout.width(15);
	cout << right << a.manxb;
	cout.width(25);
	cout << right << a.namxb;
	cout.width(y);
	cout << endl;
}
void xuatchitietsach(list l)
{
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		chitietsach1(p->dl);
	}
}
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



//MENU 
//************************************************
//menu công việc
void congviec()
{
	cout << "\n";
	cout << "\n";
	

	int n, m;
	cout << "1:Quan ly" << endl;	//1.Quản lý
	cout << "2:Doc gia" << endl;	//2.Độc giả
	do {
		cout << "Ban chon thao tac nao? " ;
		cin >> n;
		switch (n)
		{
		case 1:
		{
			system("cls");
			menuquanli();
			break;
		}
		case 2:
		{
			system("cls");
			menuamuonsach();
			break;
		}
		default:
			cout << "Gia tri khong hop le hay nhap lai." << endl;
			break;
		}
		cout << "*****Nhan ESC de thoat.*****\n";
		cout << "-----nhan ENTER de tiep tuc chon lai.-----\n";
		cout << "1:Quan ly" << endl;
		cout << "2:Doc gia" << endl;
	} while (_getch() != 27);
}
//menu người mượn sách
void menuamuonsach()
{
	
	
	int n, m;
	list l;
	CreateList(l);
	doctt("sach.txt", l);
	
	
	do {
		cout << "*_-CONG VIEC CUA NGUOI MUON SACH-_*\n";	//Công việc của người mượn sách
		cout << "0:Kiem tra sach trong kho\n";				//Kiểm tra những cuốn đã cho mượn
		cout << "1:In thong tin cac cuon sach\n";			//In thông tin các cuốn sách
		cout << "2:Tim sach theo ten\n";					//Tìm sách bằng tên sách
		cout << "3:Tim sach theo ma sach\n";				//Tìm sách bằng mã sách
		cout << "4:Liet ke theo ten NXB\n";					//Tìm tên nhà xuất bản
		cout << "5:Liet ke sach theo nam xuat ban\n";		//Tìm sách theo năm xuất bản
		cout << "6:Liet ke sach theo vi tri\n";				//Tìm sách theo vị trí
		cout << "7:Muon sach\n";							//Mượn sách
		cout << "8:Tra sach\n";								//Trả sách
		cout << "9:Tim theo the loai sach\n";				//Tìm thể loại sách
		cout << "10:Tim theo ten tac gia\n";				//Tìm tên tác giả
		cout << "ban chon thao tac nao: ";
		cin >> n;
		switch (n)
		{
		case 0:
		{
			sachkocon(l);

			break;
		}
		case 1:
		{
			inthongtinsach();
			cout << endl;
			xuatlist(l);
			cout << ">>>>>>>>>>>>>>><<<<<<<<<<<<<<<<\n";
			chitietsach();
			cout << endl;
			xuatchitietsach(l);
			break;
		}
		case 2:
		{

			timtheotensach(l);
			break;
		}
		case 3:
		{
			timtheomasach(l);

			break;
		}
		case 4:
		{
			lietketennxb(l);

			break;
		}
		case 5:
		{
			Lietkenxb(l);

			break;
		}
		case 6:
		{
			Lietkevt(l);

			break;
		}
		case 7:
		{


			cout << "nhap so nguoi muon sach: ";
			cin >> m;
			muonsach(l, m);
			cout << endl;

			break;
		}
		case 8:
		{
			int k;
			cout << "nhap so nguoi tra sach: ";
			cin >> k;
		
			trasach(l,k);
			cout << endl;
			

			break;
		}
		case 9:
		{
			timtheotheloaisach(l);


			break;
		}
		case 10:
		{
			timtheotentacgia(l);


			break;
		}

		default:
			cout << "Gia tri khong hop le" << endl;
			break;
		}
		cout << endl;
		cout << "*****Nhan ESC de thoat.*****\n";
		cout << "-----nhan ENTER de tiep tuc chon lai.-----\n";

	} while (_getch() != 27);
}

//menu nhân viên
void menuquanli()
{

	int n, m;
	quanly a[100];
	int s;
	cout << "nhap so nhan vien: ";
	cin >> s;
	nhapcacql(a, s);
	xuattql();
	xuatcacql(a, s);
	cout << endl;
	list l;
	CreateList(l);
	doctt("sach.txt", l);
	
	
	do {
		cout << "*_-CONG VIEC CUA NGUOI NHAN VIEN-_*\n";	//Công việc của nhân viên quản lý
		cout << "0:In thong tin sach\n";					//In thông tin các cuốn sách
		cout << "1:Them sach vao thu vien\n";				//Thêm sách vào
		cout << "2:Xoa di cuon sach\n";						//Xóa đi cuốn sách bằng mã sách
		cout << "3:Tim thong tin cuon sach\n";				//Tìm sách bằng mã sách	
		cout << "4:Sap xep sach theo abc\n";				//Sắp xếp theo bảng chữ cái
		cout << "5:Liet ke sach theo nam xuat ban\n";		//Tìm theo năm xuất bản
		cout << "6:Liet ke sach theo vi tri\n";				//Tìm theo vị trí để sách
		cout << "7:Dem so cuon sach \n";					//Đếm số lượng sách trong thư viện
		cout << "8:Xoa sach theo ten \n";					//Xóa đi cuốn sách bằng tên sách 
		cout << "9:Tim thong tin bang ten\n";				//Tìm sách bằng tên sách	
		cout << "\nBan chon thao tac nao: ";
		cin >> n;
		switch (n)
		{
		case 0:
		{
			inthongtinsach();
			cout << endl;
			xuatlist(l);
			cout << ">>>>>>>>>>>>>>><<<<<<<<<<<<<<<<\n";
			chitietsach();
			cout << endl;
			xuatchitietsach(l);
			break;
			
		}
		case 1:
		{
			int k;
			k = Tinh(l);
			cout << " so luong hien tai la: "<<k<<endl;
			
			ghi(l);
			inthongtinsach();
			cout << endl;
			xuatlist(l);
			//cout << "Sach trong thu vien: " << endl;
			//xuatlist(l);
			break;
		}
		case 2:
		{
			xoatheomasach(l);
			cout << "So sach con lai trong thu vien la:" << endl;
			inthongtinsach();
			cout << endl;
			xuatlist(l);
		
			break;

		}
		case 3:
		{
			timtheomasach(l);
			break;
		}
		case 4:
		{
			cout << "Danh sach sau khi sap xep  la: ";
			sapxepabc(l);
			cout << endl;
			inthongtinsach();
			cout << endl;
			xuatlist(l);
			break;
		}
		case 5:
		{
			Lietkenxb(l);
			break;
		}
		case 6:
		{
			Lietkevt(l);
			break;
		}
		case 7:
		{
			int h = Tinh(l);
			cout << "So cuon sach trong thu vien: " << h << endl;
			break;
		}
		case 8:
		{
			xoatheoten(l);
			inthongtinsach();
			cout << endl;
			xuatlist(l);
			break;
		}
		case 9: 
		{
			timtheotensach(l);
			break;
		}

		default:
			cout << "Gia tri khong hop le" << endl;
			break;
		}
		
		cout << "*****Nhan ESC de thoat.*****\n";
		cout << "-----nhan ENTER de tiep tuc chon lai.-----\n";

	} while (_getch() != 27);
	
}
//************************************************



//HÀM ĐỌC FILE
//################################################
void fix(char chuoi[])
{
	int len = strlen(chuoi) - 1;
	if (chuoi[len] == '\n')
	{
		chuoi[len] = '\0';
	}

}
bool doctt(const char* filename, list &l)
{
	errno_t f;
	FILE *fp;
	f = fopen_s(&fp, filename, "rt");
	thongtin sv;
	if (!fp)
	{
		return false;
	}
	else
	{

		quyensach *P;
		P = l.head;
		fscanf_s(fp, "%d\n", &N);
		for (int i = 0; i < N; i++)


		{
			fgets(sv.tensach, 20, fp);
			fix(sv.tensach);
			fgets(sv.tennxb, 20, fp);
			fix(sv.tennxb);
			fgets(sv.tentacgia, 20, fp);
			fix(sv.tentacgia);
			fgets(sv.theloai, 20, fp);
			fix(sv.theloai);
			fscanf_s(fp, "%d %d %d %d %f %d\n", &sv.masach, &sv.namxb, &sv.manxb, &sv.vitri, &sv.giatien, &sv.soluong);
			fscanf_s(fp, "++++++++++\n");
			P = GetNode(sv);
			AddTail(l, P);

			P = P->next;

		}

		fclose(fp);
	}

	return true;
}
//HÀM GHI FILE
void ghi1(ofstream &fileout, thongtin s)
{
	fileout << s.tensach << "\n";
	fileout << s.tennxb << "\n";
	fileout << s.tentacgia << "\n";
	fileout << s.theloai << "\n";
	fileout << s.masach << " " << s.namxb << " " << s.manxb << " " << s.vitri << " " << s.giatien << " " << s.soluong << "\n";
}
void ghi(list l)
{
	ofstream fileout;
	fileout.open("sach.TXT", ios::out);

	cout << "ban can them bao nhieu cuon sach: ";
	cin >> n;
	them(l, n);

	cout << "nhap so luong sach hien tai:";
	cin >> N;
	fileout << n + N << "\n";
	for (quyensach *k = l.head; k != NULL; k = k->next)
	{
		ghi1(fileout, k->dl);
		fileout << endl;
	}
	fileout.close();
}
//################################################



//HÀM MƯỢN VÀ TRẢ SÁCH
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//mượn sách
void ms()
{
	cout << "nhung cuon sach cho muon la: " << endl;
	cout << "======================================\n";

	
	cout << "Ten sach";

	cout << "----Ma sach";
	cout << "------so luong con lai";
	
	cout << endl;
}
void muonsach(list &l, int x)
{
	for (int j = 0; j < x; j++)
	{
		docgia d[100];
		cout << "Nhap thong tin cua doc gia thu: " << j + 1 << endl;
		cout << endl;
		nhapdocgia(d[j]);
		int n, a[50];
		cout << "nhap so cuon can muon: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "nhap ma sach thu:" << i + 1 << ": ";
			cin >> a[i];
		}
		cout << endl;
		cout << endl;
		cout << "sach cua doc gia thu: " << j + 1 << endl;
		ms();
		
		for (quyensach *p = l.head; p != NULL; p = p->next)
		{
			for (int i = 0; i < n; i++)
			{
				
				if (p->dl.masach == a[i])
				{
					p->dl.soluong--;
					
					cout.width(y);
					cout << left << p->dl.tensach;
					cout.width(y);
					cout << left << p->dl.masach;
					cout.width(y);
					cout << left << p->dl.soluong;
					cout << endl;
					cout.width(10);
				}
			}
		}
	}
}
//trả sách
void trasach(list &l,int x)
{
	for (int j = 0; j < x; j++)
	{
		docgia d[100];
		cout << "Nhap thong tin cua doc gia\n";
		nhapdocgia1(d[j]);
		int n, a[50];
		cout << "nhap so cuon can tra: ";
		cin >> n;
		for (int i = 0; i < n; i++)
		{
			cout << "nhap ma sach thu:" << i + 1 << ": ";
			cin >> a[i];
		}
		cout << "nhung cuon sach tra la: " << endl;
		cout << "======================================\n";


		cout << "Ten sach";

		cout << "----Ma sach";
		cout << "------so luong trong kho";

		cout << endl;
		for (quyensach *p = l.head; p != NULL; p = p->next)
		{
			for (int i = 0; i < n; i++)
			{
				if (p->dl.masach == a[i])
				{
					p->dl.soluong++;
					cout.width(y);
					cout << left << p->dl.tensach;
					cout.width(y);
					cout << left << p->dl.masach;
					cout.width(y);
					cout << left << p->dl.soluong;
					cout << endl;
					cout.width(10);
					
				}
			}
		}
	}
}
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%



//CÁC HÀM MỞ RỘNG

/////////////////HÀM XÓA\\\\\\\\\\\\\\\\\\\\\
//Hàm xóa theo tên
int xoatheoten(list &L){
	char id[60];
	quyensach *p, *q = NULL;
	p = L.head;
	cout << "nhap ten sach can xoa: ";
	cin.ignore();
	cin.getline(id, 25);
	cout << endl;
	while (p != NULL) {
		if (strcmp(p->dl.tensach, id) == 0) break;
		q = p;
		p = p->next;
	}
	if (p == NULL) {
		cout << "ko co sach do trong thu vien" << endl;
		return 0;}
	if (q != NULL) {
		if (p->next != NULL) {
			q->next = p->next;
			delete p;}
		else {
			q->next = p->next;
			delete p;
			L.tail = q;}
	}else {
		L.head = p->next;
		if (L.head == NULL) L.tail = NULL;
	}
	return 1;
}
//xóa theo mã sách
int xoatheomasach(list &L){
	int id;
	quyensach *p, *q = NULL;
	p = L.head;
	cout << "nhap ma sach can xoa: "; cin >> id;
	cout << endl;
	while (p != NULL) {
		if (p->dl.masach == id) break;
		q = p;
		p= p->next;
	}
	if (p == NULL) {
		cout << "ko co sach do trong thu vien" << endl;
		return 0;
	}
	if (q != NULL) {
		if (p->next != NULL) {
			q->next = p->next;
			delete p;
		}
		else {
			q->next = p->next;
			delete p;
			L.tail = q;}
	}else {
		L.head = p->next;
		if (L.head == NULL) L.tail = NULL;
	}
	return 1;
}
//xóa sách nhỏ hơn 1 mức giá nào đó
void xoatheogiatien(list &l)
{
	int gt;
	cout << "nhap gia tien can xoa: ";
	cin >> gt;
	cout << endl;
	quyensach *truoc = l.head; // Node nằm trước
	for (quyensach *p = l.head->next; p != l.tail; p = p->next)
	{
		if (p->dl.giatien <= gt)
		{
			// Xóa p
			// tìm Node nằm trước p và cho nó trỏ tới Node nằm sau p
			quyensach *sau;
			sau = p->next;
			truoc->next = sau;
			delete p;
			p = truoc;

		}
		truoc = p;
	}

	if (l.head->dl.giatien <= gt)
	{
		XoaDau(l);
	}

	if (l.tail->dl.giatien <= gt)
	{
		xoacuoi(l);
	}
}


/////////////////HÀM TÌM KIẾM\\\\\\\\\\\\\\\\\\\\\
//tìm kiếm theo mã sách
void timtheomasach(list &l)
{
	int id;
	quyensach*p;
	
	cout << "Nhap ma sach can tim: ";
	cin >> id;
	cout << endl;
	p =l.head;
	while (p != NULL) {
		if (p->dl.masach == id) {
			cout << "thong tin cua sach la:\n" << endl;
			cout<<"ma sach: "<<p->dl.masach << endl;
			cout << "ten sach la: " << p->dl.tensach << endl;
			cout << "so luong la: " << p->dl.soluong << endl;
			break;
		}
		else
		{
			
			p = p->next;
		}

	}
	if (p == NULL) {
		cout << "ko co sach trong thu vien" << endl;
		
	}

}
//tìm sách theo giá tiền
void timtheogiatien(list l)
{
	int gt;
	cout << "nhap gia tien can tim :";
	cin >> gt;

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (p->dl.giatien == gt)
		{
			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "gia tien: ";
			cout << p->dl.giatien << endl;
		}
	}

}
//tìm theo mã nhà xuất bản
void timtheomanxb(list l)
{
	int manxb;
	cout << "nhap ma nha xuat ban can tim:";
	cin >> manxb;

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (p->dl.manxb == manxb)
		{
			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
		}

	}


}
//tìm theo tên sách
void timtheotensach(list l)
{
	char ten[50];
	cout << "nhap ten sach can tim:";
	cin.ignore();
	cin.getline(ten, 25);
	
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->dl.tensach, ten) == 0)
		{

			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "ma sach: ";
			cout << p->dl.masach << endl;
			cout << "so luong la: " << p->dl.soluong << endl;
		}

	}

}
//tìm theo năm xuất bản
void Lietkenxb(list l)
{
	int nxb;
	cout << "nhap nam xuat ban can liet ke:";
	cin >> nxb;
	
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (p->dl.namxb == nxb)
		{
			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "ma sach: ";
			cout << p->dl.masach << endl;
			
		}
		
	}

}
//tìm theo thể loại sách
void timtheotheloaisach(list l)
{
	char ten[50];
	cout << "nhap the loai can tim:";
	cin.ignore();
	cin.getline(ten, 25);

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->dl.theloai, ten) == 0)
		{

			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "ma sach: ";
			cout << p->dl.masach << endl;
			cout << "so luong la: " << p->dl.soluong << endl;
		}

	}

}
//tìm theo tên nhà xuất bản
void lietketennxb(list l)
{
	char ten[50];
	cout << "nhap ten nha xuat ban can tim:";
	cin.ignore();
	cin.getline(ten, 25);

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->dl.tennxb, ten) == 0)
		{

			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "ma sach: ";
			cout << p->dl.masach << endl;
			cout << "so luong la: " << p->dl.soluong << endl;
		}

	}
}
//tìm theo tên tác giả
void timtheotentacgia(list l)
{
	char ten[50];
	cout << "nhap ten tac gia can tim:";
	cin.ignore();
	cin.getline(ten, 25);

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (strcmp(p->dl.tentacgia, ten) == 0)
		{

			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "ma sach: ";
			cout << p->dl.masach << endl;
			cout << "so luong la: " << p->dl.soluong << endl;
		}

	}

}

//liệt kê theo vị trí để sách
void Lietkevt(list l)
{
	int vtri;
	cout << "nhap vi tri can liet ke:";
	cin >> vtri;

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (p->dl.vitri == vtri)
		{
			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "ma sach: ";
			cout << p->dl.masach << endl;
		}

	}


}
//in những cuốn sách ko còn trong tv
void sachkocon(list l)
{
	int i, bienKT = 0;
	cout << "\n +========THONG TIN SACH CHO MUON HET=========+";
	cout << "\n +============================================+";
	cout << endl;
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{

		if (p->dl.soluong == 0)
		{
			bienKT++;
			cout << "\n # Sach tim thay thu :" << bienKT << endl;
			cout << p->dl.tensach << "  " << p->dl.masach << "  " << p->dl.soluong;

		}
	}
	if (bienKT == 0)
	{
		
		cout << " Tat ca cac sach trong thu vien deu co the cho muon ";
	}

}



/////////////////HÀM SẮP XẾP\\\\\\\\\\\\\\\\\\\\\
//sắp xếp theo giá tiền
void SapXep(list &l, char phanloai)
{

	for (quyensach *p = l.head; p != l.tail; p = p->next)
	{
		for (quyensach *q = p->next; q != NULL; q = q->next)
		{
			if (phanloai == 't')
			{
				if (p->dl.giatien > q->dl.giatien)
				{
					swap(p->dl.tensach, q->dl.tensach);
					swap(p->dl.masach, q->dl.masach);
					swap(p->dl.giatien, q->dl.giatien);
					swap(p->dl.manxb, q->dl.manxb);
					swap(p->dl.tentacgia, q->dl.tentacgia);
					swap(p->dl.namxb, q->dl.namxb);
					swap(p->dl.vitri, q->dl.vitri);
					swap(p->dl.soluong, q->dl.soluong);
					swap(p->dl.theloai, q->dl.theloai);
					swap(p->dl.tennxb, q->dl.tennxb);
				}
			}
			else if (phanloai == 'g')
			{
				if (p->dl.giatien < q->dl.giatien)
				{
					swap(p->dl.tensach, q->dl.tensach);
					swap(p->dl.masach, q->dl.masach);
					swap(p->dl.giatien, q->dl.giatien);
					swap(p->dl.manxb, q->dl.manxb);
					swap(p->dl.tentacgia, q->dl.tentacgia);
					swap(p->dl.namxb, q->dl.namxb);
					swap(p->dl.vitri, q->dl.vitri);
					swap(p->dl.soluong, q->dl.soluong);
					swap(p->dl.theloai, q->dl.theloai);
					swap(p->dl.tennxb, q->dl.tennxb);
				}
			}
		}
	}

}
//sắp xếp theo tên
void sapxepabc(list l)
{
	for (quyensach *p = l.head; p != l.tail; p = p->next)
	{
		for (quyensach *q = p->next; q != NULL; q = q->next)
		{
			if ((strcmp(p->dl.tensach, q->dl.tensach) > 0))
			{
				swap(p->dl.tensach, q->dl.tensach);
				swap(p->dl.masach, q->dl.masach);
				swap(p->dl.giatien, q->dl.giatien);
				swap(p->dl.manxb, q->dl.manxb);
				swap(p->dl.tentacgia, q->dl.tentacgia);
				swap(p->dl.namxb, q->dl.namxb);
				swap(p->dl.vitri, q->dl.vitri);
				swap(p->dl.soluong, q->dl.soluong);
				swap(p->dl.theloai, q->dl.theloai);
				swap(p->dl.tennxb, q->dl.tennxb);
			}
		}
	}

}



/////////////////HÀM TÍNH\\\\\\\\\\\\\\\\\\\\\
//tính tổng giá trị kho sách
int TinhTong(list l)
{
	// for(int i = 0; i < n; i++)
	int tong = 0;
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		tong += p->dl.giatien;
	}
	return tong;
}
//đếm số sách
int Tinh(list l)
{
	// for(int i = 0; i < n; i++)
	int tong = 0;
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		tong ++;
	}
	return tong;
}
void main()
{
	list l;
	CreateList(l);
	congviec();
	
	
	GiaiPhong(l);
}
