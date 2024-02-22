// #include <bits/stdc++.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iomanip>

#define push_back pb

using namespace std;

// basic contact structure
struct Contact {
    string name;
    string phone;
    string email;
};

/*
    Contact {
        name : Priyanshu
        phone : 123456789
        email : xyz@email.com
    }
*/

class ContactBook {
private:
    vector<Contact> contacts;
    string filename;

public:
    ContactBook(string& filename) : filename(filename) {}

    void addContact(string& name, string& phone, string& email) {
        contacts.pb({name, phone, email});
    }

    void displayContacts() {
        if (contacts.empty()) {
            cout << "Contact list is empty." << endl;
            return;
        }
        cout << "Contacts:" << endl;
        for (auto& contact : contacts) {
            cout << "Name: " << setw(20) << left << contact.name
                 << "Phone: " << setw(15) << left << contact.phone
                 << "Email: " << contact.email << endl;
        }
    }

    void searchContact(string& query) {
        cout << "Search Results:" << endl;
        bool found = false;
        for (auto& contact : contacts) {
            if (contact.name.find(query) != string::npos || contact.phone.find(query) != string::npos ||
                contact.email.find(query) != string::npos) {
                cout << "Name: " << setw(20) << left << contact.name
                     << "Phone: " << setw(15) << left << contact.phone
                     << "Email: " << contact.email << endl;
                found = true;
            }
        }
        if (!found) {
            cout << "No contacts found matching the query." << endl;
        }
    }

    void deleteContact(string& name) {
        auto it = std::remove_if(contacts.begin(), contacts.end(), [&name](Contact& contact) {
            return contact.name == name;
        });
        contacts.erase(it, contacts.end());
        cout << "Contact '" << name << "' deleted successfully." << endl;
    }

    void sortContactsByName() {
        sort(contacts.begin(), contacts.end(), [](Contact& a, Contact& b) {
            return a.name < b.name;
        });
        cout << "Contacts sorted by name." << endl;
    }

    void sortContactsByPhone() {
        sort(contacts.begin(), contacts.end(), [](Contact& a, Contact& b) {
            return a.phone < b.phone;
        });
        cout << "Contacts sorted by phone number." << endl;
    }

    void saveContactsToFile() {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (auto& contact : contacts) {
                outFile << contact.name << "," << contact.phone << "," << contact.email << endl;
            }
            outFile.close();
            cout << "Contacts saved to " << filename << endl;
        } else {
            cout << "Unable to open file " << filename << " for writing." << endl;
        }
    }

    void loadContactsFromFile() {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            contacts.clear(); // Clear existing contacts
            string line;
            while (getline(inFile, line)) {
                size_t pos1 = line.find(',');
                size_t pos2 = line.find(',', pos1 + 1);
                if (pos1 != string::npos && pos2 != string::npos) {
                    string name = line.substr(0, pos1);
                    string phone = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    string email = line.substr(pos2 + 1);
                    contacts.pb({name, phone, email});
                }
            }
            inFile.close();
            cout << "Contacts fetched from " << filename << endl;
        } else {
            cout << "Unable to open file " << filename << " for reading." << endl;
        }
    }
};

int main() {
    ContactBook contactBook("contacts.txt");

    // fetch contact from contacts.txt
    contactBook.loadContactsFromFile();

    int choice;
    do {
        cout << "\nContact Book Menu:\n"
             << "1. Add Contact\n"
             << "2. Display Contacts\n"
             << "3. Search Contact\n"
             << "4. Delete Contact\n"
             << "5. Sort Contacts by Name\n"
             << "6. Sort Contacts by Phone Number\n"
             << "7. Save Contacts to File\n"
             << "8. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name, phone, email;
                cout << "Enter name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter phone: ";
                getline(cin, phone);
                cout << "Enter email: ";
                getline(cin, email);
                contactBook.addContact(name, phone, email);
                break;
            }
            case 2:
                contactBook.displayContacts();
                break;
            case 3: {
                string query;
                cout << "Enter search query: ";
                cin.ignore();
                getline(cin, query);
                contactBook.searchContact(query);
                break;
            }
            case 4: {
                string name;
                cout << "Enter the name of the contact to delete: ";
                cin.ignore();
                getline(cin, name);
                contactBook.deleteContact(name);
                break;
            }
            case 5:
                contactBook.sortContactsByName();
                break;
            case 6:
                contactBook.sortContactsByPhone();
                break;
            case 7:
                contactBook.saveContactsToFile();
                break;
            case 8:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 8." << endl;
        }
    } while (choice != 8);

    return 0;
}
