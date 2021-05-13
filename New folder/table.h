//Minh Tran
//This file cotain all the structs, classes, and functions
//are defined. The client can use this file to know what
//functions/classes/structs they could impliment in the
//client program

#include <cstring>
#include <iostream>
#include <cctype>
#include <fstream>

using namespace std;

//Constant
const int WORD = 100;	//char array size throughout the program

//web LLL
struct list{
	list();
	~list();
	char * web;	//store web's name
	list * next;
};

//web LLL managaer
class manage_list{
	public:
		manage_list();
		~manage_list();
		int remove_all(); 			//use in destructor
		int insert();				//add many web nodes
		int insert_one(char web[]);  		//add one web nodes
		int display();				//display wrapper function	
		int retrieve(char *& web);  		//make a clone LLL for user
		int compare(char web[]);  		//compare wrapper function 
	private:
		int display(list * head); 		//display the LLL 
		int compare(list *& head, char web[]);	//compare if the web the user enter match any node in LLL
		list * clone;				//use in retrieve function
		list * head;				//first node of LLL
		list * tail;				//last node of LLL
};

//term data type
struct term{
	term();
	~term();
	char * key;		//key for term name and hash function
	char * des;		//term's description
	int num_web;		//number of webs in the web LLL
	manage_list web;  	//web LLL manager
}; 

//term node
struct node{
	node();
	term item;	//term data
	node * next;	
};

class table{
	public:
		table(int size=101);					//53 for hash table's size
		~table();
		int insert(char key[], char des[]);			//add a term
		int display_key (char match[]);				//display a term that that user want
		int load();						//load data from external file
		int load_insert(char key[], char des[], char web[]);	//add external file's data to hash table
		int add_web(char key[], char web[]);			//add a new web to existing term
		int remove_by_key(char key[]);				//remove_by_key wrapper function
		int retrieve(char key[], node *& copy);			//create a copy of a term entered by user
		int delete_link(char web[]);				//delete_link wrapper function

	private:
		int hash_function (char key[]) const;
		int remove_by_key(char key[], node *& hash_table);	//remove a term that the user want
		int delete_link(node *& hash_table, char web[]);	//remove a term if it has a particular web
		node ** hash_table;
		int table_size;
};


