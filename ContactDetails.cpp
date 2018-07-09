#include "ContactDetails.h"
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

using namespace std;

ContactDetails * ContactDetails::addContact(ContactDetails * first) {
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
	if(choice == "Y") {
		vector<ContactDetails *> sameDetails = arrayOfSameContactDetails(contentToDel, this);
		if(sameDetails.size() == 1) { //in case there is no contact having this detail as having just 1 element means its a NULL pointer in case.
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

vector<ContactDetails *> ContactDetails::arrayOfSameContactDetails(string contentToSearch, ContactDetails * first) {
		ContactDetails * temp = searchContact(contentToSearch, first);
		vector<ContactDetails *> sameDetails;
		sameDetails.push_back(temp);
		while(sameDetails[sameDetails.size() - 1] != NULL) {
			temp = searchContact(contentToSearch, (sameDetails[sameDetails.size() - 1])->next);
			sameDetails.push_back(temp);
		}
		return sameDetails;
}

int ContactDetails::selectionForSameDetails(vector<ContactDetails *> sameDetails) {
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
		cout << "Cannot delete the contact." << endl;
	}
	return;
}

ContactDetails * ContactDetails::searchContact(string contentToSearch, ContactDetails * first) {
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

	vector<ContactDetails *> sameDetails = arrayOfSameContactDetails(detailToUpdate, this);
	if (sameDetails.size() == 1) {
		cout << "No such contact to update." << endl;
		return;
	} 
	
	int selection = 1;
	if(sameDetails.size() > 2) {
		selection = selectionForSameDetails(sameDetails);
	}
	if(selection > sameDetails.size()) {
		cout << "Please choose a valid index." << endl;
		return;	
	}
	string updatedDetail = "";
	cout << "Enter the updated detail." << endl;
	cin >> updatedDetail;
	updateDetails(sameDetails[selection - 1], updatedDetail, choice, detailToUpdate);
}

void ContactDetails::updateDetails(ContactDetails * contactToUpdate, string updatedDetail, int choice, string detailToUpdate) {
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

/*void ContactDetails::updateFirstName() {
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
		if(temp->numbers["Mobile"] == number) temp->numbers["Mobile"] = updatedNumber;
		if(temp->numbers["Home"] == number) temp->numbers["Home"] = updatedNumber; 
		if(temp->numbers["Other"] == number) temp->numbers["Other"] = updatedNumber;	
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
}*/	
