#include <iostream>
#include "../code_1/miniGit.hpp"
#include <filesystem>
using namespace std;

/*
 * Purpose; displays a menu with options
 */
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. init " << endl;
    cout << " 2. add " << endl;
    cout << " 3. rm " << endl;
    cout << " 4. commit " << endl;
    cout << " 5. checkout" << endl;
    cout << " 6. search" << endl;
    cout << " 7. quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
int main(int argc, char* argv[]) {

    //VARIABLES
   string input;
   int option;
   bool validInput = false;
   MiniGit* miniGit = nullptr;
   int commits;

    //CALL MENU
   while(option!=7){

    //GATHER INPUT
    displayMenu();
    getline(cin, input);
    option = stoi(input);
    //CHECKING FOR VALID INPUT
    if(option==7||option==6||option==5||option==4||option==3||option==2||option==1){
        validInput = true;
    }
    while(!validInput){
        cout << "INVALID INPUT: Enter a number between 1-7." << endl;
        cout << "#> ";
        getline(cin, input);
        option = stoi(input);

        if(option<=7&&option>=1){
            validInput = true;
    }
    }

    //INPUT DEPENDENT ACTIONS
    if(option == 1){
        miniGit = new MiniGit();
        (*miniGit).init(5);
    }

    if(option == 2){
        if(miniGit == nullptr){
            cout << "You must initialize a new directory first" << endl;
        } else {
        string fileName;
        cout << "Enter the file name to add." << endl;
        cout << "#> ";
        getline(cin, fileName);
        (*miniGit).add(fileName);
        }
    }

    if(option == 3){
        if(miniGit == nullptr){
            cout << "You must initialize a new directory first" << endl;
        } else {
        string fileName;
        cout << "Enter the file name to remove." << endl;
        cout << "#> ";
        getline(cin, fileName);
        (*miniGit).rm(fileName);
        }
    }

    if(option == 4){
        if(miniGit == nullptr){
            cout << "You must initialize a new directory first" << endl;
        } else {
            string input = "";
            bool parDone = false;
            while(!parDone){
                cout << "Enter a commit message" << endl;
                cout << "#> ";
                getline(cin, input);
                if(input != ""){
                    parDone = true;
                }
            }
            (*miniGit).commit(input);
        }
    }

    if(option == 5){
        if(miniGit == nullptr){
            cout << "You must initialize a new directory first" << endl;
        } else {
            string input = "";
            cout << "Enter a commit number" << endl;
            cout << "#> ";
            getline(cin, input);
            (*miniGit).checkout(input);
        }
    }

    if(option == 6){
        if(miniGit == nullptr){
            cout << "You must initialize a new directory first" << endl;
        } else {
            string input = "";
            bool parDone = false;
                cout << "Enter a single word to search for" << endl;
                cout << "#> ";
                getline(cin, input);
                (*miniGit).search(input);
        }
    }

    if(option == 7){
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
            if(result == "yes" || result == "no"){
                confirmed = true;
                delete miniGit;
            }
        }

        if(result == "no"){
            option = 0;
        }
    }
    

        
   }

    return 0;
}