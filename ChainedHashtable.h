/**
 * @file: ChainedHashtableTester.h
 * @assignment_name: 05 Learning Activity: Chained Hashtable
 * @author: Rick Smith (rickysmith@mail.weber.edu)
 * @date: 01/20/2023
 * @brief: Using pointers to create a chained hash table
 *
 */

#ifndef INC_05_LEARNING_ACTIVITY_CHAINED_HASHTABLE_CHAINEDHASHTABLE_H
#define INC_05_LEARNING_ACTIVITY_CHAINED_HASHTABLE_CHAINEDHASHTABLE_H

#include <iostream>
#include <iomanip>

template <class Type>
struct Node{
    Type info;
    Node<Type>*link;
};

template <class Type>
class ChainedHashtable;

template <class Type>
std::ostream& operator<<(std::ostream& out, ChainedHashtable<Type> & t);

template <class Type>
class ChainedHashtable{
public:


    ChainedHashtable(int max);// Constructor for the Hashtable.  Creates an empty list
    ~ChainedHashtable();//Deconstructor for the Hashtable.  Deallocates memory
    void add(Type item);//Adds to the hashtable
    bool remove(Type item);//Removes an item from the hashtable.  Returns true if the item was successfully removed
    bool contains(Type item);//Determines if the value is in the hashtable
    bool empty();//Determines if the hashtable is empty
    int size();//Determines the number of items in the hashtable
    friend std::ostream& operator<< <>(std::ostream& out, ChainedHashtable<Type> & t);//Returns an output stream for displaying the Hashtable

protected:

    int sz;
    int capacity;
    Node<Type>** htable; //list of pointers

};

//constructor
template<class Type>
ChainedHashtable<Type>::ChainedHashtable(int max) {
    sz = 0;
    capacity = max;
    htable = new Node<Type>*[capacity]();
}

//destructor
template<class Type>
ChainedHashtable<Type>::~ChainedHashtable() {
    delete [] htable;
}

//getter
template<class Type>
int ChainedHashtable<Type>::size(){
    return sz;
}

template<class Type>
bool ChainedHashtable<Type>::empty() {
    return sz==0; //returns true of size == 0
}

template<class Type>
void ChainedHashtable<Type>::add(Type item){
    int key = item % capacity; //position in list where to add the item

    //If there is a collision
    if(htable[key]){
        auto node = new Node<Type>();
        node->info = item;
        node->link = htable[key];
        htable[key] = node;
        sz++;
    }
    else{
        htable[key] = new Node<Type>();
        htable[key]->info = item;
        sz++;
    }
}

template<class Type>
bool ChainedHashtable<Type>::contains(Type item){
    int key = item % capacity; // get hash key

    auto curr = htable[key];
    while(curr){
        if(curr->info == item){
            return true;
        }
        curr = curr->link;
    }
    return false;
}

template<class Type>
bool ChainedHashtable<Type>::remove(Type item){
    if(empty()){
        std::runtime_error("Table is empty");
    }
    int key = item % capacity;
    auto curr = htable[key];
    Node<Type>* prev = nullptr;

    while(curr){
        if(curr->info == item){
            if(prev){
                prev->link = curr->link;
                delete curr;
            }
            else{
                htable[key] = nullptr;
                delete curr;
            }
            sz--;
            return true;
        }
        prev = curr;
        curr = curr->link;
    }
    return false; //item was not in list.
}

template<class Type>
std::ostream& operator<<(std::ostream& out, ChainedHashtable<Type> & t){
    for(int i = 0; i < t.capacity; i++){
        out <<std::setw(0) << i << ": ";

        auto curr = t.htable[i];
        while(curr){
            out << curr->info << " " ;
            if(curr->link){
                out << "->";
            }
            curr = curr->link;
        }
        out << std::endl;
    }
}

#endif //INC_05_LEARNING_ACTIVITY_CHAINED_HASHTABLE_CHAINEDHASHTABLE_H