#ifndef CONTACTDETAILS_H_
#define CONTACTDETAILS_H_

#include <string>
#include <cstddef>
#include <unordered_map>
#include <vector>

using namespace std;

class ContactDetails {
private:
	/*char * lastName;
	char * firstName;
	char * number;
	char * address;*/
	string lastName;// can arrange in ascending order.
	string firstName;//Can make a class of Telephone directory and create 
	unordered_map<string, string> numbers;
	string address;//think of converting this to char *
	ContactDetails * next;
	ContactDetails * prev;
public:
	ContactDetails() {
		this->lastName = "";
		this->firstName = "";//what to do in case of multiple first names or last names
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
	//void updateFirstName(); // all the updates can be done in one function.
	//void updateLastName();
	//void updateNumber();
	//void updateAddress();
	void displayContact(ContactDetails *);
	vector<ContactDetails *> arrayOfSameContactDetails(string, ContactDetails * temp);
	int selectionForSameDetails(vector<ContactDetails *> );
	void update(int);
	void updateDetails(ContactDetails *, string, int, string);

};

#endif
