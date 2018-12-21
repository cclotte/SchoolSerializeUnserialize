#include "FSerial.h"
#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "functions.h"
#endif


using namespace std;

void Serial::put(const bool bin){
	stringstream ss;
	serialize(bin, ss);
	serialData += ss.str();

}

void Serial::put(const short sin){
	stringstream ss;
	serialize(sin,ss);
	serialData += ss.str();

}

void Serial::put(const int iin){
	stringstream ss;
	serialize(iin,ss);
	serialData += ss.str();

}

void Serial::put(const long lin){
	stringstream ss;
	serialize(lin,ss);
	serialData += ss.str();

}


void Serial::put(const char chin){
	stringstream ss;
	serialize(chin,ss);
	serialData += ss.str();

}

void Serial::put(const string strin){
	stringstream ss;
	serialize(strin,ss);
	serialData += ss.str();

}



void Serial::get(bool &boolout){
	stringstream ss;
	if(this->empty())
		throw string("Object is empty");
	ss << serialData;
	unserialize(ss, boolout);
	serialData = ss.str().substr(ss.tellg());

}

void Serial::get(short &sout){
	stringstream ss;
	if(this->empty())
		throw string("Object is empty"); 
	ss << serialData;
	unserialize(ss, sout);
	if(ss)
		serialData = ss.str().substr(ss.tellg());
	else
		serialData = ""; 
}

void Serial::get(int &iout){
	stringstream ss;
	if(this->empty())
		throw string("Object is empty"); 
	ss << serialData;
	unserialize(ss, iout);
	if(ss)
		serialData = ss.str().substr(ss.tellg());
	else
		serialData = ""; 
}

void Serial::get(long &lout){
	stringstream ss;
	if(this->empty())
		throw string("Object is empty"); 
	ss << serialData;
	unserialize(ss, lout);
	if(ss)
		serialData = ss.str().substr(ss.tellg());
	else
		serialData = ""; 
}


void Serial::get(char &chout){
	stringstream ss;
	if(this->empty())
		throw string("Object is empty"); 
	ss << serialData;
	unserialize(ss, chout);
	if(ss)
		serialData = ss.str().substr(ss.tellg());
	else
		serialData = ""; 
}

void Serial::get(string &strout){
	stringstream ss;
	if(this->empty())
		throw string("Object is empty"); 
	ss << serialData;
	unserialize(ss, strout);
	if(ss)
		serialData = ss.str().substr(ss.tellg());
	else
		serialData = ""; 
}





std::string Serial::str() const{
	return serialData;
}

void Serial::str(string stt){
	serialData = stt;
}

