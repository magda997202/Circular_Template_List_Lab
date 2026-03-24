//
// Created by Christopher Vaughn on 10/24/25.
//

#ifndef CIRCULARTEMPLATEDLIST_LINKEDLIST_H
#define CIRCULARTEMPLATEDLIST_LINKEDLIST_H

#include <iostream>

// === Templated Node Structure ===
// Now generic - can hold any type T*
template <typename T>
struct Node {
    // Data is now generic pointer type T*
    T* data;
    Node<T>* next;

    // Constructor initializes data and pointer
    Node(T* item) : data(item), next(nullptr) {}
};

// === Templated Circular LinkedList Class ===
// This list is generic and circular (tail points to head)
template <typename T>
class LinkedList {
private:
    Node<T>* head;      // Points to first node (start of list)
    Node<T>* tail;      // Points to last node (for efficient circular operations)
    Node<T>* current;   // Current position for playback (circular navigation)

public:
    // Constructor: Initializes an empty list
    LinkedList() : head(nullptr), tail(nullptr), current(nullptr) {}

    // Destructor: Cleans up all nodes and the objects they point to
    ~LinkedList() {
        if (head == nullptr) {
            return;  // Empty list, nothing to clean
        }

        Node<T>* currentPtr = head;
        Node<T>* nextNode = nullptr;

        // Traverse the circular list until we return to head
        do {
            nextNode = currentPtr->next;

            // Delete the object stored in the node's data pointer
            delete currentPtr->data;

            // Delete the node itself
            delete currentPtr;

            currentPtr = nextNode;
        } while (currentPtr != head);

        head = nullptr;
        tail = nullptr;
        current = nullptr;
        std::cout << "\n[Playlist cleanup complete. All memory deallocated.]" << std::endl;
    }

    // Insertion: Adds a new item (T*) to the end of the circular list
    void insert(T* newItem) {
        Node<T>* newNode = new Node<T>(newItem);

        if (head == nullptr) {
            // Case 1: List is empty. New node becomes head, tail, and current
            head = newNode;
            tail = newNode;
            current = newNode;
            newNode->next = head;  // Circular: point to itself
        } else {
            // Case 2: Add to the end and maintain circular structure
            tail->next = newNode;   // Old tail points to new node
            tail = newNode;          // Update tail to new node
            tail->next = head;       // Maintain circularity: tail points back to head
        }
    }

    // Traversal: Displays all items in the circular list
    void displayList() const {
        if (head == nullptr) {
            std::cout << "\n[Playlist is empty.]" << std::endl;
            return;
        }

        std::cout << "\n--- Current Playlist ---" << std::endl;
        Node<T>* currentPtr = head;
        int index = 1;

        // Traverse until we return to head (complete one full circle)
        do {
            // Polymorphism in action: calls the specific toString() method
            std::cout << index++ << ". " << currentPtr->data->toString() << std::endl;
            currentPtr = currentPtr->next;
        } while (currentPtr != head);

        std::cout << "------------------------" << std::endl;
    }

    // Play the currently selected item
    void playCurrent() const {
        if (current != nullptr) {
            current->data->play();  // Calls the virtual play() method
        } else {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
        }
    }

    // Advanced method: Plays current item and advances to next (circular logic with wrap-around)
    void playNext() {
        if (current == nullptr) {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
            return;
        }

        // Play the current item
        current->data->play();

        // Advance to next node (circular advancement)
        current = current->next;

        // Note: When current reaches the end, current->next points to head
        // So the wrap-around happens automatically
    }

    // Helper method to reset current to beginning
    void resetCurrent() {
        current = head;
    }

    // Helper method to check if list is empty
    bool isEmpty() const {
        return head == nullptr;
    }
};

#endif //CIRCULARTEMPLATEDLIST_LINKEDLIST_H