#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <cstring>

using namespace std; 

class node {
    public: 
    node(int data);
    ~node();
    void setRight(node* newnext);
    node* getRight();
    void setLeft(node* newnext);
    node* getLeft(); 
    void setValue(int valuetwo);
    int getValue();
    void setColor(int colort);
    int getColor();
    
    private:
    int data;
    int color; //0 is red, 1 is black
    node* newleft;
    node* newright;
    node* right;
    node* left;
    
};

#endif