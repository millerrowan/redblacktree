#include <iostream>
#include <cstring>
#include <fstream>
#include "node.h"

using namespace std;

void insert(node* &root, node* p, node* current, int data);
void insertFix(node* &root, node* current);
void rotateRight(node* &root, node* p);
void rotateLeft(node* &root, node* p); 
void deletion(node* &root, node* current, node* parent, int n);
void deleteFix(node* &root,node* current);
node* minimum(node* current); 
void print(node* root, int count);
bool search(int searched, node* root);
void transplant(node* &root, node* current, node* v); 

/* Red black tree is a data structure that organizes nodes into a tree with 
data values and they all have color
Author: Rowan Miller
06/03/24 */

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
      
        } 
    
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

void deletion(node* &root, node* current, node* parent, int n) { //0 is red, 1 is black
    cout << "deleting" << n << endl;
  
   if(root == NULL) {
        cout << "tree is empty" << endl;
        return;
    }
   /* if(search(n, root) == false) {
        cout << "this number is not in the tree" << endl;
        return;
    } */ 
    cout << "test " << endl;
    //int originalColor = current->getColor();
    if(current->getValue() == n) {
        cout << "test2" << endl;
        //case 1: if the node is a leaf
        if(current->getRight()==NULL && current->getLeft() == NULL) {
            //now you need to check where the node is located
            cout << "current: " << current << endl;
            //if the node is a root
            if(root->getValue()==n){
                cout << "root" << endl;
                root = NULL;
            }
            //if node is a right child
            if(current->getValue() > parent->getValue()) {
                cout << "current is a right child" << endl;
                parent->setRight(NULL); 
            }
            //if node is a left child
            if(current->getValue() < parent->getValue()) {
                cout << "current is a left child" << endl;
                parent->setLeft(NULL);
            }
            return;
        }
        //case 2: if the node has one child
        //if node has a left child
        if(current->getRight() == NULL && current->getLeft() != NULL) {
            //if current is a left child 
            cout<<"node has a left child" << endl;
            //transplant(root, current, current->getLeft());
            if(current->getValue() < parent->getValue()) {
                cout << "current is a left child" << endl;
                node* temp = current->getLeft();
                 parent->setLeft(temp);
                 deleteFix(root, current->getLeft());
                 delete current; 
            }
            //if current is a right child
            if(current->getValue() > parent->getValue()) {
                cout << "current is a right child" << endl;
                node* temp = current->getLeft();
                parent->setRight(temp);
                deleteFix(root, current->getLeft());
                delete current;
            }
    
            return; 
        }
         //if node has a right child
        if(current->getRight() != NULL && current->getLeft() == NULL) {
            //if current is a left child 
            cout << "node has a right child" << endl;
            if(current->getValue() < parent->getValue()) {
                cout << "current is a left child" << endl;
                node* temp = current->getRight(); 
                 parent->setLeft(temp);
                 deleteFix(root, current->getRight());
                 delete current; 
            }
            //if current is a right child
            if(current->getValue() > parent->getValue()) {
                cout << "current is a right child" << endl;
                node* temp = current->getRight();
                parent->setRight(temp);
                cout << "current: " << current->getValue();
                deleteFix(root, current->getRight());
                delete current;
            }
            //deleteFix(root, current);
            return; 
        }
            
        //case 3: if the node has two children
        if(current->getRight() != NULL && current->getLeft() != NULL) {
            node* temp = current->getRight();
            node* temptwo = current;
            node* tempthree = minimum(root->getRight());
            deleteFix(root, tempthree);
            while(temp->getLeft() != NULL) {
                temptwo = temp;
                temp = temp->getLeft(); 
            }
            if(temptwo != current) {
                temptwo->setLeft(temp->getRight());
            }
            else{
                temptwo->setRight(temp->getRight());
                
            }
            current->setValue(temp->getValue());
            delete temp;
            return;
            
        }
        
    }
    //recursive cases
    //move to right
    if(current->getValue() < n) {
        cout << "moving to right" << endl;
        deletion(root, current->getRight(), current, n);
    
    }
    //move to left
    else if(current->getValue() > n) {
        cout << "moving to left" << endl;
        deletion(root, current->getLeft(), current, n);
    }
}

