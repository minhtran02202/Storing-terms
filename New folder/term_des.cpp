//Minh Tran
//This is where the logic of 
//hash table functions are defined

#include "table.h"

//Term data constructor and destructor
term::term()
{
	key = NULL;
	des = NULL;
  num_web = 0;
}

term::~term()
{
	if (key){
		delete[]key;
		key = NULL;
	}
	if (des){
		delete[]des;
		des = NULL;
	}
}

//Node constructor. No need for destructor 
//because next will be delete in table destructor
node::node()
{
	next = NULL;
}


//hash table class constructor and destructor
table::table(int size){
	table_size = size;

  	//Set all indexes in hash table to NULL
	hash_table = new node *[size];
	for (int i=0; i<table_size; ++i)
		hash_table[i] = NULL;

}

table::~table(){

  	//Remove hash table at index i if it has data
	for (int i=0; i<table_size; ++i){

    		//This is to remove the chain link at index i
		node * current = hash_table[i];
		while(current){
			node * temp = current;
			current = current->next;
			delete temp;		
		}
	}

	if (hash_table) delete[]hash_table;

}



//Hash function. Determine the location of the data
int table::hash_function (char key[]) const
{
	int test=0;
	for (int i=0; i< strlen(key); ++i)
		test += key[i];

	return test % table_size;
}

//Add a term data
int table::insert(char key[], char des[])
{
  	//Get the location that the data will be
	int i = hash_function (key);

  	//If the location is empty
	if (!hash_table[i]){
		hash_table[i] = new node;
		hash_table[i]->next = NULL;
	}	

  	//If collision occur
	else{
		node * temp = hash_table[i];
		hash_table[i] = new node;
		hash_table[i]->next = temp;
	}

  	//copy the key and description to term data
	hash_table[i]->item.key = new char[strlen(key)+1];
	strcpy (hash_table[i]->item.key, key);
	hash_table[i]->item.des = new char[strlen(des)+1];
	strcpy (hash_table[i]->item.des, des);
 
  	//Call web insert function to add a list of links 
  	//store how many links are there
	hash_table[i]->item.num_web = hash_table[i]->item.web.insert();

	return 1;
}

//Display a term that that user want
int table::display_key (char match[])
{
  	//Exit if there is no hash table or hash table at index i is empty
	if (!hash_table){
	       cout<<"Table is empty"<<endl;
       	       return 0;
	}
	int i = hash_function(match);
  	if (!hash_table[i]){
		cout<<"Sorry, term is not in the data."<<endl;
		return 0;
	}
  
	node * temp = hash_table[i];

  	//Loop while temp is not at the end of the chain
	while (temp != NULL){

    		//Display if temp's key match the term entered by user
		if (strcmp(temp->item.key, match) == 0){
			cout<<"Term: "<<temp->item.key<<endl
			    <<"Description: "<<temp->item.des<<endl;

      			//Call function to display all the web links
			temp->item.web.display();
			return 1;
		}
    		//Move to next node if temp is not match
		temp = temp->next;
	}
  	//Display message if the term entered by user is not in the table
	cout<<"Sorry, term is not in the data."<<endl;
	return 1;
}

//Load data from external file
int table::load()
{
	ifstream fin;
	fin.open("file.txt");
 
  	//Display message if program can't open the file
	if(!fin.is_open()){
		cout << "Failed to read" << endl;
		return 0;
	}
 
	char key[WORD];
	char des[WORD];
	char web[WORD];

  	//Get key name from the file
	fin.get(key, WORD, ',');
	fin.ignore(100, ',');
 
  	//Loop while program is not at the end of the file
	while(!fin.eof()){

    		//Get term's description
		fin.get(des, WORD, ',');
		fin.ignore(100, ',');
    
    		//Get term's web link(
		fin.get(web, WORD, '\n');
		fin.ignore(100, '\n');

    		//Call funciton to insert the data pieces to the hash table
		load_insert(key, des, web);
		fin.get(key, WORD, ',');
		fin.ignore(100, ',');
	}
 
  	//Close the file when finish
	fin.close();
	fin.clear();
	return 1;
}

//add external file's data to hash table
int table::load_insert(char key[], char des[], char web[])
{
 	//Get the location that the data will be
	int i = hash_function (key);

  	//If the location is empty
	if (!hash_table[i]){
		hash_table[i] = new node;
		hash_table[i]->next = NULL;
	}	

  	//If collision occur
	else{
		node * temp = hash_table[i];
		hash_table[i] = new node;
		hash_table[i]->next = temp;
	}

  	//copy the key and description to term data
	hash_table[i]->item.key = new char[strlen(key)+1];
	strcpy (hash_table[i]->item.key, key);
	hash_table[i]->item.des = new char[strlen(des)+1];
	strcpy (hash_table[i]->item.des, des);
 
  	//Call function to insert web link
	hash_table[i]->item.web.insert_one(web);
	return 1;
}

//Add website to an existing term
int table::add_web(char key[], char web[])
{
	//location of the term in table
	int i = hash_function(key);
	//exit if the table location is empty
	if (!hash_table[i]){
		cout<<"Term does not exist to add web link to."<<endl;
		return 0;
	}
	node * temp = hash_table[i];
	while(temp != NULL){

		//Traverse until a chain's term match 
		if (strcmp(temp->item.key, key) == 0){
			//insert the web link and exit
			temp->item.web.insert_one(web);
			return 1;
		}
		//keep traversing if chain's term not match
		temp = temp->next;
	}

	//Display message if term does not exist	
	cout<<"Term does not exist to add web link to."<<endl;
	return 0;
}

//Remove a term entered by user
int table::remove_by_key(char key[])
{
	//Get term's location
	int i = hash_function(key);
	return remove_by_key(key, hash_table[i]);
}
int table::remove_by_key(char key[], node *& head)
{
	//Exit if term does not exist
	if (!head){
	       cout<<"Term does not exist to remove."<<endl;
       	       return 0;
	}

	//if head's term match
	if (strcmp(head->item.key, key)==0){
		//temp node to locate the next node
		node * temp = head->next;

		//delete head and link it to the next node
		delete head;
		head = temp;
		return 1;
	}

	//recursive to the next chain link	
	return remove_by_key(key, head->next);
}
int table::retrieve(char key[], node *& copy)
{
	int i = hash_function(key);
	if (!hash_table[i]) return 0;

	node * temp = hash_table[i];
	while(temp != NULL){
		if (strcmp(temp->item.key, key) == 0){
			copy = new node;
			char * web = NULL;
			copy->item.key = new char [strlen(key)+1];
			strcpy(copy->item.key, key);
			copy->item.des = new char [strlen(temp->item.des)+1];
			strcpy(copy->item.des, temp->item.des);

			for (int i=0; i< temp->item.num_web; ++i){
				temp->item.web.retrieve(web);
				//cout<<web<<endl;
				copy->item.web.insert_one(web);
				delete[]web;
				web = NULL;
			}
			return 1;
		}
		temp = temp->next;
	}
	return 1;
}
int table::delete_link(char web[])
{
	for (int i=0; i<53; ++i){
		if (hash_table[i])
			delete_link(hash_table[i], web);
	}
	return 1;
}

int table::delete_link(node *& head, char web[])
{
	if (!head) return 0;
	
	int match = head->item.web.compare(web);
	if (match >= 1){
		node * temp = head->next;
		delete head;
		head = temp;
		if (!head) return 0;
	}
	return delete_link(head->next, web);
}
