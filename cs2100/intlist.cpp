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
     /* Class to access the elements of the list. We need a seperate class
      * for this as we want to keep the pointers to the nodes private.
      */
     class Iterator {
     private:
	  Node * curr_node;
     public:
	  friend class IntList;
	  /* Constructors */
	  Iterator()
	       {
		    curr_node = 0;
	       }
	  
// 	  Iterator(Node * node)
// 	       {
// 		    curr_node = node;
// 	       }
	  
	  /* Copy constructor */
	  Iterator(const Iterator & given_iter)
	       {
		    curr_node = given_iter.curr_node;
	       }
	  
 
	  /* Assignment operator */
	  Iterator operator=(const Iterator & given_iter)
	       {
		    Node * node = new Node();
		    if(given_iter.curr_node != 0){
			 node->data = given_iter.curr_node->data;
			 node->next = given_iter.curr_node->next;
			 node->prev = given_iter.curr_node->prev;
		    }
		    else {
			 node = 0;
		    }
		    curr_node = node;
		    return *this;
	       }
	  

	  /* Prefix and postfix operators, to move forward and backward in the list
	   */
	  Iterator operator++() // prefix
	       {
		    if (! curr_node){
			 cerr << "Error : End of the list. Can't incerment further;" << endl;
			 exit(1);
		    }
		    curr_node = curr_node->next;
		    return *this;
	       }
	  
	  Iterator operator++(int n) // postfix
	       {
		    if (! curr_node){
			 cerr << "Error : End of the list. Can't incerment further;" << endl;
			 exit(1);
		    }
		    Iterator temp = *this;
		    curr_node = curr_node->next;
		    return temp;
	       }

	  Iterator operator--(int n) // postfix
	       {
		    if (! curr_node){
			 cerr << "Error : Beginning of the list. Can't decerment further;" << endl;
			 exit(1);
		    }
		    Iterator temp = *this;
		    curr_node = curr_node->prev;
		    return temp;
	       }
	  
	  Iterator operator--() // prefix
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
	  
	  // int *operator->()
	  //      {
	  // 	    return 1 ;
	  //      }
	  

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

public:
     /* Constructor */
     IntList()
	  {
	       length = 0;
	       head = 0;
	       tail = 0;
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
	       node->next = 0;
	       node->prev = 0;
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
	       node->next = 0;
	       node->prev = 0;
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
		    tail->next = 0;
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
		    head->prev = 0;
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
	       head = 0;
	       tail = 0;
	  }
     

     /* Functions to start and end an iteration
      * begin returns an Iterator corresponding to the first element
      *
      * end should return an element that indicates that iterator is
      * complete. That is it should return the value obtained on
      * incrementing an iterator corresponding to the last element.
      */
     Iterator begin() const
	  {
	       Iterator *iter = new Iterator();
	       iter->curr_node = head;
	       return *iter;
	  }
     
     Iterator end() const
	  {
	       Iterator *iter = new Iterator();
	       iter->curr_node = tail;
	       return *iter;
	  }

     /* insert adds an element after the given iterator */
     void insert(const Iterator & iter, int input)
	  {
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
		    cerr << *iter << endl;
		    
		    iter.curr_node->prev->next = iter.curr_node->next;
		    
		    iter.curr_node->next->prev = iter.curr_node->prev;
		    iter.curr_node = iter.curr_node->next;
		    cerr << *iter << endl;
		    cerr << iter.curr_node->prev->data << endl;
		    
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
     void print()
	  {
	       Iterator iter =  begin();
	       Iterator iter2 = end();
	       if ( ! iter.curr_node ){
		    cout << "Empty list. Nothing to print." << endl;
	       }
	       else{
		    
		    cout << iter.curr_node->data << " ";
		    do{
			 iter++;
			 cout << iter.curr_node->data << " ";
		    }		    		    
		    while (iter != iter2);
		    cout << endl;
	       }
	  }
     
};

int main()
{
     IntList li;
     li.push_front(14);
     li.push_back(29);
     li.push_back(20); 
     li.print();
     IntList::Iterator iter = li.begin();
     li.insert(iter, 99);
     li.insert(iter, 33);
     iter++;
     iter++;
     li.print();
     cerr << "iter is : " << *iter << endl;
     // 14 33 99 29 20
     li.remove(iter);
     li.print();
     
//      li.clear();
//      li.print();
     

     return 0;
}

