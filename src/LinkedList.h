// src/LinkedList.h
#pragma once

#include <cstddef> // for size_t
#include <stdexcept> // for std::out_of_range
#include <iterator> // for iterator tags

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        // Accept data by rvalue reference to allow moving
        Node(T&& data, Node* next = nullptr) : data(std::move(data)), next(next) {}
        // Or provide an overload for const lvalue refs if needed, but move is key for unique_ptr
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {} 
    };

    Node* head;
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

        reference operator*() const { return m_ptr->data; }
        pointer operator->() { return &(m_ptr->data); }
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

        reference operator*() const { return m_ptr->data; }
        pointer operator->() const { return &(m_ptr->data); } // Return const T*
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
    void push_back(T&& value); // Accept by rvalue reference for moving
    bool remove(const T& value); // Removes the first occurrence (comparison might need adjustment for unique_ptr)
    size_t size() const;
    bool isEmpty() const;

    // Access (Optional - useful but not strictly required by prompt for first draft)
    // T& operator[](size_t index); // Be cautious with bounds
    // const T& operator[](size_t index) const;

    // Iterator support
    iterator begin();
    iterator end();

    // Const iterator support for range-based for on const objects
    const_iterator begin() const;
    const_iterator end() const;
    const_iterator cbegin() const; // Explicit const begin
    const_iterator cend() const;   // Explicit const end

    // Algorithms (declaration)
    template <typename Compare> 
    void insertionSort(Compare comp); // TODO: Add sorting by prep time and title
    
    // TODO: Linear search (can be external or member)
    iterator linearSearch(const T& target); // TODO: Add linear search by recipe name and ingredients
    const_iterator linearSearch(const T& target) const;
};

// Include the template implementation file
#include "LinkedList.tpp"
