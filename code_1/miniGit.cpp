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
    fs::remove_all("../working_directory");
    fs::create_directory("../working_directory");
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
   commitHead->fileHead = nullptr;
   currentDirectory = commitHead;

}

void MiniGit::add(string fileName) {
    string name = fileName;
    bool exists;
    exists = fs::exists("../working_directory/" + name);
    while(!exists){
        cout << "Enter a valid file name that exists in the current directory:" << endl;
        cout << "#> ";
        name ="";
        cin >> name;
        exists = fs::exists("../working_directory/" + name);
    }
        FileNode* crawler = currentDirectory->fileHead;
        //FileNode* crawler = nullptr;
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
    /* while(crawler!=nullptr){
        cout << crawler->name << endl;
        crawler = crawler->next;
    } */

    crawler = currentDirectory->fileHead;
    FileNode* temp;
    while(crawler->next!=nullptr){
        int pos = crawler->name.find("_");
        string name = crawler->name.substr(pos+1);
        int pos2 = crawler->next->name.find("_");
        string name2 = crawler->next->name.substr(pos2+1);
        if(name==fileName&&crawler==currentDirectory->fileHead){
            //IF ITS HEAD
            //cout << "head" << endl;
            temp = crawler;
            currentDirectory->fileHead = temp->next;
            delete temp; 
        }
        else if(name2 == fileName){
            //IF SOMEWHERE ELSE
            //cout << "not head" << endl;
            temp = crawler->next;
            crawler->next = temp->next;
            delete temp; 
        }
        crawler = crawler->next;
    }
   /*  crawler = currentDirectory->fileHead;
    while(crawler!=nullptr){
        cout << crawler->name << endl;
        crawler = crawler->next;
    } */

}



void MiniGit::printSearchTable()
{
     ht->printTable();
}


void MiniGit::search(string key) 
{
    ht->searchItem(key);
}



string MiniGit::commit(string msg) {
    //cout << msg << endl;
    currentDirectory->commitMessage = msg;
    FileNode* crawler = currentDirectory->fileHead;
    //cout << crawler->name << endl;
    while(crawler!=nullptr){
         int pos = crawler->name.find("_");
         string pureFile = crawler->name.substr(pos+1);
         //cout << pureFile << endl;
         //cout << crawler->name << endl;
        if(fs::exists("../.minigit/" + crawler->name)){
            //cout << crawler->name << endl;
           string dataOne = "";
           string dataTwo = "";
           string temp = "";
           ifstream inputOne;
           inputOne.open("../working_directory/" + pureFile);
           while(getline(inputOne, temp)){
            dataOne+=temp;
            dataOne+="\n";
           } 
           inputOne.close();

           ifstream inputTwo;
           inputTwo.open("../.minigit/" + crawler->name);
           while(getline(inputTwo, temp)){
            dataTwo+=temp;
            dataTwo+="\n";
           }
            inputTwo.close();

            if(dataOne != dataTwo){
                //cout << crawler->name << "HERE" << endl;
                crawler->version++;
                string c = to_string(crawler->version);
                crawler->name.replace(0, 1, c);
                ofstream file("../.minigit/" + crawler->name);
                file << dataOne;
            } /* else {
                cout << dataOne << endl;
                cout << endl;
                cout << dataTwo << endl;
            } */
        }else {
            string temp;
            string data;
            ifstream input;
            pureFile = "../working_directory/" + pureFile;
            input.open(pureFile);
            while(getline(input, temp)){
                data+=temp;
                data+= "\n";
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
/*         cout << crawler->name << endl;
 */        crawler = crawler->next;
    }
    
    string t2;
    stringstream s(msg);
    //cout << msg << endl;
    while(getline(s, t2, ' ')){
        //cout << t2 << endl;
        ht->insertItem(t2, currentDirectory->commitID);
    }

    //cout << ht->printTable() << endl;

    BranchNode* temp = new BranchNode;
    temp->previous = currentDirectory;
    temp->commitMessage = "";
    temp->commitID = currentDirectory->commitID + 1;
    temp->fileHead = nullptr;
    currentDirectory->next = temp;
    FileNode* crawl = currentDirectory->fileHead;
    FileNode* last;
    FileNode* newNode;
    while(crawl!=nullptr){
        //cout << crawl->name << endl;
        newNode = new FileNode;
        newNode->name = crawl->name;
        newNode->version = crawl->version;
        newNode->next = temp->fileHead;
        temp->fileHead = newNode;
       /*  if(temp->fileHead->next!=nullptr)
            cout << temp->fileHead->next->name << endl; */
        if(newNode->next==nullptr)
        last = newNode;
        crawl = crawl->next;
        newNode = nullptr;
    }
    last->next = nullptr;
    
    currentDirectory = currentDirectory->next;
    crawl = currentDirectory->fileHead;
    while(crawl!=nullptr){
    //cout << crawl->name << endl;
    crawl=crawl->next;
    }
    return to_string(currentDirectory->previous->commitID); //should return the commitID of the commited DLL node
}

void printTempMenu(){
    cout << "Select a numerical option, you may not add, remove, or commit until you checkout your most recent commit:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. checkout" << endl;
    cout << " 2. search" << endl;
    cout << " 3. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}

void MiniGit::checkout(string commitID) {
   BranchNode* crawler = commitHead;
   while(crawler!=nullptr){
    if(crawler->commitID==stoi(commitID)){
        string input ="";
        cout << "Are you sure you want to check out, you will lose all of your changes? (yes or no)" << endl;
        cout << "#> ";
        getline(cin, input);
        if(input == "no"){
            return;
            //cout << "1" << endl;
        }
        else{
             fs::remove_all("../working_directory");
             fs::create_directory("../working_directory");
             FileNode* crawler2 = crawler->fileHead;
             while(crawler2!=nullptr){
                //cout << "2" << endl;
                string data = "";
                string temp = "";
                ifstream input;
                input.open("../.minigit/" + crawler2->name);
                while(getline(input, temp)){
                    data += temp;
                    data += "\n";
                }
                input.close();
                int pos = crawler2->name.find("_");
                string pureFile = crawler2->name.substr(pos+1);
                ofstream file("../working_directory/" + pureFile);
                if(file.is_open()){
                    file << data;
                }
                file.close();
                crawler2 = crawler2->next;
             }
            //
                bool commited = false;
                string input = "";
                if(stoi(commitID)!=currentDirectory->commitID-1)
                while(!commited){
                    printTempMenu();
                    getline(cin, input);

                if(input == "1"){
                    string data = "";
                    cout << "Enter a commit number" << endl;
                    cout << "#> ";
                    getline(cin, data);
                    checkout(data);
                    if(stoi(data)==((currentDirectory->commitID)-1)){
                        commited = true;
                    }
                }
                if(input == "2"){
                    string data = "";
                    cout << "Enter a single word to search for" << endl;
                    cout << "#> ";
                    getline(cin, data);
                    search(data);
                }

                if(input == "3"){
                    bool confirmed = false;
                        string result;

                        cout << "Are you sure you want to quit? All of your files will be deleted. (yes/no)" << endl;
                        cout << "#> ";
                    getline(cin, result);
                if(result == "yes" || result == "no")
                    confirmed = true;

                while(!confirmed){
                    cout << "Please enter yes or no." << endl;
                    cout << "#> ";
                    getline(cin, result);
                    if(result == "yes"||result == "no"){
                        confirmed = true;
                    }
                    }

                    if(result == "yes"){
                        exit(1);
                    }
                            }
                }

            //
             return;
        }
    }
    crawler = crawler->next;
   }
    cout << "That commit number does not exist" << endl;
    return;
}
