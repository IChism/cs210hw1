#ifndef LIST_H
#define LIST_H

#include <algorithm>
#include <iostream>
using namespace std;

template <typename Object>
class List
{
private:
    // The basic doubly linked list node.
    // Nested inside of List, can be public
    // because the Node is itself private
    struct Node
    {
        Object  data;
        Node* prev;
        Node* next;

        Node(const Object& d = Object{ }, Node* p = nullptr, Node* n = nullptr)
            : data{ d }, prev{ p }, next{ n } { }

        Node(Object&& d, Node* p = nullptr, Node* n = nullptr)
            : data{ std::move(d) }, prev{ p }, next{ n } { }
    };

public:
    class const_iterator
    {
    public:

        // Public constructor for const_iterator.
        const_iterator() : current{ nullptr }
        { }

        // Return the object stored at the current position.
        // For const_iterator, this is an accessor with a
        // const reference return type.
        const Object& operator* () const
        {
            return retrieve();
        }

        const_iterator& operator++ ()
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++ (int)
        {
            const_iterator old = *this;
            ++(*this);
            return old;
        }

        const_iterator& operator-- ()
        {
            current = current->prev;
            return *this;
        }

        const_iterator operator-- (int)
        {
            const_iterator old = *this;
            --(*this);
            return old;
        }

        bool operator== (const const_iterator& rhs) const
        {
            return current == rhs.current;
        }

        bool operator!= (const const_iterator& rhs) const
        {
            return !(*this == rhs);
        }

    protected:
        Node* current;

        // Protected helper in const_iterator that returns the object
        // stored at the current position. Can be called by all
        // three versions of operator* without any type conversions.
        Object& retrieve() const
        {
            return current->data;
        }

        // Protected constructor for const_iterator.
        // Expects a pointer that represents the current position.
        const_iterator(Node* p) : current{ p }
        { }

        friend class List<Object>;
    };

    class iterator : public const_iterator
    {
    public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator()
        { }

        Object& operator* ()
        {
            return const_iterator::retrieve();
        }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object& operator* () const
        {
            return const_iterator::operator*();
        }

        iterator& operator++ ()
        {
            this->current = this->current->next;
            return *this;
        }

        iterator operator++ (int)
        {
            iterator old = *this;
            ++(*this);
            return old;
        }

        iterator& operator-- ()
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- (int)
        {
            iterator old = *this;
            --(*this);
            return old;
        }

    protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator(Node* p) : const_iterator{ p }
        { }

        friend class List<Object>;
    };

public:
    List()
    {
        init();
    }

    ~List()
    {
        clear();
        delete head;
        delete tail;
    }


    /*      ONLY TOUCH CODE AFTER THIS LINE      */

    // Return mutable iterator representing beginning of list.
    iterator begin()
    {
        return iterator(head);
    }

    // Return constant iterator representing beginning of list.
    const_iterator begin() const
    {
        return const_iterator(head);
    }

    // Return iterator representing endmarker of list.
    // Mutator version is first, then accessor version.
    iterator end()
    {
        return iterator(tail);
    }

    const_iterator end() const
    {
        return const_iterator(tail);
    }

    // Return number of elements currently in the list.
    int size() const
    {
        return count;
    }

    // Return true if the list is empty, false otherwise.
    bool empty() const
    {
        return count == 0;
    }

    // Removes all elements from the list
    void clear()
    {
        init();
    }

    /* front, back, push_front, push_back, pop_front, and pop_back
       are the basic double-ended queue operations. */
    

    //Returns the value stored in the first element of the list
    const Object& front() const
    {
        //note: these values need to be replaced, just here for compilation purposes
        return head->data;
    }

    //Returns the value stored in the last element of the list
    const Object& back() const
    {
        //note: these values need to be replaced, just here for compilation purposes
        return tail->data;
    }

    //Inserts an object at the front of the list
    void push_front(const Object& x)
    {
        //std::cout << "x: " << x << std::endl;
        Node *newNode = new Node(x);
        newNode->prev = NULL;
        newNode->next = head;
        if (head != NULL) {
            head->prev = newNode;
        }
        if (tail == NULL) {
            tail = head;
        }
        head = newNode;
        count++;
    }

    //Inserts an object at the back of the list
    void push_back(const Object& x)
    {
        Node *newNode = new Node(x);
        newNode->next = NULL;
        newNode->prev = tail;
        if (tail != NULL) {
            tail->next = newNode;
        }
        if (head == NULL) {
            head = tail;
        }
        tail = newNode;
        count++;
    }

    //Removes the first element in the list
    void pop_front()
    {
        if (empty()) {
            return;
        }

        head = head->next;

        if (head == NULL) {
            tail = NULL;
        }

        count--;
    }

    //Removes the last element in the list
    void pop_back()
    {
        if (empty()) {
            return;
        }

        tail = tail->prev;

        if (tail == NULL) {
            head = NULL;
        }

        count--;
    }

    // Insert x before itr.
    iterator insert(iterator itr, const Object& x)
    {
        count++;
        Node *n = itr.current;
        itr--;
        Node *p = itr.current;

        Node *item = new Node(x);
        item->prev = p;
        item->next = n;

        if (p == NULL) {
            head = item;
            return begin();
        }

        (p)->next = item;
        (n)->prev = item;
        
        itr++;

        //need to update the return value, just itr so it will compile
        return itr;
    }

    // Erase item at itr.
    iterator remove(iterator itr)
    {
        if (*itr == head->data) {
            itr++;
            pop_front();
            return itr;
        }

        if (*itr == tail->data) {
            itr--;
            pop_back();
            return itr;
        }

        itr++;
        Node *g = itr.current;
        itr--;
        itr--;
        Node *n = itr.current;

        g->prev = n;
        n->next = g;

        count--;

        //need to update the return value, just itr so it will compile
        return itr;
    }

    // Return the index of the node containing the matching value
    // Return -1 if no matching value
    int find(const Object& x)
    {
        int ctr = 0;
        iterator itr = begin();
        for (int i = 0; i < count; i++) {
            //cout << *itr << endl;
            if (*itr == x) {
                return ctr;
            }
            itr++;
            ctr++;
        }

        return -1;
    }

private:
    Node* head;
    Node* tail;
    int count;

    void init()
    {
        count = 0;
        head = NULL;
        tail = NULL;
    }
};

#endif
