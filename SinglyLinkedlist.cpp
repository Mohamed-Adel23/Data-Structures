// بسم الله الرحمن الرحيم
// Created by BnAdel on 3/14/2024.
// =====> SINGLYLINKEDLIST <=====


#include<iostream>
#include <cassert>
#include <sstream>
#include <vector>
#include <set>

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

    // Remove a Node
    // Analysis: O(1) TIME | O(1) MEMORY
    void remove_node(Node *node) {
        delete node;
        node = nullptr;
        this->length--;
    }

    // Insert a new node in the front
    // Analysis: O(1) TIME | O(1) MEMORY
    void insert_front(int val) {
        Node *newNode = new Node(val);
        newNode->next = this->head;
        this->head = newNode;
        this->length++;
        if(this->length == 1)
            this->tail = this->head;
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
        if(this->head == nullptr && this->tail == nullptr) {
            this->head = newNode;
            this->tail = newNode;
            newNode->next = nullptr;
        }
        else {
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

    // Delete the back node
    // Analysis: O(N) TIME | O(1) MEMORY
    void delete_back() {
        assert(this->length);
        Node *delNode = this->tail;
        // Get The Previous Node of The Tail One.
        Node *temNode = this->get_nth_node_front(this->length-1);
        // Make the whole tail points to the previous NODE
        this->tail = temNode;
        // Make the next of the last node points to NULLPTR
        temNode->next = nullptr;
        // Remove the node
        temNode = nullptr;
        remove_node(delNode);
    }

    // Insert a new Node in nth position
    void insert_nth_node(int pos, int val) {
        assert(pos > 0 && pos <= this->length);
        // Create a New Node
        Node *newNode = new Node(val);
        // Pick the Current Node and its previous one
        Node *curNode = this->get_nth_node_front(pos),
        *prevNode  = this->get_nth_node_front(pos-1);
        // Fix Pointers
        prevNode->next = newNode;
        newNode->next = curNode;
        ++this->length;
    }

    // Delete the nth Node
    // Analysis: O(N) TIME | O(1) MEMORY
    void delete_nth_node(int pos) {
        assert(this->length);
        assert(pos > 0 && pos <= this->length);
        if(pos == 1) {
            delete_front();
            return;
        }
        else if(pos == this->length) {
            delete_back();
            return;
        }
        // Pick the Node and its previous one
        Node *curNode = this->get_nth_node_front(pos),
        *prevNode  = this->get_nth_node_front(pos-1);
        // Delete and link
        delete_node_and_link(prevNode, curNode);
    }

    // Delete a node with a value
    // Analysis: O(N) TIME | O(1) MEMORY
    void delete_valued_node(int val) {
        assert(this->length);
        if(this->head->data == val) {
            delete_front();
            return;
        }
        else if(this->tail->data == val) {
            delete_back();
            return;
        }
        // Searching for the Node
        Node *temNode = this->head, *prevNode {};
        while(temNode && temNode->data != val) prevNode = temNode, temNode = temNode->next;
        // If there is no such a node with this value
        assert(temNode);
        // Delete and link
        delete_node_and_link(prevNode, temNode);
    }

    // Get The nth from the front
    // Analysis: O(N) TIME | O(1) MEMORY
    Node *get_nth_node_front(int n) {
        assert(this->length);
        Node *temHead = this->head;
        while(n > 1) {
            temHead = temHead->next;
            n--;
        }
        return temHead;
    }

    // Get The nth from the back
    // Analysis: O(N) TIME | O(1) MEMORY
    Node *get_nth_node_back(int n) {
        assert(this->length);
        // change the n to be from the last
        n = this->length - n + 1;
        Node *temHead = this->head;
        while(n > 1) {
            temHead = temHead->next;
            n--;
        }
        return temHead;
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

    // ==================
    // ==== Problems ====
    // ==================
    // *** Homework (2) ***
    // Recursive function to reverse the nodes of LinkedList
    // Analysis: O(N) TIME | O(1) MEMORY
    Node *reverse_nodes(Node *cur) {
        // 1->2->3->4->5
        while(cur && cur->next) {
            Node *tem = reverse_nodes(cur->next);
            tem->next = cur;
            cur->next = nullptr;
        }
        return cur;
    }

    // An Interface for the client to deal with reverse function
    void reverse() {
        Node *node = this->reverse_nodes(this->head);
        this->swap_head_tail();
    }

    // Swap head and tail
    // Analysis: O(1) TIME | O(1) MEMORY
    void swap_head_tail() {
        Node *tem = this->head;
        this->head = this->tail;
        this->tail = tem;
    }

    // Swap pairs in the linkedList
    void swap_pairs() {
        // 1->2->3->4->5
        Node *temHead = this->head;
        while(temHead && temHead->next) {
            Node *nextNode = temHead->next;
            std::swap(nextNode->data, temHead->data);
            temHead = temHead->next->next;
        }
        // 2->1->4->3->5
    }

    // Delete Nodes from LinkedList directly
    void delete_node_and_link(Node* prevNode, Node *curNode) {
        if(curNode == this->head) delete_front();
        else if(curNode == this->tail) delete_back();
        else {
            prevNode->next = curNode->next;
            remove_node(curNode);
        }
    }

    // Delete Even Positions
    void delete_even_positions() {
        int i = 1;
        std::vector<std::pair<Node*, Node*>> delNodes;
        Node *temHead = this->head, *prevNode {};
        while(temHead) {
            if(i%2 == 0) delNodes.push_back({prevNode, temHead});
            i++;
            prevNode = temHead;
            temHead = temHead->next;
        }
        for(auto it: delNodes) delete_node_and_link(it.first, it.second);
    }

    // Insert values to be sorted
    void insert_sorted(int val) {
        if(this->head == nullptr && this->tail == nullptr) {
            Node *newNode = new Node(val);
            this->head = this->tail = newNode;
            newNode->next = nullptr;
            ++this->length;
        }
        else {
            if(this->head->data >= val) insert_front(val);
            else if(this->tail->data <= val) insert_end(val);
            else {
                Node *curNode = this->head->next;
                int i = 2;
                while(curNode->data < val) curNode = curNode->next, i++;
                insert_nth_node(i, val);
            }
        }
    }

    // ===============================
    // ==== HW3 - Medium Q ====
    // [1] Swap The nodes of head and tail
    void swap_head_tail_nodes() {
        assert(this->length > 1);
        Node *prevTail = this->get_nth_node_back(2);
        prevTail->next = this->head;
        this->tail->next = this->head->next;
        this->head->next = nullptr;
        swap_head_tail();
    }

    // [2] Rotate Left
    void left_rotate(int k) {
        assert(this->length > 1);
        int rotate = k % this->length;
        // The LinkedList stays the same
        if(rotate == 0) return;
        // Get The nth element
        Node *curNode = get_nth_node_front(rotate);
        // Fix The Pointers
        this->tail->next = this->head;
        this->head = curNode->next;
        curNode->next = nullptr;
        this->tail = curNode;
    }

    // [3] Removing Duplicates
    void remove_duplicates() {
        assert(this->length > 1);
        int i = 2;
        std::set<int> st;
        st.emplace(this->head->data);
        Node *temHead = this->head->next;
        while(temHead) {
            if(st.find(temHead->data) != st.end()) {
                // Fix the pointer to next before deleting
                temHead = temHead->next;
                delete_nth_node(i);
            }
            else {
                st.emplace(temHead->data);
                i++;
                temHead = temHead->next;
            }
        }
    }

    // [4] Remove The last Occurrence
    void remove_last_occurrence(int key) {
        Node *curNode {}, *prevNode {}, *prevDelNode {}, *temHead = this->head;
        while(temHead) {
            if(temHead->data == key) prevDelNode = prevNode, curNode = temHead;
            prevNode = temHead;
            temHead = temHead->next;
        }
        // if delNode is null then the key value is not found
        assert(curNode);
        delete_node_and_link(prevDelNode, curNode);
    }

    // [5] Move To Back
    void move_to_back(int key) {
        Node *temHead = this->head, *prevNode {}, *flagNode {};
        while(temHead && temHead != flagNode) {
            if(temHead->data == key) {
                // Make the flag points to the first element of the key
                if(!flagNode) flagNode = temHead;
                if(temHead == this->head) {
                    temHead = temHead->next;
                    this->tail->next = this->head;
                    this->tail = this->head;
                    this->head = this->head->next;
                    this->tail->next = nullptr;
                }
                else {
                    Node *temHead2 = temHead;
                    temHead = temHead->next;
                    prevNode->next = temHead2->next;
                    this->tail->next = temHead2;
                    this->tail = temHead2;
                    this->tail->next = nullptr;
                }
            }
            else {
                prevNode = temHead;
                temHead = temHead->next;
            }
        }
        // If the key not found
        assert(flagNode);
    }

    // [6] Recursive Max
    int max_node() {
        assert(this->length);
        if(!this->head->next) return this->head->data;
        Node *temHead = this->head;
        this->head = this->head->next;
        return std::max(temHead->data, max_node());
    }

    // ================

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

    // Testing function
    void test01() {
        this->insert_end(6);
        this->insert_end(10);
        this->insert_end(8);
        this->insert_end(15);
        this->insert_end(20);
        this->insert_end(1);
        this->insert_end(99);
        this->insert_end(12);
        this->print();
        std::cout << "\nThe Max Node is [" << this->max_node() << "]\n";
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
    Linkedlist *l = new Linkedlist();
    l->test01();


    return 0;
}
