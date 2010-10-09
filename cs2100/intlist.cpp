// intlist.cpp : This is a doubly linked list implementation of function prototypes
//               given in the accompanying file "list.h".
// Author      : Sujeet Gholap


#include <iostream>
#include <cstdlib>
using namespace std;

struct Node
{
  int data;
  struct Node * next;
  struct Node * prev;
};
typedef struct Node Node;

class IntList {
private:
     Node * head;
     Node * tail;
     int length;
     
public:
     /* Class to access the elements of the list.*/
     class Iterator {
     private:
	  Node * curr_node;
     public:
	  friend class IntList;
	  /* Constructors */
	  Iterator()
	       {
		    curr_node = NULL;
	       }
	  
	  /* Copy constructor */
	  Iterator(const Iterator & given_iter)
	       {
		    curr_node = given_iter.curr_node;
	       }
	  
 
	  /* Assignment operator */
	  Iterator operator=(const Iterator & given_iter)
	       {
		    Node * node = new Node();
		    if(given_iter.curr_node != NULL){
			 node->data = given_iter.curr_node->data;
			 node->next = given_iter.curr_node->next;
			 node->prev = given_iter.curr_node->prev;
		    }
		    else {
			 node = NULL;
		    }
		    curr_node = node;
		    return *this;
	       }
	  

	  /* Prefix and postfix operators, to move forward and backward in the list
	   */
	  Iterator operator++() // prefix (increment, return incremented)
	       {
		    if (! curr_node){
			 cerr << "Error : End of the list. Can't incerment further;" << endl;
			 exit(1);
		    }
		    curr_node = curr_node->next;
		    return *this;
	       }
	  
	  Iterator operator++(int n) // postfix (increment, return old one)
	       {
		    if (! curr_node){
			 cerr << "Error : End of the list. Can't incerment further;" << endl;
			 exit(1);
		    }
		    Iterator temp = *this;
		    curr_node = curr_node->next;
		    return temp;
	       }

	  Iterator operator--(int n) // postfix (decrement, return old one)
	       {
		    if (! curr_node){
			 cerr << "Error : Beginning of the list. Can't decerment further;" << endl;
			 exit(1);
		    }
		    Iterator temp = *this;
		    curr_node = curr_node->prev;
		    return temp;
	       }
	  
	  Iterator operator--() // prefix (decrement, return decremented)
	       {
		    if (! curr_node){
			 cerr << "Error : Beginning of the list. Can't decerment further;" << endl;
			 exit(1);
		    }
		    curr_node = curr_node->prev;
		    return *this;
	       }
	  
           
	  /* Operators to return elements contained in the list */
	  int &operator*()
	       {
	  	    return curr_node->data;
	       }
	  

	  /* Operators to compare two iterators */
	  bool operator==(Iterator & given_iter) const
	       {
		    if (( !curr_node )&&( given_iter.curr_node )){
			      return false;
			 }
		    if (( curr_node )&&( !given_iter.curr_node)){
			      return false;
			 }
		    if (( !curr_node )&&( !given_iter.curr_node)){		    
			      return true;
			 }
		    bool condition = (   curr_node->data == given_iter.curr_node->data
                                      && curr_node->next == given_iter.curr_node->next
				      && curr_node->prev == given_iter.curr_node->prev);
		    if (condition) {
			      return true;
			 }
		    return false;
	       }
	  
		    
	  bool operator!=(Iterator & given_iter) const
	       {
		    return !(*this == given_iter);
	       }
	  
     };
private:
     // Function to check whther the given itertor 
     // is a valid iterator of the list or not
     bool iterIsValid(Iterator iter)
	  {
	       Iterator temp = begin();
	       Iterator last = end();
	       while (temp != last ){
		    if (temp == iter){
			 return true;
		    }
		    temp++;
	       }
	       return false;
	  }

     // Function to terminate the program with an 
     // error message when the iterator is not valid
     void terminateOnInvalidIterator(Iterator iter)
	  {
	       if ( ! iterIsValid(iter) ){
		    cerr << "Error : The iterator is not that of the given list." << endl;
		    exit(1);
	       }
	  }
     


public:
     /* Constructor */
     IntList()
	  {
	       length = 0;
	       head = NULL;
	       tail = NULL;
	  }

     /* Copy constructor */
     IntList(const IntList & given_list)
	  {
	       *this = given_list;
	  }

     /* assignment Operator */
     IntList &operator=(const IntList & given_list)
	  {
	       Iterator end = given_list.end();
	       for(Iterator i = given_list.begin(); i!=end; i++){
		    push_back(*i);
	       }
	       return *this;
	  }
     
     /* Function to check if the list is empty */
     bool empty() const
	  {
	       return (length == 0);
	  }
     
     /* Function to return the number of elements */
     unsigned int size() const
	  {
	       return length;
	  }
        
