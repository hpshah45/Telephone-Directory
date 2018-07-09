#ifndef CONTACTDETAILS_H_
#define CONTACTDETAILS_H_

#include <string>
#include <cstddef>
#include <unordered_map>
#include <vector>

using namespace std;

class ContactDetails {
private:
	string lastName;
	string firstName;
	unordered_map<string, string> numbers;
	string address;
	ContactDetails * next;
	ContactDetails * prev;
public:
	ContactDetails() {
		this->lastName = "";
		this->firstName = "";
		this->address = "";
		this->numbers = {{"Mobile", ""}, {"Home", ""}, {"Other", ""}};
		this->next = NULL;
		this->prev = NULL;
	}
	
	ContactDetails * addContact(ContactDetails * first);
	ContactDetails * deleteContact();
	void deleteThisContact(ContactDetails *);
	ContactDetails * searchContact(string , ContactDetails *);
	void listAllContacts();
	ContactDetails * deleteAllContacts();
	void updateContact();
	void displayContact(ContactDetails *);
	vector<ContactDetails *> arrayOfSameContactDetails(string, ContactDetails * temp);
	int selectionForSameDetails(vector<ContactDetails *> );
	void update(int);
	void updateDetails(ContactDetails *, string, int, string);
};

#endif
