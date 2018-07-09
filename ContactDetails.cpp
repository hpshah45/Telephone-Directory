#include "ContactDetails.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

ContactDetails * ContactDetails::addContact(ContactDetails * first) {// to add a new contact
	cout << "Enter the following details for adding the new contact:" << endl;
	cout << "Enter the last name:" << endl;
	cin >> this->lastName;
	cout << "Enter the first name:" << endl;
	cin >> this->firstName;
	cout << "Enter the Mobile number:" << endl;
	cin.ignore();
	getline(cin, this->numbers["Mobile"]);
	cout << "Enter the Home phone number:" << endl;
	getline(cin, this->numbers["Home"]);
	cout << "Enter any other number you have:" << endl;
	getline(cin, this->numbers["Other"]);
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

void ContactDetails::listAllContacts() {// lists all the contacts
	if (this == NULL) {
		cout << "There are no contacts to display." << endl;
		return;
	}
	cout << "The following are all the contacts stored in the telephone directory." << endl;
	ContactDetails * temp = this;
			
	while(temp) {
		displayContact(temp);
		temp = temp->next;
	}
	return;
}

void ContactDetails::displayContact(ContactDetails * temp) {
	if(temp) { //displays the contact for the given pointer
		cout << "First Name: " << temp->firstName << " Last Name: " << temp->lastName; 
		if (temp->numbers["Mobile"].length() != 0) cout << " Mobile Number: " << temp->numbers["Mobile"];
		if (temp->numbers["Home"].length() != 0) cout << " Home Number: " << temp->numbers["Home"];
		if (temp->numbers["Other"].length() != 0) cout << " Other Number: " << temp->numbers["Other"];
		cout << " Address: " << temp->address << endl;
		return;
	}
}


ContactDetails * ContactDetails::deleteContact() {
	//delete a contact given the details.
	string contentToDel;
	cout << "Please enter the name or the number which you want to delete:" << endl;
	cin >> contentToDel;
	cout << "Are you sure you want to delete the contact? Type 'Y' to proceed." << endl;
	string choice = "N";
	cin >> choice;
	if(choice == "Y") {// asking for user permission
		vector<ContactDetails *> sameDetails = arrayOfSameContactDetails(contentToDel, this);
		if(sameDetails.size() == 1) { //in case there is no contact having this detail as having just 1 element means its a NULL pointer.
			cout << "No such contact to delete." << endl;
		}
		else if(sameDetails.size() == 2) { //just have 1 contact with this detail.
			if(sameDetails[0] == this) { //if the contact is the first contact in the list. need to update first.
				ContactDetails * temp2 = this->next;
				deleteThisContact(this);
				return temp2;
			}
			if(sameDetails[0]) { //other than first.
				deleteThisContact(sameDetails[0]);
			}				
		} else { //if there are multiple contacts with this detail.
			int selection = selectionForSameDetails(sameDetails);
			if(selection > sameDetails.size()) {
				cout << "Please choose a valid index." << endl;
				return this;
			}
			cout << "Okay. Deleting the contact at index " << selection << " ." << endl;//check the value of selection.
			if(sameDetails[selection - 1] == this) {
				ContactDetails * temp2 = this->next;
				deleteThisContact(this);
				return temp2;
			}
			if(sameDetails[selection - 1]) {
				deleteThisContact(sameDetails[selection - 1]);
			}
		}
	}
	return this;
}

vector<ContactDetails *> ContactDetails::arrayOfSameContactDetails(string contentToSearch, ContactDetails * first) {// making a vector of the contacts having the same details.
		ContactDetails * temp = searchContact(contentToSearch, first);
		vector<ContactDetails *> sameDetails;
		sameDetails.push_back(temp);
		while(sameDetails[sameDetails.size() - 1] != NULL) {
			temp = searchContact(contentToSearch, (sameDetails[sameDetails.size() - 1])->next);
			sameDetails.push_back(temp);
		}
		return sameDetails;
}

int ContactDetails::selectionForSameDetails(vector<ContactDetails *> sameDetails) {// for selection of contact from multiple contact stored in the vector
	cout << "There are multiple contacts with the same details." << endl;
	cout << "Please specify which one would like to delete/update by specifying the index of that contact from the following contacts" << endl;
	for(int i = 0; i < (sameDetails.size() - 1); i++) {
		cout << i+1 << ". ";
		displayContact(sameDetails[i]);
	}
	int selection = 0;
	cin >> selection;
	return selection;
}

void ContactDetails::deleteThisContact(ContactDetails * temp) {// deletes the contact for which the pointer is given.
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
		cout << "Cannot delete the contact." << endl;
	}
	return;
}

ContactDetails * ContactDetails::searchContact(string contentToSearch, ContactDetails * first) {//search for the contact.
	while(first) {
		if ((first->firstName == contentToSearch) || (first->lastName == contentToSearch) 
	     	|| (first->numbers["Mobile"] == contentToSearch) || (first->numbers["Home"] == contentToSearch)
		|| (first->numbers["Other"] == contentToSearch) || (first->address == contentToSearch)) {
			return first;
		}
		first = first->next;	
	}
	return NULL;
}

ContactDetails * ContactDetails::deleteAllContacts() {//deletes all the contacts.
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

void ContactDetails::updateContact() {//to update a contact
	int choice = 5;
	cout << "What would you like to update?" << endl
	<< "1. First Name." << endl
	<< "2. Last Name." << endl
	<< "3. Number." << endl
	<< "4. Address." << endl;

	cin >> choice;

	if(choice >= 1 && choice <=4) {
		this->update(choice);	
	} else {
		cout << "Please enter a valid choice between 1 and 4." << endl;
	}
}

void ContactDetails::update(int choice) {
	string detailToUpdate = "";
	cout << "Please enter the detail that you would like to update." << endl;
	cin >> detailToUpdate;

	vector<ContactDetails *> sameDetails = arrayOfSameContactDetails(detailToUpdate, this);//get the vector for the contacts having the same detail.
	if (sameDetails.size() == 1) {//in case there is no contact for the given detail.
		cout << "No such contact to update." << endl;
		return;
	} 
	
	int selection = 1;
	if(sameDetails.size() > 2) {//if there are multiple contacts having the same detail, need a selection for it.
		selection = selectionForSameDetails(sameDetails);
	}
	if(selection > sameDetails.size()) {// if the slection is out of bound.
		cout << "Please choose a valid index." << endl;
		return;	
	}
	string updatedDetail = "";
	cout << "Enter the updated detail." << endl;
	cin >> updatedDetail;
	updateDetails(sameDetails[selection - 1], updatedDetail, choice, detailToUpdate);
}

void ContactDetails::updateDetails(ContactDetails * contactToUpdate, string updatedDetail, int choice, string detailToUpdate) {//where actual updation happens given the pointer to the contact.
	if(contactToUpdate) {
		if (choice == 1) contactToUpdate->firstName = updatedDetail;
		else if (choice == 2) contactToUpdate->lastName = updatedDetail;
		else if (choice == 3) {
			if(contactToUpdate->numbers["Mobile"] == detailToUpdate) contactToUpdate->numbers["Mobile"] = updatedDetail;
			else if(contactToUpdate->numbers["Home"] == detailToUpdate) contactToUpdate->numbers["Home"] = updatedDetail;
			else if(contactToUpdate->numbers["Other"] == detailToUpdate) contactToUpdate->numbers["Other"] = updatedDetail;
		}
		else if (choice == 4) contactToUpdate->address = updatedDetail;
		return;
	}
	else {
		cout << "Error finding contact." << endl;
	}
}
