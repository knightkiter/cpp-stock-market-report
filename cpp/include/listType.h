#ifndef LISTTYPE_H
#define LISTTYPE_H

#include <iostream>
#include <stdexcept>

// Array list from the previous exercise. stockListType derives from this
// template, specialized on stockType, and is itself no longer a template.
template <class elemType>
class listType {
public:
    bool isEmpty() const;
    bool isFull() const;
    int listSize() const;
    int maxListSize() const;
    void print() const;
    bool isItemAtEqual(int location, const elemType& item) const;
    void insertAt(int location, const elemType& insertItem);
    void insertEnd(const elemType& insertItem);
    void removeAt(int location);
    void retrieveAt(int location, elemType& retItem) const;
    void replaceAt(int location, const elemType& repItem);
    void clearList();
    int seqSearch(const elemType& item) const;
    void insert(const elemType& insertItem);
    void remove(const elemType& removeItem);
    void sort();

    const elemType& at(int location) const;
    elemType& at(int location);

    listType(int size = 100);
    listType(const listType<elemType>& otherList);
    ~listType();
    const listType<elemType>& operator=(const listType<elemType>& otherList);

protected:
    elemType* list;
    int length;
    int maxSize;

private:
    void copyList(const listType<elemType>& otherList);
};

template <class elemType>
bool listType<elemType>::isEmpty() const {
    return length == 0;
}

template <class elemType>
bool listType<elemType>::isFull() const {
    return length == maxSize;
}

template <class elemType>
int listType<elemType>::listSize() const {
    return length;
}

template <class elemType>
int listType<elemType>::maxListSize() const {
    return maxSize;
}

template <class elemType>
void listType<elemType>::print() const {
    for (int i = 0; i < length; i++) {
        std::cout << list[i] << '\n';
    }
}

template <class elemType>
bool listType<elemType>::isItemAtEqual(int location, const elemType& item) const {
    if (location < 0 || location >= length) {
        return false;
    }
    return list[location] == item;
}

template <class elemType>
void listType<elemType>::insertAt(int location, const elemType& insertItem) {
    if (isFull()) {
        std::cerr << "Cannot insert: the list is full.\n";
        return;
    }
    if (location < 0 || location > length) {
        std::cerr << "Cannot insert: location is out of range.\n";
        return;
    }
    for (int i = length; i > location; i--) {
        list[i] = list[i - 1];
    }
    list[location] = insertItem;
    length++;
}

template <class elemType>
void listType<elemType>::insertEnd(const elemType& insertItem) {
    if (isFull()) {
        std::cerr << "Cannot insert: the list is full.\n";
        return;
    }
    list[length] = insertItem;
    length++;
}

template <class elemType>
void listType<elemType>::removeAt(int location) {
    if (location < 0 || location >= length) {
        std::cerr << "Cannot remove: location is out of range.\n";
        return;
    }
    for (int i = location; i < length - 1; i++) {
        list[i] = list[i + 1];
    }
    length--;
}

template <class elemType>
void listType<elemType>::retrieveAt(int location, elemType& retItem) const {
    if (location < 0 || location >= length) {
        std::cerr << "Cannot retrieve: location is out of range.\n";
        return;
    }
    retItem = list[location];
}

template <class elemType>
void listType<elemType>::replaceAt(int location, const elemType& repItem) {
    if (location < 0 || location >= length) {
        std::cerr << "Cannot replace: location is out of range.\n";
        return;
    }
    list[location] = repItem;
}

template <class elemType>
void listType<elemType>::clearList() {
    length = 0;
}

template <class elemType>
int listType<elemType>::seqSearch(const elemType& item) const {
    for (int i = 0; i < length; i++) {
        if (list[i] == item) {
            return i;
        }
    }
    return -1;
}

template <class elemType>
void listType<elemType>::insert(const elemType& insertItem) {
    if (seqSearch(insertItem) != -1) {
        std::cerr << "Cannot insert: the item is already in the list.\n";
        return;
    }
    insertEnd(insertItem);
}

template <class elemType>
void listType<elemType>::remove(const elemType& removeItem) {
    int location = seqSearch(removeItem);
    if (location == -1) {
        std::cerr << "Cannot remove: the item is not in the list.\n";
        return;
    }
    removeAt(location);
}

// Physical sort using the element's overloaded relational operators.
template <class elemType>
void listType<elemType>::sort() {
    for (int i = 1; i < length; i++) {
        elemType key = list[i];
        int j = i - 1;
        while (j >= 0 && list[j] > key) {
            list[j + 1] = list[j];
            j--;
        }
        list[j + 1] = key;
    }
}

template <class elemType>
const elemType& listType<elemType>::at(int location) const {
    if (location < 0 || location >= length) {
        throw std::out_of_range("list index out of range");
    }
    return list[location];
}

template <class elemType>
elemType& listType<elemType>::at(int location) {
    if (location < 0 || location >= length) {
        throw std::out_of_range("list index out of range");
    }
    return list[location];
}

template <class elemType>
void listType<elemType>::copyList(const listType<elemType>& otherList) {
    delete[] list;
    maxSize = otherList.maxSize;
    length = otherList.length;
    list = new elemType[maxSize];
    for (int i = 0; i < length; i++) {
        list[i] = otherList.list[i];
    }
}

template <class elemType>
listType<elemType>::listType(int size) {
    if (size <= 0) {
        size = 100;
    }
    maxSize = size;
    length = 0;
    list = new elemType[maxSize];
}

template <class elemType>
listType<elemType>::listType(const listType<elemType>& otherList) : list(nullptr) {
    copyList(otherList);
}

template <class elemType>
listType<elemType>::~listType() {
    delete[] list;
}

template <class elemType>
const listType<elemType>& listType<elemType>::operator=(
    const listType<elemType>& otherList
) {
    if (this != &otherList) {
        copyList(otherList);
    }
    return *this;
}

#endif