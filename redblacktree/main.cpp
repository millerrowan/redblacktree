#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void insert();
void rotateRight();
void rotateLeft(); 

int main() {
    bool stillPlaying = true;
    int mannum;
    int numcounter = 0;
    node* root = NULL;
    int searched;
    int n;
    char input[30];
    
    while(stillPlaying == true) {
    cout << "Enter ADD, PRINT, DELETE, SEARCH, or QUIT" << endl;
    cin >> input; 
    
    if(strcmp(input, "ADD")==0) {
      char input2[20]; 
      cout << "input from file or manual?";
      cout << "Enter 'FILE' or 'MANUAL'" << endl;
      cin >> input;
      
    if(strcmp(input, "FILE")==0){
	cout << "what is the file name and include .txt at end" << endl;
	char fileName[30];
	cin >> fileName;

	ifstream fin;
	fin.open(fileName);
	int input1;
	while(fin >> input1) {
	  insert(root, input1);
	}

      }
      if(strcmp(input, "MANUAL")==0) {
	    cout << "Type a number between 1 and 999" << endl;
        cin >> mannum;
        
        insert(root, mannum);
      }

    }

    if(strcmp(input, "PRINT")==0) {
        print(root, 0);

    }
    /*
    if(strcmp(input, "DELETE")==0) {
        cout << "what number would you like to delete?" << endl; 
        cin >> n; 
        remove(root, root, root, n);
    }
    if(strcmp(input, "SEARCH")==0) {
        
      cout << "what number are you searching for?" << endl;
      cin >> searched;
      bool inTree = search(searched, root);
      if(inTree == false) {
          cout << "your number is not in the tree" << endl;
      }
      else if(inTree == true) {
          cout << "your number is in the tree" << endl;
      } 
      
    } */
    
    if(strcmp(input, "QUIT")==0) {
      stillPlaying = false; 
    }
  }
    
    
}

// A node is either red or black.
 //The root is black.
// All leaves (NULL) are black.
 //Both children of every red node are black.
// Every simple path from a given node to any of its descendant leaves contains the same number of black nodes.

void insert(node* &root, node* node) {
    //if tree doesn't exist yet
    if(root == NULL) {
        root = new node(data); 
        root->setLeft(NULL);
        root->setRight(NULL);
        return;
    }
    if(root->getValue() > data) {
        cout << "you are in left section" << endl;
        if(root->getLeft() == NULL) {
            root->setLeft(new node(data)); 
        }
        else {
            node* left = root->getLeft();
            add(left, data);
        }
    }
    else{
        cout << "you are in right section" << endl;
        if(root->getRight() == NULL) {
             root->setRight(new node(data));
        }
        else{
        node* right = root->getRight(); 
            add(right, data); 
        }
    }
    return;  
    
    
}

void insertFix(node* &root, node* &node) {
   
}

void rotateLeft(node* &root, node* & parent) {
    node* y = parent->getRight(); 
    parent->setRight(y->getLeft); 
    if(y->getLeft() != NULL) {
        y->getLeft->parent = parent;
    }
    y->parent = parent->parent;
    //parent is root
    if(parent->parent == NULL) {
        root = y;
    }
    //parent is left child
    else if(parent == parent->parent->getLeft()) {
        parent->parent->setLeft(y);
        
    }
    //is parent is right child
    else {
        parent->parent->setRight(y);
    }
    y->setLeft(y);
    parent->parent = y; 
    
    
}

void rotateRight(node* &root, node* parent) {
    node* y = parent->getLeft();
    parent->setLeft(y->getRight()); 
    //if right doesn't exist
    if(y->getRight != NULL) {
        y->getRight->parent = parent; 
    }
    y->parent = parent->parent; 
    //if parent is root
    if(parent->parent == NULL) {
        root = y; 
    }
    //if parent is left child
    else if(parent == parent->parent->getRight()) {
        parent->parent->setRight(y);
        
    }
    //if parent is right child
    else {
        x->parent->setLeft(y);
    }
    y->setRight(parent);
    parent->parent = y;
    
}