#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

#include <filesystem>
namespace fs = std::filesystem;

#include "miniGit.hpp"
#include <vector>

//g++ -std=c++17 app_1/main_1.cpp code_1/hash.cpp code_1/hash.hpp code_1/miniGit.cpp code_1/miniGit.hpp

MiniGit::MiniGit() {
    fs::remove_all(".minigit");
    fs::create_directory(".minigit");
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
}

void MiniGit::init(int hashtablesize) {
   ht = new HashTable(hashtablesize);
   commits = 0;
   commitHead = new BranchNode;
   commitHead->commitID = commits;
   commitHead->next = nullptr;
   commitHead->previous = nullptr;
   currentDirectory = commitHead;

}

void MiniGit::add(string fileName) {
    string name = fileName;
    bool exists;
    exists = fs::exists(name);
    while(!exists){
        cout << "Enter a valid file name that exists in the current directory:" << endl;
        cout << "#> ";
        cin >> name;
        exists = fs::exists("" + name);
    }
        FileNode* crawler = currentDirectory->fileHead;
        while(crawler!=nullptr){
            if(crawler->name == name){
                cout << "This file has already been added." << endl;
                return;
            }
            crawler = crawler->next;
        }

        FileNode* newNode = new FileNode;
        newNode->version = 0;
        newNode->name = "0_" + name;
        newNode->next = currentDirectory->fileHead;
        currentDirectory->fileHead = newNode;
        cout << currentDirectory->fileHead->name;
    }




void MiniGit::rm(string fileName) {
    
}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
}



string MiniGit::commit(string msg) {
    return " "; //should return the commitID of the commited DLL node
}

void MiniGit::checkout(string commitID) {
   

}
