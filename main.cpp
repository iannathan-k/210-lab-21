#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// COMSC-210 | Lab 21 | Ian Kusmiantoro

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;
const int SIZE = 15;
const int MIN_AGE = 1;
const int MAX_AGE = 20;

class Goat {
    private:
        int age;
        string name;
        string color;
        string names[SIZE] = {
            "Biscuit", "Clover", "Nibbles", "Pebble", "Maple", 
            "Sprout", "Patches", "Juniper", "Tater", "Willow", 
            "Pickles", "Hazel", "Muffin", "Acorn", "Butterscotch"
        };
        string colors[SIZE] = {
            "White", "Black", "Brown", "Tan", "Cream", 
            "Gray", "Spotted", "Speckled", "Caramel", "Chestnut",
             "Mahogany", "Silver", "Golden", "Ivory", "Mocha"
        };
    
    public:
        Goat() {
            age = rand() % (MAX_AGE - MIN_AGE + 1) + MIN_AGE;
            name = names[rand() % SIZE]; // Range is actually 0-14, so this will do
            color = colors[rand() % SIZE];
        }

        Goat(int a, string n, string c) {
            age = a;
            name = n;
            color = c;
        }

        // Not mentioned but we need getters to actually print stuff
        int getAge() {return age;}
        string getName() {return name;}
        string getColor() {return color;}
};

class DoublyLinkedList {
private:
    struct Node {
        Goat data; // Doesn't say that we have to point to a goat, so we just use the object
        Node* prev;
        Node* next;
        Node(Goat val, Node* p = nullptr, Node* n = nullptr) {
            data = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat value) {
        Node* newNode = new Node(value); // Directly passes in a goat
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat value) {
        Node* newNode = new Node(value);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Must edit these 2 in order for program to compile
    void insert_after(Goat value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(Goat value) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && &temp->data != &value)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty";
            return;
        }
        while (current) {
            cout << "\t" << current->data.getName() << " "; //\t just does the tab
            cout << "(" << current->data.getColor() << ", ";
            cout << current->data.getAge() << ")" << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty";
            return;
        }
        while (current) {
            cout << "\t" << current->data.getName() << " ";
            cout << "(" << current->data.getColor() << ", ";
            cout << current->data.getAge() << ")" << endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i)
        list.push_back(Goat());

    cout << "Forward: " << endl;
    list.print();

    cout << "Backward: " << endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();

    return 0;
}
