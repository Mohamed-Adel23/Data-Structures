// بسم الله الرحمن الرحيم
// Created by BnAdel on 3/14/2024.
// =====> LINKEDLIST <=====


#include<iostream>
#include <cassert>
#include <sstream>
#include <vector>

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
    Node *head {};
    Node *tail {};
    int length = 0;
    std::vector<Node*> debug_data;

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
            std::cout << this->head->data << " ";
            Node *tem = this->head;
            this->head = this->head->next;
            delete tem; // release the memory
            tem = nullptr; // reset the memory
        }
    }

    // Insert a new node in the front
    // Analysis: O(1) TIME | O(1) MEMORY
    void insert_front(int val) {
        Node *newNode = new Node(val);
        newNode->next = this->head;
        this->head = newNode;
        this->length++;
        if(this->length == 1)
            this->head = this->tail;
    }

    // Delete the front element
    // Analysis: O(1) TIME | O(1) MEMORY
    void delete_front() {
        assert(this->length); // check the length first
        Node *delNode = this->head;
        this->head = this->head->next;
        delete delNode;
        delNode = nullptr;
        this->length--;
    }

    // Insert a new node in the end
    // Analysis: O(1) TIME | O(1) MEMORY
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
        ++this->length;
    }

    // Get The nth from the front
    // Analysis: O(N) TIME | O(1) MEMORY
    int get_nth_node_front(int n) {
        assert(this->length);
        Node *temHead = this->head;
        while(n > 1) {
            temHead = temHead->next;
            n--;
        }
        return temHead->data;
    }

    // Get The nth from the back
    // Analysis: O(N) TIME | O(1) MEMORY
    int get_nth_node_back(int n) {
        assert(this->length);
        // change the n to be from the last
        n = this->length - n + 1;
        Node *temHead = this->head;
        while(n > 1) {
            temHead = temHead->next;
            n--;
        }
        return temHead->data;
    }

    // Analysis: O(1) TIME | O(1) MEMORY
    int getHead() {
        assert(this->head);
        return this->head->data;
    }

    // Analysis: O(1) TIME | O(1) MEMORY
    int getTail() {
        assert(this->tail);
        return this->tail->data;
    }

    // Analysis: O(1) TIME | O(1) MEMORY
    int getLength() {
        return this->length;
    }

    // Check if two linkedlists are equal
    // Analysis: O(N) TIME | O(1) MEMORY
    bool is_same(Linkedlist *l2) {
        if(this->length != l2->length) return false;
        Node *h1 = this->head, *h2 = l2->head;
        while(h1 != nullptr && h2 != nullptr) {
            if(h1->data != h2->data) return false;
            h1 = h1->next;
            h2 = h2->next;
        }
        return true;
    }

    // Searching for a node
    // Analysis: O(N) TIME | O(1) MEMORY
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

    // Visualizing LinkedList using vector
    // code here ...

    // ===> DEBUGGING FUNCTIONS <===
    // Printing nodes in another way
    void debug_print_single_node(Node *node) {
        if(node == nullptr) std::cout << "Oops, nullptr\n";
        std::cout << node->data << " ";
        if(node->next == nullptr) std::cout << "X ";
        else std::cout << node->next->data << " ";

        if(node == this->head) std::cout << "Head\n";
        else if(node == this->tail) std::cout << "Tail\n";
        else std::cout << '\n';
    }
    void debug_print_list() {
        std::cout << "\n\tPRINTING LINKEDLIST\n\t---------------\n";
        Node *temHead = this->head;
        while(temHead != nullptr)
            debug_print_single_node(temHead), temHead = temHead->next;
        std::cout << "\t---------------\n";
    }
    // Convert The LinkedList to a string to check if it matches the expected output
    std::string debug_to_string() {
        if(this->length == 0) return "";
        std::ostringstream oss;
        for(Node* ele = this->head; ele != nullptr; ele=ele->next) {
            oss << ele->data;
            if(ele->next != nullptr)
                oss << " ";
        }
        return oss.str();
    }
    // A Function To Debug and verify the data integrity of the linkedlist
    void debug_verify_data_integrity() {
        if(this->length == 0) {
            assert(this->head == nullptr);
            assert(this->tail == nullptr);
        }
        else {
            assert(this->head != nullptr);
            assert(this->tail != nullptr);
            if(this->length == 1)
                assert(this->head == this->tail);
            else
                assert(this->head != this->tail);
            assert(this->tail->next == nullptr);
        }
        // Check if the length of the linkedlist correct
        int temLen = 0;
        for(Node *ele = this->head; ele != nullptr; ele=ele->next, temLen++)
            assert(temLen < 1000); // Ensure that There is no cycles
        assert(this->length == temLen);
//        assert()
    }

    // Testing functions
    void test01() {
        this->insert_end(12);
        this->insert_end(56);
        this->insert_end(60);
        this->insert_end(98);
        this->insert_end(41);
        this->insert_end(37);
        // check if the nodes representation match the expected string
        std::string checkStr = "12 56 60 98 41 37";
        std::string result = this->debug_to_string();
        if(checkStr != result)
            std::cout << "\nLinkedList: " << result << "\t" << "Expected: " << checkStr << "\n=> Unfortunately!!Your LinkedList doesn't match the expected result\n";
        else
            std::cout << "\nLinkedList: " << result << "\t" << "Expected: " << checkStr << "\n=> Your LinkedList matches the expected result\n";

        this->debug_print_list();

        this->debug_verify_data_integrity();
    }
    void test02() {
        this->insert_end(10);
        this->insert_end(20);
        this->insert_end(30);
        this->insert_end(40);
        this->print();
        this->insert_front(80);
        this->insert_front(70);
        this->print();
        this->delete_front();
        this->print();
        this->debug_verify_data_integrity();
        std::cout << "Element at position (2) from front " << this->get_nth_node_front(2) << '\n';
        std::cout << "Element at position (2) from back " << this->get_nth_node_back(2) << '\n';
    }
    void test03() {
        Linkedlist *l2 = new Linkedlist();
        this->insert_end(1);
        this->insert_end(2);
        this->insert_end(3);
        l2->insert_end(1);
        l2->insert_end(2);
        l2->insert_end(3);
        std::cout << (this->is_same(l2)?"SAME":"NOT SAME") << '\n';
        l2->insert_front(0);
        this->insert_end(0);
        std::cout << (this->is_same(l2)?"SAME":"NOT SAME") << '\n';
        l2->delete_front();
        l2->insert_end(10);
        std::cout << (this->is_same(l2)?"SAME":"NOT SAME") << '\n';
        delete l2;
    }
};

