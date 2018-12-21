#include "functions.h"
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include "hw2.h"



using namespace std;
int get_number_of_bytes(const string &str); 
int get_length(const string &str);

void serialize(bool b, std::ostream &stream){
	if(!b){
		stream << 'f';
	}else
		stream << 't';
}

void serialize(short s, std::ostream &stream){


	hw2 serializer;
	char tag = 's';
	vector<int> binary = serializer.make_tagged_number(s,tag);
	stringstream ss;
	for(int i: binary){
		ss << i;
	}
	bitset<32> bset(ss.str());
	int num = int(long(bset.to_ulong()));
	ss.str("");
	ss.write(reinterpret_cast<const char*>(&num), int(4));
	string tempy = ss.str();
	reverse(tempy.begin(), tempy.end());
	char cc = tempy[0];
	int counter = 0;
	while(cc == '\x00'){
		++counter;
		cc = tempy[counter];
	}
	tempy.erase(0,counter);
	stream << tempy;  
}

void serialize(int i, std::ostream &stream){


	hw2 serializer;
	char tag = 'i';
	vector<int> binary = serializer.make_tagged_number(i,tag);
	
	stringstream ss;
	for(int i: binary){
		ss << i;
	}
	bitset<64> bset(ss.str());
	long num = long(bset.to_ulong());
	ss.str("");
	ss.write(reinterpret_cast<const char*>(&num), int(8));
	string tempy = ss.str();
	reverse(tempy.begin(), tempy.end());
	char cc = tempy[0];
	int counter = 0;
	while(cc == '\x00'){
		++counter;
		cc = tempy[counter];
	}
	tempy.erase(0,counter);
	stream << tempy;  
}

void serialize(long l, std::ostream &stream){


	hw2 serializer;
	char tag = 'l';
	vector<int> binary = serializer.make_tagged_number(l,tag);
	
	stringstream ss;
	string tempy;
//add tag and length to tempy first
	binary.erase(binary.begin(),binary.begin()+8); //erase tag from binary;
	//put length in
	int blength = binary.size();
	if(blength>64){
		string slength = "";
		for(int i = 0; i < 8; i++){
			int one = binary[i];
			if(one == 1)	
				slength+='1';
			else if(one ==0)
				slength+='0';

		}
		//slength += "0000";
		bitset<8> bslength(slength);
		int lengthy = int(bslength.to_ulong());
		binary.erase(binary.begin(),binary.begin()+8);
		ss.write(reinterpret_cast<const char*>(&lengthy),int(1));
		tempy = "";
		tempy += ss.str();
		reverse(tempy.begin(),tempy.end());
		 	
			
	}
	stream << tag;	
	stream << tempy;
	ss.str("");
	for(int i: binary){
		ss << i;
	}
	bitset<64> bset(ss.str());
	long num = long(bset.to_ulong());
	ss.str("");
	ss.write(reinterpret_cast<const char*>(&num), int(8));
	tempy = ss.str();
	reverse(tempy.begin(), tempy.end());
	char cc = tempy[0];
	int counter = 0;
	while(cc == '\x00'){
		++counter;
		cc = tempy[counter];
	}
	tempy.erase(0,counter);
	stream << tempy;  
}

void serialize(char c, std::ostream &stream){
	//hw2 serializer;
	//vector<int> ser = serializer.make_tagged_char();
	//stringstream ss;
	//for(int i: ser){
	//	ss<<i;
	//}
	//string tempy = ss.str();
	//bitset<16> bset(tempy);
	//int num = int(bset.to_ulong());
	char tag = 'c';
	stream << tag;
	stream << c;
		


}

