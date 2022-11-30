// CPP program to implement hashing with chaining
#include<iostream>
#include "hash.hpp"



using namespace std;

HashNode* HashTable::createNode(string key, HashNode* next)
{
    HashNode* nw = new HashNode();
    nw->key = key;
    nw->next = next;
    return nw;
}

HashTable::HashTable(int bsize)
{
   tableSize = bsize;
   table = new HashNode*[tableSize];
   table[0] = nullptr;
   table[1] = nullptr;
   table[2] = nullptr;
   table[3] = nullptr;
   table[4] = nullptr;
}

//function to calculate hash function
unsigned int HashTable::hashFunction(string s)
{
    int sum = 0;
    int size = s.size();
    for(int i = 0; i < size; i++){
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
        if(crawler->key == key){
            cout << "The commit numbers containing the word \"" << key << "\" are: ";
            for(int i = 0; i < crawler->commitNums.size(); i++){
                cout << crawler->commitNums[i];
                if(i != crawler->commitNums.size()-1)
                    cout << ", ";
            }
            cout << endl;
            return crawler;
        }
        crawler = crawler->next;
    }
    //TODO
    cout << "No commits containing the word \"" << key << "\" were found." << endl;
    return NULL;
}

//TODO Complete this function
//function to insert
bool HashTable::insertItem(string key, int cNum)
{
    int index;
    HashNode* crawler;
    index = hashFunction(key);
    //cout << index << endl;
    crawler = table[index];

        while(crawler!=nullptr){
            if(crawler->key == key){
                crawler->commitNums.push_back(cNum);
                return true;
            }
            crawler=crawler->next;
        }
        HashNode* newNode = createNode(key, (table[index]));
        newNode->commitNums.push_back(cNum);
        //cout << newNode->commitNums.size();
        table[index] = newNode;
        //cout << table[index]->key << endl;
    //printTable();
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
    for(int j = 0; j < tableSize; j++){
    cout << j << "|| ";
    HashNode* crawler = table[j];
    if(crawler!=nullptr){
    cout << crawler->key << "(";
    for(int i = 0; i < crawler->commitNums.size(); i++){
        cout << crawler->commitNums[i] << ",";
    }
    cout << ")";
    crawler=crawler->next;

    while(crawler!=nullptr){
        cout << "-->";
        cout << crawler->key << "(";
        for(int i = 0; i < crawler->commitNums.size(); i++){
        cout << crawler->commitNums[i] << ",";
    }
    cout << ")";
        crawler = crawler->next;
    }
    }
    cout << endl;
    }
 }
