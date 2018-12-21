/* hw2.cc
 * Tyler Engle
 * 1/25/2017
 * CS253
 */
#include "hw2.h"
typedef std::vector<int>::iterator int_vector_iterator;
//converts to a twos complement binary number
//input: vector<int> containing the positive binary number
//Modifies: the vector<int> passed to it
//Output: irrelevant
int hw2::twos_complement(std::vector<int> &number){
	//nots the bits
	for(unsigned int i = 0; i < number.size(); i++){
		if(number[i] == 0)
			number[i] = 1;
		else
			number[i] = 0;
	}
	//add 1
	for(unsigned int j = number.size()-1; j > 0 ; j--){
		if(number[j] != 0){
			number[j] = 0;
		}else if(number[j] == 0){
			number[j] = 1;
			return 0;
		}else{
			number.insert(number.begin(),1);
		}
	}
return 0;
}











//pads the number so its bit length is 8n, where n is the number of bytes needed
//input: vector<int> containing the serialized number, boolean that says if it's negative or not
//modifies: binary int vector passed to it
int hw2::pad_bits(std::vector<int> &number, bool negative){
	if(number.size() <= 3){
		while(number.size() < 4){
			number.insert(number.begin(),0);	
		}
	}else{
		unsigned int size = 4-(number.size() % 4);
//		cout << size << '\n';	
		for(unsigned int i = 0; i < size; i++){	
			number.insert(number.begin(),0);
		}
		if(size == 0 && negative){	
			number.insert(number.begin(),0);		
			number.insert(number.begin(),0);		
			number.insert(number.begin(),0);		
			number.insert(number.begin(),0);		
		}
	}
	while((number.size()+4)%8 != 0){
		number.insert(number.begin(),0);
	}
		
	
return 0;
}











//converts int to twos complement binary number with with length 8n where n is the number of bytes of form bn...b0
//where bn is the most significant bit and b0 is the first bit
//This is held in a vector
//Input: integer number to convert
//Modifies: nothing
//Output: Vector containing binary number
std::vector<int> hw2::to_vector_binary(long &number){
	long to_convert = number;
	//std::vector<int>::iterator int_Vec_Iterator = binary_number.begin()
	std::vector<int> binary_number = {};
	bool negative = 0;
	//check if is negative
	if(to_convert == std::numeric_limits<long>::min()){
		to_convert++;
	}
	if(to_convert<0){
		negative = 1;
		to_convert *= -1;
	}
	int bit = 0;
	//converts number to binary
	while(to_convert>1){
		bit = to_convert % 2;
		to_convert /= 2;
		binary_number.insert(binary_number.begin(),bit);
				
	}
	binary_number.insert(binary_number.begin(),to_convert);
	pad_bits(binary_number, negative);	

	if(negative){
		twos_complement(binary_number);
	
	}
	
	if(number == std::numeric_limits<long>::min()){
		binary_number[binary_number.size()-1]=0;
	}
	return binary_number;
}










//serializes a string
//vector<int> to_vector_binary(string &str){
//	cout << "begin method";
//	string to_convert = str;
//	vector<int> binary_number;
//	int current =0;
//	int bit = 0;
//	cout << "before loop";
//	for(auto ch : to_convert){
//		current = ch;
//		
//		while(current>1){
//			bit = current%2;
//			current = current/2;
//			binary_number.insert(binary_number.begin(),bit);
//		}
//	cout << "\n insertion"<<endl;
//	binary_number.insert(binary_number.begin(),current);
//	
//	}
//	
	//cout<<binary_number[0];	
	//pad_bits(binary_number,0);	
//
//	return binary_number;
//}









//turns the string into a binary vector in the form bn...b0
//input: string to serialize
//returns: vector<int> containing the serialized string
std::vector<int> hw2::serialize_string(std::string &str){
//	int piece = 0;
	std::vector<int> bit_vector;
	for(std::string::iterator iter = str.begin(); iter != str.end(); ++iter){
		std::bitset<8> bits(*iter);
//		cout << bits << '\n';
	   	for(int i = 7; i >=0 ;i-=1){
			bit_vector.push_back(bits[i]);		
//			cout << bits[i];
		//	cout << *(bit_vector.end());	
		}
//		 cout<< '\n';
		}
	//	for(unsigned int j = 0; j < bit_vector.size(); j++){
	//		cout << bit_vector[j];
	//	}
	 
	
	return bit_vector;	
}






