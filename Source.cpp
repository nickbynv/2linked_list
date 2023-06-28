#include <iostream>
#include <string>
#include <cmath>
using namespace std;

template <typename T>
class List {
public:
    List() {
        head = tail = nullptr;
        size = 0;
    }

    ~List() {
        clear();
    }

    T& operator[](const int index) {
        return get_at(index)->data;
    }

    int get_size() {
        return size;
    }

    void clear() {
        while (size) pop_front();
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        newNode->ptrNext = head;

        if (head != nullptr) head->ptrPrev = newNode;
        if (tail == nullptr) tail = newNode;

        head = newNode;
        size++;
    }

    void pop_front() {
        if (head == nullptr) return;

        Node* nextNode = head->ptrNext;
        delete head;
        head = nextNode;

        if (head != nullptr) head->ptrPrev = nullptr;
        else tail = head;

        size--;
    }

    void push_back(T data) {
        Node* newNode = new Node(data);
        newNode->ptrPrev = tail;

        if (tail != nullptr) tail->ptrNext = newNode;
        if (head == nullptr) head = newNode;

        tail = newNode;
        size++;
    }

    void pop_back() {
        if (tail == nullptr) return;

        Node* prevNode = tail->ptrPrev;
        delete tail;
        tail = prevNode;

        if (tail != nullptr) tail->ptrNext = nullptr;
        else head = tail;

        size--;
    }

    void insert(T data, const int index) {
        if (index == 0) push_front(data);

        else if (index <= size - 1) {
            Node* currentNode = get_at(index);
            Node* newNode = new Node(data, currentNode, currentNode->ptrPrev);
            currentNode->ptrPrev->ptrNext = newNode;
            currentNode->ptrPrev = newNode;
            size++;
        }

        else if (index == size) push_back(data);
    }

    void remove_at(const int index) {
        if (index == 0) pop_front();

        else if (index < size - 1) {
            Node* currentNode = get_at(index);
            currentNode->ptrPrev->ptrNext = currentNode->ptrNext;
            currentNode->ptrNext->ptrPrev = currentNode->ptrPrev;
            delete currentNode;
            size--;
        }

        else if (index == size - 1) pop_back();
    }

private:
    class Node {
    public:
        Node(T data, Node* ptrNext = nullptr, Node* ptrPrev = nullptr) {
            this->data = data;
            this->ptrNext = ptrNext;
            this->ptrPrev = ptrPrev;
        }

        T data;
        Node* ptrPrev, ptrNext;
    };

    Node* head, tail;
    int size;

    Node* get_at(const int index) {
        Node* currentNode;
        int count;

        if (index + 1 <= ceil((float)size / 2)) {
            currentNode = head;
            count = 0;

            while (currentNode != nullptr) {
                if (count == index) return currentNode;

                currentNode = currentNode->ptrNext;
                count++;
            }
        }

        else {
            currentNode = tail;
            count = size - 1;

            while (currentNode != nullptr) {
                if (count == index) return currentNode;

                currentNode = currentNode->ptrPrev;
                count--;
            }
        }
    }
};

int main() {
    List<int> list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    for (size_t i = 0; i < list.get_size(); ++i) {
        cout << list[i] << endl;
    }

    return 0;
}
