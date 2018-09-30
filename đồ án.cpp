
#include <windows.h>
#include "pch.h"
#include <iostream>
#include<stdio.h>
#include "math.h"
#include "conio.h"
#define MAX 200
#define X 20
using namespace std;
struct thongtin {
	char tensach[50];   // tên sách
	char tennxb[100];   //tên nhà xuất bản
	char tentacgia[50]; //tên tác giả
	int masach;         //mã sách
	int vitri;          //vị trí để sách
	int manxb;			//mã nhà xuất bản
	float giatien;      //giá tiền
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

thongtin x;
quyensach *sach;
list l;
//khai báo hàm
void CreateList(list &l);
void nhapsach(thongtin &a);
quyensach *GetNode(thongtin a);
void AddTail(list &L, quyensach *p); //thêm sách vào cuối (để xuất theo thứ tự)
void nhap(list &l, int n);         //Nhập danh sách quản lí
void insach(thongtin a);           //in thông tin sách
void xuatlist(list l);             //in nhiều sách
void GiaiPhong(list &l);			//giải phóng bộ nhớ

/////////////////////////////////////////////////
//thao tác 1
void menu()
{
	cout << "MENU CAC CONG VIEC CUA DO AN";
	cout << "\n1:xuat sach theo thu tu nhap";
	cout << "\n2:xoa sach nam o dau";
	cout << "\n3:xoa sach nam o cuoi";
	cout << "\n4:xoa sach theo ma sach";
	cout << "\n5:tim kiem sach theo ma sach";
	cout << "\n6:liet ke sach theo nam xuat ban";
	cout << "\n7:sap xep sach theo gia tien";
	cout << "\n8:tim sach theo gia tien";
	cout << "\n9:tinh tong gia tien cua kho sach";
	cout << "\n10:liet ke sach theo vi tri ";
	cout << "\n11:tim sach theo ma nha xuat ban";
	cout << "\n12:tim sach theo ten sach";
	cout << "\n13:xoa tat ca sach nho hon muc gia\n";
	cout << "------------------------------------------\n";
	int n;
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
//thao tác 2
void nhapsach(thongtin &a)
{
	
	cout << "Nhap ten sach : ";
	
	cin.getline(a.tensach, 9);
	/*cout << "Nhap ten nxb: ";
	cin.getline(a.tennxb, 100);
	cout << "Nhap ma sach: ";
	cin >> a.masach;
	cout << "Nhap ma nha xuat ban:";
	cin >> a.manxb;
	cout << "Nhap ten tac gia cua sach: ";
	cin.ignore();
	cin.getline(a.tentacgia, 50);
	cout << "Nhap vi tri cua sach:";
	cin >> a.vitri;
	cout << "Nhap gia tien cua sach: ";
	cin >> a.giatien;*/
	cout << endl;
}
//thao tác 3
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
//thao tác 4
void insach(thongtin a)
{
	cout << endl;
	cout << "Ten sach la : " << a.tensach << endl;
	/*cout << "Ten nxb la: " << a.tennxb << endl;
	cout << "Ma sach la: " << a.masach << endl;
	cout << "Ten tac gia cua sach: " << a.tentacgia << endl;;
	cout << "Vi tri cua sach: " << a.vitri << endl;
	cout << "Ma nha xuat ban: " << a.manxb << endl;
	cout << "Gia tien cua sach la: " << a.giatien << endl;*/
}
void xuatlist(list l)
{

	for (quyensach *p = l.head; p != NULL; p = p->next)
	{
		insach(p->dl);
	}
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
	
	int n;
	CreateList(l);
	system("color 8E");
	cout << "Nhap so luong sach can quan li: ";
	cin >> n;
	cin.ignore();	
	nhap(l, n);
	menu();
	cout << endl;
	GiaiPhong(l); // Giải phóng danh sách
	
}
