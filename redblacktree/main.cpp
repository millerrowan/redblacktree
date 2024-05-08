#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void insert(node* &root, node* &node, int data);
void insertFix(node* &root, node* &node);
void rotateRight(node* &root, node* &parent);
void rotateLeft(node* &root, node* &parent); 
void print(node* root, int count);

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
    
       /* if(strcmp(input, "ADD")==0) {
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
	            insert(root, root, input1);
	            }

            }
        
            if(strcmp(input, "MANUAL")==0) {
	            cout << "Type a number between 1 and 999" << endl;
                cin >> mannum;
                insert(root, root, mannum);
            }

        } */

       /* if(strcmp(input, "PRINT")==0) {
            print(root, 0);

        }    */
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
    
       /* if(strcmp(input, "QUIT")==0) {
            stillPlaying = false; 
        } */
    }
  
}
    
    

// A node is either red or black.
 //The root is black.
// All leaves (NULL) are black.
 //Both children of every red node are black.
// Every simple path from a given node to any of its descendant leaves contains the same number of black nodes.

void insert(node* &root, node* &node, int data) {
    node* p = NULL;
    node* temp = root; 
    node->setValue(data);
    //while root is not NULL
    while(temp != NULL) {
        p = temp;
        if(node->getValue() < temp->getValue()){
            temp = temp->getLeft();
        }
        else {
            temp = temp->getRight(); 
        }
    }
    node->parent = p;
    node->setColor(0);
    //if newly added node is the root
    if(p == NULL) {
        p->setLeft(node);
    }
    //if data of child is less than parent
    else if(node->getValue() < p->getValue()) {
        p->setLeft(node);
        
    }
    else {
        p->setRight(node);
    }
    node->setRight(NULL);
    node->setLeft(NULL);
    
    insertFix(root, node);
    
    
}

void insertFix(node* &root, node* &node) {
    //while node's parent is red
    while(node->parent->getColor() == 0) {
        //if node's parent is the left child
        if(node->parent == node->parent->parent->getLeft()) {
            node* uncle = node->parent->parent->getRight(); 
            
            //case 1: if the uncle is red
            if(uncle->getColor() == 0) {
                node->parent->setColor(1);
                uncle->setColor(1);
                node->parent->parent->setColor(0);
                node = node->parent->parent; 
            }
            //case 2 or 3
            else {
                //case 2: if the uncle of node is black and the node is the right child
                if(node == node->parent->getRight()) {
                    node = node->parent; 
                    rotateLeft(root, node); 
                }
                //case 3: if the uncle of node is black and the node is left child
                node->parent->setColor(1);
                node->parent->parent->setColor(0);
                rotateRight(root, node->parent->parent); 
            }
                
        }
        //if node's parent is the right child
        else {
            node* uncle = node->parent->parent->getLeft();
             //case 1: if the uncle is red
            if(uncle->getColor == 0) {
                node->parent->setColor(1); 
                uncle->setColor(1)l 
                node->parent->parent->setColor(0);
                node = node->parent->parent;
                
            }
            //case 2 or 3
            else {
                //case 2: if the uncle of node is black and the node is the right child
                if(node == node->parent->getLeft()) {
                    node = node->parent;
                    rotateRight(root, node);
                }
                //case 3: if the uncle of node is black and the node is left child
                node->parent->setColor(1);
                node->parent->parent->setColor(0);
                rotateLeft(root, node->parent->parent);
            }
        }
        
    }
    root->setColor(1);
    
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
    if(y->getRight() != NULL) {
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

void print(node* root, int count) {
    if(root == NULL) {
        return;
    }
    //if left child exists
    if(root->getRight() != NULL) {
        //calls print function but passes in left child
        print(root->getRight(), count+1);
    }
    for(int a = 0; a < count; a++) {
        cout << "\t";
    }
    cout << root->getValue() << " " << root->getColor() << endl; 
    //if right child exists
    if(root->getLeft() != NULL) {
        //calls print function but passes in right child
        print(root->getLeft(), count+1); 
    }
}