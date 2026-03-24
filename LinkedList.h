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
    Node<T>* head;
    Node<T>* tail;  // Added tail pointer for efficient circular operations

public:
    // Constructor: Initializes an empty list
    LinkedList() : head(nullptr), tail(nullptr) {}

    // Destructor: Cleans up all nodes and the objects they point to
    ~LinkedList() {
        if (head == nullptr) {
            return;  // Empty list, nothing to clean
        }

        Node<T>* current = head;
        Node<T>* next_node = nullptr;

        // Traverse the circular list until we return to head
        do {
            next_node = current->next;

            // Delete the object stored in the node's data pointer
            delete current->data;

            // Delete the node itself
            delete current;

            current = next_node;
        } while (current != head);

        head = nullptr;
        tail = nullptr;
        std::cout << "\n[Playlist cleanup complete. All memory deallocated.]" << std::endl;
    }

    // Insertion: Adds a new item (T*) to the end of the circular list
    void insert(T* newItem) {
        Node<T>* newNode = new Node<T>(newItem);

        if (head == nullptr) {
            // Case 1: List is empty. New node becomes the head and points to itself
            head = newNode;
            tail = newNode;
            newNode->next = head;  // Circular: point to itself
        } else {
            // Case 2: Add to the end and maintain circular structure
            tail->next = newNode;
            tail = newNode;
            tail->next = head;  // Maintain circularity: tail points back to head
        }
    }

    // Traversal: Displays all items in the circular list
    void displayList() const {
        if (head == nullptr) {
            std::cout << "\n[Playlist is empty.]" << std::endl;
            return;
        }

        std::cout << "\n--- Current Playlist ---" << std::endl;
        Node<T>* current = head;
        int index = 1;

        // Traverse until we return to head (complete one full circle)
        do {
            // Polymorphism in action: calls the specific toString() method
            std::cout << index++ << ". " << current->data->toString() << std::endl;
            current = current->next;
        } while (current != head);

        std::cout << "------------------------" << std::endl;
    }

    // Simple play method for demonstration
    void playCurrent() const {
        if (head != nullptr) {
            head->data->play();  // Calls the virtual play() method
        } else {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
        }
    }

    // New method: Plays the current item and moves to the next (circular logic)
    void playNext() {
        if (head == nullptr) {
            std::cout << "[Playlist is empty. Nothing to play.]" << std::endl;
            return;
        }

        // Play the current head item
        head->data->play();

        // Move head to the next node (circular advancement)
        head = head->next;
        // Note: tail remains unchanged as it still points to the original tail
    }
};

#endif //CIRCULARTEMPLATEDLIST_LINKEDLIST_H