//Jacqueline Vermette
//COP4530
//Assignment2

#ifndef LIST_HPP
#define LIST_HPP


#include <iostream>

using namespace cop4530;
using namespace std;


//Default constructor
template <typename T>
List<T>::List(){
    init();
}

// Copy Constructor
template <typename T>
List<T>::List(const List &rhs){
    init();
    for (auto &val : rhs) {
        push_back(val);
    }
}

template <typename T>
List<T>::List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}{
    rhs.theSize = 0;
    rhs.head = nullptr;
    rhs.tail = nullptr;
}

template <typename T>
const List<T>& List<T>::operator=(const List &rhs){
    if (this != &rhs){
        clear();
        for (auto &val : rhs){
            push_back(val);
        }
    }
    return *this;
}

template <typename T>
List<T>::List(int num, const T & val){
    init();
    for (int i = 0; i < num; ++i){
        push_back(val);
    }
}

// List constructor for const_iterator range
template <typename T>
List<T>::List(const_iterator start, const_iterator end){
    init();
    while (start != end){
        push_back(*start);
        ++start;
    }
}

// Move Assignment operator
template <typename T>
List<T>& List<T>::operator=(List &&rhs){
    if (this != &rhs){
        clear();
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
    }
    return *this;
}

template <typename T>
List<T>::~List(){
    clear();
    delete head;
    delete tail;
}

template <typename T>
void List<T>::init(){
    theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

template <typename T>
bool List<T>::empty() const{
    return theSize == 0;
}

template <typename T>
void List<T>::clear(){
    while (!empty()){
        pop_front();
    }
}

template <typename T>
void List<T>::push_front(const T & val){
    insert(begin(), val);
}

template <typename T>
void List<T>::push_back(const T & val){
    insert(end(), val);
}

template <typename T>
void List<T>::pop_front(){
    erase(begin());
}

template <typename T>
void List<T>::pop_back(){
    erase(--end());
}

template <typename T>
void List<T>::push_back(T && val){
    insert(end(), std::move(val));
}

template <typename T>
int List<T>::size() const{
    return theSize;
}

// Iterators
template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, T&& val){
    Node *p = itr.current;
    theSize++;
    Node *newNode = new Node(std::move(val), p->prev, p);
    p->prev->next = newNode;
    p->prev = newNode;
    return iterator(newNode);
}

template <typename T>
typename List<T>::iterator List<T>::insert(iterator itr, const T& val){
    Node *p = itr.current;
    theSize++;
    Node *newNode = new Node(val, p->prev, p);
    p->prev->next = newNode;
    p->prev = newNode;
    return iterator(newNode);
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator itr){
    Node *p = itr.current;
    iterator retVal(p->next);
    p->prev->next = p->next;
    p->next->prev = p->prev;
    delete p;
    theSize--;
    return retVal;
}

template <typename T>
typename List<T>::iterator List<T>::begin(){
    return iterator(head->next);
}

template <typename T>
typename List<T>::const_iterator List<T>::begin() const{
    return const_iterator(head->next);
}

template <typename T>
typename List<T>::iterator List<T>::end(){
    return iterator(tail);
}

template <typename T>
typename List<T>::const_iterator List<T>::end() const{
    return const_iterator(tail);
}

template <typename T>
void List<T>::remove(const T &val){
    auto itr = begin();
    while (itr != end()){
        if (*itr == val){
            itr = erase(itr);
        } else {
            ++itr;
        }
    }
}

template <typename T>
typename List<T>::iterator List<T>::erase(iterator start, iterator end){
    while (start != end){
        start = erase(start);
    }
    return start;
}

template <typename T>
void List<T>::print(std::ostream &os, char ofc) const{
    for (auto itr = begin(); itr != end(); ++itr){
        os << *itr;
        if (itr != --end()){
            os << ofc;
        }
    }
}

template <typename T>
T& List<T>::front(){
    return *begin();
}

template <typename T>
const T& List<T>::front() const{
    return *begin();
}

template <typename T>
T& List<T>::back(){
    return *(--end());
}

template <typename T>
const T& List<T>::back() const{
    return *(--end());
}

template <typename T>
void List<T>::reverse(){
    if (theSize <= 1) return;
    Node *curr = head;
    while (curr != nullptr){
        std::swap(curr->next, curr->prev);
        curr = curr->prev;
    }
    std::swap(head, tail);
}

template <typename T>
List<T>::const_iterator::const_iterator(Node *p) : current(p) {
}

template <typename T>
const T & List<T>::const_iterator::operator*() const{
    return retrieve();
}

template <typename T>
const T * List<T>::const_iterator::operator->() const{
    return &retrieve();
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator++(){
    current = current->next;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator++(int){
    const_iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::const_iterator & List<T>::const_iterator::operator--(){
    current = current->prev;
    return *this;
}

template <typename T>
typename List<T>::const_iterator List<T>::const_iterator::operator--(int){
    const_iterator old = *this;
    --(*this);
    return old;
}

// Iterator Implementation
template <typename T>
List<T>::iterator::iterator(Node *p) : const_iterator(p){
}

template <typename T>
T & List<T>::iterator::operator*(){
    return const_iterator::retrieve();
}

template <typename T>
T* List<T>::iterator::operator->(){
    return &const_iterator::retrieve();
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator++(){
    this->current = this->current->next;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int){
    iterator old = *this;
    ++(*this);
    return old;
}

template <typename T>
typename List<T>::iterator & List<T>::iterator::operator--(){
    this->current = this->current->prev;
    return *this;
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator--(int){
    iterator old = *this;
    --(*this);
    return old;
}

template <typename T>
bool List<T>::const_iterator::operator==(const const_iterator &rhs) const{
    return current == rhs.current;
}

template <typename T>
bool List<T>::const_iterator::operator!=(const const_iterator &rhs) const{
    return current != rhs.current;
}

template <typename T>
T & List<T>::const_iterator::retrieve() const{
    return current->data;
}

template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs){
    if (lhs.size() != rhs.size())
        return false;
    auto lit = lhs.begin();
    auto rit = rhs.begin();
    while (lit != lhs.end()){
        if (*lit != *rit)
            return false;
        ++lit;
        ++rit;
    }
    return true;
}

template <typename T>
bool operator!=(const List<T> &lhs, const List<T> &rhs){
    return !(lhs == rhs);
}

template <typename T>
std::ostream &operator<<(std::ostream & os, const List<T> &l){
    l.print(os);
    return os;
}

#endif
