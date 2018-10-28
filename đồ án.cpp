#include "pch.h"
#include <iostream>
#include<stdio.h>
#include "math.h"
#include "conio.h"
#include <windows.h>
#include <io.h>
#include <fcntl.h>


#define MAX 200
#define X 20
#define y 13
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
	char tendocgia[50];
	int madocgia;
	char diachidg[50];
	int sdtdg;
};
struct quanly
{
	char ten[50];
	int maso;
	char diachi[50];
	int sdt;
};
quanly ql;
docgia dg;
thongtin x;
quyensach *sach;
list l;
//khai báo hàm
void CreateList(list &l);
void nhapsach(thongtin &a);
quyensach *GetNode(thongtin a);
void AddTail(list &L, quyensach *p);	//thêm sách vào cuối (để xuất theo thứ tự)
void nhap(list &l, int n);				//Nhập danh sách quản lí
void insach(thongtin a);				//in thông tin sách
void xuatlist(list l);					//in nhiều sách
void GiaiPhong(list &l);				//giải phóng bộ nhớ
void timtheomasach(list &l);			//tìm kiếm theo mã sách
int xoatheomasach(list &L);				//xóa theo mã sách
void XoaDau(list &l);					//xóa đầu
void xoacuoi(list &l);					//xóa cuối
void Lietkenxb(list l);					//liệt kê theo năm xuất bản
void SapXep(list &l, char phanloai);	//sắp xếp theo giá tiền
void timtheogiatien(list l);			//tìm theo giá tiền
int TinhTong(list l);					//tính tổng tiền kho sách
void Lietkevt(list l);					//liệt kê theo vị trí
void timtheomanxb(list l);				//tìm theo mã nhà xuất bản
void timtheotensach(list l);			//tìm theo tên sách
void xoatheogiatien(list &l);			//xóa sách nhỏ hơn 1 mức giá nào đó
int chonquanly(quanly l[100], int n, int id);
/////////////////////////////////////////////////
//nhập thông tin của người quản lí
void nhapql(quanly &a)
{
	cin.ignore();
	cout << "Nhap ten nguoi quan ly: ";
	cin.getline(a.ten, 9);
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
//xuất các quản lý
void xuattql()
{
	cout << "thong tin nhan vien quan ly: " << endl;
	cout << "======================================\n";
	cout << "ho va ten";
	cout.width(15);
	cout << "ma so";
	cout.width(20);
	cout << "so dien thoai";
	cout.width(15);
	cout << "dia chi";
	

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
//xuất độc giả
void xuatttdg() 
{
	cout << "thong tin doc gia " << endl;
	cout << "======================================\n";
	cout << "ho va ten";
	cout.width(15);
	cout << "ma so";
	cout.width(20);
	cout << "so dien thoai";
	cout.width(15);
	cout << "dia chi";
	cout << endl;
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
//tạo menu người quản lí
void menuquanli()
{
	
	cout << "\n				  *_-CONG VIEC CUA NGUOI QUAN LY-_*\n";
	cout << "\n				|***********************************|";
	cout << "\n				|1:Them sach vao thu vien	    |";
	cout << "\n				|2:Xoa di cuon sach		    |";
	cout << "\n				|3:Tim thong tin cuon sach	    |";
	cout << "\n				|4:Sap xep lai kho sach		    |";
	cout << "\n				|5:Liet ke sach theo nam xuat ban   |";
	cout << "\n				|6:Liet ke sach theo vi tri	    |";
	cout << "\n				|===================================|";
	int n,m;
	do {
		cout << "\nBan chon thao tac nao: ";
		cin >> n;
		switch (n)
		{
		case 1: //thêm sách
		{
			cout << "Can them bao nhieu cuon: ";
			cin >> m;
			nhap(l, m);
			cout << "Sach trong thu vien: " << endl;
			xuatlist(l);
			break;
		}
		case 2: 
		{
			xoatheomasach(l);
			cout << "So sach con lai trong thu vien la:" << endl;
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
			cout << "Danh sach sau khi sap xep tang la: ";
			SapXep(l, 't');
			xuatlist(l);
			break;
		}case 5:
		{
			Lietkenxb(l);
			break;
		}
		case 6:
		{
			Lietkevt(l);
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
//menu người mượn sách
void menua()
{
	cout << "\n				  *_-CONG VIEC CUA NGUOI MUON SACH-_*\n";
	cout << "\n				|***********************************|";
	cout << "\n				|1:In thong tin cac cuon sach|";
	cout << "\n				|2:Tim sach theo ten sach	    |";
	cout << "\n				|3:Tim sach theo ma sach	    |";
	cout << "\n				|4:Sap xep lai kho sach		    |";
	cout << "\n				|5:Liet ke sach theo nam xuat ban   |";
	cout << "\n				|6:Liet ke sach theo vi tri	    |";
	cout << "\n				|===================================|";
	int n, m;

	do {
		cout << "ban chon thao tac nao\n";
		cin >> n;
		switch (n)
		{
		case 1:
		{
			xuatlist(l);
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
//nhập thông tin sách
void nhapsach(thongtin &a)
{
	cin.ignore();
	cout << "Nhap ten sach : ";
	cin.getline(a.tensach, 9);
	cout << "Nhap ma sach: ";
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
	cout << endl;
}
//thêm sách vào cuối
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
//in thông tin của sách
void insach1()
{
	cout << "thong tin sach " << endl;
	cout << "======================================\n";
	cout << "Ten sach";
	cout.width(10);
	cout << "Ma sach";
	cout.width(10);
	cout << "Vi tri";
	cout.width(y);
	cout << "Gia tien";
	cout.width(15);
	cout << "Nam xuat ban ";
	cout.width(10);
	cout << "Ten nxb";
	cout.width(20);
	cout << "Ma nha xuat ban";
	cout.width(25);
	cout << "Ten tac gia cua sach";
	cout << endl;
}
void insach(thongtin a)
{
	
	cout.width(y);
	cout << left << a.tensach;
	cout.width(y);
	cout << left << a.masach;
	cout.width(y);
	cout << left << a.vitri;
	cout.width(y);
	cout << left << a.giatien;
	cout.width(y);
	cout << left << a.namxb;
	cout.width(y);
	cout << left << a.tennxb;
	cout.width(y);
	cout << left << a.manxb;
	cout.width(35);
	cout << left << a.tentacgia;
	cout.width(y);
	cout << endl;
}
void xuatlist(list l)
{
	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		
		insach(p->dl);
	}
}
//xóa đầu
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
//xóa theo mã sách
int xoatheomasach(list &L)
{
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
			L.tail = q;
		}
	}
	else {
		L.head = p->next;
		if (L.head == NULL) L.tail = NULL;
	}
	return 1;
}
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
//liệt kê theo năm xuất bản
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
		}
		
	}

}
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
					swap(p->dl.giatien, q->dl.giatien);
				}
			}
			else if (phanloai == 'g')
			{
				if (p->dl.giatien < q->dl.giatien)
				{
					swap(p->dl.tensach, q->dl.tensach);
					swap(p->dl.giatien, q->dl.giatien);
				}
			}
		}
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
	cin >>ten;

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		if (strstr(p->dl.tensach, ten))
		{
			cout << "ten sach: ";
			cout << p->dl.tensach << endl;
			cout << "ma sach: ";
			cout << p->dl.masach << endl;
		}

	}

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
		if (p->dl.giatien<=gt )
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
//sắp xếp theo tên
void sapxepabc(list l)
{
	for (quyensach *p = l.head; p != l.tail; p = p->next)
	{
		for (quyensach *q = p->next; q != NULL; q = q->next)
		{
			if ((strcmp(p->dl.tensach, q->dl.tensach) > 0) )
			{
				swap(p->dl.tensach, q->dl.tensach);
			}
		}
	}

}
//chọn người làm việc
int chonquanly(quanly l[100],int n,int id)
{
	
	
	for (int i = 0; i < n; i++) 
	{
		if (l[i].maso == id)
		{
			
			cout << "ho va ten: "<< l[i].ten;
			cout << endl;
			cout << "ma so: "<< l[i].maso;
			cout << endl;
			cout << "so dien thoai: " << l[i].sdt;
			cout << endl;
			cout << "dia chi: " <<l[i].diachi;
			cout << endl;
			return 1;
			break;
		}
	}
	return 0;
}

/////////////////////////////////////////////////

void CreateList(list &l)
{
	l.head = l.tail = NULL;
}
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
/////////////////////////////////////////////////

void main()
{
	/*docgia b;
	cout << "nhap thong tin doc gia: ";
	nhapdocgia(b);
	xuatttdg();
	xuatdg(b);*/

	//quanly a[100];
	//int n;
	//cout << "nhap so quan ly: ";
	//cin >> n;
	//nhapcacql(a, n);
	//xuattql();
	//xuatcacql(a, n);
	
	/*int n,m;
	CreateList(l);
	system("color E");
	cout << "Nhap so luong sach can quan li: ";
	cin >> n;
	nhap(l, n);
	insach1();
	sapxepabc(l);
	xuatlist(l);*/

	//system("cls"); //xóa màn hình
	//cout << endl;
	//menuquanli();
	//*system("cls");
	//menua();*/
	//*XoaDau(l);
	//xoacuoi(l);
	//timtheomasach(l);
	//xoatheomasach(l);
	//cout << "so sach con lai trong thu vien la:" << endl;
	//xuatlist(l);
	//Lietkenxb(l);
	//cout<<"Danh sach sau khi sap xep tang la: ";
	//SapXep(l, 't');
	//xuatlist(l);
	//cout<<"Danh sach sau khi sap xep giam la: ";
	//SapXep(l, 'g');
	//xuatlist(l); 
	//timtheogiatien(l);
	//int gt = TinhTong(l);
	//cout <<"tong gia tri kho sach la: "<< gt;
	//Lietkevt(l);
	//timtheomanxb(l);
	//timtheotensach(l);
	//xoatheogiatien(l);
	//cout << "sach con lai trong thu vien la:" << endl;
	//xuatlist(l);
	//cout << "can them bao nhieu cuon: " << endl;
	//cin >> m;
	//nhap(l, m);
	//cout << "sach trong thu vien: " << endl;
	//xuatlist(l);*/
	//GiaiPhong(l); // Giải phóng danh sách

	/*quanly a[100];
	int n;
	cout << "nhap so quan ly: ";
	cin >> n;
	nhapcacql(a, n);
	xuattql();
	xuatcacql(a, n);
	cout << endl;
	int id;
	cout << "Nhap ma nhan vien quan ly lam viec hom nay: ";
	cin >> id;
	cout << endl;
	int k = chonquanly(a, n,id);
	if (k != 1) 
		cout << "ko co nguoi nay trong thu vien";*/
}
