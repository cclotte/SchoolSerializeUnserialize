#include "FSerial.h"
OFSerial& OFSerial::operator<<(const bool rhs){
	ser.put(rhs);
	file << ser.str();
	bool temp;
	ser.get(temp);
	return *this;	


}

OFSerial& OFSerial::operator<<(const short rhs){
	ser.put(rhs);
	file << ser.str();
	short temp;
	ser.get(temp);

	return *this;	


}

OFSerial& OFSerial::operator<<(const int rhs){
	ser.put(rhs);
	file << ser.str();
	int temp;
	ser.get(temp);

	return *this;	


}

OFSerial& OFSerial::operator<<(const long rhs){
	ser.put(rhs);
	file << ser.str();
	long temp;
	ser.get(temp);
	return *this;	


}

OFSerial& OFSerial::operator<<(const char rhs){
	ser.put(rhs);
	file << ser.str();
	char temp;
	ser.get(temp);
	return *this;	


}

OFSerial& OFSerial::operator<<(const std::string rhs){
	ser.put(rhs);
	file << ser.str();
	std::string temp;
	ser.get(temp);
	return *this;	


}
