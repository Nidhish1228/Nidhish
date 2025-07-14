#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Contact {
    int id;
    string name, nickname, phone, email,address;

public:
    void input() {
        cout << "Enter ID: "; cin >> id;
        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Nickname: "; getline(cin, nickname);
        cout << "Enter Phone: "; getline(cin, phone);
        cout << "Enter Email: "; getline(cin, email);
        cout<<"Enter Address:"; getline(cin,address);
    }

    void display() const {
        cout << "\nID: " << id
             << "\nName: " << name
             << "\nNickname: " << nickname
             << "\nPhone: " << phone
             << "\nEmail: " << email <<"\nAddress:"<< endl;
    }

    int getID() const { return id; }

    void save(ofstream& out) const {
        out << id << '\n' << name << '\n' << nickname << '\n'
            << phone << '\n' << email << '\n';
    }

    bool load(ifstream& in) {
        if (!(in >> id)) return false;
        in.ignore();
        getline(in, name);
        getline(in, nickname);
        getline(in, phone);
        getline(in, email);
        getline(in,address);
        return true;
    }
};

void addContact() {
    ofstream out("contacts.txt", ios::app);
    Contact c;
    c.input();
    c.save(out);
    out.close();
    cout << "Contact saved.\n";
}

void showContacts() {
    ifstream in("contacts.txt");
    Contact c;
    while (c.load(in)) {
        c.display();
    }
    in.close();
}

void searchContact(int targetID) {
    ifstream in("contacts.txt");
    Contact c;
    bool found = false;
    while (c.load(in)) {
        if (c.getID() == targetID) {
            c.display();
            found = true;
            break;
        }
    }
    in.close();
    if (!found) cout << "Contact not found.\n";
}

void deleteContact(int targetID) {
    ifstream in("contacts.txt");
    ofstream out("temp.txt");
    Contact c;
    bool deleted = false;

    while (c.load(in)) {
        if (c.getID() != targetID) {
            c.save(out);
        } else {
            deleted = true;
        }
    }

    in.close();
    out.close();
    remove("contacts.txt");
    rename("temp.txt", "contacts.txt");

    if (deleted) cout << "Contact deleted.\n";
    else cout << "Contact not found.\n";
}

int main() {
    int choice, id;
    do {
        cout << "\n--- Phone Dictionary Menu ---\n";
        cout << "1. Add Contact\n2. Show All Contacts\n3. Search Contact\n4. Delete Contact\n5. Address\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addContact(); break;
            case 2: showContacts(); break;
            case 3:
                cout << "Enter ID to search: ";
                cin >> id;
                searchContact(id);
                break;
            case 4:
                cout << "Enter ID to delete: ";
                cin >> id;
                deleteContact(id);
                break;
            case 5:
               cout << "Enter ID to view address: ";
               cin >> id;
               searchContact(id); 
               break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 0);

    return 0;
}