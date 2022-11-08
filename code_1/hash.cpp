// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"


using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = NULL;
    return nw;
}

HashTable::HashTable(int bsize)
{
   
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    
    return 0;
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
   

    //TODO
    return NULL;
    
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    
    //TODO
    return false;
}


// function to display hash table //
/* assume the table size is 5. For each bucket it will show the 
** the string key and the commit number (separated by comma) within parenthesis
** e.g. the key is science and commit numbers are 1 and 4. The key science
** is hashed to position 0. So the print format will be-

0|| science(1,4,)
1|| 
2|| 
3|| 
4|| difficult(3,)-->fun(2,)-->computer(0,)

*/
void HashTable::printTable()
{

 }
