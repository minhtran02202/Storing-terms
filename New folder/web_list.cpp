//Minh Tran
//This is where the logic of 
//the web's list functions are defined

#include "table.h"

//web LLL constructor and destructor
list::list()
{
	web = NULL;
	next = NULL;
}

list::~list()
{
	if (web){
		delete[]web;
		web = NULL;
	}

}

//web LLL manage class constructor and destructor
manage_list::manage_list(){
	head = NULL;
	tail = NULL;
 	clone = NULL;
}

manage_list::~manage_list(){
	remove_all();
}

int manage_list::remove_all(){
	if (!head) return 0;
	list * temp = head->next;
	delete head;
	head = temp;
	return remove_all() + 1;
}	

//Add many web nodes
int manage_list::insert(){
	char web[WORD];
	char res;
  int count = 0;

	//Loop if user want to add more web links
	do{
		//Get user web link
		cout<< "Enter the term's website: ";
		cin.get (web, WORD);
		cin.ignore (100,'\n');
		//function to insert the link
		insert_one(web);
    ++count;

		//Ask if user want to add more web links
		cout<<"Do you want to enter another website?(Y/N): ";
		cin>>res;
		cin.ignore(100,'\n');
	} while (toupper(res) == 'Y');

	return count;
}

//Add one web link
int manage_list::insert_one(char web[]){

	//if the list is empty
	if (!head){
		head = new list;
		head->next = NULL;
		tail = head;
	}

	//if the list has data
	else{
		tail->next = new list;
		tail = tail->next;
		tail->next = NULL;
	}

	//copy the link info over to the node's data
	tail->web = new char[strlen(web)+1];
	strcpy (tail->web, web);
	return 1;
}

//Display wrapper function
int manage_list::display(){
	if (!head) return 0;
	return display (head);
}

//Display the LLL
int manage_list::display(list * head){

	//exit if list is empty
	if (!head) return 0;

	//display web link info
	cout<<"Website: "<<head->web<<endl;

	//recursion to display until it reach the end of the list
	return display(head->next) + 1;
}

int manage_list::retrieve(char *& web){
	if (!head) return 0;
	if (!clone)
		clone = head;
	else
		clone = clone->next;
	web = new char[strlen(clone->web)+1];
	strcpy(web, clone->web);
	return 1;
}

int manage_list::compare(char web[])
{
	return compare(head, web);
}

int manage_list::compare(list *& head, char web[])
{ 
	if (!head) return 0;
	if (strcmp(head->web, web) ==0){
		return compare(head->next, web) +1;
	}
	return compare(head->next, web);
}
