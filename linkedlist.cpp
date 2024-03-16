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
    Node *head {};
    Node *tail {};
    int lenght = 0;

public:
//    Linkedlist(Node *h) : head(h) {}

    // Insert a new node in the end
    void insert_end(int val) {
        // Make a new node
        Node *newNode = new Node(val);
        // First if the head is null
        if(this->head == nullptr && this->tail == nullptr) {
            this->head = newNode;
            this->tail = newNode;
            newNode->next = nullptr;
        }
        else {
            // IF THERE IS NO TAIL::Here we will make a linear search of the last element
//            Node *tem = head;
//            while(tem->next != nullptr) tem = tem->next;
            this->tail->next = newNode;
            this->tail = newNode;
            newNode->next = nullptr;
        }
        ++lenght;
    }


    int get_nth_node(int n) {
        if(n > this->getLength() || n <= 0) return -1;
        Node *temHead = this->head;
        while(n > 1) {
            temHead = temHead->next;
            n--;
        }
        return temHead->data;
    }
    int getHead() {
        if(this->head == nullptr) return -1;
        return this->head->data;
    }
    int getTail() {
        if(this->tail == nullptr) return -1;
        return this->tail->data;
    }
    int getLength() {
        return this->lenght;
    }

    // Searching for a node
    int find(int val) {
        Node *curNode = this->head, *prevNode = nullptr;
        int pos = 1;
        while(curNode != nullptr) {
            // When finding the element I will swap the current node with the previous (shifting)
            if(curNode->data == val) {
                if(prevNode != nullptr) {
                    std::swap(curNode->data, prevNode->data);
                }
                return pos;
            }
            prevNode = curNode;
            curNode = curNode->next;
            pos++;
        }
        return -1; // Not Found
    }

    void print() {
        // Iterative using WHILE
        if(this->head == nullptr) { std::cout << "NO ELEMENTS YET!!\n"; return; }
        Node *temHead = this->head;
        while(temHead != nullptr) {
            std::cout << temHead->data;
            temHead = temHead->next;
            if(temHead != nullptr) std::cout << "->";
        }
        std::cout << '\n';
        // Iterative using FOR
        /* for(;head != nullptr;head=head->next) {
            std::cout << head->data;
            if(head->next != nullptr) std::cout << "->";
        }*/
        // Recursive
        /*if(this->head == nullptr) { std::cout << "NO ELEMENTS YET!!\n"; return; }
        std::cout << head->data;
        if(head->next != nullptr) std::cout << "->";
        this->head = this->head->next;
        print();*/
    }
};


int main() {
    // ===> FIRST <===
    /*Node *n1 = new Node(5);
    Node *n2 = new Node(2);
    Node *n3 = new Node(4);
    Node *n4 = new Node(6);
    Node *n5 = new Node(9);

    n1->next = n2;
    n2->next = n3;
    n3->next = n4;
    n4->next = n5;
    n5->next = nullptr;*/

    // Printing Linkedlist
    Linkedlist l;
    l.print();
    l.insert_end(5);
    l.insert_end(6);
    l.insert_end(2);
    l.insert_end(1);
    l.insert_end(8);
    l.insert_end(100);
    l.print();

    // Searching for an element
    int findEle = l.find(6);
    if(findEle != -1)
        std::cout << "Searching for a node (6) ..... FOUND :) at position [" << findEle << "]\n";
    else
        std::cout << "Searching for a node (6) ..... NOT FOUND :|\n";
    // After shifting if the element found
    l.print();

    std::cout << "The Head => " << l.getHead() << std::endl;
    std::cout << "The Tail => " << l.getTail() << std::endl;
    std::cout << "The Length => " << l.getLength() << std::endl;
    std::cout << "The 4th element => " << l.get_nth_node(1) << std::endl;


    return 0;
}
