// بسم الله الرحمن الرحيم
// Created by BnAdel on 5/13/2024.
// ===> STACK USING LINKEDLIST <===

#include <iostream>
#include <cassert>

// NODE => |Data|Next| ---> |Data|Next|
struct Node {
    int data;
    Node* next;
    // Parametrized Constructor to initialize the data
    Node(int d) : data(d) {}
    // Track The Nodes tha will be deleted
    ~Node() {
        std::cout << "The Deleted Node: Data => " << this->data << " | Address => " << this << '\n';
    }
};

class Stack {
private:
    Node *head;
    int length;

public:
    Stack() : length(0), head(nullptr) {}

    void push(int val) {
        Node *newNode = new Node(val);
        newNode->next = this->head;
        this->head = newNode;
        this->length++;
    }

    void pop() {
        assert(this->length);
        Node *delNode = this->head;
        this->head = this->head->next;
        delete delNode;
        delNode = nullptr;
        this->length--;
    }

    int top() {
        assert(this->length);
        return this->head->data;
    }

    void print() {
        if(this->length <= 0) { std::cout << "\n|| NO ELEMENTS YET ||\n"; return; }
        std::cout << "==> STACK ELEMENTS <==\n";
        Node *temHead = this->head;
        while(temHead) {
            std::cout << temHead->data << '\n';
            temHead = temHead->next;
        }
    }
};



int main() {

    Stack *st = new Stack();
    st->push(1);
    st->push(2);
    st->push(3);
    st->push(88);
    st->push(45);
    st->push(89);
    st->push(100);

    st->print();

    st->pop();

    st->print();

    st->pop();
    st->pop();
    st->pop();

    st->print(); 

    return 0;
}
