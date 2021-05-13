//Minh Tran
//05/12/2021
//This is the client program
//The client can use the functions in table.h file
//to design how the program will run.
//I have design a basic menu to test all the functions
//available

#include "table.h"

int main(){
	term my_term;
	table my_table;
	int choice = 0;
	node * copy = NULL;
	char key[WORD];
	char des[WORD];
	char web[WORD];
	char match[WORD];
	char add_web[WORD];
	char delete_web[WORD];
	char key_web[WORD];
	char key_delete[WORD];
	char key_retrieve[WORD];
	char res, res1, res2;

	do{

		//Ask if user want to add another term
		cout<<"Do you want to enter another term?(Y/N): ";
		cin>>res;
		cin.ignore(100,'\n');

		if (toupper(res) == 'Y'){
			//Loop if user want to enter new term
			do{

				//get term/key from user
				cout<< "Enter term: ";
				cin.get (key, WORD);
				cin.ignore (100,'\n');

				//get term's description from user
				cout<< "Enter the term's description: ";
				cin.get (des, WORD);
				cin.ignore (100,'\n');

				//inset the term and description to hash table
				//web link insert is in the function
				my_table.insert(key, des);	

				//Ask if user want to add another term
				cout<<"Do you want to enter another term?(Y/N): ";
				cin>>res;
				cin.ignore(100,'\n');

			} while (toupper(res) == 'Y');
		}
		
		//Ask user if they want to load the file and warn them to not do it
		//if they already done.
		cout<<"Do you want to load terms from a file?"
			<<"(enter N terms already loaded) (Y/N)"<<endl;
		cin>>res1;
		cin.ignore (100,'\n');

		//Load info from an external file
		if (res1 == 'Y') my_table.load();

		//Prompt user to what they can do with the data
		cout<<"Do you want to add website link to an existing term (enter 1),"<<'\n'
			<<"remove a term (enter 2), retrieve a term information (enter 3),"<<'\n'
			<<"remove all that contain a specific link (enter 4),"<<'\n'
			<<"or display information of a term (enter 5)"<<endl;
		cin>>choice;
		cin.ignore(100,'\n');

		do{	
			if (choice == 1){ 
				//User enter term to add web link
				cout<<"Please enter the term's name to add website: ";
				cin.get(key_web, WORD);
				cin.ignore(100, '\n');

				//User add web link
				cout<<"Please enter website."<<endl;
				cin.get(add_web, WORD);
				cin.ignore(100, '\n');
				my_table.add_web(key_web, add_web);
			}

			else if (choice == 2){
				//User enter term to remove from table
				cout<<"Please enter term to remove: ";
				cin.get (key_delete, WORD);
				cin.ignore (100,'\n');
				my_table.remove_by_key(key_delete);
			}

			else if (choice == 3){
				//Get the term to retrieve
				cout<<"Please enter term retrieve: ";
				cin.get (key_retrieve, WORD);
				cin.ignore (100,'\n');
				my_table.retrieve(key_retrieve, copy);

				//Display the retrieve info
				cout<<"Term: "<<copy->item.key<<'\t'
				<<"Descriptioni: "<<copy->item.des<<endl;
				copy->item.web.display();
			}

			else if (choice == 4){
				//Get user link to delete
				cout<<"What link you want to delete?"<<endl;
				cin.get(delete_web, WORD);
				cin.ignore(100, '\n');
				my_table.delete_link(delete_web);
			}

			else if (choice == 5){
				//User enter what term they want to display its data
				cout<< "Enter term to display (case sensitive): ";
				cin.get (match, WORD);
				cin.ignore (100,'\n');
				my_table.display_key(match);
			}

			else
				//Display message when user type in wrong command
				cout<<"Invalid action. Please try again"<<endl;

		//loop if user mistype their choice
		} while ((choice < 1) || (choice > 5));
		
		//Delete copy node if it has info to preven memory leak
		if (copy){
			delete copy;
			copy = NULL;
		}

		//Ask if user want to user program again
		cout<<"Do you want to use the program again? (Y/N)"<<endl;
		cin>>res2;
		cin.ignore(100,'\n');

	//Loop if user want to use program again
	} while (toupper(res2) == 'Y');

	return 1;
}

