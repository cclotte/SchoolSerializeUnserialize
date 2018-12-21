#include "FSerial.h"

IFSerial& IFSerial::operator>>(bool &rhs){
	
	if(ser.empty())
		eofbit = true;	
	try{
	ser.get(rhs);
	}catch(std::string){
		failure = true;
		
	}
	return *this;

}
IFSerial& IFSerial::operator>>(short &rhs){
	
	if(ser.empty())
		eofbit = true;
	
	try{
	ser.get(rhs);
	}catch(std::string){
		failure = true;
		
	}
	return *this;

}
IFSerial& IFSerial::operator>>(int &rhs){
	
	if(ser.empty())
		eofbit = true;	
	try{
	ser.get(rhs);
	}catch(std::string){
		failure = true;
		
	}
	return *this;

}
IFSerial& IFSerial::operator>>(long &rhs){
	
	if(ser.empty())
		eofbit = true;	
	try{
	ser.get(rhs);
	}catch(std::string){
		failure = true;
		
	}
	return *this;

}
IFSerial& IFSerial::operator>>(char &rhs){
	if(ser.empty())
		eofbit = true;	
	try{
	ser.get(rhs);
	}catch(std::string){
		failure = true;
		
	}
	return *this;

}
IFSerial& IFSerial::operator>>(std::string &rhs){
	
	try{
	ser.get(rhs);
	}catch(std::string){
		failure = true;
		
	}
	return *this;

}

bool IFSerial::eof() const{
	return eofbit;
}

bool IFSerial::fail() const{
	return failure;
}

//bool IFSerial::operator!() const{
//	return !(eofbit == true || failure == true);
//}

std::string IFSerial::getstream() const{
	return ser.str();
}
