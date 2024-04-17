// بسم الله الرحمن الرحيم
// Created by BnAdel on 4/16/2024.
// =====> DOUBLYLINKEDLIST <=====

#include <iostream>
#include <cassert>

// NODE => NULL<---|Prev|Data|Next|---><----|Prev|Data|Next|--->NULL
struct Node {
    int data;
    Node* next;
    Node* prev;
    // Parametrized Constructor to initialize the data
    Node(int d) : data(d) {}
    // Track The Nodes tha will be deleted
    ~Node() {
        std::cout << "The Deleted Node: Data => " << this->data << " | Address => " << this << '\n';
    }
};

class Linkedlist {
private:
    Node* head {};
    Node* tail {};
    int length = 0;
public:
    // To prevent crashes
    Linkedlist(){}
    Linkedlist(const Linkedlist&) = delete;
    Linkedlist &operator = (const Linkedlist &another) = delete;
    // Destructor to free the memory from nodes
    // Analysis: O(N) TIME | O(1) MEMORY
    ~Linkedlist() {
        std::cout << "\n\t\t----< CODE LOG >----\n";
        while(this->head != nullptr) {
//            std::cout << this->head->data << " ";
            Node *tem = this->head;
            this->head = this->head->next;
            delete tem; // release the memory
            tem = nullptr; // reset the memory
        }
    }

    // Insert a New Node in the end
    // Analysis: O(1) TIME | O(1) MEMORY
    void insert_end(int val) {
        Node* newNode = new Node(val);
        if(this->head == nullptr) {
            this->head = newNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            this->tail = newNode;
        }
        else {
            this->tail->next = newNode;
            newNode->prev = tail;
            newNode->next = nullptr;
            this->tail = newNode;
        }
        this->length++;
    }
    // Insert a New Node in the front
    // Analysis: O(1) TIME | O(1) MEMORY
    void insert_front(int val) {
        Node* newNode = new Node(val);
        if(this->head == nullptr) {
            this->head = newNode;
            newNode->next = nullptr;
            newNode->prev = nullptr;
            this->tail = newNode;
        }
        else {
            this->head->prev = newNode;
            newNode->next = this->head;
            newNode->prev = nullptr;
            this->head = newNode;
        }
        this->length++;
    }
    // Remove a Node
    // Analysis: O(1) TIME | O(1) MEMORY
    void remove_node(Node *node) {
        delete node;
        node = nullptr;
        this->length--;
    }
    // Searching for a Node
    // Analysis: O(N) TIME | O(1) MEMORY
    Node *search_for_node(int val) {
        assert(this->getLen());
        Node *temHead = this->head;
        while(temHead) {
            if(temHead->data == val)
                return temHead;
            temHead = temHead->next;
        }
        return nullptr;
    }
    // This is an interface for the client (Main) to deal with
    // Because We want to deal with LinkedList Class only,
    // Assuming that We don't know that there is a class called (Node)
    // Analysis: O(N) TIME | O(1) MEMORY
    std::string search(int val) {
        Node *node = search_for_node(val);
        if(node) return "Node is FOUND :)";
        return "Node is not FOUND :(";
    }
    // Delete the front node
    // Analysis: O(1) TIME | O(1) MEMORY
    void delete_front() {
        assert(this->getLen()); // check the length first
        Node *delNode = this->head;
        this->head = this->head->next;
        remove_node(delNode);
    }
    // Delete the back node
    // Analysis: O(1) TIME | O(1) MEMORY
    void delete_back() {
        Node* delNode = this->tail;
        this->tail = this->tail->prev;
        this->tail->next = nullptr;
        remove_node(delNode);
    }
    // Delete a Node With Specific Value
    // Analysis: O(N) TIME | O(1) MEMORY
    void delete_node(int val) {
        Node *delNode = search_for_node(val);
        assert(delNode);
        if(delNode == this->head) delete_front();
        else if(delNode == this->tail) delete_back();
        else {
            Node *prevNode = delNode->prev;
            Node *nextNode = delNode->next;
            prevNode->next = nextNode;
            nextNode->prev = prevNode;
            remove_node(delNode);
        }
    }
    // Get The Current Length of The LinkedList
    int getLen() {
        return this->length;
    }
    // Print The LinkedList in a reverse order
    // Analysis: O(N) TIME | O(1) MEMORY
    void rev_print() {
        assert(this->getLen());
        Node* temTail = this->tail;
        while(temTail) {
            std::cout << temTail->data << " <=> ";
            temTail = temTail->prev;
        }
    }
    // Print All Nodes
    // Analysis: O(N) TIME | O(1) MEMORY
    void print() {
        assert(this->getLen());
        Node* temHead = this->head;
        std::cout << "\n====> The LinkedList <====\n";
        while(temHead) {
            if(temHead == this->head) std::cout << "NULL<--- " << temHead->data;
            else std::cout << " <=> " << temHead->data;
            temHead = temHead->next;
            if(!temHead) std::cout << "--->NULL\n";
        }
    }

};


int main() {
    Linkedlist l;
    l.insert_end(10);
    l.insert_end(20);
    l.insert_end(30);
    l.insert_end(40);
    l.insert_end(50);
    l.insert_front(44);
    l.insert_front(12);
    l.delete_front();
    l.delete_back();
    l.print();
    std::cout << "\nSearching for a node with value (20) .... \n\t" << l.search(20) << '\n';
    l.delete_node(20);
    l.print();
    std::cout << "\nSearching for a node with value (20) .... \n\t" << l.search(20) << '\n';
//    l.rev_print();

    return 0;
}