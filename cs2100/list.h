
class IntList {
public:
     /* Class to access the elements of the list. */
     class Iterator {
     public:
	  friend class Intlist;
	  /* Constructor */
	  Iterator();
	  /* Copy constructor */
	  Iterator(const Iterator &);

	  /* Assignment operator */
	  Iterator operator=(const Iterator &);

	  /* Prefix and postfix operators, to move forward and 
             backward in the list
	   */
	  Iterator operator++();
	  Iterator operator++(int);
	  Iterator operator--();
	  Iterator operator--(int);
           
	  /* Operator to return elements contained in the list */
	  int &operator*();

	  /* Operators to compare two iterators */
	  bool operator==(Iterator &) const;
	  bool operator!=(Iterator &) const;
     };
public:
     /* Constructor */
     IntList();

     /* Copy constructor */
     IntList(const IntList &);

     /* Assignment Operator */
     IntList &operator=(const IntList &);

     /* Function to check if the list is empty */
     bool empty() const;
     /* Function to return the number of elements */
     unsigned int size() const;
        
     /* Functions to add an element to the start and end of the list */
     void push_back(int);
     void push_front(int);

     /* Functions to remove an element from the start and end of the list */
     int pop_back();
     int pop_front();

     /* Function to delete all elements from the list */
     void clear();

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

     Iterator first() const;
     Iterator end() const;

     /* insert adds an element after the given iterator */
     void insert(const Iterator &, int);
     /* remove, deletes the element at the iterator and moves the iterator
      * to the next element
      */
     void remove(Iterator &);

     /* Destructor to delete elements */
     ~IntList();
};
