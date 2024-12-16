// COMP 51 Nov 26, 2021
// PA06
// Programmer <Cindy Ung>

#include <string.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int SIZE = 100;

class ContactList {
  struct Contact {
    string name;
    string email;
    string number;
  };

  Contact contacts[SIZE];
  int num_contacts = 0;

 public:
  void ReadContacts();
  void WriteContacts();
  void AddContact();
  void DeleteContact();
  void ModifyContact();
  int FindContact();
  void DisplayContacts();

  void Add(Contact contact);
  void Delete(int i);

  ContactList() {} 
};

void ContactList::ReadContacts() {
  ifstream input_file("contacts.txt");

  if (input_file.is_open()) {
    while (!input_file.eof()) {
      getline(input_file, contacts[num_contacts].name, ',');
      getline(input_file, contacts[num_contacts].email, ',');
      getline(input_file, contacts[num_contacts].number, ',');
      num_contacts++;
    }
    num_contacts--;
    input_file.close();
  } else {
    cout << "Error opening file";
  }
};

void ContactList::WriteContacts() {
  ofstream output_file("contacts.txt",
                       std::ofstream::trunc);
  if (output_file.is_open()) {
    for (int i = 0; i < num_contacts; i++) {
      output_file << contacts[i].name << ",";
      output_file << contacts[i].email << ",";
      output_file << contacts[i].number << ",";
    }
    output_file.close();
  } else {
    cout << "Error opening file";
  }
};

void ContactList::Add(Contact contact) {
  int i = 0;
  while ((contacts[i].name.compare(contact.name) < 0) && (i < num_contacts)) {
    i++;
  }
  for (int j = num_contacts - 1; j >= i; j--) {
    contacts[j + 1] = contacts[j];
  }
  contacts[i] = contact;
  num_contacts++;
}

void ContactList::AddContact() {
  Contact new_contact;
  cin.ignore();
  cout << "    Insert contact name: ";
  getline(cin, new_contact.name);
  cout << "    Insert contact email: ";
  getline(cin, new_contact.email);
  cout << "    Insert contact number: ";
  getline(cin, new_contact.number);
  Add(new_contact);
  cout << endl;
  cout << "    Contact added" << endl;
  cout << endl;
}

void ContactList::Delete(int i) {
  for (int j = i; j < num_contacts; ++j) {
    contacts[j] = contacts[j + 1];
  }
  num_contacts -= 1;
  return;
}

void ContactList::DeleteContact() {
  int i = FindContact();
  Delete(i);
  cout << "    Contact deleted" << endl;
  cout << endl;
}

void ContactList::ModifyContact() {
  int i;
  do {
    i = FindContact();
  } while (i == -1);
  int choice;
  do {
    cout << "    0. Modify Name" << endl;
    cout << "    1. Modify Email" << endl;
    cout << "    2. Modify Phone Number" << endl;
    cout << "    Choice: ";
    cin >> choice;
    cout << endl;
  } while ((choice != 0) && (choice != 1) && (choice != 2));

  cin.ignore();
  string input;
  Contact modified_contact = contacts[i];
  if (choice == 0) {
    cout << "    Enter New Name: ";
    getline(cin, modified_contact.name);
  } else if (choice == 1) {
    cout << "    Enter New Email: ";
    getline(cin, modified_contact.email);
  } else if (choice == 2) {
    cout << "    Enter New Phone Number: ";
    getline(cin, modified_contact.number);
  }
  Delete(i);
  Add(modified_contact);
  cout << "    Modified contact:" << endl;
  cout << "    Name: " << modified_contact.name << endl;
  cout << "    Email: " << modified_contact.email << endl;
  cout << "    Number: " << modified_contact.number << endl;
  cout << endl;
}

int ContactList::FindContact() {
  int choice;
  do {
    cout << "    0. Search By Name" << endl;
    cout << "    1. Search by Email" << endl;
    cout << "    2. Search by Phone Number" << endl;
    cout << "    Choice: ";
    cin >> choice;
    cout << endl;
  } while ((choice != 0) && (choice != 1) && (choice != 2));

  cin.ignore();
  string input;
  if (choice == 0) {
    cout << "    Enter Name: ";
  } else if (choice == 1) {
    cout << "    Enter Email: ";
  } else if (choice == 2) {
    cout << "    Enter Phone Number: ";
  }
  getline(cin, input);
  for (int i = 0; i < num_contacts; i++) {
    if (((choice == 0) && contacts[i].name.compare(input) == 0) ||
        ((choice == 1) && contacts[i].email.compare(input) == 0) ||
        ((choice == 2) && contacts[i].number.compare(input) == 0)) {
      cout << "    Contact found" << endl;
      cout << "    Name: " << contacts[i].name << endl;
      cout << "    Email: " << contacts[i].email << endl;
      cout << "    Number: " << contacts[i].number << endl;
      cout << endl;
      return i;
    }
  }
  cout << "    Found no contact" << endl;
  return -1;
}

void ContactList::DisplayContacts() {
  for (int i = 0; i < num_contacts; i++) {
    cout << "    Name: " << contacts[i].name << endl;
    cout << "    Email: " << contacts[i].email << endl;
    cout << "    Number: " << contacts[i].number << endl;
    cout << endl;
  }
}

ContactList my_contacts;

int main() {
  my_contacts.ReadContacts();

  int choice;
  do {
    cout << "0. Quit" << endl
         << "1. Add Contact" << endl
         << "2. Delete Contact" << endl
         << "3. Modify Contact" << endl
         << "4. Find Contact" << endl
         << "5. Display All Contacts" << endl
         << "Choice: ";
    cin >> choice;
    cout << endl;

    if (choice == 0) {
      my_contacts.WriteContacts();
    } else if (choice == 1) {
      my_contacts.AddContact();
    } else if (choice == 2) {
      my_contacts.DeleteContact();
    } else if (choice == 3) {
      my_contacts.ModifyContact();
    } else if (choice == 4) {
      my_contacts.FindContact();
    } else if (choice == 5) {
      my_contacts.DisplayContacts();
    } else {
      cout << "Invalid choice" << endl;
    }

  } while (choice != 0);

  return 0;
}