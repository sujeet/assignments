#include <vector>
#include <cstdio>
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <fstream>

using namespace std;

class Student
{
     string id;
     string name;
     string address;
     string birth_date;
     string cgpa;
public:
     Student (string id, string name, string address, string birth_date, string cgpa)
	  {
	       this->id = id;
	       this->name = name;
	       this->address = address;
	       this->birth_date = birth_date;
	       this->cgpa = cgpa;
	  }
     Student ()
	  {
	       id = "";
	       name = "";
	       address = "";
	       birth_date = "";
	       cgpa = "";
	  }
     void printRecord()
	  {
	       cout <<"id            : "<<id<<"\n";
	       cout <<"name          : "<<name<<"\n";
	       cout <<"address       : "<<address<<"\n";
	       cout <<"date of birth : "<<birth_date<<"\n";
	       cout <<"cgpa          : "<<cgpa<<"\n";
	  }
     string getId()
	  {
	       return id;
	  }
};

class StudentDB
{
     vector<Student> database;
public :
     Student searchById(string id)
	  {
	       int i;
	       for (i=0; i<database.size(); i++){
		    if ( database[i].getId() == id ){
			 return database[i];
		    }
	       }
	       string err = "not found";
	       Student no_one = Student(err, err, err, err, err);
	       return no_one;
	  }
     void populateFromFile(char* filename, int population, char delimiter)
	  {
	       ifstream file;
	       string id, name, address, birth_date, cgpa;
	       Student student;
	       int i = 0;
	       file.open(filename);
	       if ( !file ){
		    cout << "The file " << filename << " does not exist.\n";
		    exit(0);
	       }
	       while ( (!file.eof()) && (i<population) ){
		    getline (file, id, delimiter);
		    getline (file, name, delimiter);
		    getline (file, address, delimiter);
		    getline (file, birth_date, delimiter);
		    getline (file, cgpa);
		    student = Student(id, name, address, birth_date, cgpa);
		    database.push_back(student);
		    i++;
	       }
	  }
};

int main (int argc, char* argv[])
{
     if ( argc == 3 ){
          int no_of_students = atoi(argv[2]);
	  StudentDB database;
	  string id ;
	  database.populateFromFile(argv[1], no_of_students, '|');
	  cout << "Please enter the id or type 'exit' to exit.\n";
	  cin >> id;
	  while ( id != "exit" ){
	       database.searchById(id).printRecord();
	       cout << "\n";
	       cin >> id;
	  }
     }
     else {
	  cout << "Please give proper command line arguments\n";
     }
     return 0;
}
     
	  
 
