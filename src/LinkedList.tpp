// src/LinkedList.tpp
// Implementation for LinkedList template class

#include <utility> // For std::swap
#include <type_traits>

// Helper for deleting pointer types in C++11
namespace detail {
    template<typename T, bool is_ptr>
    struct PointerDeleter {
        static void deleteValue(T&) {}
    };
    template<typename T>
    struct PointerDeleter<T, true> {
        static void deleteValue(T& ptr) { delete ptr; }
    };
}

// --- Constructor/Destructor ---
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

template <typename T>
void LinkedList<T>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        detail::PointerDeleter<T, std::is_pointer<T>::value>::deleteValue(current->value);
        delete current;
        current = next;
    }
    head = nullptr;
    tail = nullptr;
    count = 0;
}

// --- Basic Operations ---
template <typename T>
void LinkedList<T>::push_back(const T& value) {
    Node* newNode = new Node(value, nullptr, tail);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

template <typename T>
void LinkedList<T>::push_back(T&& value) {
    Node* newNode = new Node(std::move(value), nullptr, tail);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    count++;
}

template <typename T>
bool LinkedList<T>::remove(const T& value) {
    if (head == nullptr) {
        return false;
    }

    if (head->value == value) { // Check if head needs removal
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->value == value) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            count--;
            return true;
        }
        current = current->next;
    }
    return false; // Value not found
}

template <typename T>
template <typename Predicate>
bool LinkedList<T>::removeIf(Predicate pred) {
    if (head == nullptr) {
        return false;
    }

    // Check if the head node should be removed
    if (pred(head->value)) {
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    // Iterate through the rest of the list
    Node* current = head;
    while (current->next != nullptr) {
        if (pred(current->next->value)) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
            count--;
            return true;
        }
        current = current->next;
    }

    return false; // No element satisfied the predicate
}

template <typename T>
int LinkedList<T>::size() const {
    return count;
}

template <typename T>
bool LinkedList<T>::isEmpty() const {
    return head == nullptr;
}

// --- Iterator Support ---
template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() {
    return iterator(head);
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() {
    return iterator(nullptr); // Points one past the end
}

// --- Const Iterator Support Implementation ---
template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::begin() const {
    return const_iterator(head);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::end() const {
    return const_iterator(nullptr);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cbegin() const {
    return const_iterator(head);
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::cend() const {
    return const_iterator(nullptr);
}

// --- Insertion Sort Implementation --- 
template <typename T>
template <typename Compare>
void LinkedList<T>::insertionSort(Compare comp) {
    if (!head || !head->next) { 
        return; // List is empty or has only one element
    }

    Node* sorted = nullptr; // Head of the sorted list portion
    Node* current = head;   // Node currently being inserted into the sorted portion

    while (current != nullptr) {
        Node* next = current->next; // Save next node before modifying current's links

        // Find the correct position to insert 'current' in the 'sorted' list
        if (sorted == nullptr || comp(current->value, sorted->value)) {
            // Insert at the beginning of the sorted list
            current->next = sorted;
            sorted = current;
        } else {
            // Find the node *before* the insertion point in the sorted list
            Node* search = sorted;
            while (search->next != nullptr && comp(search->next->value, current->value)) {
                search = search->next;
            }
            // Insert 'current' after 'search'
            current->next = search->next;
            search->next = current;
        }
        current = next; // Move to the next node in the original list
    }
    head = sorted; // Update the list head to the new sorted list
}

template <typename T>
typename LinkedList<T>::iterator LinkedList<T>::linearSearch(const T& target) {
    Node* current = head;
    while (current) {
        if (current->value == target) {
            return iterator(current);
        }
        current = current->next;
    }
    return end();
}

template <typename T>
typename LinkedList<T>::const_iterator LinkedList<T>::linearSearch(const T& target) const {
    const Node* current = head;
    while (current) {
        if (current->value == target) {
            return const_iterator(current);
        }
        current = current->next;
    }
    return cend();
}