void serialize(const std::string &str, std::ostream &stream){
	string mystring = str;
	hw2 serializer;
	vector<int> strser = serializer.make_tagged_string(mystring);
	char tag = 'S';
	strser.erase(strser.begin(), strser.begin()+8);
	string svlength = "";
	for(int i = 0; i<4;i++){
		if(strser[i] == 1)
			svlength += '1';
		else
			svlength += '0';
		
	}
	bitset<4> sbsv(svlength);
	int vlength = int(sbsv.to_ulong());
	//use vlength to get length of string
	short iterlength = 8;
	bool vlengthZero = 0;
	if(vlength == 0){
		vlength = 1;
		iterlength = 4;
		vlengthZero = 1;
		
		
	}
	int tempi = 0;
	stringstream ss;
	string mything = "";
	string numlength = "";
	while(tempi < vlength){
		for(int i = 0; i < iterlength; i++){	
			if(strser[(i+iterlength)] == 1)
				mything += '1';
			else
				mything += '0';

		
		}
		++tempi;	
	}
	if(vlengthZero ==1)
		vlength = 0;
	bitset<64> mybs(mything);
	int strlength = int(mybs.to_ulong());
	//skip over vnum and throw in string
	stream << tag;
	ss.write(reinterpret_cast<const char*>(&strlength), int(4));
	string tempy = "";
	tempy = ss.str();
	reverse(tempy.begin(), tempy.end());
	char cc = tempy[0];
	int counter = 0;
	while(cc == '\x00'){
		++counter;
		cc = tempy[counter];
	}
	tempy.erase(0,counter);
	//add vnum length
	vlength <<=4;
	ss.str("");
	ss.write(reinterpret_cast<const char*>(&vlength), int(4));
	string tempv = "";
	tempv = ss.str();
	reverse(tempv.begin(), tempv.end());
	char ccv = tempv[0];
	int counterv = 0;
	while(ccv == '\x00'){
		++counterv;
		ccv = tempv[counterv];
	}
	tempv.erase(0,counterv);
	stream << tempv;
	stream << tempy;  
	stream << str;

}
void unserialize(std::istream &stream, bool &b){
	char current;
	stream.get(current);
	if(current == '\x74'){
		b = 1;
	}else if(current == '\x66'){
		b = 0;
	}else{
		throw string(current + " is not a valid boolean");
	}

}

