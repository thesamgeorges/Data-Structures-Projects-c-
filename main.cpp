#include <iostream>

using namespace std;

// Data Class
class PrintItem {
public:
    float fileSize;
    string fileName;

    PrintItem(float fileSize, string fileName) : fileSize(fileSize), fileName(fileName) {}

    void print() {
        cout << fileSize << " " << endl;
        cout << fileName << " " << endl;
    }
};

// Node Class
template <typename T>
class Node {
public:
    T* value;
    Node<T>* next;

    Node(T* value) : value(value), next(nullptr) {}

    void print() { value->print(); }
};

// LLStack
template <typename T>
class LLStack {
private:
    Node<T>* top;
    int stackSize;
    int SMAXITEMS;

public:
    // Constructor
    LLStack() : top(nullptr), stackSize(0), SMAXITEMS(10) {}

    Node<T>* getTop() {
        return top;
    }

    int getStackSize() {
        return stackSize;
    }

    LLStack(T* value) : top(new Node<T>(value)), stackSize(1) {}

    // Destructor
    ~LLStack() {
        Node<T>* temp = top;
        while (top) {
            top = top->next;
            delete temp;
            temp = top;
        }
    }

void printList() {
    LLStack<T> temp;

    // peek, push, & pop to print the list
    while (!isEmpty()) {
        T* item = peek();
        pop();
        temp.push(item);
    }
    while (!temp.isEmpty()) {
        T* item = temp.peek();
        temp.pop();
        push(item);
        item->print();
    }
}

    

    bool isFull() {
        return stackSize == SMAXITEMS;
    }

    bool isEmpty() {
        return stackSize == 0;
    }

    void push(T* value) {
        if (isFull()) {
            return;
        }
        Node<T>* newNode = new Node<T>(value);
        newNode->next = top;
        top = newNode;
        stackSize++;
    }

    void pop() {
        if (!isEmpty()) {
            Node<T>* temp = top;
            top = top->next;
            delete temp;
            stackSize--;
        }
    }

    T* peek() {
        if (!isEmpty()) {
            return top->value;
        }
        return nullptr;
    }

    //void print() { //ALTER THIS FOR STACK
        //Node<T>* temp = top;
        //while (temp != nullptr) {
         //   temp->print();
         //   temp = temp->next;
        //}
   // }
};

// StackQ Class
template <typename T>
class StackQ {
private:
    LLStack<T>* enQStack;
    LLStack<T>* deQStack;
    int queueSize;
    const int QMAXITEMS;

public:
    StackQ() : enQStack(new LLStack<T>()), deQStack(new LLStack<T>()), queueSize(0), QMAXITEMS(10) {}

    ~StackQ() {
        delete enQStack;
        delete deQStack;
    }

    bool IsFull() {
        return queueSize == QMAXITEMS;
    }

    bool IsEmpty() {
        return queueSize == 0;
    }

    void enqueue(T* item) {
        if (IsFull()) {
            cout << "Queue is full. Cannot enqueue." << endl;
            return;
        }

        enQStack->push(item);
        queueSize++;
    }

    void dequeue() {
        if (IsEmpty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }

        if (deQStack->isEmpty()) {
            while (!enQStack->isEmpty()) {
                T* item = enQStack->peek();
                enQStack->pop();
                deQStack->push(item);
            }
        }

        deQStack->pop();
        queueSize--;
    }

    T* peek() {
        if (IsEmpty()) {
            cout << "The queue is empty. Cannot peek." << endl;
            return nullptr;
        }

        if (deQStack->isEmpty()) {
            while (!enQStack->isEmpty()) {
                T* item = enQStack->peek();
                enQStack->pop();
                deQStack->push(item);
            }
        }

        return deQStack->peek();
    }

    void printQueue() {
        cout << "Queue Elements: \n";
        deQStack->printList();
        enQStack->printList();
        cout << endl;
    }

    int getSize() {
        return queueSize;
    }

    void printStacks() {
        cout << "enQStack: ";
        enQStack->printList();
        cout << "deQStack: ";
        deQStack->printList();
    }
};

int main() {
    // create StackQ object
    StackQ<PrintItem>* myQueue = new StackQ<PrintItem>();


// pre populating
  PrintItem* d1 = new PrintItem(10, "a");
  PrintItem* d2 = new PrintItem(11, "b");
  PrintItem* d3 = new PrintItem(12, "c");
  PrintItem* d4 = new PrintItem(14, "d");
  PrintItem* d5 = new PrintItem(15, "e");
  PrintItem* d6 = new PrintItem(16, "d");
    char choice;

  myQueue -> enqueue(d1);
  myQueue -> enqueue(d2);
  myQueue -> enqueue(d3);
  myQueue -> enqueue(d4);
  myQueue -> enqueue(d5);
  myQueue -> enqueue(d6);
  
;
    do {
        cout << "\nMenu:\n";
        cout << "a. Add Item to print queue\n";
        cout << "b. Delete from print queue\n";
        cout << "c. Peek from the print queue\n";
        cout << "d. Display the print queue\n";
        cout << "e. Display print queue size\n";
        cout << "f. Display enQStack and deQStack\n";
        cout << "g. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 'a': {
                float fileSize;
                string fileName;
                cout << "Enter the file size: ";
                cin >> fileSize;
                cout << "Enter the file name: ";
                cin >> fileName;

                PrintItem* newItem = new PrintItem(fileSize, fileName);
                myQueue->enqueue(newItem);
              myQueue -> printQueue();
                break;
            }
            case 'b':
                myQueue->dequeue();
              myQueue -> printQueue();
                break;
            case 'c': {
                PrintItem* peekedItem = myQueue->peek();
                if (peekedItem != nullptr) {
                    cout << "Peeked Item: ";
                    peekedItem->print();
                }
                break;
            }
            case 'd':
                myQueue->printQueue();
                break;
            case 'e':
                cout << "Print the queue size: " << myQueue->getSize() << endl;
                break;
            case 'f':
                myQueue->printStacks();
                break;
            case 'g':
                cout << "You have exited the program.\n";
                break;
            default:
                cout << "Invalid input choice. Please try again.\n";
                break;
        }
    } while (choice != 'g');

    delete myQueue;

    return 0;
}
