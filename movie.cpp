//chuong trinh quan li ve trong rap chieu phim


#include<iostream>
#include<windows.h>
#include<conio.h>
#include<fstream>//thu vien thao tac voi file
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<iomanip>
//#include <graphics.h>
using namespace std;

int k=7,r=0,flag=0;
COORD coord = {0, 0};//he toa do decac
//ham khai bao he toa do de cac
void gotoxy(int x, int y)
{
 COORD coord;
 coord.X = x;
 coord.Y = y;
 SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//ham khai bao mau sac trong thu vien do hoa
//void textcolor(int x){
//	HANDLE mau;
//	mau=GetStdHandle(STD_OUTPUT_HANDLE);
//	SetConsoleTextAttribute(mau,x);
//}
//cau truc ngay thang nam
struct date
{
int mm,dd,yy;
};

ofstream fout;//output thong tin tu file
ifstream fin;//input thong tin vao file
//lop soat ve
class ticket
{
        int itemno;//ma so ve
        char name[25];//ten ve
        date d;//ngay chieu

public:
	//ham them ve
     void add()
	  {
     	cout<<"\n\n\tTicket No: ";
        cin>>itemno;
        cout<<"\n\n\tName of the Movie: ";
        cin>>name;
        cout<<"\n\n\tReleasing Date(dd-mm-yy): ";
        cin>>d.mm>>d.dd>>d.yy;
	  }
	//Ham xuat ve
	void show()
      {
        cout<<"\n\tTicket No: ";
		cout<<itemno;
		cout<<"\n\n\tName of the Movie: ";
		cout<<name;
		cout<<"\n\n\tReleasing Date : ";
		cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
	  }
	void report()
      {
		gotoxy(3,k);
		cout<<itemno;
		gotoxy(13,k);
		puts(name);
		cout<<name;
	  }

	int retno()
	  {
   		 return(itemno);

	  }

};

//ham tinh gia ve
class amount: public ticket
{
    float price,qty,netamt;
	public:
		void add();//them gia tien
		void show();//show gia tien
		void report();//bao cao gia
		void calculate();//tinh toan gia
		void pay();//input tong tien phai tr
		float retnetamt()
		  {
   			 return(netamt);
		  }
}amt;

void amount::calculate()
 {
	netamt=qty*price;//tong tien=soluong x gia/ve
 }

void amount::add()
 {
	ticket::add();
	cout<<"\n\n\tPrice: ";
	cin>>price;
	cout<<"\n\n\tQuantity: ";
	cin>>qty;
	calculate();//tinh toan gia tien
	fout.write((char *)&amt,sizeof(amt));//ghi du lieu moi vao file
	fout.close();//dong file
 }


void amount::show()
 {
	fin.open("itemstore.dat",ios::binary);//mo file co ten itemstore.dat trong thu muc
	fin.read((char*)&amt,sizeof(amt));//doc file
	ticket::show();//in ra man hinh thong tin co trong file
	cout<<"\n\n\tNet Amount: ";
	cout<<netamt;//in them thong tin ve so luong(ko ghi truc tiep vao file)
	fin.close();//dong file
 }

void amount::report()
 {
	ticket::report();
	gotoxy(23,k);
	cout<<price;
	gotoxy(33,k);
	cout<<qty;
	gotoxy(64,k);
	cout<<netamt;
	k=k+1;
	if(k==50)
	  {
	  	  gotoxy(25,50);
		  cout<<"PRESS ANY KEY TO CONTINUE...";
		  getch();
		  k=7;
		  system("cls");
		  gotoxy(30,3);
		  cout<<" TICKET DETAILS ";
		  gotoxy(3,5);
		  cout<<"NUMBER";
		  gotoxy(13,5);
		  cout<<"NAME";
		  gotoxy(23,5);
		  cout<<"PRICE";
		  gotoxy(33,5);
		  cout<<"QUANTITY";
		  gotoxy(36,5);
		  cout<<"NET AMOUNT";
        }
}

void amount::pay()
{
 	show();
	cout<<"\n\n\n\t\t*********************************************";
	cout<<"\n\t\t                 DETAILS                  ";
	cout<<"\n\t\t*********************************************";
	cout<<"\n\n\t\tPRICE                       :"<<price;
	cout<<"\n\t\tQUANTITY                    :"<<qty;
	cout<<"\n\n\t\tNET AMOUNT\t             :$"<<netamt;
	cout<<"\n\n\t\t*********************************************";
}

int main()
{
//
// gotoxy(40,4);
// cout<<"==================================\n\n";
// gotoxy(40,5);
// cout<<"\tUSER PANEL - LOGIN ";
// gotoxy(40,6);
// cout<<"==================================\n\n";
// string username=" ";
// string password=" ";
// bool loginSucess= false;
//
// do
// {
//   gotoxy(40,10);
//   cout<<"Enter Username: ";
//   cin>> username;
//   gotoxy(40,12);
//   cout<<"Enter Password: ";
//   cin>> password;
//   if(username=="admin" && password=="admin")
//   {
//   	cout<<"\n You're 'sucessfully logged in\n\n" ;
//   	loginSucess = true;
//   }else
//   {
//   	cout<<" Incorrect username and password\n";
//   	cout<<" Please try to login again";
//   }
// } while(!loginSucess);

	cout.setf(ios::fixed);// co hien thi so dau cham dong theo yeu cau
	cout.setf(ios::showpoint);//co de xuat hien cac dau thap phan
	cout<<setprecision(2);//dinh dang so luong chu so trong phan thap phan cua so thuc, dung trong thu vien iomanip
	fstream tmp("temp.dat",ios::binary|ios::out);
menu:
	system("cls");
	gotoxy(25,2);
	cout<<"==============================\n\n";
	gotoxy(25,3);
	cout<<"MOVIE TICKET MANAGEMENT SYSTEM ";
	gotoxy(25,4);
	cout<<"==============================\n\n";
	//gotoxy(25,5);
	cout<<"\n\t\t1.CART REPORT \n\n";
	//gotoxy(25,6);
	cout<<"\n\t\t2.ADD/REMOVE/EDIT Ticket\n\n";
	//gotoxy(25,7);
	cout<<"\n\t\t3.SHOW TICKET DETAILS\n\n";
	//gotoxy(25,8);
	cout<<"\n\t\t4.EXIT\n\n";
	//gotoxy(25,9);
	cout<<"\n\t\tPlease Enter Required Option: ";
	int ch,ff;
	float gtotal;
	cin>>ch;
	switch(ch)
	 {
	 case 1:
ss:
		system("cls"); //clear screen mode
		gotoxy(25,2);
		cout<<"CART DETAILS";
		gotoxy(25,3);
		cout<<"================\n\n";
		cout<<"\n\t\t1.All Ticketa\n\n";
		cout<<"\t\t2.BACK TO MAIN MENU\n\n";
		cout<<"\t\tPlease Enter Required Option: ";
		int cho;
		cin>>cho;
		if(cho==1)
		  {
		    system("cls");
			gotoxy(30,3);
			cout<<" CART DETAILS ";
			gotoxy(3,5);
			cout<<"NO";
			gotoxy(13,5);
			cout<<"NAME";
			gotoxy(23,5);
			cout<<"PRICE";
			gotoxy(33,5);
			cout<<"QUANTITY";
			gotoxy(64,5);
			cout<<"NET AMOUNT";
			fin.open("itemstore.dat",ios::binary);//mo file
			if(!fin)
			 {
			    cout<<"\n\nFile Not Found...";
				goto menu;
			}
			fin.seekg(0); //Set position in input sequence. Sets the position of the next character to be extracted from the input stream.
			gtotal=0;
			while(!fin.eof())
			 {
			   fin.read((char*)&amt,sizeof(amt));
			   if(!fin.eof())
				{
				  amt.report();
				  gtotal+=amt.retnetamt();
				  ff=0;
				}
			   if(ff!=0)
			   gtotal=0;
			}
		   	gotoxy(17,k);
			cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
			getch();
			fin.close();
	   }
			if(cho==2)
			 {
			   goto menu;
			 }
			goto ss;
		case 2:
db:
		system("cls");
		gotoxy(25,2);
		cout<<"============\n\n";
		gotoxy(25,3);
		cout<<"MAIN SECTION";
		gotoxy(25,4);
		cout<<"============\n\n";
		cout<<"\n\t\t1.ADD TICKET DETAILS\n\n";
		cout<<"\t\t2.EDIT TICKET DETAILS\n\n";
		cout<<"\t\t3.DELETE TICKET DETAILS\n\n";
		cout<<"\t\t4.BACK TO MAIN MENU";
		int apc;
		cin>>apc;
		switch(apc)
		 {
			case 1://case 1:add ticket details
				fout.open("itemstore.dat",ios::binary|ios::app);
				amt.add();
				cout<<"\n\t\tTicket Added Successfully!";
				getch();
				goto db;

			case 2://2.EDIT TICKET DETAILS
				int ino;
				flag=0;
				cout<<"\n\n\tENTER TICKET NUMBER TO BE EDITED :";
				cin>>ino;
				fin.open("itemstore.dat",ios::binary);
				fout.open("itemstore.dat",ios::binary|ios::app);
				if(!fin)
		 		{
		   			cout<<"\n\nFile Not Found...";
		   			goto menu;
				}
				fin.seekg(0);
				r=0;
				while(!fin.eof())
		 		{
		  			 fin.read((char*)&amt,sizeof(amt));
		   			 if(!fin.eof())
				 	  {
			  			int x=amt.ticket::retno();
			  			if(x==ino)
				        {
				 			flag=1;
				  			fout.seekp(r*sizeof(amt));
				  			system("cls");
				 			cout<<"\n\t\tCURRENT DETAILS ARE\n";
				  			amt.show();
				  			cout<<"\n\n\t\tENTER NEW DETAILS\n";
				  			amt.add();
				  			cout<<"\n\t\tTICKET DETAILS EDITED";
						}
					 }r++;
				}
			   if(flag==0)
 		 		{
   					cout<<"\n\t\tTicket No does not exist...Please Retry!";
					getch();
					goto db;
 		 		}
				fin.close();
				getch();
				goto db;

			case 3://3.DELETE TICKET DETAILS
				flag=0;
				cout<<"\n\n\tEnter Ticket Number to be deleted :";
				cin>>ino;
				fin.open("itemstore.dat",ios::binary);
				if(!fin)
	 			{
	   			cout<<"\n\nFile Not Found...";
	   			goto menu;
     			}

				fin.seekg(0);
				while(fin.read((char*)&amt, sizeof(amt)))
				{
    				int x=amt.ticket::retno();
					if(x!=ino)
						tmp.write((char*)&amt,sizeof(amt));
					else
	 				{
	   					flag=1;
	 				}
				}
					fin.close();
					tmp.close();
					fout.seekp(0);
					tmp.open("temp.dat",ios::binary|ios::in);
					if(!tmp)
 					 {
   						cout<<"Error in File";
						goto db;
					 }
					while(tmp.read((char*)&amt,sizeof(amt)))
					fout.write((char*)&amt,sizeof(amt));
					tmp.close();
					fout.close();
						if(flag==1)
						cout<<"\n\t\tTicket Succesfully Deleted";
					else if (flag==0)
					cout<<"\n\t\tTicket does not Exist! Please Retry";
					getch();
					goto db;
			case 4://4.BACK TO MAIN MENU
				goto menu;
				default: cout<<"\n\n\t\tYou Choose Wrong Choice!!! Retry";
				getch();
				goto db;
			}
		
		case 3://3.SHOW TICKET DETAILS
			system("cls");
			flag=0;
			int ino;
			cout<<"\n\n\t\tENTER TICKET NUMBER:";
			cin>>ino;
			fin.open("itemstore.dat",ios::binary);
			if(!fin)
	 		 {
	 			cout<<"\n\nFile Not Found...\nProgram Terminated!";
				goto menu;
	 		}
			fin.seekg(0);
			while(fin.read((char*)&amt,sizeof(amt)))
	 		 {
	   			int x=amt.ticket::retno();
	   			if(x==ino)
	    		 {
					amt.pay();
					flag=1;
					break;
				}
			}
			if(flag==0)
			cout<<"\n\t\tTicket does not exist....Please Retry!";
			getch();
			fin.close();
			goto menu;

		case 4://4.EXIT
				system("cls");
				gotoxy(20,20);
				cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
				char yn;
				cin>>yn;
				if((yn=='Y')||(yn=='y'))
	 			 {
					system("cls");
					gotoxy(40,4);
					cout<<"==============================\n\n";
					gotoxy(40,5);
					cout<<"THANK YOU FOR USING OUR SYSTEM ";
					gotoxy(40,6);
					cout<<"==============================\n\n";
					getch();
					exit(0);
				}
				else if((yn=='N')||(yn=='n'))
					goto menu;
				else
				{
					goto menu;
				}
		default:
			cout<<"\n\n\t\tWrong Choice....Please Retry!";
			getch();
			goto menu;
		}
			return 0;
	}
