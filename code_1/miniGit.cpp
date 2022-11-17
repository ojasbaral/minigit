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
    fs::remove_all("../.minigit");
    fs::create_directory("../.minigit");
}

MiniGit::~MiniGit() {   
    // Any postprocessing that may be required
    fs::remove_all("../.minigit");
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
    exists = fs::exists("../working_directory/" + name);
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
        //cout << currentDirectory->fileHead->name;
    }




void MiniGit::rm(string fileName) {
    FileNode* crawler = currentDirectory->fileHead;
    FileNode* temp;
    while(crawler!=nullptr){
        if(crawler->name==fileName&&crawler==currentDirectory->fileHead){
            //IF ITS HEAD
            temp = crawler;
            currentDirectory->fileHead = temp->next;
            delete temp;
        }
        if(crawler->next->name == fileName){
            //IF SOMEWHERE ELSE
            temp = crawler->next;
            crawler->next = temp->next;
            delete temp;
        }
        crawler = crawler->next;
    }
}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key)
{
}



string MiniGit::commit(string msg) {
    currentDirectory->commitMessage = msg;
    FileNode* crawler = currentDirectory->fileHead;
    while(crawler!=nullptr){
         int pos = crawler->name.find("_");
         string pureFile = crawler->name.substr(pos+1);
        if(fs::exists("../.minigit/" + crawler->name)){
           string dataOne;
           string dataTwo;
           string temp;
           ifstream inputOne;
           inputOne.open("../working_directory/" + pureFile);
           while(getline(inputOne, temp, ' ')){
            dataOne+=temp;
           } 
           inputOne.close();

           ifstream inputTwo;
           inputTwo.open("../.minigit/" + crawler->name);
           while(getline(inputTwo, temp, ' ')){
            dataTwo+=temp;
           }
            inputTwo.close();

            if(dataOne != dataTwo){
                crawler->version++;
                string c = to_string(crawler->version);
                crawler->name.replace(0, 1, c);
                ofstream file("../.minigit/" + crawler->name);
                file << dataOne;
            }
        }else {
            string temp;
            string data;
            ifstream input;
            pureFile = "../working_directory/" + pureFile;
            input.open(pureFile);
            while(getline(input, temp, ' ')){
                data+=temp;
            }
            input.close();
            //DATA IS NOT COMING THROUGH
            string path = "../.minigit/" + crawler->name;
            ofstream file(path);
            if(file.is_open()){
            file << data;
            }
            file.close();
            
        }
        crawler = crawler->next;
    }

    BranchNode* temp = new BranchNode;
    temp->previous = currentDirectory;
    temp->commitMessage ="";
    temp->commitID = currentDirectory->commitID + 1;
    currentDirectory->next = temp;
    FileNode* crawl = currentDirectory->fileHead;
    while(crawl!=nullptr){
        FileNode* newNode = new FileNode;
        newNode->name = crawl->name;
        newNode->version = crawl->version;
        newNode->next = temp->fileHead;
        temp->fileHead = newNode;
        crawl = crawl->next;
    }
    currentDirectory = currentDirectory->next;
    return to_string(currentDirectory->previous->commitID); //should return the commitID of the commited DLL node
}

void MiniGit::checkout(string commitID) {
   

}
