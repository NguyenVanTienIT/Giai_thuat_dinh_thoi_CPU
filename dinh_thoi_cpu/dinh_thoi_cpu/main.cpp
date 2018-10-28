#include <stdio.h>
#include <math.h>
#include <string.h>
#include <string>
#include <iostream>
#include "Process.h""

using namespace std;

Process listProcess[20];
Process listTest[20];
int n, j, ok[20];
int time_quantum;


void Clone() {
	for (int i = 0; i < n; ++i) {
		listTest[i].setName(listProcess[i].getName());
		listTest[i].setT_xuly(listProcess[i].getT_xuly());
		listTest[i].setT_vao(listProcess[i].getT_vao());
		listTest[i].setRuning(listProcess[i].getRuning());
	}
}

void Input() {
	int i = 0;
	fflush(stdin);
	while (i <= n - 1)
	{
		//fflush(stdin);
		string name;
		cout << "\tTen tien trinh : ";
		cin >> name;
		listProcess[i].setName(name);

		int time_Xuly;
		cout << "\tThoi gian xu ly: ";
		cin >> time_Xuly;
		listProcess[i].setT_xuly(time_Xuly);

		int time_Vao;
		cout << "\tThoi gian vao: ";
		cin >> time_Vao;
		listProcess[i].setT_vao(time_Vao);
		i++;
		cout << endl;
	}
	
}

void Ouput(Process list[20]) {
	cout << "\n\t\t|TT" << "\t\t" << "Ten TT |" << "\t\t" << " SD CPU |" << "\t\t" << " Tgxly|" << "\t\t" << " TgCho|" << endl;
	cout << "\t\t----------------------------------------" << endl;
	for (int i = 0; i <= n - 1; i++)
	{

		//cout<<"\n\t\t|"<<list[i].getSTT()<<"|"<<"\t\t" << list[i].getName()<<"|"<<"\t\t",
		cout << "\n\t\t|" << list[i].getT_xuly() << "|" << "\t\t" << list[i].getName() << "\t\t" << list[i].getT_vao()<<"|" << "\t\t";
	}
}



void sort() {
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; j++)
		{
			if (listTest[j].getT_vao() < listTest[i].getT_vao()) {
				Process tam = listTest[i];
				listTest[i] = listTest[j];
				listTest[j] = tam;
			}
		}
	}
}

void setup() {
	do {
		cout <<"\t----------------NHAP VAO DU LIEU---------------"<<endl;
		cout <<"So luong tien trinh: n = ";
		fflush(stdin);
		cin >> n;
		//cout << endl;
		cout << "Nhap vao thoi gian dinh muc = ";
		fflush(stdin);
		cin >> time_quantum;
		cout << endl;
	} while ((n <= 0) || (n > 20));
	fflush(stdin);
	Input();
	//Ouput(listTest);
}







void FCFS() {
	Clone();
	sort();
	int sum_timecho = 0;
	cout << "\n\t\t=============GIAI THUAT DINH THOI CPU FCFS==================" << endl;
	int time_chay = 0;
		for (int i = 0; i < n; ++i) {
			if (i != 0)
			{
				int time_cho = time_chay - listTest[i].getT_vao();  // time cho dau tien
				if (time_cho <= 0) time_cho = 0;
				sum_timecho += time_cho;
				time_chay += listTest[i].getT_xuly();
			}
			else {
				int time_cho = 0;
				time_chay = listTest[0].getT_xuly() + listTest[0].getT_cho();  // thoi gian lan chay dau tien
				 time_cho = listTest[0].getT_cho();
				 sum_timecho += time_cho;
			}
		}

		cout << "\nThoi gian cho trung binh la " << sum_timecho / (n+1)<<endl;
		//cout << "\nTong thoi gian thuc hien la " << time_chay << endl;
}

