#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void insert(node* &root, node* p, node* current, int data);
void insertFix(node* &root, node* current);
void rotateRight(node* &root, node* p);
void rotateLeft(node* &root, node* p); 
void deletion(node* &root, node* current, node* p);
void deleteFix();
void print(node* root, int count);
bool search(int searched, node* root);

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
	            insert(root, root, root, input1);
	            }

            }
        
            if(strcmp(input, "MANUAL")==0) {
	            cout << "Type a number between 1 and 999" << endl;
                cin >> mannum;
                insert(root, root, root, mannum);
            }

        } 

        if(strcmp(input, "PRINT")==0) {
            print(root, 0);

        }    
        if(strcmp(input, "DELETE")==0) {
            cout << "what number would you like to delete?" << endl; 
            cin >> n; 
            deletion(root, root, root, n);
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

void insert(node* &root, node* p, node* current, int data) {
    cout << "insert" << endl;
    //n->setValue(data);
    //if root is NULL 
    if(root == NULL) {
        root = new node(data); 
        root->setLeft(NULL);
        root->setRight(NULL);
        root->setColor(1);
        return;
    }
    //while root is not NULL
    else if(current == NULL) {
        current = new node(data); 
        current->setColor(0);
        if(data > p->getValue()) {
            p->setRight(current);
        }
        else{
            p->setLeft(current);
        }
        current->parent = p; 
        insertFix(root, current);
    }
    
    else if(data <= current->getValue()) {
        node* l = current->getLeft();
        insert(root, current, l, data); 
    }
    else {
        node* r = current->getRight();
        insert(root, current, r, data); 
    }
}

//credit: https://www.codesdope.com/course/data-structures-red-black-trees-insertion/
void insertFix(node* &root, node* current) {
    //while node's parent is red
    bool stillRunning = true;
   // while(stillRunning == true) {
    while(current->parent->getColor() == 0) {
        cout << "parent is red" << endl;
         //if node's parent is the left child
        if(current->parent == current->parent->parent->getLeft()) {
            cout<< "parent is the left child" << endl;
            node* uncle = current->parent->parent->getRight(); 
            
            //case 1: if the uncle is red
            if(uncle != NULL && uncle->getColor() == 0) {
                cout << "uncle is red" << endl;
                if (current->parent->parent==NULL) {
                    cout << "GRANDPA NULL" << endl;
                }
                current->parent->setColor(1);
                uncle->setColor(1);
                if(current->parent->parent != root) {
                    current->parent->parent->setColor(0);
                    current = current->parent->parent;
                }
                else {
                    
                    return;
                }
                
                //current = current->parent->parent; 
                cout << "line 148" << endl;
            }
            //case 2
            else {
                //case 2: if the uncle of node is black and the node is the right child
                if(current == current->parent->getRight()) {
                    cout << "case 2" << endl;
                    current = current->parent; 
                    rotateLeft(root, current); 
                }
                //if the uncle of node is black and the node is left child
                else {
                    cout << "case 3" << endl;
                    current->parent->setColor(1);
                    current->parent->parent->setColor(0);
                    rotateRight(root, current->parent->parent); 
                }
            }
                
        }
        //if node's parent is the right child
        else {
            cout << "parent is right child" << endl;
            node* uncle = current->parent->parent->getLeft();
             //case 1: if the uncle is red
            if(uncle != NULL && uncle->getColor() == 0) {
                cout << "case 1 r" << endl;
                if (current->parent->parent==NULL) {
                    cout << "GRANDPA NULL" << endl;
                }
                current->parent->setColor(1);
                uncle->setColor(1);
                if(current->parent->parent != root) {
                    cout << "here1" << endl;
                    current->parent->parent->setColor(0);
                    //current = current->parent->parent;
                }
                else {
                    cout << "here 3" << endl;
                    return;
                }
                //current->parent->parent->setColor(0);
                cout << "here2" << endl; 
                current = current->parent->parent;
                cout << "current" << current->getValue() << endl;
                insertFix(root, current);
                return;
            }
            //if uncle is black
            else {
                //if the uncle of node is black and the node is the Left child
                if(current == current->parent->getLeft()) {
                    cout << "case2r" << endl;
                    current = current->parent;
                    rotateRight(root, current);
                    print(root, 0);
                }
                //else {
                //if the uncle of node is black and the node is Right child
                    cout << "case3r" << endl; 
                    current->parent->setColor(1);
                    //if(current->getRight() != NULL) {
                     //   current->getRight()->setColor(0); 
                   // } 
                    current->parent->parent->setColor(0);
                    cout << "current parent parent" << current->parent->parent->getValue() << endl;
                    rotateLeft(root, current->parent->parent);
                    cout << "parent color" << current->parent->getColor() << endl;
                    print(root, 0);
                //}
            }
        }
        
    }
    cout << "exited while loop" << endl;
    root->setColor(1);
    
}

void rotateLeft(node* &root, node* p) {
    cout << "rotate left" << endl; 
    node* y = p->getRight(); 
    p->setRight(y->getLeft()); 
   
    if(y->getLeft() != NULL) {
        y->getLeft()->parent = p;
    }
    y->parent = p->parent;
    //parent is root
    if(p->parent == NULL) {
        root = y;
    }
    //parent is left child
    else if(p == p->parent->getLeft()) {
        p->parent->setLeft(y);
        
    }
    //is parent is right child
    else {
        p->parent->setRight(y);
    }
    y->setLeft(p);
    p->parent = y; 
    
    
}

void rotateRight(node* &root, node* p) {
    cout << "rotate right" << endl; 
    node* y = p->getLeft();
    //if(y != NULL) { 
        p->setLeft(y->getRight());
    //}
    //if right doesn't exist
    if(y->getRight() != NULL) {
        cout << "here1" << endl;
        y->getRight()->parent = p; 
    }
    y->parent = p->parent; 
    //if parent is root
    if(p->parent == NULL) {
        cout << "here2" << endl;
        root = y; 
    }
    //if parent is left child
    else if(p == p->parent->getRight()) {
        cout << "here3" << endl;
        p->parent->setRight(y);
        
    }
    //if parent is right child
    else {
        cout << "here4" << endl;
        p->parent->setLeft(y);
    }
    y->setRight(p);
    p->parent = y;
    cout << "end of rotate right" << endl;
    
}

//programiz
void deletion(node* &root, node* p, node* current, int n) {
  
  
    if(root == NULL) {
        cout << "there is nothing to delete" << endl;
    }
    //if the current value == the value to be deleted
    if(current->getValue == n) {
        node y = current; 
        int originalColor = current->getColor();
        node* x;
        
        //if current's left is NULL
        if(current->getLeft() == NULL) {
        current->setRight(x);
        transplant(current, x); //current is replaced with x
        }
        //if current's right is NULL
        else if(current->getRight() == NULL) {
            current->setLeft(x);
            transplant(current, x); //current is replaced with x
        }
        //if current's left and right are not NULL
        else {
            y = minimum(current->getRight()); //y is smallest element is subtree
            originalColor = y->getColor();
            y->setRight(x);
            if(y->parent == current) { //if y's parent == the node to be deleted
                x->parent = y;
            }
            else {
                transplant(y, y->getRight());
                y->setRight(current->getRight());
                y->getRight()->parent = y;
            }
            transplant(current, y);
            y->setLeft(current->getLeft());
            y->getLeft()->parent = y;
            y->setColor(current->getColor()); 
        }
        if(originalColor == 1) {
            deleteFix(root, x);
        }
    }
    
    else if(n < current->getValue()) {
        return deletion(root, p, current->getLeft(), n);
    }
    else {
        return deletion(root, p, current->getRight(), n);
    }
}

void deleteFix() {
    
    
}

node* minimum(node* current) {
    while(current->getLeft() != NULL) {
        current = current->getLeft();
    }
    return node; 
}

void transplant(node* &root, node* &current, node* &v) {
    //current is root
    if(current->parent == NULL) {
        root = v;
    }
    //if current is left child
    else if(current == current->parent->getLeft()) {
        current->parent->setLeft(v);
    }
    //if current is right child
    else {
        current->parent->setRight(v));
    }
    v->parent = current->parent; 
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

bool search(int searched, node* root) {
    //if root doesnt exist
    if(root == NULL) {
        return false; 
    }
    //if root equals the value searched
    if(root->getValue() == searched) {
        return true; 
    }
    //if root value is less than search value
    if(root->getValue() > searched) {
        //call search again but pass in left child
        node* left = root->getLeft();
        return(search(searched, left));
    }
    //if root value is greater than search value
    if(root->getValue() < searched) {
        //call search again but pass in right child
        node* right = root->getRight();
        return(search(searched, right)); 
    }