// src/LinkedList.h
#pragma once

#include <cstddef> // for size_t
#include <stdexcept> // for std::out_of_range
#include <iterator> // for iterator tags

// Doubly-linked list node
// Now includes prev pointer for full doubly-linked list support

template <typename T>
class LinkedList {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev; // Added prev pointer for doubly-linked list
        // Accept data by rvalue reference to allow moving
        Node(T&& value, Node* next = nullptr, Node* prev = nullptr) : value(std::move(value)), next(next), prev(prev) {}
        // Or provide an overload for const lvalue refs if needed, but move is key for unique_ptr
        Node(const T& value, Node* next = nullptr, Node* prev = nullptr) : value(value), next(next), prev(prev) {} 
    };

    Node* head;
    Node* tail; // Added tail pointer for O(1) push_back and reverse traversal
    size_t count;

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

    size_t size() const;
    bool isEmpty() const;

    // Iterator support
    iterator begin();
    iterator end();

    // Const iterator support for range-based for on const objects
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const; // Explicit const begin
    const_iterator cend() const;   // Explicit const end

    // Doubly-linked list accessors
    Node* getHead() const { return head; }
    Node* getTail() const { return tail; }
    int getSize() const { return static_cast<int>(count); }

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
