#ifndef INTLIST_H
#define INTLIST_H

#ifndef TYPE
#define TYPE int
#endif

class Node 
{ 
public: 
     TYPE data; 
     Node *next; 
     Node() {data = 0; next = NULL;} 
     Node(TYPE num, Node * next_node = NULL) {data = num; next = next_node;} 
};     

class IntList 
{
private :
     Node * head;
public :
     class Iterator 
     {
     private:
          Node * curr_node;
     public :
          friend class IntList;
          Iterator ();
          Iterator (const Iterator&);
          Iterator& operator = (const Iterator &);
          Iterator operator ++ ();
          Iterator operator ++ (int);
          TYPE operator * ();
          bool operator == (const Iterator &) const;
          bool operator != (const Iterator &) const;
     };
     IntList();
     IntList(const IntList &);
     bool is_empty() const;
     unsigned int length() const;
     void push_front(TYPE);
     void push_back(TYPE);
     TYPE pop_front();
     TYPE pop_back();
     void clear();
     Iterator begin() const;
     Iterator end() const;
     void insert_after(Iterator&, TYPE);
     void remove(Iterator &);
     void print();
     ~IntList();
};

#endif
