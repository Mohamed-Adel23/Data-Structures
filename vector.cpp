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

    // Insert A New Element in The Vector
    void insertByIndex(int idx, int val) {
        if(idx < 0 || idx >= this->curSize) {
            std::cout << "\n\t-->Oops, Can't insert a value in this position [" << idx << "] !!<--\n";
            return;
        }
        if(this->curSize >= this->capacity)
            expandCapacity();
        for (int i = this->curSize; i > idx; --i) {
            this->arr[i] = this->arr[i-1];
        }
        this->arr[idx] = val;
        this->curSize++;
    }

    // Right Rotation 1 Element
    void right_rotate() {
        int ele = this->arr[this->curSize-1];
        for (int i = this->curSize-1; i > 0; --i) {
            this->arr[i] = this->arr[i-1];
        }
        this->arr[0] = ele;
    }

    // WORST: N = Size, O(N^2)
    // Right Rotation N Steps
    /*void right_rotate_with_steps(int n) {
        while(n--) { // N
            int ele = this->arr[this->curSize-1]; // N
            for (int i = this->curSize-1; i > 0; --i) { // N
                this->arr[i] = this->arr[i-1]; // (N-1)*N
            }
            this->arr[0] = ele; // N
        }
    }*/
    // WORST: N = Size, O(N)
    void right_rotate_with_steps(int n) {
        // Making a new array to take the new arrangement of old array elements
        int *temArr = new int[this->curSize];
        // Getting rid of useless rotations and get the starting position to rotate
        int s = this->curSize-n%this->curSize, j = 0;
        // Copying the targeted elements
        for (int i = s; i < this->curSize; ++i) { // N
            temArr[j++] = this->arr[i];
        }
        // Copying the remaining elements
        for (int i = 0; i < s; ++i) { // 0
            temArr[j++] = this->arr[i];
        }
        // copying the new elements
        for (int i = 0; i < this->curSize; ++i) { // N
            this->arr[i] = temArr[i];
        }
    }

    // Left Rotation 1 Element
    void left_rotate() {
        int ele = this->arr[0];
        for (int i = 0; i < this->curSize-1; ++i) {
            this->arr[i] = this->arr[i+1];
        }
        this->arr[this->curSize-1] = ele;
    }

    // Delete an element by its index
    int pop(int idx) {
        if(idx < 0 || idx >= this->curSize) return -1;
        int ele = this->arr[idx];
        for (int i = idx; i < this->curSize-1; ++i) {
            this->arr[i] = this->arr[i+1];
        }
        // Make the last element with the initial value of the array and reduce the size
        this->curSize--;
        this->arr[this->curSize] = 0;
        return ele;
    }

    // Search for an element with shifting Left to improve searching process
    int find_transposition(int val) {
        if(this->arr[0] == val) return 0; // O(1)
        // Implementing Linear search O(N)
//        for (int i = 1; i < this->curSize; ++i) {
//            if(this->arr[i] == val) {
//                std::swap(this->arr[i], this->arr[i-1]); // Shifting Left
//                return i;
//            }
//        }
        // Implementing Binary Search O(logN)
        int l = 0, r = this->curSize-1;
        while(l <= r) {
            int md = (l+r)/2;
            if(this->arr[md] == val) {
                std::swap(this->arr[md], this->arr[md-1]);
                return md;
            }
            else if(this->arr[md] > val) r = md-1;
            else l = md+1;
        }
        return -1;
    }

    // Printing The Elements of the vector
    void print() {
        int s;
        if(this->curSize == 0 && this->size == 0) {
            std::cout << "\tNO Elements Yet!!\n";
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

    {
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
}

    // //////////////////////////////////////
    // //////////////////////////////////////
    // //////////////////////////////////////

    // ====================
    // VECTOR WITH NO SIZE
    // ====================
    vector v;
    std::cout << "\n::BEFORE::\n";
    v.print();
    std::cout << "The Size of The Vector: " << v.getCurrentSize() << std::endl;
    std::cout << "The Capacity of The Vector: " << v.getCapacity() << std::endl;
    v.push_back(2);
    v.push_back(3);
    v.push_back(8);
    v.insertByIndex(2, 150);
    std::cout << "\n::AFTER::\n";
    v.print();
    std::cout << "The Size of The Vector: " << v.getCurrentSize() << std::endl;
    std::cout << "The Capacity of The Vector: " << v.getCapacity() << std::endl;
    std::cout << "\nThe Back Element: " << v.getBack() << "\nThe Front Element: " << v.getFront() << "\nElement with Index (1): " << v.getElementBy(-1) << std::endl;

    v.right_rotate();
    std:: cout << "\nAfter Right Rotation: \n";
    v.print();
    v.left_rotate();
    std:: cout << "\nAfter Left Rotation: \n";
    v.print();
    v.right_rotate_with_steps(3);
    std::cout << "\nAfter 2 rotation steps: \n";
    v.print();

    int delEle = v.pop(0);
    if(delEle == -1)
        std::cout << "\n-->Invalid index to delete!!<--\n";
    else
        std::cout << "\nAfter deleting element with index (2): [" << delEle << "]\n", v.print();

    int findEle = v.find_transposition(150);
    if(findEle == -1)
        std::cout << "\n-->Element Not Found<--\n";
    else
        std::cout << "\n-->Element Found on position [" << findEle << "] .. Array after shifting: \n", v.print();


    return 0;
}
