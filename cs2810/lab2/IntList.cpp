#include <iostream>
#include <cstdlib>
#include "intlist.h"

using namespace std;

IntList::Iterator::Iterator()
{
     this->curr_node = NULL;
}

IntList::Iterator::Iterator(const IntList::Iterator& iter)
{
     this->curr_node = iter.curr_node;
}

IntList::Iterator& IntList::Iterator::operator =(const IntList::Iterator& iter) 
{
     this->curr_node = iter.curr_node;
     return *this;
}

IntList::Iterator IntList::Iterator::operator ++(int n)
{
     // postfix : increment, return old one
     if (this->curr_node == NULL) {
          cerr << "ERROR : Can't increment the iterator." << endl;
          exit(-1);
     }
     IntList::Iterator return_iter(*this);
     this->curr_node = (this->curr_node)->next;
     return return_iter;
}

IntList::Iterator IntList::Iterator::operator ++()
{
     // prefix : increment, return incremented
     if (this->curr_node == NULL) {
          cerr << "ERROR : Can't increment the iterator." << endl;
          exit(-1);
     }
     this->curr_node = (this->curr_node)->next;
     return *this;
}

int IntList::Iterator::operator *()
{
     if (this->curr_node == NULL) {
          cerr << "ERROR : The iterator is not pointing to any data." << endl;
          exit(-1);
     }
     return (this->curr_node)->data;
}

bool IntList::Iterator::operator ==(const IntList::Iterator& iter) const 
{
     return (this->curr_node == iter.curr_node);
}

bool IntList::Iterator::operator !=(const IntList::Iterator& iter) const
{
     return (this->curr_node != iter.curr_node);
}

IntList::Iterator IntList::begin() const
{
     IntList::Iterator iter;
     iter.curr_node = this->head;
     return iter;
}

IntList::Iterator IntList::end() const
{
     IntList::Iterator iter;
     iter.curr_node = NULL;
     return iter;
}

IntList::IntList()
{
     this->head = NULL;
}

void IntList::insert_after(IntList::Iterator& iter, int data)
{
     if (iter.curr_node == NULL) {
          if (this->head == NULL) {
               Node * new_node = new Node(data, NULL);
               this->head = new_node;
               iter.curr_node = new_node;
          }
          else {
               cerr << "ERROR : The iterator is not pointing to any data and the list is not empty." << endl;
          }
     }
     else {
          Node *new_node = new Node(data, (iter.curr_node)->next);
          (iter.curr_node)->next = new_node;
     }
     
}

void IntList::remove(IntList::Iterator& iter)
{
     // removes the node pointed to by iterator
     // and the iterator points to the next node

     // in the implementation, actually, the iterator
     // is not moved at all; but the data in each node
     // after the pointed node is moved towards the
     // head by one node and the tail is deleted
     if (iter.curr_node == NULL){
          cerr << "ERROR : The iterator does not point to any data." << endl;
          exit(-1);
     }
     Node * end_but_one;
     IntList::Iterator iter2(iter);
     while ((iter2.curr_node)->next != NULL) {
          // shift the data by one node towards head
          if ( iter2.curr_node->next->next == NULL) {
               end_but_one = iter2.curr_node;
          }
          (iter2.curr_node)->data = *(++iter2);
     }
     end_but_one->next = NULL;	// make the last but one into tail
     delete iter2.curr_node;	// delete the tail
}

bool IntList::is_empty() const
{
     return (this->head == NULL);
}

IntList::IntList(const IntList& list) 
{
     // deep copies the list
     if (list.head == NULL) {
          this->head = NULL;
     }
     else {
          this->head = new Node;
          IntList::Iterator iter1 = this->begin(), iter2 = list.begin();
          (this->head)->data = (list.head)->data;
          iter2++;
          while (iter2 != list.end()) {
               this->insert_after(iter1, *iter2);
               iter1++;
               iter2++;
          }
     }
}

unsigned int IntList::length() const
{
     unsigned int length = 0;
     IntList::Iterator iter = this->begin();
     while (iter != this->end()){
          iter++;
          length++;
     }
     return length;
}

void IntList::push_front(int data)
{
     Node * new_node = new Node(data, this->head);
     this->head = new_node;
}

void IntList::push_back(int data)
{
     if (this->head == NULL) {
          this->push_front(data);
     }
     else {
          IntList::Iterator iter1 = this->begin();
          IntList::Iterator iter2;
          while (iter1 != this->end()) {
               iter2 = iter1++;
          }
          this->insert_after(iter2, data);
     }
}

int IntList::pop_front()
{
     if (this->head == NULL) {
          cerr << "ERROR : Can't pop from an empty list." << endl;
          exit(-1);
     }
     int return_value = (this->head)->data;
     Node * old_head = this->head;
     this->head = (this->head)->next;
     delete old_head;
     return return_value;
}

int IntList::pop_back() 
{
     if (this->head == NULL) {
          cerr << "ERROR : Can't pop from an empty list." << endl;
          exit(-1);
     }
     if (this->head->next == NULL) {
          return this->pop_front();
     }
     IntList::Iterator iter1 = this->begin();
     IntList::Iterator iter2;
     while ((iter1.curr_node)->next != NULL) {
          iter2 = iter1++;
     }
     int return_vaule = (iter1.curr_node)->data;
     delete iter1.curr_node;
     (iter2.curr_node)->next = NULL;
     return return_vaule;
}

void IntList::clear()
{
     int length = this->length();
     for (int i = length; i > 0; i--) {
          this->pop_front();
     }
}

IntList::~IntList()
{
     this->clear();
}

void IntList::print()
{
     IntList::Iterator iter;
     for (iter = this->begin(); iter != this->end(); iter++) {
          cout << *(iter) << " ";
     }
     cout << endl;
}

// int main()
// {
//      IntList list;
//      for (int i = 0; i < 7; i++){
// 	  list.push_front(i);
//      }
//      list.print();
//      cout << list.pop_front() << endl;
//      cout << list.pop_back() << endl;
//      list.print();
//      IntList::Iterator iter;
//      for (int i = 19; i < 25; i++) {
// 	  list.push_back(i);
//      }
//      list.print();
//      list.clear();
//      for (int i = 19; i < 25; i++) {
// 	  list.push_back(i);
//      }
//      list.print();
//      IntList list2(list);
//      list2.print();
//      list2.push_back(99999);
//      list2.pop_front();
     
//      list2.print();
//      list.print();
    
//      for (iter = list.begin(); *(iter) != 21; iter++) {
//      }
//      list.insert_after(iter, 555);
//      list.print();
//      list.remove(iter);
//      list.print();
//      list.remove(iter);
//      list.print();
//      cout << list.is_empty() << endl;
//      cout << list.length() << endl;
//      list.clear();
//      cout << list.length() << endl;
//      list.pop_back();
     
     
//      return 0;
// }