void sortSJF() {
	Clone();
	sort();
	int index = 0;
	Process listSJF[20];
	int time_chay = 0;
	for (int i = 0; i < n; ++i) 
	{
		if (i != 0)
		{
			int min_time_xuly = -1;
			for (int j = 1; j < n; j++)  // chon min ban dau la 1 cái chua run va time xuat hien < time chay
			{
				if ((listTest[j].getRuning() == false) && (listTest[j].getT_vao() < time_chay)) {
					min_time_xuly = listTest[j].getT_xuly();
					break;
				}
			}

			for (int j = 1; j < n; ++j) {  
				if (min_time_xuly > listTest[j].getT_xuly() && listTest[j].getRuning() == false && listTest[j].getT_vao() < time_chay)
				{
					// kiem tra xem tien trinh nay da chay chua
					min_time_xuly = listTest[j].getT_xuly();  
				}
			}

			if (min_time_xuly == -1) // neu trong khoang thoi gian do khong co tien trinh nao chay them
			{
				for (int j = 1; j < n; j++)  
				{
					if (listTest[j].getRuning() == false) {
						listSJF[index] = listTest[j];
						listTest[j].setRuning(true);
						time_chay += listTest[j].getT_xuly();
						index++;
						break;
					}
				}
			}
			else {
				for (int j = 1; j < n; ++j) {  // 
					if (min_time_xuly == listTest[j].getT_xuly())
					{
						listSJF[index] = listTest[j];
						listTest[j].setRuning(true);  // set true cho nhung tien trinh duoc chon
						time_chay += listTest[j].getT_xuly();
						index++;
						break;
					}
				}
			}

		}
		else {   // chay lan dau tien
			int time_cho = 0;
			listTest[0].setRuning(true);
			time_chay = listTest[0].getT_xuly() + listTest[0].getT_cho();  // thoi gian lan chay dau tien
			time_cho = listTest[0].getT_cho();
			listSJF[index] = listTest[0];
			index++;
		}

	}

	for (int i = 0; i < n; ++i) {
		listTest[i] = listSJF[i];
	}

	
}

void SJF() {
	sortSJF();
	int sum_timecho = 0;
	cout << "\n\t\t=============GIAI THUAT DINH THOI CPU SJF==================" << endl;
	int time_chay = 0;
	for (int i = 0; i < n; ++i) {
		if (i != 0)
		{
			int time_cho = time_chay - listTest[i].getT_vao();  // time cho dau tien
			if (time_cho <= 0) time_cho = 0;
			cout<< time_cho << endl;
			sum_timecho += time_cho;
			time_chay += listTest[i].getT_xuly();
		}
		else {
			int time_cho = 0;
			time_chay = listTest[0].getT_xuly() + listTest[0].getT_cho();  // thoi gian lan chay dau tien
			time_cho = listTest[0].getT_cho();
			cout << time_cho << endl;
			sum_timecho += time_cho;
		}
	}
	cout << "\nThoi gian cho trung binh la " << sum_timecho / n << endl;
	cout << "\nTong thoi gian thuc hien la " << time_chay << endl;

}


bool checkProcess() {  // check xem cac tien trinh da chay het hay chua
	for (int i = 0; i < n; ++i) {
		if (listTest[i].getT_xuly() > 0)
		{
			return true;
		}
	}
	return false;
}


