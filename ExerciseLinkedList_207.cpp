#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int rollNumber;
    string name;
    Node* next;
};

class CircularLinkedList {
private:
    Node* LAST;

public:
    CircularLinkedList() {
        LAST = NULL;
    }

    void addNode();
    bool search(int rollno, Node** hossain, Node** shabit);
    bool listEmpty();
    bool delNode();
    void traverse();
};

void CircularLinkedList::addNode() {
    //  Beginning of the list
    Node* newnode = new Node;
    cout << "Enter roll number: ";
    cin >> newnode->rollNumber;
    cout << "Enter name: ";
    cin >> newnode->name;

    if (LAST == NULL) {
        LAST = newnode;
        newnode->next = LAST;
    }
    else {
        newnode->next = LAST->next;
        LAST->next = newnode;
    }

    //  Between two nodes in the list
    
    Node* current = LAST->next;
    Node* previous = NULL;

    while (current->rollNumber > newnode->rollNumber && previous != LAST) {
        previous = current;
        current = current->next;
    }

    previous->next = newnode;
    newnode->next = current;
    

    //  End of the list
    
    Node* newnode = new Node;
    cout << "Enter roll number: ";
    cin >> newnode->rollNumber;
    cout << "Enter name: ";
    cin >> newnode->name;

    newnode->next = LAST->next;
    LAST->next = newnode;
    LAST = newnode;
    
}

bool CircularLinkedList::search(int rollno, Node** previous, Node** current) {
    *previous = LAST->next;
    *current = LAST->next;

    while (*current != LAST) {
        if (rollno == (*current)->rollNumber) {
            return true;
        }
        *previous = *current;
        *current = (*current)->next;
    }

    if (rollno == LAST->rollNumber) {
        return true;
    }
    else {
        return false;
    }
}

bool CircularLinkedList::listEmpty() {
    return LAST == NULL;
}

bool CircularLinkedList::delNode() {
    if (listEmpty()) {
        cout << "List is empty" << endl;
        return false;
    }

    int rollno;
    cout << "Enter roll number to delete: ";
    cin >> rollno;

    Node* previous = NULL;
    Node* current = NULL;

    if (search(rollno, &previous, &current)) {
        //  Beginning of the list
        if (current == LAST && current->next == LAST) {
            LAST = NULL;
            delete current;
        }

        else {
            Node* temp = LAST->next;

            if (current == temp) {
                LAST->next = current->next;
                delete current;
            }
            else {
                while (temp->next != current) {
                    temp = temp->next;
                }

                temp->next = current->next;
                if (current == LAST) {
                    LAST = temp;
                }
                delete current;
            }
        }
        return true;
    }
    else {
        cout << "Node with roll number " << rollno << " not found" << endl;
        return false;
    }
}

void CircularLinkedList::traverse() {
    if (listEmpty()) {
        cout << "List is empty" << endl;
    }
    else {
        cout << "Records in the list are:" << endl;
        Node* currentNode = LAST->next;
        while (currentNode != LAST) {
            cout << currentNode->rollNumber << " " << currentNode->name << endl;
            currentNode = currentNode->next;
        }
        cout << LAST->rollNumber << " " << LAST->name << endl;
    }
}

int main() {
    CircularLinkedList obj;
    while (true) {
        try {
            cout << "\nMenu" << endl;
            cout << "1. Add a record to the list" << endl;
            cout << "2. Delete a record from the list" << endl;
            cout << "3. View all the records in the list" << endl;
            cout << "4. Exit" << endl;
            cout << "\nEnter your choice (1-4): ";
            char ch;
            cin >> ch;

            switch (ch) {
            case '1': {
                obj.addNode();
                break;
            }
            case '2': {
                obj.delNode();
                break;
            }
            case '3': {
                obj.traverse();
                break;
            }
            case '4': {
                return 0;
            }
            default: {
                cout << "Invalid option" << endl;
                break;
            }
            }
        }
        catch (exception& e) {
            cout << e.what() << endl;
        }
    }
    return 0;
}