     /* Functions to add an element to the start and end of the list */
     void push_back(int data)
	  {
	       Node * node = new Node();
	       node->data = data;
	       node->next = NULL;
	       node->prev = NULL;
	       if (length == 0){
		    tail = node;
		    head = node;
	       }
	       else{
		    tail->next = node;
		    node->prev = tail;
		    tail = node;
	       }
	       length++;
	  }

	       
     void push_front(int data)
	  {
	       Node * node = new Node();
	       node->data = data;
	       node->next = NULL;
	       node->prev = NULL;
	       if (length == 0){
		    tail = node;
		    head = node;
	       }
	       else{
		    head->prev = node;
		    node->next = head;
		    head = node;
	       }
	       length++;
	  }
	       

     /* Functions to remove an element from the start and end of the list */
     int pop_back()
	  {
	       if (length == 0){
		    cerr << "Error : Can not pop from an empty list." << endl;
		    exit(1);
	       }
	       Node * temp = tail;
	       int data = tail->data;
	       tail = tail->prev;
	       if (! tail){
		    head = tail;
	       }
	       else{
		    tail->next = NULL;
	       }
	       length--;
	       delete temp;
	       return data;
	  }
	       
     int pop_front()
	  {
	       if (length == 0){
		    cerr << "Error : Can not pop from an empty list." << endl;
		    exit(1);
	       }
	       Node * temp = head;
	       int data = head->data;
	       head = head->next;
	       if (! head){
		    tail = head;
	       }
	       else {
		    head->prev = NULL;
	       }
	       length--;
	       delete temp;
	       return data;
	  }

     /* Function to delete all elements from the list */
     void clear()
	  {
	       int x;
	       while(length){
		    x = pop_front();
	       }
	       head = NULL;
	       tail = NULL;
	  }
     

     /* Functions to start and end an iteration
      * begin returns an Iterator corresponding to the first element
      *
      * end should return an element that indicates that iterator is
      * complete. That is it should return the value obtained on
      * incrementing an iterator corresponding to the last element.
      */

     // Note : as the list is doubly linked, to preserve the symmetry,
     // the end() returns an iterator corrosponding to the tail.
     // The increment and decrement operators return iterators with
     // null node pointers if iterator corrosponding to head is decremented
     // or that corrosponding to the tail is incermented
     Iterator begin() const
	  {
	       Iterator iter;
	       iter.curr_node = head;
	       return iter;
	  }
     
     Iterator end() const
	  {
	       Iterator iter;
	       iter.curr_node = tail;
	       return iter;
	  }

     /* insert adds an element after the given iterator */
     void insert(const Iterator & iter, int input)
	  {
	       terminateOnInvalidIterator(iter);
	       if ( iter.curr_node == NULL ){
		    cerr << "Error : The iterator is not associated to any list. Or the list is empty." << endl;
		    exit(1);
	       }
	       Node * node = new Node();
	       node->next = iter.curr_node->next;
	       node->data = input;
	       node->prev = iter.curr_node;
	       iter.curr_node->next->prev = node;
	       iter.curr_node->next = node;
	       length++;
	  }
     
     /* remove, deletes the element at the iterator and moves the iterator
      * to the next element
      */
     void remove(Iterator & iter)
	  {
	       terminateOnInvalidIterator(iter);
	       Iterator itr1 = begin();
	       Iterator itr2 = end();
	       if (iter ==  itr1){
		    pop_front();
		    iter = begin();
	       }
	       else if (iter == itr2){
		    cerr << "Error : Iterator at the end of the list. Can't remove." << endl;
		    exit(1);
	       }
	       else {
		    Node * temp = iter.curr_node;
		    iter.curr_node->prev->next = iter.curr_node->next;
		    iter.curr_node->next->prev = iter.curr_node->prev;
		    iter.curr_node = iter.curr_node->next;
		    delete temp;
	       }
	       length--;
	  }

     /* Destructor to delete elements */
     ~IntList()
	  {
	       clear();
	       delete head;
	       delete tail;
	  }

     // Print the list (for debugging purposes)
//      void print()
// 	  {
// 	       Iterator iter =  begin();
// 	       Iterator iter2 = end();
// 	       if ( ! iter.curr_node ){
// 		    cout << "Empty list. Nothing to print." << endl;
// 	       }
// 	       else{
		    
// 		    cout << iter.curr_node->data << " ";
// 		    do{
// 			 iter++;
// 			 cout << iter.curr_node->data << " ";
// 		    }		    		    
// 		    while (iter != iter2);
// 		    cout << endl;
// 	       }
// 	  }
     
};

// int main()
// {
//      IntList li, li2;
//      li.push_front(14);
//      li.push_back(29);
//      li.push_back(20); 
     
//      li.print();
//      IntList::Iterator iter = li.begin();
//      li.insert(iter, 99);
//      li.insert(iter, 33);
//      cerr << "iter is : " << *iter << endl;
//      iter++;
//      iter++;
//      li.print();
//      cerr << "iter is : " << *iter << endl;
//      // 14 33 99 29 20
//      li.remove(iter);
//      li.print();
//      cerr << "iter is : " << *iter << endl;
//      iter--;
//      cerr << "iter is : " << *iter << endl;
//      cerr << "end is : " << li.pop_back() << endl;
//      li.print();
//      cerr << "front is : " << li.pop_front() << endl;     
//      li.clear();
//      li.insert(iter, 9999);
     
//      li.print();
     

//      return 0;
// }


