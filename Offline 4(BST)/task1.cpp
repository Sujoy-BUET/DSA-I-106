#include <iostream>
#include <fstream>
#include<string.h>
#include "listBST.hpp"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file) {
        cerr << "Unable to open file\n";
        return 2;
    }
    char c, str[5];
    int val;
    BST<int, int> *bst = new ListBST<int, int>();
    if (!bst) {
        cerr << "Memory allocation failed\n";
        return 3;
    }
    //ofstream out_file(argv[2]);
    while (in_file >> c) {
        // TODO: Implement the logic to read commands from the file and output accordingly
        // After every insertion and removal, print the BST in nested parentheses format
        // Handle exceptions where necessary and print appropriate error messages

        // Start your code here
        
        if(c=='I'){
            int key;
            in_file >> key;
            if(bst->insert(key,key)){
                cout << "Key " << key << " inserted into BST, ";
            }else{
                cout << "Insertion failed! Key " << key << " already exists in BST, "; 
            }
            bst->print();
        }else if(c=='D'){
            int key;
            in_file >> key;
            if(bst->remove(key)){
                cout << "Key " << key << " removed from BST, ";
            }else{
                cout << "Removal failed! Key " << key << " not found in BST, "; 
            }
            bst->print();
            
        }else if(c=='F'){
            int key;
            in_file >> key;
            if(bst->find(key)){
                cout << "Key " << key << " found in BST.\n";
            }else{
                cout << "Key " <<key << " not found in BST.\n";
            }
        }else if(c=='G'){
            int key;
            in_file >> key;
            cout << "Key " << key << " has value " << bst->get(key) << '\n';
        }else if(c=='U'){
            int key,value;
            in_file >> key >> value;
            bst->update(key,value);
        }else if(c=='C'){
            bst->clear();
        }else if(c=='S'){
            cout << "Size: " << bst->size() << '\n';
        }else if(c=='E'){
            if(bst->empty()){
                cout << "Empty\n";
            }else{
                cout << "Not Empty\n";
            }
        }else if(c=='M'){
            in_file >> str;
            if(!strcmp(str,"Min")){
                cout << "Minimum value: " << bst->find_min() << '\n';
            }else if(!strcmp(str,"Max")){
                cout << "Maximum value: " << bst->find_max() << '\n';
            }else{
                cout << "Invalid input\n";
            }
        }else if(c=='T'){
            in_file >> str;
            if(!strcmp(str,"In")){
                bst->print('I');
            }else if(!strcmp(str,"Pre")){
                bst->print('P');
            }else if(!strcmp(str,"Post")){
                bst->print('O');
            }else{
                bst->print('D');
            }
        }
        // End your code here
    }
    in_file.close();
    delete bst;
    return 0;
}

// g++ −std=c++11 task1.cpp −o task1
// ./task1 in_task1.txt > myout_task1.txt