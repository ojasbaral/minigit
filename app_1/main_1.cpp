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

    //CALL MENU
   while(option!=7){

    //GATHER INPUT
    displayMenu();
    cin >> input;
    option = stoi(input);

    //CHECKING FOR VALID INPUT
    if(option<=7&&option>=1){
        validInput = true;
    }
    while(!validInput){
        cout << "INVALID INPUT: Enter a number between 1-7." << endl;
        cin >> input;
        option = stoi(input);

        if(option<=7&&option>=1){
            validInput = true;
    }
    }

    //INPUT DEPENDENT ACTIONS
    if(option == 1){
        MiniGit* miniGit = new MiniGit();
        (*miniGit).init(5);
    }

    if(option == 2){
        string fileName;
        cout << "Enter the file name." << endl;
        cin >> fileName;
        (*miniGit).add(fileName);
    }

    if(option == 3){

    }

    if(option == 4){

    }

    if(option == 5){

    }

    if(option == 6){

    }

    if(option == 7){
        bool confirmed = false;
        string result;

        cout << "Are you sure you want to quit? All of your files will be deleted. (yes/no)" << endl;
        cin >> result;
        if(result == "yes" || result == "no")
            confirmed = true;

        while(!confirmed){
            cout << "Please enter yes or no." << endl;
            cin >> result;
            if(result == "yes" || result == "no")
                confirmed = true;
        }

        if(result == "no"){
            option = 1;
        }
    }
    

        
   }

    return 0;
}