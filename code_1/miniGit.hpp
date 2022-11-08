#pragma once

#include<iostream>
#include<vector>
#include "hash.hpp"

using namespace std;


enum GITOP {init, add, rm, commit, checkout, status};

struct FileNode {
    string name;
    int version;
    FileNode* next;
};

struct BranchNode {
    int commitID;
    string commitMessage;
    BranchNode* next;
    BranchNode* previous;
    FileNode* fileHead;   
};

//*** You can add helper functions if you desire ***//
class MiniGit {
private:    
    BranchNode* commitHead;
    int commits;
    HashTable* ht;
    
   

public:
    MiniGit();
    ~MiniGit();

    void init(int hashtablesize);
    void add(string fileName);
    void rm(string fileName);
    void search(string key);
    string commit(string msg);
    void checkout(string commitID);
    void printSearchTable();
    
    
};