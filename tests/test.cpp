// If you change anything in this file, your changes will be ignored 
// in your homework submission.
// Chekout TEST_F functions bellow to learn what is being tested.
#include <gtest/gtest.h>
#include "../code_1/hash.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>
#include <array>
#include <vector>
#include "test_helpers.hpp"

using namespace std;

class test_x : public ::testing::Test {
protected:
	// This function runs only once before any TEST_F function
	static void SetUpTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)0;
			outgrade.close();
		}
	}

	// This function runs after all TEST_F functions have been executed
	static void TearDownTestCase(){
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
			std::cout << "Total Grade is : " << (int)std::ceil(100*total_grade/max_grade) << std::endl;
		}
	}

	void add_points_to_grade(double points){
		if(!::testing::Test::HasFailure()){
			total_grade += points;
		}
	}

	// this function runs before every TEST_F function
	void SetUp() override {}

	// this function runs after every TEST_F function
	void TearDown() override {
		std::ofstream outgrade("./total_grade.txt");
		if(outgrade.is_open()){
			outgrade.clear();
			outgrade << (int)std::ceil(100*total_grade/max_grade);
			outgrade.close();
		}
	}
	
	static double total_grade;
	static double max_grade;
};

double test_x::total_grade = 0;
double test_x::max_grade = 100;



/////////////////////////////////////////
// Tests start here
/////////////////////////////////////////

TEST_F(test_x, TestInsert){
    
    
    string result;
    string expected;
       
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    
    result = test_insert(commits, len, tabSize);
    
    expected = "0|| science(1,4,)\n1|| \n2|| \n3|| \n4|| difficult(3,)-->fun(2,)-->computer(0,)\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(10);

	len = 5;

	string commitsTwo[] = {"first function done", "second function partially done", "halfway complete", "almost there", "completed"};
	result = test_insert(commitsTwo, len, tabSize);

	expected = "0|| function(0,1,)\n1|| there(3,)-->almost(3,)-->second(1,)\n2|| completed(4,)-->complete(2,)-->done(0,1,)-->first(0,)\n3|| halfway(2,)-->partially(1,)\n4|| \n";

	ASSERT_EQ(expected, result);
    add_points_to_grade(20);

	len = 3;

	string commitsThree[] = {"adding an empty string", "should produce an error message", ""};

	result = test_insert(commitsThree, len, tabSize);

	expected = "You must have a commit message.\n0|| (2,)-->should(1,)-->adding(0,)\n1|| message(1,)\n2|| an(0,1,)\n3|| string(0,)\n4|| error(1,)-->produce(1,)-->empty(0,)\n";

	ASSERT_EQ(expected, result);
    add_points_to_grade(20);
	

}

TEST_F(test_x, TestSearch){
	string result;
    string expected;
       
    int len = 5;
    
    string commits[] = {"computer", "science", "fun", "difficult", "science"};
    int tabSize = 5;
    
    result = test_search(commits, len, tabSize, "fun");
    
    expected = "The commit numbers containing the word \"fun\" are: 2\n";
    
    ASSERT_EQ(expected, result);
    add_points_to_grade(20);

	
	len = 5;

	string commitsTwo[] = {"first function done", "second function partially done", "halfway complete", "almost there", "completed"};
	result = test_search(commitsTwo, len, tabSize, "done");

	expected = "The commit numbers containing the word \"done\" are: 0, 1\n";

	ASSERT_EQ(expected, result);
    add_points_to_grade(20);

	len = 3;

	string commitsThree[] = {"hopefully", "the key isnt", "found"};
	result = test_search(commitsTwo, len, tabSize, "error");

	expected = "No commits containing the word \"error\" were found.\n";

	ASSERT_EQ(expected, result);
    add_points_to_grade(10);
}	


//TODO add more tests for insert. Design tests for search from hashTable.