//serializes a character
//input: character to serialize
//output: vector<int> containing serialized character
std::vector<int> hw2::serialize_char(char &ch){
	std::string temp;
	temp += ch;   
	return serialize_string(temp);
}













//adds the vnum byte length to a binary vector
//input: binary vector
//modifies: passed vector
int hw2::append_length(std::vector<int> &number){
	int length = 0;
	
//	while((number.size()+4) % 8 != 0){
//		number.insert(number.begin(),0);
//	}

//	if(number.size()/8 <=1){
//		length = 0;
//	}else
	length += ceil(number.size()/8);
	int mask = 1;
	bool insert = 0;
	if(number.size() % 8 == 0){
		for(int i = 0; i<4; i++)
			number.insert(number.begin(),0);
	}
	for(int i = 0; i < 4; i++){
		insert = (mask & length) != 0;
		number.insert(number.begin(),insert);
		mask = mask << 1;
	}
	
//	while(number.size() % 8 != 0){
//		number.insert(number.begin(),0);
//	}
	
return 0;	
}










//converts an int to a vnum held in a vector
//input: integer number to convert
//Modifies: nothing
//Output: returns vector containing binary number of length 8n+4 where n is number of bytes-1
std::vector<int> hw2::make_vnum_vector(long &number){
	std::vector<int> to_convert = to_vector_binary(number);
	append_length(to_convert);
	return to_convert;
}











//Converts the vector to a long
//input: int vector containing binary number
//output: number of type long
long hw2::get_num(std::vector<int> &number){
	long mask = 0;
	long num = 0;
	
	for(unsigned int i = number.size()-1; i > 0; i=i-1){
		num |= number[i] << mask;
		mask++;
	}
	num |= number[0] << mask;
	return num;

}









//converts binary vector to hex vector (each index is 4 bits ie a hex number)
//input: the vector containing the vnum in binary
//output: vector containing the vnum in hex
std::vector<int> hw2::to_hex_array(const std::vector<int> &number) const {
	std::vector<int> hex_array;
//	int_vector_iterator vecit = number.begin();
	unsigned int count = 0;
	int hex_place = 0;
	while(count < number.size()){
		std::vector<int> bit_hex_array(4);
		for(int i = 0; i < 4;i++){
			//cout<<bit_hex_array[i];
			bit_hex_array[i] = number[count];  
			count=count + 1;		
		}
		//cout <<'\n';
		int shifted_bit = 0;
		int shifter = 3;
		hex_array.push_back(0);
		for(int index = 0; index < 4; index++){
			shifted_bit = bit_hex_array[index];
			shifted_bit = shifted_bit << shifter;
			hex_array[hex_place] += shifted_bit;
			shifter -=1;
		}
	//	if(count>3)
	//		exit(1);
		hex_place+=1;
		
			
	}
	return hex_array;

}







//takes in a serialized string and attaches a vnum length to the front
//input: serialized string in vector format
//modifies: passed serialized string in vector format
int hw2::add_string_length(std::vector<int> &number){
//	int size = number.size();
//	size /= floor(8);
//	size = 1;
//	cout << "\nsize is " << size << '\n';
//	vector<int> bit_size = make_vnum_vector(size);
//	cout << "binary size: ";
//	for(unsigned int in = bit_size.size(); in > 0; in-=1){
//		cout << bit_size[in];	
//		number.insert(number.begin(), bit_size[in]);
//	}
//	number.insert(number.begin(), bit_size[0]); 
	long size = number.size();
	size /=8;
//	cout<< "\nSize: " << size << '\n';
	std::vector<int> vnum_size = make_vnum_vector(size);
	for(unsigned int k = vnum_size.size()-1;k>0;k-=1){
//		cout << vnum_size[k];
		number.insert(number.begin(),vnum_size[k]);
	}
//	cout << '\n';
	number.insert(number.begin(), vnum_size[0]);
//	for(auto m : number){
//		cout << m;
//	}
	return 0;
}







//adds tag to serialized number or string
//input: serialized number with length added
//output: char representing type 
//s: short
//i: int
//l: long
//c: char
//S: string
int hw2::add_tag(std::vector<int> &number, char tag){
	std::vector<int> temp = serialize_char(tag);
	for(unsigned int i = temp.size()-1;i>0;i-=1){
		//cout<<temp[i];
		number.insert(number.begin(),temp[i]);
	}
	number.insert(number.begin(),temp[0]);
	
	return 0;
}



