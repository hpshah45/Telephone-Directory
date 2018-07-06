#ifndef CONTACTDETAILS_H_
#define CONTACTDETAILS_H_

#include <string>
#include <cstddef>
//#include<unordered_map>

using namespace std;

class ContactDetails {
private:
	/*char * lastName;
	char * firstName;
	char * number;
	char * address;*/
	string lastName;// can arrange in ascending order.
	string firstName;//Can make a class of Telephone directory and create 
	string number;//think of a way to add more than 1 numbers
	string address;//think of converting this to char *
	ContactDetails * next;//could add a previous as well.
	ContactDetails * prev;
public:
	ContactDetails() {
		this->lastName = "";
		this->firstName = "";//what to do in case of multiple first names or last names
		this->address = "";
		this->number = "";
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
	void updateFirstName(); // all the updates can be done in one function.
	void updateLastName();
	void updateNumber();
	void updateAddress();
	
};

#endif