//rebalances tree after deletion and fixes coloring 
//credit: programiz
void deleteFix(node* &root, node* current) {
    cout << "delete fix" << endl;
    node* w; 
    while(current != root && current->getColor() != 1) {
        cout << "while current is black and isn't root" << endl;
        cout << "current value" << current->getValue() << endl;
        cout << "current parent" << current->parent->getValue() << endl;
        //cout << "current parent right" << current->parent->getRight()->getValue() << endl;
        if(current == current->parent->getLeft()) {
            cout << "current is the left child" << endl;
            w = current->parent->getRight(); 
            if(w == NULL) {
                current->setColor(1);
                return;
            }
            else if(current->parent->getRight()->getColor() == 0) {
                cout << "currents parents right is black" << endl;
                current->parent->getRight()->setColor(1);
                current->parent->setColor(0); 
                rotateLeft(root, current->parent);
                current->parent->setRight(w);
            }
            
            else if(w->getRight()->getColor() == 1 && w->getLeft()->getColor() == 1) {
                cout << "ws right and left are black" << endl;
                w->setColor(0);
                current = current->parent; 
            }
            else{
                cout << "else left" << endl;
                if(w->getRight()->getColor() == 1) {
                    cout << "ws right is black" << endl;
                    w->getLeft()->setColor(1);
                    w->setColor(0);
                    rotateRight(root, w);
                    current->parent->setRight(w);
                }
                cout << "else left2" << endl;
                w->setColor(current->parent->getColor());
                current->parent->parent->setColor(1);
                w->getRight()->setColor(1);
                rotateLeft(root, current->parent); 
                root = current; 
                
            }
            
        }
        else if(current == current->parent->getRight()) {
            cout << "current is right child" << endl;
            w = current->parent->getLeft();
            if(w == NULL) {
                current->setColor(1);
                return;
            }
            else if(current->parent->getLeft()->getColor() == 0) {
                cout << "currents parent left child is red" << endl;
                current->parent->getLeft()->setColor(1);
                current->parent->setColor(0); 
                rotateRight(root, current->parent);
                current->parent->setLeft(w);
            }
            
            else if(w->getLeft()->getColor() == 1 && w->getRight()->getColor() == 1) {
                cout << "ws left and right are black" << endl;
                w->setColor(0);
                current = current->parent; 
            }
            else{
                cout << "else right" << endl;
                if(w->getLeft()->getColor() == 1) {
                    cout << "ws left is black" << endl;
                    w->getRight()->setColor(1);
                    w->setColor(0);
                    rotateLeft(root, w);
                    current->parent->setLeft(w);
                }
                cout << "else right2" << endl;
                w->setColor(current->parent->getColor());
                current->parent->parent->setColor(1);
                w->getLeft()->setColor(1);
                rotateRight(root, current->parent); 
                root = current; 
                
            }
            
        }
        
        current->setColor(1);
        cout << "end delete fix" << endl;
        
    }    
    cout << "out of while loop" << endl;
    
    
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


node* minimum(node* current) {
    cout << "minimum" << endl;
    while(current->getLeft() != NULL) {
        current = current->getLeft();
    }
    return current; 
}

void transplant(node* &root, node* current, node* v) {
    cout << "transplant" << endl;
    cout << "current" << current->getValue() << endl;
    if(v != NULL) {
        cout << "v" << v->getValue() << endl;
    }
    if(current->parent == NULL) {
        cout << "transplant 1" << endl;
        root = v;
    }
    //if current is left child
    else if(current == current->parent->getLeft()) {
        cout << "transplant 2" << endl;
        v = current->parent->getRight(); 
        //current->parent->setLeft(v);
    }
    //if current is right child
    else {
        cout << "transplant 3" << endl;
        v = current->parent->getRight();
        //current->parent->setRight(v);
    }
    cout << "transplant 4" << endl;
    if(v == NULL) {
        cout << "v is null" << endl;
    }
    v->parent = current->parent; 
    cout << "current val" << current->getValue() << endl;
    cout << "exit transplant" << endl;
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
}