void STR() {
	Clone();
	sort();
	
	int sum_time_cho = 0;	
	int sum_time_xuly = 0;
	int i = 0;
	int index = -1; // vi tri co tien trinh co time xu ly nho nhat

	for (int i = 0; i < n; ++i) {
		int min_xuly = 10000;
		if (i == n - 1) {
				while (true) {
					min_xuly = 10000;
					if (!checkProcess()) break;
						for (int x = 0; x < n; ++x) {  
							if (listTest[x].getT_xuly() < min_xuly && listTest[x].getT_xuly() > 0 ) {
								min_xuly = listTest[x].getT_xuly();
								index = x;
							}
						}

					for (int k = 0; k < n; ++k) {  // cong vao thoi gian cho
						if (k != index && listTest[k].getT_xuly() > 0) {
							//cout << "P" << index + 1 << " is runing" << endl;
							sum_time_cho += listTest[index].getT_xuly();
						}
					}
					listTest[index].setT_xuly(0);
				}
		}
		else {
			//cout << "-----------tu " << listTest[i].getT_vao() << "den " << listTest[i + 1].getT_vao() << "---------" << endl;
			sum_time_xuly += listTest[i + 1].getT_vao() - listTest[i].getT_vao();
			for (int j = listTest[i].getT_vao(); j < listTest[i + 1].getT_vao() ; ++j) {

				// check tim tien trinh co thoi gian xu ly it nhat
				if (j == listTest[i].getT_vao() || listTest[index].getT_xuly() == 0) {
					min_xuly = 1000;
					//cout << "check" << endl;
					for (int k = 0; k < n; ++k) {
						if (listTest[k].getT_xuly() < min_xuly && listTest[k].getT_xuly() > 0 && listTest[k].getT_vao() < listTest[i + 1].getT_vao()) {
							min_xuly = listTest[k].getT_xuly();
							index = k;
						}
					}
				}

				for (int k = 0; k < n; ++k) {  // cong thoi gian tre
					if (k != index && listTest[k].getT_xuly() > 0 && listTest[k].getT_vao() < listTest[i + 1].getT_vao()) {
						// xet nhung tien trinh can chay trong thoi gian nay
						//cout << "Tien trinh p" << k + 1 << " dang cho" << endl;
						sum_time_cho ++;
					}
				}
				//cout << "Tien trinh p" << index + 1 << " dang chay" << endl;
				int time = listTest[index].getT_xuly();
				listTest[index].setT_xuly(time - 1);
			}
			//cout << "---------------------------------------" << endl;
		}
	}
	cout << "thoi gian cho la " << sum_time_cho << endl;
}




void RR() {
	Clone();
	sort();
	int sum_time_delay = 0;
	int sum_time_xuly = 0;
	Process listRR[20];
	int length = 0;
	int time_start = listTest[0].getT_vao();
	int check_process = false;

	while (true) {
		if (!checkProcess()) break;
		for (int i = time_start; i < time_start + time_quantum; ++i) {

			if (i == time_start) {
				cout << i << endl;
				if (check_process) {
					check_process = false;
				}
				else {
					
					if (length > 1)  //  xoay vong mang cac tien trinh
					{
						Process tam = listRR[0];
						for (int x = 0; x < length; ++x) { // thuc hien copy mang
							listRR[x] = listRR[x+1];
							if (x == length - 1)
							{
								listRR[x] = tam;
							}
						}
					}
				}
			}

			for (int j = 0; j < n; j++)  // add vao tien trinh xuat hien 
			{
				if (listTest[j].getT_vao() == i)
				{
					listRR[length] = listTest[j];  // roi add tien trinh xuat hien trong khoang thoi gian 
					length++;
				}
			}

			if (length >= 1) {
				listRR[0].setT_xuly(listRR[0].getT_xuly() - 1);
				
				for (int k = 0; k < n; ++k) {  // 
					if (listTest[k].getT_vao() == listRR[0].getT_vao()) {
						listTest[k].setT_xuly(listTest[k].getT_xuly() - 1);
						cout << "tien trinh p" << k + 1 << " dang chay"<< endl;
						break;
					}
				}

				if (length > 1)
				{
					for (int y = 1; y < length; ++y) {  // tinh time delay
						cout << "---------tien trinh " << listRR[y].getName() << " dang cho-----------" << endl;
						sum_time_delay++;
						listRR[y].setT_cho(listRR[y].getT_cho() + 1);
						for (int k = 0; k < n; ++k) {  // 
							if (listTest[k].getT_vao() == listRR[y].getT_vao()) {
								listTest[k].setT_cho(listRR[y].getT_cho());
								break;
							}
						}
						
					}
				}
				
				if (listRR[0].getT_xuly() == 0)   // trong qua trinh chay ma tien trinh nao chay het thi bo khoi hang doi
				{
					for (int j = 0; j < length - 1; ++j) {
						listRR[j] = listRR[j + 1];
					}
					--length;
					time_start = i + 1;
					check_process = true;
					break;
				}
			}
		}
		if (check_process)
		{
			continue;
		}
		else {
			time_start = time_start + time_quantum;
		}
	}

	cout << "thoi gian cho cua cac tien trinh la :" << sum_time_delay << endl;

	for (int i = 0; i < n; ++i) {
		cout << "thoi gian cho cua " << listTest[i].getName() << " la" << listTest[i].getT_cho() << endl;
	}

}

