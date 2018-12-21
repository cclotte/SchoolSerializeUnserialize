#ifndef HW2_H
#define HW2_H

#include <iostream>
#include <vector>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <fstream>
#include <limits>
#include <regex>
class hw2 {

	public:
		std::string gfilepath;
		std::vector<std::string> gfiles;
		std::string gPname;
		std::vector<std::vector<int>> serializedThings;
		
		hw2(){}
		hw2(std::string _filepath):gfilepath(_filepath){gfiles.push_back(_filepath);};
		hw2(std::vector<std::string> filepaths):gfiles(filepaths){};
		 
		int set_v();//{verbose = 1; return 0;}
		int twos_complement(std::vector<int> &number);
		int pad_bits(std::vector<int> &number, bool negative);
		std::vector<int> to_vector_binary(long &number);
		std::vector<int> serialize_string(std::string &str);
		std::vector<int> serialize_char(char &ch);
		int append_length(std::vector<int> &number);
		std::vector<int> make_vnum_vector(long &number);
		long get_num(std::vector<int> &number);
		std::vector<int> to_hex_array(const std::vector<int> &number) const;
		int add_string_length(std::vector<int> &number);
		int add_tag(std::vector<int> &number, char tag);
		std::vector<int> make_tagged_number(long number, char tag);
		std::vector<int> make_tagged_string(std::string str);
		std::vector<int> make_tagged_char(char ch);
		int printnonhexvec(std::vector<int> vec);
		std::vector<std::vector<int>> process_files();
		int test1();
		int testVnum();

	private:
		bool verbose;
};

std::ostream &operator<<(std::ostream &stream, const hw2 h);
#endif
		
