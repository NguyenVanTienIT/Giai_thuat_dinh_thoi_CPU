#include "Process.h"



Process::Process()
{
}

string Process::getName() {
	return name;
}

void Process::setName(string s) {
	this->name = s;
}

int Process::getT_vao() {
	return this->t_vao;
}
void Process::setT_vao(int s) {
	this->t_vao = s;
}

int Process::getT_xuly() {
	return this->t_xuly;
}
void Process::setT_xuly(int s) {
	this->t_xuly = s;
}

int Process::getT_cho() {
	return t_cho;
}
void Process::setT_cho(int s) {
	this->t_cho = s;
}

int Process::getT_luu() {
	return this->t_luu;
}
void Process::setT_luu(int s) {
	this->t_luu = s;
}

int Process::getSTT() {
	return this->stt;
}
void Process::setSTT(int s) {
	this->stt = s;
}

bool Process::getRuning() {
	return this->running;
}
void Process::setRuning(bool s) {
	this->running = s;
}


Process::~Process()
{
}
