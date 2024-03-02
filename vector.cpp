// بسم الله الرحمن الرحيم

#include <iostream>


class vector {
private:
    int *arr = nullptr;
    int size;
    int curSize;
    int capacity;

public:
    // Default Constructor without vector size
    vector() {
        this->size = 0;
        this->curSize = 0;
        this->capacity = 10;
        // initialize the array with default value (0)
        this->arr = new int[this->capacity];
        for (int i = 0; i < this->capacity; ++i) {
            this->arr[i] = 0;
        }
    }

    // Constructor to initialize the vector with initial values (0)
    vector(int size) {
        if(size <= 0) {
            std::cout << "Oops, Invalid Vector Size!! Size must be greater than zero.\n";
            return;
        }
        // User Size
        this->size = size;
        this->curSize = 0;
        // The Actual Size of The Vector
        this->capacity = this->size + 10;
        // initialize the array with default value (0)
        this->arr = new int[this->capacity];
        for (int i = 0; i < this->capacity; ++i) {
            this->arr[i] = 0;
        }
    }

    // Constructor to initialize the vector with initial values (..)
    vector(int size, int defVal) {
        if(size <= 0) {
            std::cout << "Oops, Invalid Vector Size!! Size must be greater than zero.\n";
            return;
        }
        // User Size
        this->size = size;
        this->curSize = 0;
        // The Actual Size of The Vector
        this->capacity = this->size + 10;
        // initialize the array with default value (0)
        this->arr = new int[this->capacity];
        for (int i = 0; i < this->capacity; ++i) {
            this->arr[i] = defVal;
        }
    }

    // Destructor
    ~vector() {
        delete[] this->arr;
        this->arr = nullptr;
    }

    // Getting Elements
    int getCurrentSize() {
        return this->curSize;
    }
    int getUserSize() {
        return this->size;
    }
    int getCapacity() {
        return this->capacity;
    }
    int getElementBy(int indx) {
        if(indx < 0 || indx >= this->getCurrentSize())
            return -1;
        else
            return this->arr[indx];
    }
    int getBack() {
        return this->arr[this->curSize-1];
    }
    int getFront() {
        return this->arr[0];
    }

    // Expand The Capacity of The Vector
    void expandCapacity() {
        this->capacity *= 2;
        int *old = arr;
        arr = new int[this->capacity];
        // copying old elements
        for (int i = 0; i < this->getCapacity(); ++i) {
            arr[i] = old[i];
        }
        delete[] old;
        old = nullptr;
    }

    // pushing back a new element
    void push_back(int val) {
        if(this->curSize < this->capacity) {
            this->arr[this->curSize++] = val;
        }
        else {
            expandCapacity();
            this->arr[this->curSize++] = val;
        }
    }

    // Printing The Elements of the vector
    void print() {
        int s;
        if(this->curSize == 0 && this->size == 0) {
            std::cout << "\n\tNO Elements Yet!!\n";
            return;
        }
        else if(this->curSize == 0) {
            s = this->size;
        }
        else {
            s = this->curSize;
        }
        std::cout << "The Elements: \n";
        for (int i = 0; i < s; ++i) {
            std::cout << this->arr[i] << " ";
        }
        std::cout << std::endl;
    }
};

int main() {
    // ================
    //   SIZED VECTOR
    // ================
//    std::cout << "Enter The Size of The Vector: \n";
//    int s, x; std::cin >> s;
//    vector v(s, 3);
//
//    v.print();
//
//    std::cout << "Enter The Elements: \n";
//    for (int i = 0; i < s; ++i) {
//        std::cin >> x;
//        v.push_back(x);
//    }
//
//    std::cout << "\n::BEFORE::\nThe Size of The Vector: " << v.getCurrentSize() << std::endl;
//    std::cout << "The Capacity of The Vector: " << v.getCapacity() << std::endl;
//    v.print();
//    std::cout << '\n';
//
//    v.push_back(55);
//    v.push_back(78);
//
//    std::cout << "\n::AFTER::\nThe Size of The Vector: " << v.getCurrentSize() << std::endl;
//    std::cout << "The Capacity of The Vector: " << v.getCapacity() << std::endl;
//    v.print();
//    std::cout << "\nThe Back Element: " << v.getBack() << "\nThe Front Element: " << v.getFront() << "\nElement with Index (4): " << v.getElementBy(4) << std::endl;


    // //////////////////////////////////////
    // //////////////////////////////////////
    // //////////////////////////////////////


    // ====================
    // VECTOR WITH NO SIZE
    // ====================
    vector v;
    v.print();
    std::cout << "\n::BEFORE::\nThe Size of The Vector: " << v.getCurrentSize() << std::endl;
    std::cout << "The Capacity of The Vector: " << v.getCapacity() << std::endl;
    v.push_back(2);
    v.push_back(3);
    v.push_back(8);
    v.push_back(8);
    v.push_back(8);
    v.push_back(8);
    v.push_back(8);
    v.push_back(8);
    v.push_back(8);
    v.push_back(8);
    v.push_back(8);
    v.print();
    std::cout << "\n::AFTER::\nThe Size of The Vector: " << v.getCurrentSize() << std::endl;
    std::cout << "The Capacity of The Vector: " << v.getCapacity() << std::endl;
    std::cout << "\nThe Back Element: " << v.getBack() << "\nThe Front Element: " << v.getFront() << "\nElement with Index (1): " << v.getElementBy(1) << std::endl;


    return 0;
}
