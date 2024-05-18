// بسم الله الرحمن الرحيم
// Created by BnAdel on 5/16/2024.
// ===> QUEUE USING LINKEDLIST <===

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

// A Singly LinkedList with Head, Tail, Length
class Linkedlist {
private:
    Node *head{};
    Node *tail{};
    int length = 0;

public:
    // To prevent crashes
    Linkedlist() {}

    Linkedlist(const Linkedlist &) = delete;

    Linkedlist &operator=(const Linkedlist &another) = delete;

    // Destructor to free the memory from nodes
    // Analysis: O(N) TIME | O(1) MEMORY
    ~Linkedlist() {
        std::cout << "\n\t\t----< CODE LOG >----\n";
        while (this->head != nullptr) {
            std::cout << this->head->data << " ";
            Node *tem = this->head;
            this->head = this->head->next;
            delete tem; // release the memory
            tem = nullptr; // reset the memory
        }
    }

    // Remove a Node
    // Analysis: O(1) TIME | O(1) MEMORY
    void remove_node(Node *node) {
        delete node;
        node = nullptr;
        this->length--;
    }

    // Delete the front node
    // Analysis: O(1) TIME | O(1) MEMORY
    void delete_front() {
        assert(this->length); // check the length first
        Node *delNode = this->head;
        this->head = this->head->next;
        remove_node(delNode);
    }

    // Insert a new node in the end
    // Analysis: O(1) TIME | O(1) MEMORY
    void insert_end(int val) {
        // Make a new node
        Node *newNode = new Node(val);
        // First if the head is null
        if (this->head == nullptr && this->tail == nullptr) {
            this->head = newNode;
            this->tail = newNode;
            newNode->next = nullptr;
        } else {
            // IF THERE IS NO TAIL::Here we will make a linear search of the last element
//            Node *tem = head;
//            while(tem->next != nullptr) tem = tem->next;
            // Fix the next pointer of the tail
            this->tail->next = newNode;
            // Make the whole tail points to the new NODE
            this->tail = newNode;
            // Make the next of the new node points to NULLPTR
            newNode->next = nullptr;
        }
        ++this->length;
    }

    // Printing nodes
    // Analysis: O(N) TIME | O(1) MEMORY
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
    }
};

class Queue {
private:
    Linkedlist *list;

public:
    Queue() {
        list = new Linkedlist();
    }

    void enqueue(int val) {
        list->insert_end(val);
    }
    void dequeue() {
        list->delete_front();
    }
    void print() {
        list->print();
    }
};

int main() {
    Queue *q = new Queue();
    q->enqueue(1);
    q->enqueue(2);
    q->enqueue(3);
    q->enqueue(4);
    q->enqueue(5);
    q->dequeue();
    q->dequeue();
    q->print();

    return 0;
}


