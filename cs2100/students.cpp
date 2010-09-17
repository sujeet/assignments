#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

class Student{
public:
     string id;
     string name;
     string address;
     string birth_date;
     string cgpa;
     Student (string id, string name, string address, string birth_date, string cgpa)
	  {
	       id = id;
	       name = name;
	       address = address;
	       birth_date = birth_date;
	       cgpa = cgpa;
	  }
     Student ()
	  {
	       id = "";
	       name = "";
	       address = "";
	       birth_date = "";
	       cgpa = "";
	  }
     void print_record()
	  {
	       cout <<"id            : "<<id<<"\n";
	       cout <<"name          : "<<name<<"\n";
	       cout <<"address       : "<<address<<"\n";
	       cout <<"date of birth : "<<birth_date<<"\n";
	       cout <<"cgpa          : "<<cgpa<<"\n";
	  }

};



int search_by_id (string id, int no_of_students, Student* archive )
{
     int i = 0;
     while (i<no_of_students){
	  if (archive[i].id == id){
	       archive[i].print_record();
	       return 0;
	  }
	  i++;
     }
     cout << "Student not in record\n";
     return 1;
}


int main (int argc, char* argv[])
{
     ifstream data;
     if ( argc >= 3 ){
          int no_of_students = atoi(argv[2]);
 	  Student* archive = new Student [no_of_students];
	  data.open ( argv[1] );
	  if ( !data ){
	       cout << "the file " << argv[1] << " does not exist.\n";
	       return 1;
	  }
	  int i = 0;
	  while ( ( !data.eof() )&&( i<no_of_students ) ){
	       getline (data, archive[i].id, '|');
	       getline (data, archive[i].name, '|');
	       getline (data, archive[i].address, '|');
	       getline (data, archive[i].birth_date, '|');
	       getline (data, archive[i].cgpa);
	       i++;
	  }
	  string command ;
	  cout << "Please enter the id or type 'exit' to exit.\n";
	  cin >> command;
	  while ( command != "exit"){
	       search_by_id(command, no_of_students, archive);
	       cout << "\n";
	       cin >> command;
	  }
     }
     else {
	  cout << "please give proper command line arguments\n";
     }
     return 0;
}

	  
 
