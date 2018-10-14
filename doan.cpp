
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
void timtheomasach(list &l);	//tìm kiếm theo mã sách
int xoatheomasach(list &L);		//xóa theo mã sách
void XoaDau(list &l);			//xóa đầu
void xoacuoi(list &l);			//xóa cuối
/////////////////////////////////////////////////
//tạo menu
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
//nhập thông tin sách
void nhapsach(thongtin &a)
{
	cin.ignore();
	cout << "Nhap ten sach : ";
	
	cin.getline(a.tensach, 9);
	/*cout << "Nhap ten nxb: ";
	cin.getline(a.tennxb, 100);*/
	cout << "Nhap ma sach: ";
	cin >> a.masach;
	/*cout << "Nhap ma nha xuat ban:";
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
void insach(thongtin a)
{
	cout << endl;
	cout << "Ten sach la : " << a.tensach << endl;
	//cout << "Ten nxb la: " << a.tennxb << endl;
	cout << "Ma sach la: " << a.masach << endl;
	/*cout << "Ten tac gia cua sach: " << a.tentacgia << endl;;
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
	quyensach *r = l.tail; //khai báo con trỏ gán với node cuối của danh sách
	if (p == r) //Nếu danh sách chỉ có một node
	{
		l.head = l.tail = NULL;
		delete p;
	}
	else //Nếu không p chạy tới node cận cuối cùng
	{
		while (p->next != r) p = p->next;
		p->next = NULL; //p trỏ đến NULL
		l.tail = p; //Node cận cuối p trở thành node cuối
		delete r; //Xóa node cuối ban đầu
	}

}
//xóa theo mã sách
int xoatheomasach(list &L)
{
	int id;
	quyensach *pN, *tmpN = NULL;
	pN = L.head;
finddelete:
	cout << "nhap ma sach can xoa: "; cin >> id;
	cout << endl;
	while (pN != NULL) {
		if (pN->dl.masach == id) break;
		tmpN = pN;
		pN = pN->next;
	}
	if (pN == NULL) {
		cout << "ko co sach do trong thu vien" << endl;
		return 0;
	}

	if (tmpN != NULL) {
		if (pN->next != NULL) {
			tmpN->next = pN->next;
			delete pN;
		}
		else {
			tmpN->next = pN->next;
			delete pN;
			L.tail = tmpN;
		}
	}
	else {
		L.head = pN->next;
		if (L.head == NULL) L.tail = NULL;
	}
	return 1;
}
//tìm kiếm theo mã sách
void timtheomasach(list &l)
{
	int id;
	quyensach* pN;
	int count = 0;
	cout << "nhap ma sach can tim: ";
	cin >> id;
	cout << endl;
	pN =l.head;
	while (pN != NULL) {
		if (pN->dl.masach == id) {
			cout << "thong tin cua sach la:\n" << endl;
			cout<<"ma sach: "<<pN->dl.masach << endl;
			cout << "ten sach la: " << pN->dl.tensach << endl;
			
			break;
		}
		else
		{
			++count;
			pN = pN->next;
		}

	}
	if (pN == NULL) {
		cout << "No record is existing with ur selection" << endl;
		cout << "We listed " << count << endl;
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
	//menu();
	xuatlist(l);
	cout << endl;
	//XoaDau(l);
	xoacuoi(l);
	//timtheomasach(l);
	//xoatheomasach(l);
	//cout << "so sach con lai trong thu vien la:" << endl;
	xuatlist(l);
	GiaiPhong(l); // Giải phóng danh sách
	
}
