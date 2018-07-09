#include <iostream>
#include <new>
#include <cstring>
#include <string.h>
#include "ContactDetails.h"

using namespace std;

int listOfChoices();

int main() {

	int choice = 6;
	ContactDetails * first = NULL;

	do {
	choice = listOfChoices();
	switch(choice) {
	case 1:
		{
		ContactDetails * newEntry = new ContactDetails();
		first = newEntry->addContact(first);
		}
		break;
	case 2:	if(first) {
			first = first->deleteContact();
		} else {
			cout << "There are no contacts in the telephone directory." << endl;
		}  
		break;
	case 3:
		first->listAllContacts();
		break;
	case 4:
		first = first->deleteAllContacts();
		break;
	case 5:
		first->updateContact();
		break;
	case 6:
		break;
	default:
		cout << "Please enter a valid choice between 1 and 6." << endl;
		break; 
	}
	} while(choice != 6); 
	// write code to delete memory of all the contacts
	delete first;
	return 0;
}

int listOfChoices() {
	int choice;	
	cout << "Please select your choice from the following:" << endl;
	cout << "1. Add a new Contact." << endl;
	cout << "2. Delete a Contact." << endl;
	cout << "3. List all Contacts." << endl;
	cout << "4. Delete all Contacts." << endl;
	cout << "5. Update a contact." << endl;	
	cout << "6. Exit." << endl;
	cin >> choice;
	return choice;
};
