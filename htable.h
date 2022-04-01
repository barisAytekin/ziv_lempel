#include <iostream>
#include <string>
#include<vector>
using namespace std;

#ifndef HASH_H
#define HASH_H

template <class HashedObj>
class HashTable
{
public:
    HashTable(const HashedObj& notFound, int size);
    const HashedObj& find(const HashedObj& x) const;
    void insert(const HashedObj& x);
    enum EntryType {ACTIVE, EMPTY};
private:
    struct HashEntry
    {
        HashedObj element;
        EntryType info;
        HashEntry(const HashedObj& e = HashedObj(), EntryType i = EMPTY)
            : element(e), info(i) { }
    };
    vector<HashEntry> array;
    const HashedObj ITEM_NOT_FOUND;
    bool isActive(int currentPos) const;
    int findPos(const HashedObj& x) const;
};
#endif
template <class HashedObj>
HashTable<HashedObj>::HashTable(const HashedObj& notFound, int size) //constructor
    : ITEM_NOT_FOUND(notFound), array(size)
{}
template <class HashedObj>
int HashTable<HashedObj>::findPos(const HashedObj& x) const
{
    int p = Hash(x,array.size()); // current position

    while (array[p].info != EMPTY && array[p].element != x) { //check whether the slot is empty or not

        p++;  // linear probe

        if (p >= array.size()) { //mod
            p -= array.size();
        }
                          
    }

    return p;
}
template <class HashedObj>
bool HashTable<HashedObj>::isActive(int currentPos) const
{
    return array[currentPos].info == ACTIVE; //entrytype check
}
template <class HashedObj>
const HashedObj& HashTable<HashedObj>::find(const HashedObj& x) const
{
    int currentPos = findPos(x);

    if (isActive(currentPos))
        return array[currentPos].element;//if found return the element

    return   ITEM_NOT_FOUND;//if not found
}
template <class HashedObj>
void HashTable<HashedObj>::insert(const HashedObj& x)
{
    // Insert x as active
    int currentPos = findPos(x);

    if (isActive(currentPos))//if vacant do not insert
        return;

    array[currentPos] = HashEntry(x, ACTIVE);//if empty insert the element
}






