// src/LinkedList.tpp
// Implementation for LinkedList template class

#include <utility> // For std::swap

// --- Constructor/Destructor ---
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), count(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = nullptr; // Good practice
    count = 0;
}

// --- Basic Operations ---
template <typename T>
void LinkedList<T>::push_back(T&& value) { // Take T&& 
    // Use std::move to pass the value to the Node constructor
    Node* newNode = new Node(std::move(value)); 
    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
    count++;
}

template <typename T>
bool LinkedList<T>::remove(const T& value) {
    if (head == nullptr) {
        return false;
    }

    if (head->data == value) { // Check if head needs removal
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->data == value) {
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
    if (pred(head->data)) {
        Node* temp = head;
        head = head->next;
        delete temp;
        count--;
        return true;
    }

    // Iterate through the rest of the list
    Node* current = head;
    while (current->next != nullptr) {
        if (pred(current->next->data)) {
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
size_t LinkedList<T>::size() const {
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
        if (sorted == nullptr || comp(current->data, sorted->data)) {
            // Insert at the beginning of the sorted list
            current->next = sorted;
            sorted = current;
        } else {
            // Find the node *before* the insertion point in the sorted list
            Node* search = sorted;
            while (search->next != nullptr && comp(search->next->data, current->data)) {
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
        if (current->data == target) {
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
        if (current->data == target) {
            return const_iterator(current);
        }
        current = current->next;
    }
    return cend();
}
