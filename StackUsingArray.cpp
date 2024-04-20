// بسم الله الرحمن الرحيم
// Created by BnAdel on 4/20/2024.
// ===> STACK USING ARRAY <===

#include <iostream>
#include <cassert>

class Stack {
private:
    int top {};
    int size {};
    int *array {};
public:
    // Default Constructor with initial size = 5
    Stack() : size(5), top(-1) {
        this->array = new int[this->size];
    }
    // Parametrized Constructor to Initialize The Stack
    Stack(int size) : size(size), top(-1) {
        this->array = new int[this->size];
    }

    // Expand The Array Size
    // Analysis: O(N) TIME | O(N) MEMORY
    void expand_array_capacity() {
        int newSize = this->size*2;
        int *temArray = this->array;
        this->array = new int[newSize];
        for (int i = 0; i <= this->top; ++i) {
            this->array[i] = temArray[i];
        }
        this->size = newSize;
        delete[] temArray;
        temArray = nullptr;
    }
    // Pushing a new element into the stack
    // Analysis: WORST CASE, if we expand the array ==> O(N) TIME | O(N) MEMORY
    void push(int val) {
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
        this->array[this->top--] = -1;
    }
    // Get the top element in the stack
    // Analysis: O(1) TIME | O(1) MEMORY
    int peek() {
        assert(!this->is_empty());
        return this->array[this->top];
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
            std::cout << this->array[temTop--] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    Stack st(6);
    st.push(1);
    st.push(5);
    st.push(3);
    st.push(4);
    st.push(9);
    st.push(8);
    st.pop();
    st.pop();
    st.print_stack();

    std::cout << "Peek Element: " << st.peek() << "\nIs Full: " << st.is_full() << "\nIs Empty: "
    << st.is_empty() << "\nCurrent Size: " << st.get_size() << "\nCurrent capacity: "
    << st.get_capacity() << std::endl;

    return 0;
}
