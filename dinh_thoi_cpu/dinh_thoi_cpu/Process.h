#pragma once
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <iostream>

using namespace std;
class Process
{
	string name;
	int t_vao;
	int t_xuly;
	int t_cho = 0;
	int t_luu;
	int stt;
	bool running = false;

public:
	Process();

	string getName();
	void setName(string s);

	int getT_vao();
	void setT_vao(int s);

	int getT_xuly();
	void setT_xuly(int s);

	int getT_cho();
	void setT_cho(int s);

	int getT_luu();
	void setT_luu(int s);

	int getSTT();
	void setSTT(int s);

	bool getRuning();
	void setRuning(bool s);


	~Process();
};

