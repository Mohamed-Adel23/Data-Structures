// بسم الله الرحمن الرحيم
// Created by BnAdel on 3/14/2024.
// =====> LINKEDLIST <=====


#include<iostream>

struct Node {
    int data;
    Node* next;
    // Parametrized Constructor to initialize the data
    Node(int d) : data(d) {}
};

class Linkedlist {
private:
    Node *head;

public:
    Linkedlist(Node *h) : head(h) {}

    // Searching for a node
    bool find(int val) {
        Node *temHead = this->head;
        while(temHead != nullptr) {
            if(temHead->data == val) return true;
            temHead = temHead->next;
        }
        return false;
    }

    void print(Node *head) {
        // Iterative using WHILE
        /*while(head != nullptr) {
            std::cout << head->data;
            head = head->next;
            if(head != nullptr) std::cout << "->";
        }*/
        // Iterative using FOR
        /* for(;head != nullptr;head=head->next) {
            std::cout << head->data;
            if(head->next != nullptr) std::cout << "->";
        }*/
        // Recursive
        if(head == nullptr) return;
        std::cout << head->data;
        if(head->next != nullptr) std::cout << "->";
        print(head->next);
    }
};


int main() {
    Node *n1 = new Node(5);
    Node *n2 = new Node(2);
    Node *n3 = new Node(4);
    Node *n4 = new Node(6);
    Node *n5 = new Node(9);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = nullptr;

    // Printing Linkedlist
    Linkedlist l(n1);
    l.print(n1);

    // Searching for an element
    bool findEle = l.find(1);
    if(findEle)
        std::cout << "\nSearching for a node (1) ..... FOUND :)";
    else
        std::cout << "\nSearching for a node (1) ..... NOT FOUND :|";


    return 0;
}
