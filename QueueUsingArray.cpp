// بسم الله الرحمن الرحيم
// Created by BnAdel on 5/16/2024.
// ===> CIRCULAR QUEUE USING ARRAY <===



#include <iostream>
#include <cassert>

class Queue {
private:
    int front;
    int rear;
    int *array;
    int size;
    int length;
public:
    Queue() {
        front = rear = length = 0;
        size = 5;
        array = new int[size];
    }
    Queue(int sz) {
        front = rear = length = 0;
        size = sz;
        array = new int[size];
    }

    bool is_empty() {
        return this->length == 0;
    }
    bool is_full() {
        return this->length == this->size;
    }
    int cur_len() {
        return this->length;
    }
    // Circular Queue
    int next(int pos) {
        return (pos+1)%this->size;
    }

    void enqueue(int val) {
        assert(!is_full());
        // Circular Adding
        this->array[this->rear] = val;
        this->rear = this->next(this->rear);
        this->length++;
    }
    void dequeue() {
        assert(!is_empty());
        // Circular
        this->front = this->next(this->front);
        this->length--;
    }

    void print() {
        if(this->length == 0) { std::cout << "NO ELEMENTS YET!!\n"; return; }
        std::cout << "==> QUEUE REPRESENTATION <==\n";
        for(int i = this->front, sz = 0; sz != this->length; i++, sz++) {
            int curIndex = i%this->size;
            std::cout << this->array[curIndex] << " ";
        }
        std::cout << '\n';
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
    q->enqueue(12);
    q->dequeue();
    q->dequeue();
    std::cout << q->cur_len() << std::endl;
    q->enqueue(78);
    q->print();
    std::cout << q->cur_len() << std::endl;


    return 0;
}
