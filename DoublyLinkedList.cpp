// بسم الله الرحمن الرحيم
// Created by BnAdel on 4/16/2024.
// =====> DOUBLYLINKEDLIST <=====

#include <iostream>
#include <cassert>
#include <vector>
#include <bits/move_only_function.h>

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
    // Get nth Node Forward
    Node *get_nth_node_forward(int pos) {
        assert(pos <= this->length);
        Node *temHead = this->head;
        while(temHead && pos > 1)
            temHead = temHead->next, pos--;
        return temHead;
    }
    // Get nth Node Backward
    Node *get_nth_node_backward(int pos) {
        assert(pos <= this->length);
        Node *temTail = this->tail;
        while(temTail && pos > 1)
            temTail = temTail->prev, pos--;
        return temTail;
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

    // ==> HW1 - 2-Easy-Problems
    // [1] Delete All Nodes with a key
    void delete_nodes_with(int val) {
        assert(this->getLen());
        Node *temHead = this->head;
        while(temHead) {
            if(temHead->data == val) temHead = temHead->next, delete_node(val);
            else temHead = temHead->next;
        }
    }
    // [2] Is Palindrome
    bool is_palindrome() {
        Node *temHead = this->head, *temTail = this->tail;
        while(temHead != temTail && temHead->next != temTail) {
            if(temHead->data != temTail->data) return false;
            temHead = temHead->next;
            temTail = temTail->prev;
        }
        if(temHead != temTail && temHead->data != temTail->data) return false;
        return true;
    }

    // HW2 - 4-Medium-Problems
    // [1] Find The Middle Element (First Approach)
    int find_middle_01() {
        Node *temHead = this->head, *temTail = this->tail;
        while(temHead != temTail && temHead->next != temTail) {
            temHead = temHead->next;
            temTail = temTail->prev;
        }
        if(temHead == temTail) return temHead->data;
        return temTail->data;
    }
    // (Second Approach)
    int find_middle_02() {
        Node *slow_pointer = this->head;
        Node *fast_pointer = this->head;
        while(fast_pointer && fast_pointer->next) {
            fast_pointer = fast_pointer->next->next;
            slow_pointer = slow_pointer->next;
        }
        return slow_pointer->data;
    }

    // [2] Swap Forward with Backward
    void swap_head_tail() {
        if(this->length > 2) {
            this->tail->next = this->head->next;
            this->head->prev = this->tail->prev;
            this->tail->prev->next = this->head;
            this->head->next->prev = this->tail;
            this->head->next = nullptr;
            this->tail->prev = nullptr;
        }
        else {
            this->tail->next = this->head;
            this->head->prev = this->tail;
            this->head->next = nullptr;
            this->tail->prev = nullptr;
        }
        // Swapping the actual head and tail
        std::swap(this->head, this->tail);
    }
    void swap_kth(int k) {
        // If k is greater than the half
        assert(k <= this->length/2);
        if(k == 1)
            swap_head_tail();
        else if(k == this->length/2 && this->length%2 == 0) {
            Node *node_forward = get_nth_node_forward(k);
            Node *node_backward = get_nth_node_backward(k);
            Node *t1 = node_forward->prev, *t2 = node_backward->next;
            node_forward->next = t2;
            node_backward->prev = t1;
            node_forward->prev = node_backward;
            node_backward->next = node_forward;
            t1->next = node_backward;
            t2->prev = node_forward;
        }
        else if(k == this->length/2 && this->length%2 == 1) {
            Node *node_forward = get_nth_node_forward(k);
            Node *node_backward = get_nth_node_backward(k);
            Node *t1 = node_forward->prev, *t2 = node_backward->next, *t3 = node_forward->next;
            node_forward->next = t2;
            node_backward->prev = t1;
            node_forward->prev = t3;
            node_backward->next = t3;
            t3->next = node_forward;
            t3->prev = node_backward;
            t1->next = node_backward;
            t2->prev = node_forward;
        }
        else {
            Node *node_forward = get_nth_node_forward(k);
            Node *node_backward = get_nth_node_backward(k);
            Node *t1 = node_forward->prev, *t2 = node_backward->next, *t3 = node_forward->next, *t4 = node_backward->prev;
            node_forward->next = t2;
            node_backward->prev = t1;
            node_forward->prev = t4;
            node_backward->next = t3;
            t3->prev = node_backward;
            t4->next = node_forward;
            t1->next = node_backward;
            t2->prev = node_forward;
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
    l.insert_end(60);
    l.insert_end(70);
    l.insert_end(80);
    l.insert_end(90);
    std::cout << "\nBEFORE\n";
    l.print();
    std::cout << "\nAFTER\n";
    l.swap_kth(3);
    l.print();

    //std::cout << "\nIs Palindrome: " << (l.is_palindrome()?"YES":"NO") << std::endl;
    //std::cout << "\nThe Middle Element is [" << l.find_middle_02() << "]" << std::endl;

    return 0;
}