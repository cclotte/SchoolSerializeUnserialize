#ifndef FSERIAL_H
#define FSERIAL_H

#include <iostream>
#include <string>
#include <istream>
#include <ostream>
#include <fstream>
//#include "Serial.h"




#include <string>
#include <sstream>

class Serial{
	public:
		Serial():serialData(""){};
		Serial(const Serial &ser){
			serialData = ser.str();
		};
		
		//serialize respective type and put serialized string in serialData
		void put(const bool);
		void put(const short);
		void put(const int);
		void put(const long);
		void put(const char);
		void put(const std::string);
		
		//grab respective type from serialData and unserialize. Won't modify serialData if fail so user can try to grab correct type
		void get(bool &);
		void get(short &);
		void get(int &);
		void get(long &);
		void get(char &);
		void get(std::string &);
		
		//get serialData
		std::string str() const;
		
		//set serialData
		void str(std::string);
		
		//get size of serialData
		int size() const{return serialData.length();};
		
		//check if serialData is empty
		bool empty() const{return serialData.empty();};
		
		//swap method for assignment operator
		friend void swap(Serial &first, Serial &second){
			using std::swap;
			
			swap(first.serialData, second.serialData);
		};
		
		//assigns rhs serial to current serial
		Serial& operator=(Serial rhs){
			swap(*this, rhs);
			return *this;	
		};
		
		//serial += thingi
		//same as .put()
		template<typename T>
		Serial &operator+=(const T rhs){ this->put(rhs); return *this;};
		//Serial &operator+=(const short &rhs);
		//Serial &operator+=(const int &rhs);
		//Serial &operator+=(const long &rhs);
		//Serial &operator+=(const char &rhs);
		//Serial &operator+=(const std::string &rhs);
		Serial &operator+=(const Serial rhs){serialData += rhs.str(); return *this;};
		Serial &operator+=(const char* rhs)=delete;
		//serial + thing
		//same as .put()
		template<typename T>	
		Serial operator+(const T rhs){return operator+=(rhs);return *this;};
		//Serial operator+(const short &rhs);
		//Serial operator+(const int &rhs);
		//Serial operator+(const long &rhs);
		//Serial operator+(const char &rhs);
		//Serial operator+(const std::string &rhs);
		Serial operator+(const char* &rhs)=delete;

		//same as .get()
		//template<typename T>
		//Serial &operator<<=(T &rhs){this->get(rhs);return *this;};
//		Serial &operator<<=(const short &rhs);
//		Serial &operator<<=(const int &rhs);
//		Serial &operator<<=(const long &rhs);
//		Serial &operator<<=(const char &rhs);
//		Serial &operator<<=(const std::string &rhs);
		
		friend bool operator==(const Serial lhs, const Serial rhs){ return (lhs.str() == rhs.str());};
		friend bool operator!=(const Serial lhs, const Serial rhs){ return !(lhs.str() == rhs.str());};

		
	private:
		//contains serialized data
		std::string serialData;	
		//here to stop bool from trying to use something like this	
		void get(char* non)=delete;
		void put(char* non)=delete;
};
//********************************************************************************************************************

		//same as .put() 
		//thing + serial = new serial
		template<typename T>
		Serial operator+(T lhs, Serial &rhs){
			Serial ser;
			ser += lhs;
			ser += rhs;
			return ser;
		}
//		Serial operator+(int &lhs, Serial &rhs);
//		Serial operator+(short &lhs, Serial &rhs);
//		Serial operator+(long &lhs, Serial &rhs);
//		Serial operator+(char &lhs, Serial &rhs);
//		Serial operator+(std::string &lhs, Serial &rhs);
//		Serial operator+(Serial &l, Serial &r){
//			Serial ser;
//			ser += l;
//			ser += r;
//			return ser;
//		}
		Serial operator+(char* &lhs, Serial &rhs)=delete;
		//same as .get()
		template<typename T>
		Serial &operator<<=(T &lhs, Serial &rhs){rhs.get(lhs);return rhs;};
//		Serial &operator<<=(const short &rhs);
//		Serial &operator<<=(const int &rhs);
//		Serial &operator<<=(const long &rhs);
//		Serial &operator<<=(const char &rhs);
//		Serial &operator<<=(const std::string &rhs);
		//std::ostream& operator<<(std::ostream& os, Serial ser){
		//	std::string temp = ser.str();	
		//	os << temp;
		//	return os;
		//}		

class IFSerial{
	public:
		IFSerial(std::string filename) {
			file.open(filename, std::ifstream::binary);
			if(!file)
				failure = true;
			std::string content((std::istreambuf_iterator<char>(file)),(std::istreambuf_iterator<char>())); 
			ser.str(content);
		};
		IFSerial& operator>>(bool &rhs);
		IFSerial& operator>>(short &rhs);
		IFSerial& operator>>(int &rhs);
		IFSerial& operator>>(long &rhs);
		IFSerial& operator>>(char &rhs);
		IFSerial& operator>>(std::string &rhs);
		bool eof() const;
		bool fail() const;
		//bool operator!() const;
		explicit operator bool() const{
			return (failure || eofbit);
		}
		std::string getstream() const;
		
		~IFSerial(){
			file.close();
		}
		
		IFSerial& operator>>(const char* &rhs) = delete;

	private: 
		std::ifstream file;
		Serial ser;
		bool failure = 0;
		bool eofbit = 0;
		

}; 

class OFSerial{
	public:
		OFSerial(std::string filename){
			file.open(filename,std::ofstream::binary);
			if(!file)
				failure = 0;
		
		};
		OFSerial& operator<<(const bool rhs);
		OFSerial& operator<<(const short rhs);
		OFSerial& operator<<(const int rhs);
		OFSerial& operator<<(const long rhs);
		OFSerial& operator<<(const char rhs);
		OFSerial& operator<<(const std::string rhs);
		bool eof() const;
		bool fail() const {return failure;}; 
		OFSerial& operator<<(const char* &rhs) = delete;
		explicit operator bool() const{
			return (failure || eofbit);
		}
	private: 
		std::ofstream file;
		bool failure;
		bool eofbit;
		Serial ser;
		


};

#endif