void unserialize(std::istream &stream, short &s){
	string tag;
	char temp;
	stream.get(temp);
	tag = temp;
	short num = 0;
	if(tag != "s"){
		string error;
		error += tag;
		error += string(" is not a valid tag for short");
		throw error;	
	}else{
		//char length;
		//stream.get(length);
		//need to get length then grab number and convert to readable
		string number;
		stream.get(temp);
		int lmask = 0xf0;
		int length = lmask & temp;	
		length >>= 4;
		bool neg = 0;
		int negmask = 8;
		int negg = negmask & temp;
		if(negg != 0)
			neg = 1;
		int x0fmask = 0x0f;
		temp &= x0fmask;
		
		if(neg){
			int f0mask = 0xf0;
			int x0fmask = 0x0f;
			temp &= x0fmask;
			temp |= f0mask;	
		}
		//convert to number
		string snum = "";   
		for(int i = length; i>=0; i--){
		
			if(stream.fail() | stream.bad())
				throw string("ran out of bytes to process at " + temp);
		//	stream.unget();
			bitset<8> bs8(temp);
			snum += bs8.to_string();	
			stream.get(temp);
				
		}
		stream.unget();
		if(neg){
			while(snum.length() < 16){
				snum.insert(snum.begin(),char('1'));
			}

		}	
		bitset<64> bsnum(snum);
		num = short(int(long(bsnum.to_ulong())));
	}
	
	s = num;	
	 	

}
void unserialize(std::istream &stream, int &i){
	string tag;
	char temp;
	stream.get(temp);
	tag = temp;
	int num = 0;
	signed int sint = 0;
	if(tag != "i"){
		string error;
		error += tag;
		error += string(" is not a valid tag for i");
		throw error;	
	}else{
		//char length;
		//stream.get(length);
		//need to get length then grab number and convert to readable
		string number;
		stream.get(temp);
		int lmask = 0xf0;
		int length = lmask & temp;	
		length >>= 4;
		bool neg = 0;
		int negmask = 8;
		int negg = negmask & temp;
		if(negg != 0)
			neg = 1;
		int x0fmask = 0x0f;
		temp &= x0fmask;
		
		if(neg){
			int f0mask = 0xf0;
			int x0fmask = 0x0f;
			temp &= x0fmask;
			temp |= f0mask;	
		}
		//convert to number
		string snum = "";   
		for(int i = length; i>=0; i--){
			if(stream.fail() | stream.bad())
				throw string("ran out of bytes to process ");
			bitset<8> bs8(temp);
			snum += bs8.to_string();	
			stream.get(temp);
				
				
		}
		stream.unget();
		if(neg){
			while(snum.length() < 32){
				snum.insert(snum.begin(),char('1'));
			}

		}	
		bitset<64> bsnum(snum);
		num = int(long(bsnum.to_ulong()));
		sint = num;
	}
	
	i = sint;	
	 	

}
void unserialize(std::istream &stream, long &l){
	string tag;
	char temp;
	stream.get(temp);
	tag = temp;
	long num = 0;
	if(tag != "l"){
		string error;
		error += tag;
		error += string(" is not a valid tag for long");
		throw error;	
	}else{
		//char length;
		//stream.get(length);
		//need to get length then grab number and convert to readable
		string number;
		stream.get(temp);
		int lmask = 0xf0;
		int length = lmask & temp;	
		length >>= 4;
		bool neg = 0;
		int negmask = 8;
		int negg = negmask & temp;
		if(negg != 0)
			neg = 1;
		int x0fmask = 0x0f;
		temp &= x0fmask;
		
		if(neg){
			int f0mask = 0xf0;
			int x0fmask = 0x0f;
			temp &= x0fmask;
			temp |= f0mask;	
		}
		//convert to number
		string snum = "";   
		for(int i = length; i>=0; i--){
		
			if(stream.fail() | stream.bad())
				throw string("ran out of bytes to process at ");
		//	stream.unget();
			bitset<8> bs8(temp);
			snum += bs8.to_string();	
			stream.get(temp);
				
		}
		stream.unget();
		if(neg){
			while(snum.length() < 64){
				snum.insert(snum.begin(),char('1'));
			}

		}
		if(snum.length() > 64){
			while(snum.length() > 64){
				snum.erase(snum.begin());

			}
		}	
		bitset<64> bsnum(snum);
		num = long(bsnum.to_ulong());
	}
	
	l = num;	
	 	

}
void unserialize(std::istream &stream, char &c){
	char cc;
	stream.get(cc);
	if(cc != 'c')
		throw string(cc + " is not a valid tag for character");
	
	if(!stream.get(c))
		throw string("ran out of bytes to parse. No character?");

}

void unserialize(std::istream &stream, std::string &str){
	char tag;
	stream.get(tag);
	if(tag != 'S')
		throw string(tag + " is not a valid tag for string");
	stringstream ss;
	char cc;
	stream.get(cc);
	int lmask = 0xf0;
	int vlen = lmask & cc;
	vlen >>=4;
	ss << string("i");
	ss << cc;
	for(int i = vlen; i > 0; i--){
		stream.get(cc);
		if(stream.bad() | stream.fail())
			throw string("ran out of bytes to parse. Invalid length?");
		ss << cc;
		
	}
	//get number
	int lenv = 0;
	unserialize(ss,lenv);
	string temps = "";
	while(lenv>0){
		stream.get(cc);
		if(stream.bad() | stream.fail())
			throw string("ran out of bytes to parse. Invalid length?");
		temps +=cc;
		--lenv;

	}
	

	str = temps;



}
//gets number of bytes and 
int get_number_of_bytes(const string &str){
	char temp = str[0];
	int counter = 0;
	int length = str.length();
	while(temp == '\x00'){
		if(str[counter+1] < 8)
			--length;
		++counter;
		temp = str[counter];	
	}
	
	
	return (length);
}

int get_length(const string &str){
	char temp = str[1];
	int mask = 0x11110000;
	int length = mask | temp;
	return length;

}
