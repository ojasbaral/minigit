#include <gtest/gtest.h>
#include "test_helpers.hpp"
#include <sstream>
#include "../code_1/hash.hpp"


std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string readFileIntoString(std::string fileName){
	std::string line, out;
  	ifstream A;
  	A.open(fileName);
  	if(!A){throw std::runtime_error("could not open file: " + fileName);}
	while(getline(A,line)){
		out = out+line+"\n";
	}
	return out;
}

string test_insert(string arr[], int len, int tabSize)
{
    
    testing::internal::CaptureStdout();
    HashTable* ht = new HashTable(tabSize);
    
    for(int i=0;i<len;i++)
    {
        stringstream s(arr[i]);
        string temp;
        while(getline(s, temp, ' ')){
        ht->insertItem(temp,i);
        }

        if(arr[i]==""){
            ht->insertItem("", i);
        }
    }
    
    ht->printTable();
    string output = testing::internal::GetCapturedStdout();
    return output;
}