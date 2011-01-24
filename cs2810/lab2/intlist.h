class Node 
{ 
public: 
     int data; 
     Node *next; 
     Node() {data = 0; next = NULL;} 
     Node(int num, Node * next_node = NULL) {data = num; next = next_node;} 
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
          int operator * ();
          bool operator == (const Iterator &) const;
          bool operator != (const Iterator &) const;
     };
     IntList();
     IntList(const IntList &);
     bool is_empty() const;
     unsigned int length() const;
     void push_front(int);
     void push_back(int);
     int pop_front();
     int pop_back();
     void clear();
     Iterator begin() const;
     Iterator end() const;
     void insert_after(Iterator&, int);
     void remove(Iterator &);
     void print();
     ~IntList();
};