//makes a tagged number 
//input: number to make, tag to give it
//output: returns tagged number
std::vector<int> hw2::make_tagged_number(long number, char tag){
	std::vector<int> taggedNum = to_vector_binary(number);
	append_length(taggedNum);	
	add_tag(taggedNum,tag);
	return taggedNum;
}

//makes a tagged string 
//input: string to make
//output: tagged string in vector<int> form
//Output form: <tag><length vnum><serialized string>
std::vector<int> hw2::make_tagged_string(std::string str){
	std::vector<int> taggedStr = serialize_string(str);
	add_string_length(taggedStr);
	add_tag(taggedStr, 'S');
	return taggedStr;
}

//makes a tagged char 
//input: char to make
//output: tagged char in vector<int> form
//Output form: <tag><length vnum><serialized char>
std::vector<int> hw2::make_tagged_char(char ch){
	std::vector<int> taggedChar = serialize_char(ch);
	add_tag(taggedChar, 'c');
	return taggedChar;
}
int hw2::printnonhexvec(std::vector<int> vec){
	std::vector<int> hexer;
	hexer = to_hex_array(vec);
	int count = 0;
	for(auto i : hexer){
		std::cout<< std::hex << i;
		if(count == 1){
			std::cout<<" ";
			count = 0;
		}else
			count = 1;			
	}

return 0;
}

//takes file and processes it
//input: input arguments (currently only takes file path);
//output: returns a vector of vector<int> containing the tagged strings, chars and numbers 
std::vector<std::vector<int>> hw2::process_files(){
	std::ifstream in;
	int numArguments = gfiles.size();
	std::string path;
	std::vector<std::vector<int>> processedArguments;
	for(int i = 0; i<numArguments;i++){//loop for going through multiple files
		path = gfiles[i];
		
		if(verbose){
			std::cerr << "Processing file " << path << '\n';
		}

		in.open(path);
		
		
		long longy;
		char chary;
		bool processing = 0;

		while(in.get(chary)){//file processor
			std::string quicktest;
			std::string stringy = "";	
			std::vector<int> number;
			std::vector<int> stri;
			quicktest +=chary;
			
		//	if(std::regex_match(quicktest,std::regex("[a-zA-Z]"))){
		//		std::cerr << '\n' << program_name <<  ": no quotes or double quotes around \'" << chary << "\'\n";
		//		std::exit(1);
		//	}
			if(!processing){
				if(chary == ' ' || chary == '\n' || chary == '\t'){
					continue;	
				}
			}
			
			if(chary == 't' || chary == 'f'){
				std::string booltest;
				in.unget();
				//int term;
				//if(chary == 't')
				//	term = 4;
				//else
				//	term = 5;
				in >> booltest;	
						
				//for(int i = 0; i < term; i++){			
				//	booltest += chary;					
				//	in.get(chary);
				//}
				
				char boolthing;
				if(booltest == "true"){
					boolthing = 't';
				}else if(booltest == "false"){
					boolthing = 'f';
				}
				
				stri.push_back(boolthing);
				stri = serialize_char(boolthing);
				processedArguments.push_back(stri);
				stri.clear();
				continue;
			}
			
			if(chary == '\"'){ //process string
				in.get(chary);
				
				while(chary != '\"'){
					
					stringy += chary;
					in.get(chary);
				}
				stri = make_tagged_string(stringy);
				processedArguments.push_back(stri);
				stri.clear();
				continue;	
					
			}
			if(chary == '\''){ //process char
				in.get(chary);
				stri = make_tagged_char(chary);
				processedArguments.push_back(stri);
				in.get(chary);
				stri.clear();
				continue;
				
					
			}
			in.unget();	
			if(in >> longy){//process numbers
				char tag;
				if(longy >= std::numeric_limits<short>::min()  && longy <=  std::numeric_limits<short>::max())
					tag = 's';
				else if(longy >= std::numeric_limits<int>::min() && longy <= std::numeric_limits<int>::max())
					tag = 'i';
				else if(longy >= std::numeric_limits<long>::min() && longy <= std::numeric_limits<long>::max())
					tag = 'l';
				else{
					
				}
				number = make_tagged_number(longy,tag);
				processedArguments.push_back(number);
			}
		}

		in.close();		
	}
	serializedThings.swap(processedArguments);
	//TODO put in member var	
	return processedArguments;
}


