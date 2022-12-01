# CSCI 2275 – Data Structures - Final Project

Ojas Baral

## Minigit Description

This minigit application utilizes various data structures in order to create a basic version of git. Through this application you are able to create files in the **working_directory** folder ( which will be created upon initialization), and through the menu you are able to add, remove, and commit your files to the **.minigit** folder, as well as, checkout previous commits, and search for previous commit numbers based on a keyword. Below will be a description and guide to all of the functions.

## Initialization 

This option must be chosen before any other option (other than quit). It creates the **working_directory** and **.minigit** folders and creates the linked list which stores the commits. Directions to the function are shown below. 

1. Enter **1** into the menu.

## Add

This option should be chosen when the user wants to add a file to the staging of the next commit. **The user can only add a file that exists in the working_directory folder and a file that has not been added before.** This means that a file only needs to be added once throughout the whole usage of the application. A linked list is used to store the file data. Directions to the function are shown below.

1. Enter **2** into the menu.
2. Enter the name of a file that exists in the **working_directory** folder, and a file that has not been added before.

## Remove

This option should be chosen when the user wants to remove a file from the staging of the next commit. This option **does not** delete the file in the **working_directory** folder, it only stops the files changes from being stored in future commits. Directions to the function are shown below. 

1. Enter **3** into the menu.
2. Enter the name of a file that the user has already added.

## Commit 

This option should be chosen when the user wants to commit their changes. Any files that have been added, or changed since the last commit will then be saved as a new file in the **.minigit** directory. The user is also asked to enter a commit message, which is then stored in a hash table, for effecient searching. Directions to the function are shown below.

1. Enter **4** into the menu.
2. Enter a commit message. The commit message **can not** be empty.

## Checkout

This option should be chosen when the user wants to commit their changes. If the user chooses to checkout a prior commit, all of their local changes will be lost. The contents inside of the **working_directory** will be replaced by the commit chosen. The user will then only be allowed to checkout again, search for a commit number, or quit the application until they checkout to their last commit. Directions to the function are shown below. 

1. Enter **5** into the menu.
2. Enter a past commit number. 
3. Enter **yes** to confirm.
4. If the user wants to be able to add, remove, or commit again, they must checkout back to their most recent commit.

## Search

This option should be chosen when the user wants to search for a commit number using a single key word. This function utilizes a hash table and effeciently searches for the commit number based on a single word. Directions to the function are shown below. 

1. Enter **6** into the menu.
2. Enter a single word used in a prior commit message.

## Tests

By running **./run_tests** the user can test the functionality of the hash data structure, by running tests of the insert function and the search function.