// A Singly LinkedList with Head Only
class Linkedlist2 {
private:
    Node *head {};

public:
    Linkedlist2() {}

    // Analysis: O(1) TIME | O(1) MEMORY
    void add_element(int val) {
        Node *newNode = new Node(val);
        if(this->head == nullptr) {
            this->head = newNode;
            newNode->next = nullptr;
        }
        else {
            newNode->next = this->head;
            this->head = newNode;
        }
    }

    // Analysis: O(N) TIME | O(1) MEMORY
    Node *get_tail_node() {
        Node *temHead = this->head;
        while(temHead->next != nullptr)
            temHead = temHead->next;
        return temHead;
    }

    // Analysis: O(N) TIME | O(1) MEMORY
    void print() {
        std::cout << "\n\t-----< THE ELEMENTS >-----\n";
        Node *temHead = this->head;
        while(temHead != nullptr) {
            std::cout << temHead->data;
            temHead = temHead->next;
            if(temHead != nullptr)
                std::cout << "->";
        }
        std::cout << '\n';
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
    /* Linkedlist l;
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
    std::cout << "The 4th element => " << l.get_nth_node(1) << std::endl; */

    // Tests
//    Linkedlist *l = new Linkedlist();
//    l->test03();
//    delete l;

    // Linkedlist with head only
    Linkedlist2 *l = new Linkedlist2();
    l->add_element(5);
    l->add_element(6);
    l->add_element(7);
    l->add_element(9);
    l->print();
    Node *node = l->get_tail_node();
    std::cout << "\nThe Tail Node is => " << node->data << '\n';


    return 0;
}
