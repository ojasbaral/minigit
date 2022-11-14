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
   tableSize = bsize;
   *table = new HashNode[tableSize];
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int sum;

    for(int i = 0; i < s.size(); i++){
        sum+=s[i];
    }

    return sum % tableSize;
}

// TODO Complete this function
//function to search
HashNode* HashTable::searchItem(string key)
{
    int index = hashFunction(key);
    HashNode* crawler = table[index];
    while(crawler!=nullptr){
        if(crawler->key == key)
            return crawler;
        crawler = crawler->next;
    }
    //TODO
    return NULL;
    
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    int index;
    HashNode* crawler;


    index = hashFunction(key);
    crawler = table[index];

        while(crawler!=nullptr){
            if(crawler->key == key){
                crawler->commitNums.push_back(cNum);
                return true;
            }
            crawler=crawler->next;
        }

        HashNode* newNode = new HashNode;
        newNode->key = key;
        newNode->commitNums.push_back(cNum);
        newNode->next = table[index];
        table[index] = newNode;
    
    //TODO
    return true;
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