int hw2::set_v(){
	verbose = 1;
	return 0;
}


std::ostream &operator<<(std::ostream &stream, const hw2 h){
	int count = 0;
	for(auto i :h.serializedThings){
		std::vector<int> hexer = h.to_hex_array(i);
		for(auto mm : hexer){	 
			stream << std::hex << mm;
			if(count == 1){
				stream<<" ";
				count = 0;
			}else
				count = 1;			
		}
		std::cout<< '\n';
	}
	return stream;

	
}
//tests to_hex_array, serialize_string, add_string_length, add_tag for string
int hw2::test1(){
	std::cout << "\n\nto_hex_array test\n" << "should be abcd || Result: ";
	std::vector<int> test(16);
	test[0] = 1;
	test[1] = 0;
	test[2] = 1;
	test[3] = 0;
	test[4] = 1;
	test[5] = 0;
	test[6] = 1;
	test[7] = 1;
	test[8] = 1;
	test[9] = 1;
	test[10] = 0;
	test[11] = 0;
	test[12] = 1;
	test[13] = 1;
	test[14] = 0;
	test[15] = 1;
	
	test = to_hex_array(test);
	std::cout << std::hex << test[0] << test[1] << test[2] << test[3] << '\n';
		
	std::string testString = "Jack Applin";
//	cout << "String made" << endl;	
	std::vector<int> stringVecTest;
	stringVecTest = serialize_string(testString);
	for(unsigned int i = 0; i<stringVecTest.size();i++){
		std::cout << stringVecTest[i];
	}
	std::vector<int> stringHexVec;
	stringHexVec = to_hex_array(stringVecTest);
	std::cout << '\n';		
	for(unsigned int pr = 0; pr < stringHexVec.size(); pr++ ){
		std::cout << stringHexVec[pr];
	}
	std::cout<<'\n';
	std::cout << "\n\nAdd vnum size test\n"<< "Number before adding length\n";
	for(unsigned int pr = 0; pr < stringHexVec.size(); pr++ ){
		std::cout << stringHexVec[pr];
	}
	
	add_string_length(stringVecTest);
	stringHexVec = to_hex_array(stringVecTest);
	std::cout << "\nAdded Size\n should be: 10 0b || Is: " << std::setfill('0') << stringHexVec[0] << stringHexVec[1] <<" " << stringHexVec[2] << stringHexVec[3] <<'\n';
	for(unsigned int pr = 0; pr < stringHexVec.size(); pr++ ){
		std::cout << stringHexVec[pr];
	}
	
	std::cout << "\nTesting tag adder\n" << "Adding s\n Should be 73 || Result: ";
	add_tag(stringVecTest, 'S');
	stringHexVec = to_hex_array(stringVecTest);
	std::cout << stringHexVec[0] << stringHexVec[1] << '\n';
	for(unsigned int pr = 0; pr < stringHexVec.size(); pr++ ){
		std::cout << stringHexVec[pr];
	}
		

	
	return 0;
}


//tests making a vnum exclusively
int hw2::testVnum(){
	std::cout<<"\nVnum Test\n";
	long testNumber = 1;
	std::cout<<"testing " << testNumber << ": ";
	std::vector<int> vnum = make_vnum_vector(testNumber);
	std::vector<int> vnumHex = to_hex_array(vnum);
	for(auto j : vnum){
		std::cout << j;
	}
	std::cout << '\n';
	for(auto i : vnumHex){
		std::cout << std::hex << i;
	}
	std::cout << "\ntest complete";
	return 0;
	
	
}
//TODO write output operator method

//int main(int argc, char **argv){
//	testVnum();
//	test1();
//	std::vector<std::vector<int>> numbers = process_input(argc,argv);
//	cout<< "\nsuccessfully parsed input\n";
//	std::vector<int> hexer;
//	for(std::vector<int> thing : numbers){
//		hexer = to_hex_array(thing);
//		bool count = 0;	
//		for(auto i : hexer){
//			std::cout<< std::hex << i;
//			if(count == 1){
//				std::cout<<" ";
//				count = 0;
//			}else
//				count = 1;			
//		}
//		std::cout << '\n';	
//	}
//	return 0;
//}