int main() {

	bool exit = false;
	bool set = true;

	/*
	example:
	p1		11		0
	p2		7		3
	p3		19		8
	p4		4		13
	p5		9		17
	
	*/
	while (true) {
		char option;
		if (set)
		{
			setup();
		}
		
		cout << "\t\t\t===================Option===================" << endl;
		cout << "\t\t\t1.Thuat toan FCFS" << endl;
		cout << "\t\t\t2.Thuat toan SJF" << endl;
		cout << "\t\t\t3.Thuat toan STR" << endl;
		cout << "\t\t\t4.Thuat toan RR" << endl;
		cout << "\t\t\t5.Tat ca giai thuat" << endl;
		cout << "\t\t\t============================================" << endl;
		cin >> option;
		if (option == '1')
		{
			system("cls");
			FCFS();
			char a;
			cout << "ban co muon tiep tuc khong neu co thi nhan phim bat ki , neu khong nhan 0 : ";
			cin >> a;
			if (a == '0')
			{
				break;
			}

		}
		else if (option == '2')
		{
			system("cls");
			SJF();
			char a;
			cout << "ban co muon tiep tuc khong neu co thi nhan phim bat ki , neu khong nhan 0 : ";
			cin >> a;
			if (a == '0')
			{
				break;
			}
		}
		else if (option == '3')
		{
			system("cls");
			STR();
			char a;
			cout << "ban co muon tiep tuc khong neu co thi nhan phim bat ki , neu khong nhan 0 : ";
			cin >> a;
			if (a == '0')
			{
				break;
			}
		}
		else if (option == '4')
		{
			system("cls");
			RR();
			char a;
			cout << "ban co muon tiep tuc khong neu co thi nhan phim bat ki , neu khong nhan 0 : ";
			cin >> a;
			if (a == '0')
			{
				break;
			}
		}
		else if (option == '5')
		{
			system("cls");
			FCFS();
			SJF();
			STR();
			RR();
			char a;
			cout << "ban co muon tiep tuc khong neu co thi nhan phim bat ki , neu khong nhan 0 : ";
			cin >> a;
			if (a == '0')
			{
				break;
			}
		}


		while (true) {
			char chon;
			cout << "\t\t\t===================Option===================" << endl;
			cout << "\t\t\t1.Nhap lai n" << endl;
			cout << "\t\t\t2.Nhap lai tat ca" << endl;
			cout << "\t\t\t3.Thoat chuong trinh" << endl;
			cout << "\t\t\t4.Quay Lai" << endl;
			cout << "\t\t\t============================================" << endl;
			cin >> chon;
			if (chon == '1')
			{
				cout << "\t\t\tMoi nhap vao thoi gian dinh muc = ";
				cin >> time_quantum;
				set = false;
			}
			else if (chon == '2') {
				set = true;
				break;
			}
			else if (chon == '3')
			{
				exit = true;
				break;
			}
			else
			{
				set = false;
				break;
			}
		}

		if (exit) {
			break;
		}

	}

	//Ouput(listTest);
	system("pause");

	return 0;
}