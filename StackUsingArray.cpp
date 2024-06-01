// بسم الله الرحمن الرحيم
// Created by BnAdel on 4/20/2024.
// ===> STACK USING ARRAY <===

#include <iostream>
#include <cassert>
#include <algorithm>
#include <vector>

// Template Class
template<typename T>
class Stack {
private:
    int top {};
    int size {};
    T *array {};
public:
    // Default Constructor with initial size = 5
    Stack() : size(5), top(-1) {
        this->array = new T[this->size];
    }
    // Parametrized Constructor to Initialize The Stack
    Stack(int size) : size(size), top(-1) {
        this->array = new T[this->size];
    }

    // Expand The Array Size
    // Analysis: O(N) TIME | O(N) MEMORY
    void expand_array_capacity() {
        int newSize = this->size*2;
        T *temArray = this->array;
        this->array = new T[newSize];
        for (int i = 0; i <= this->top; ++i) {
            this->array[i] = temArray[i];
        }
        this->size = newSize;
        delete[] temArray;
        temArray = nullptr;
    }
    // Resize The Array
    void resize(int sz) {
        // The new size must be greater than the current
        assert(this->size < sz);
        this->size = sz;
        // If There are elements in the stack
        T *temArray = this->array;
        this->array = new T[this->size];
        for (int i = 0; i <= this->top; ++i) {
            this->array[i] = temArray[i];
        }
        delete[] temArray;
        temArray = nullptr;
    }

    // Pushing a new element into the stack
    // Analysis: WORST CASE, if we expand the array ==> O(N) TIME | O(N) MEMORY
    void push(T val) {
        if(this->top == this->size-1) {
            expand_array_capacity();
        }
        this->array[++this->top] = val;
    }
    // Deleting the top element
    // Analysis: O(1) TIME | O(1) MEMORY
    void pop() {
        assert(!this->is_empty());
        // Reset the value
//        this->array[this->top--] = -1;
        this->top--;
    }
    // Get the top element in the stack
    // Analysis: O(1) TIME | O(1) MEMORY
    T peek() {
        assert(!this->is_empty());
        return this->array[this->top];
    }
    T top_and_pop() {
        assert(!this->is_empty());
        T ele = this->array[this->top];
        this->pop();
        return ele;
    }
    int get_size() {
        return this->top+1;
    }
    int get_capacity() {
        return this->size;
    }
    bool is_full() {
        return this->top == this->size-1;
    }
    bool is_empty() {
        return this->top == -1;
    }
    // Printing The Stack
    // Analysis: O(N) TIME | O(1) MEMORY
    void print_stack() {
        std::cout << "\nThe Stack Elements: \n";
        if(this->is_empty()) {
            std::cout << "....... NO ELEMENTS YET!!\n";
            return;
        }
        int temTop = this->top;
        while(temTop >= 0) {
            std::cout << "| " << this->array[temTop--] << " |" << (temTop+1 == this->top? "   <--- TOP":"") << '\n';
        }
        std::cout << std::endl;
    }

    // === problems ===
    // (6) E-M-Q
    // [1] Reverse Sub words
    std::string reverse_subwords(std::string word) {
        this->resize(word.size()); // Resize the stack
        std::string newWord = "";
        for(int i = 0; i < word.size(); i++) {
            if(word[i] == ' ') {
                while(!this->is_empty()) {
                    newWord += this->top_and_pop();
                }
                newWord += " ";
            }
            else if(word.size()-1 == i) {
                this->push(word[i]);
                while(!this->is_empty()) {
                    newWord += this->top_and_pop();
                }
            }
            else this->push(word[i]);
        }
        return newWord;
    }
    // [2] Reverse The Number
    int reverse_num(int num) {
        // 123 => 123
        while(num) {
            this->push(num%10);
            num/=10;
        }
        int tens = 1;
        while(!is_empty()) num = this->top_and_pop() * tens + num, tens *= 10;
        return num;
    }
    // [3] Valid Parentheses
    bool is_valid(std::string s) {
        // Empty String Is Valid
        if(s.size() == 0) return true;
        this->resize(s.size());
        for(auto ch: s) {
            if(ch == '(' || ch == '[' || ch == '{') this->push(ch);
            else {
                if(this->is_empty()) return false;
                else {
                    if((this->peek() == '(' && ch == ')') || (this->peek() == '[' && ch == ']') || (this->peek() == '{' && ch == '}')) this->pop();
                    else return false;
                }
            }
        }
        if(this->is_empty()) return true;
        return false;
    }
    // [4] Remove All Adjacent Duplicates in String
    std::string remove_duplicates(std::string s) {
        if(s.size() == 0 || s.size() == 1) return s;
        this->resize(s.size());
        // abbaca
        for(auto ch: s) {
            if(!this->is_empty() && this->peek() == ch) this->pop();
            else this->push(ch);
        }
        std::string ans = "";
        while(!this->is_empty()) ans += this->top_and_pop();
        std::reverse(ans.begin(), ans.end());
        return ans;
    }

