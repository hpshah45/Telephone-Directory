#include "ContactDetails.h"
#include <iostream>
#include <stdio.h>
#include <cstring>

using namespace std;

ContactDetails * ContactDetails::addContact(ContactDetails * first) {
	cout << "Enter the following details for adding the new contact:" << endl;
	cout << "Enter the last name:" << endl;
	cin >> this->lastName;
	cout << "Enter the first name:" << endl;
	cin >> this->firstName;
	cout << "Enter the contact number details:" << endl;
	cin >> this->number;
	cout << "Enter the address:" << endl;
	cin >> this->address;

	if (first == NULL) {
		first = this;
	}
	else {
		ContactDetails * prev = first;
		ContactDetails * temp = first;
		while(temp) {
			prev = temp;
			temp = temp->next;
		}
		prev->next = this;
		this->prev = prev;	
	}
	return first;
}

void ContactDetails::listAllContacts() {
	if (this == NULL) {
		cout << "There are no contacts to display." << endl;
		return;
	}
	cout << "The following are all the contacts stored in the telephone directory." << endl;
	ContactDetails * temp = this;
			
	while(temp) {
		cout << "First Name: " << temp->firstName << " Last Name: " << 
		temp->lastName << " Contact Number: " << temp->number << " Address: " 
		<< temp->address << endl;
		temp = temp->next;
	}
	
}


ContactDetails * ContactDetails::deleteContact() {
	string contentToDel;
	cout << "Please enter the name or the number which you want to delete:" << endl;
	cin >> contentToDel;//Ask for user permission to delete.
	if ((this->firstName == contentToDel) || (this->number == contentToDel) || (this->lastName == contentToDel)) {				
		ContactDetails * temp = this;
		ContactDetails * temp2 = temp->next;
		delete temp;
		temp2->prev = NULL;
		temp = NULL;
		return temp2;			
	}
	ContactDetails * temp = searchContact(contentToDel, this);
	if(temp) {
		deleteThisContact(temp);
	} else {
		cout << "No such contact to delete." << endl;
	}
	return this;
}

void ContactDetails::deleteThisContact(ContactDetails * temp) {
	if(temp) {
		if(temp->prev) {	
			temp->prev->next = temp->next;
		} 
		if(temp->next) {
			temp->next->prev = temp->prev;
		}
		delete temp;
		temp->next = NULL;
		temp->prev = NULL;
		temp = NULL;
	}
	else {
		//something to write.
	}
	return;
}

ContactDetails * ContactDetails::searchContact(string contentToSearch, ContactDetails * first) {
	while(first) {
		if ((first->firstName == contentToSearch) || (first->lastName == contentToSearch) 
	     	|| (first->number == contentToSearch)) {
			return first;
		}
		first = first->next;	
	}
	return NULL;
}

ContactDetails * ContactDetails::deleteAllContacts() {
	if(this == NULL) {	
		cout << "There are no contacts in the directory to be deleted." << endl;
		return this;	
	}
	cout << "Are you sure you want to delete all the contacts? Type 'Y' to delete all the contacts." << endl;
	char choice;
	cin >> choice;
	if(choice == 'Y') {
		ContactDetails * temp = this;
		ContactDetails * next = temp;
		while(temp) {
			next = temp->next;
			deleteThisContact(temp);
			temp = next;
		}
		return NULL;
	}
	else {
		cout << "Okay. Not deleting any of the contacts." << endl; 
		return this;
	}
}

void ContactDetails::updateContact() {
	int choice = 5;
	cout << "What would you like to update?" << endl
	<< "1. First Name." << endl
	<< "2. Last Name." << endl
	<< "3. Number." << endl
	<< "4. Address." << endl;

	cin >> choice;
	switch(choice) {
		case 1:
			this->updateFirstName();
			break;
		case 2:
			this->updateLastName();
			break;
		case 3:
			updateNumber();
			break;
		case 4:
			updateAddress();
			break;
		default:
			cout << "Please enter a valid choice." << endl;
	}
}

void ContactDetails::updateFirstName() {
	string firstName = "";
	cout << "Please enter the first name of the contact you would like to change." << endl;
	cin >> firstName;

	ContactDetails * temp = searchContact(firstName, this);
	if(temp) {
		cout << "Please enter the first name that you would like to change to." << endl;
		string updatedFirstName = "";
		cin >> updatedFirstName;
		temp->firstName = updatedFirstName;
	}
	else {
		cout << "Sorry. No such contact found." << endl;
	}	
	return;	
}

void ContactDetails::updateLastName() {
	string lastName = "";
	cout << "Please enter the last name of the contact you would like to change." << endl;
	cin >> lastName;

	ContactDetails * temp = searchContact(lastName, this);
	if(temp) {
		cout << "Please enter the last name that you would like to change to." << endl;
		string updatedLastName = "";
		cin >> updatedLastName;
		temp->lastName = updatedLastName;
	}
	else {
		cout << "Sorry. No such contact found." << endl;
	}	
	return;	
}

void ContactDetails::updateNumber() {
	string number = "";
	cout << "Please enter the number of the contact you would like to change." << endl;
	cin >> number;

	ContactDetails * temp = searchContact(number, this);
	if(temp) {
		cout << "Please enter the number that you would like to change to." << endl;
		string updatedNumber = "";
		cin >> updatedNumber;
		temp->number = updatedNumber;
	}
	else {
		cout << "Sorry. No such contact found." << endl;
	}	
	return;	
}

void ContactDetails::updateAddress() {
	string contactDetail = "";
	cout << "Please enter the contact detail of the contact that you would like to change the address." << endl;
	cin >> contactDetail;

	ContactDetails * temp = searchContact(contactDetail, this);
	if(temp) {
		cout << "Please enter the updated address." << endl;
		string updatedAddress = "";
		cin >> updatedAddress;
		temp->address = updatedAddress;	
	}
	else {
		cout << "Sorry. No such contact." << endl;
	}

	return;
}	
