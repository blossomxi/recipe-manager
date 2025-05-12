// src/LinkedList.h
#pragma once

#include <cstddef> // for size_t
#include <stdexcept> // for std::out_of_range
#include <iterator> // for iterator tags

// =============================
// Custom Doubly-Linked List (Template)
// - Generic (template) for any type
// - Doubly-linked (prev/next)
// - Head/tail pointers for O(1) push_back
// - Custom iterator for safe traversal
// - Safe memory management
// =============================

// Doubly-linked list template
// For presentation: core structure only

template <typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev; // Added prev pointer for doubly-linked list
        Node(T&& value, Node* next = nullptr, Node* prev = nullptr) : value(std::move(value)), next(next), prev(prev) {}
        Node(const T& value, Node* next = nullptr, Node* prev = nullptr) : value(value), next(next), prev(prev) {} 
    };

    Node* head;
    Node* tail; // Added tail pointer for O(1) push_back and reverse traversal
    int count;

public:
    // --- Iterator --- 
    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = T;
        using pointer           = T*;  
        using reference         = T&; 

        iterator(Node* ptr) : m_ptr(ptr) {} 

        reference operator*() const { return m_ptr->value; }
        pointer operator->() { return &(m_ptr->value); }
        iterator& operator++() { m_ptr = m_ptr->next; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const iterator& a, const iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const iterator& a, const iterator& b) { return a.m_ptr != b.m_ptr; }; 

    private:
        Node* m_ptr;
    };
    // --- End Iterator ---

    // --- Const Iterator --- (Needed for iterating over const LinkedList)
    class const_iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type        = const T; // Value is const
        using pointer           = const T*;  
        using reference         = const T&; 

        const_iterator(const Node* ptr) : m_ptr(ptr) {} // Takes const Node*

        reference operator*() const { return m_ptr->value; }
        pointer operator->() const { return &(m_ptr->value); } // Return const T*
        const_iterator& operator++() { m_ptr = m_ptr->next; return *this; }
        const_iterator operator++(int) { const_iterator tmp = *this; ++(*this); return tmp; }

        friend bool operator== (const const_iterator& a, const const_iterator& b) { return a.m_ptr == b.m_ptr; };
        friend bool operator!= (const const_iterator& a, const const_iterator& b) { return a.m_ptr != b.m_ptr; }; 

    private:
        const Node* m_ptr; // Pointer to const Node
    };
    // --- End Const Iterator ---

    LinkedList();
    ~LinkedList();

    // Basic operations
    void push_back(const T& value); // Overload for const T&
    void push_back(T&& value); // Existing rvalue overload
    bool remove(const T& value); // Removes the first occurrence (comparison might need adjustment for unique_ptr)
    template <typename Predicate>
    bool removeIf(Predicate pred); // Removes the first element matching the predicate

    int size() const;
    bool isEmpty() const;

    // Safe cleanup for pointer types (e.g., LinkedList<Recipe*>)
    // Deletes all nodes and, if T is a pointer, also deletes each pointed-to object.
    // Safe to call on non-pointer types as well (no effect on non-pointers).
    void clear();

    // Iterator support
    iterator begin();
    iterator end();

    // Const iterator support for range-based for on const objects
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const;
    const_iterator cend() const; 

    // Doubly-linked list accessors
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    int getSize() const { return count; }

    // Algorithms (declaration)
    template <typename Compare> 
    void insertionSort(Compare comp);
    
    iterator linearSearch(const T& target);
    const_iterator linearSearch(const T& target) const;

    template <typename Compare>
    void sort(Compare comp) { insertionSort(comp); }
};

// Include the template implementation file
#include "LinkedList.tpp"