    // (6) M-H-Q
    // [1] Asteroid collisions
    // TIME: O(N^2), SPACE: O(N)
    std::vector<int> asteroid_collision(std::vector<int> arr, int len) {
        this->resize(len);
        for(int i = 0; i < len; i++) {
            int asteroid = arr[i];
            bool is_explode = false;
            while(!this->is_empty() && asteroid < 0 && this->peek() > 0) {
                if(this->peek() < abs(asteroid)) {
                    this->pop();
                    continue;
                }
                else if(this->peek() == abs(asteroid)) this->pop(); // Both will explode
                // else the current will explode, so any way we'll break immediately
                is_explode = true;
                break;
            }
            if(!is_explode) this->push(asteroid);
        }
        // reverse stack to make sure the order of elements
        this->reverse_stack();
        std::vector<int> v;
        int temTop = this->top;
        while(temTop >= 0) {
            v.push_back(this->array[temTop--]);
        }
        return v;
    }

    // [2] Insert at the bottom
    // TIME: O(N), SPACE: O(N)
    void insert_bottom_recursive(int x, int temTop, int pos) {
        if(temTop < pos) {
            this->array[pos] = x;
            return;
        }
        this->array[temTop+1] = this->array[temTop];
        return insert_bottom_recursive(x, temTop-1, pos);
    }
    // An interface for insert_bottom function
    void insert_bottom(int x, int pos = 0) {
        if(this->top == this->size-1) {
            expand_array_capacity();
        }
        insert_bottom_recursive(x, this->top, pos);
        this->top++;
    }
    // Another way to insert bottom
    void insert_bottom_2(int x) {
        if(this->is_empty()) this->push(x);
        else {
            int cur = this->top_and_pop();
            insert_bottom_2(x);
            this->push(cur);
        }
    }
    // [3] Reverse Stack
    // TIME: O(N^2), SPACE: O(N)
    void reverse_stack(int pos = 0) {
        if(this->is_empty()) return; // if the stack is empty
        if(pos == this->top) return;
        int ele = this->top_and_pop();
        insert_bottom(ele, pos);
        return reverse_stack(pos+1);
    }
    // Another Way to reverse
    void reverse_stack_2() {
        // WHAT: [1, 2, 3]  =>>  [3, 2, 1]
        if(this->is_empty()) return; // if stack is empty don't make anything
        else {
            // HOW:
            // 3  =>> [1, 2]
            int cur = this->top_and_pop();
            // [2, 1] 
            reverse_stack_2();
            // Here, we must use insert bottom to make the reversing properly
            // if we push only the stack will be the same
            // [3, 2, 1]
            this->insert_bottom_2(cur);
        }
    }




};

int main() {
    Stack<int> st(5);
    st.push(1);
    st.push(2);
    std::cout << "\nBEFORE\n";
    st.print_stack();
    st.reverse_stack_2();
    std::cout << "\nAFTER\n";
    st.print_stack();

//    Stack<int> st(3);
//    st.push(1);
//    st.push(2);
//    st.insert_bottom_2(45);
//    st.print_stack();

//    Stack<int> st(1);
//    std::vector<int> v = {1, 2, 8, 4, -15};
//    v = st.asteroid_collision(v, 5);
//    for(auto it: v) std::cout << it << " ";


    return 0;
}
