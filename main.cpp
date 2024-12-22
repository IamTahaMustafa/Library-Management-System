#include <iostream>
#include <string>
using namespace std;

// Constants for maximum numbers of books and members
const int MAX_BOOKS = 100;
const int MAX_MEMBERS = 100;

// Author Class (Composition)
class Author {
private:
    string name;
    string email;

public:
    Author(string name = "Unknown", string email = "N/A") : name(name), email(email) {}

    void displayAuthor() const {
        cout << "Author Name: " << name << ", Email: " << email << endl;
    }
};

// Book Class
class Book {
private:
    string title;
    string ISBN;
    bool available;
    Author author;

public:
    Book(string title = "Unknown", string ISBN = "0000", Author author = Author())
        : title(title), ISBN(ISBN), available(true), author(author) {}

    void displayBook() const {
        cout << "Title: " << title << ", ISBN: " << ISBN
             << ", Available: " << (available ? "Yes" : "No") << endl;
        author.displayAuthor();
    }

    bool isAvailable() const { return available; }
    void issueBook() { available = false; }
    void returnBook() { available = true; }
};

// Member Class (Polymorphic Base Class)
class Member {
protected:
    string name;
    int memberID;

public:
    Member(string name = "Unknown", int memberID = 0) : name(name), memberID(memberID) {}
    virtual ~Member() {} // Virtual destructor to make the class polymorphic

    virtual void displayMember() const {
        cout << "Member Name: " << name << ", ID: " << memberID << endl;
    }
};

// StaffMember Class (Derived from Member)
class StaffMember : public Member {
private:
    string position;

public:
    StaffMember(string name = "Unknown", int memberID = 0, string position = "N/A")
        : Member(name, memberID), position(position) {}

    void displayMember() const override {
        cout << "Staff Name: " << name << ", ID: " << memberID << ", Position: " << position << endl;
    }
};

// Global arrays to store books and members
Book books[MAX_BOOKS];
Member* members[MAX_MEMBERS];
int bookCount = 0;
int memberCount = 0;

// Main Function
int main() {
    int choice;

    do {
        cout << endl;
        cout << "===============================" << endl;
        cout << " Library Management System Menu " << endl;
        cout << "===============================" << endl;
        cout << "1. Add a Book" << endl;
        cout << "2. Display Book Details" << endl;
        cout << "3. Issue a Book" << endl;
        cout << "4. Return a Book" << endl;
        cout << "5. Add a Member" << endl;
        cout << "6. Display Member Details" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << endl << "------ Add a Book ------" << endl;
                if (bookCount >= MAX_BOOKS) {
                    cout << "Error: Cannot add more books. Maximum limit reached." << endl;
                    break;
                }

                string title, ISBN, authorName, authorEmail;
                cout << "Enter book title: ";
                cin.ignore();
                getline(cin, title);
                cout << "Enter book ISBN: ";
                getline(cin, ISBN);
                cout << "Enter author's name: ";
                getline(cin, authorName);
                cout << "Enter author's email: ";
                getline(cin, authorEmail);

                books[bookCount] = Book(title, ISBN, Author(authorName, authorEmail));
                bookCount++;
                cout << "Book added successfully." << endl;
                break;
            }
            case 2: {
                cout << endl << "------ Display Book Details ------" << endl;
                if (bookCount == 0) {
                    cout << "No books available." << endl;
                    break;
                }

                for (int i = 0; i < bookCount; ++i) {
                    cout << "Book " << (i + 1) << ":" << endl;
                    books[i].displayBook();
                    cout << endl;
                }
                break;
            }
            case 3: {
                cout << endl << "------ Issue a Book ------" << endl;
                int bookIndex;
                cout << "Enter book number to issue (1-" << bookCount << "): ";
                cin >> bookIndex;

                if (bookIndex < 1 || bookIndex > bookCount) {
                    cout << "Invalid book number." << endl;
                } else if (!books[bookIndex - 1].isAvailable()) {
                    cout << "Book is already issued." << endl;
                } else {
                    books[bookIndex - 1].issueBook();
                    cout << "Book issued successfully." << endl;
                }
                break;
            }
            case 4: {
                cout << endl << "------ Return a Book ------" << endl;
                int bookIndex;
                cout << "Enter book number to return (1-" << bookCount << "): ";
                cin >> bookIndex;

                if (bookIndex < 1 || bookIndex > bookCount) {
                    cout << "Invalid book number." << endl;
                } else {
                    books[bookIndex - 1].returnBook();
                    cout << "Book returned successfully." << endl;
                }
                break;
            }
            case 5: {
                cout << endl << "------ Add a Member ------" << endl;
                if (memberCount >= MAX_MEMBERS) {
                    cout << "Error: Cannot add more members. Maximum limit reached." << endl;
                    break;
                }

                string name;
                int memberID, isStaff;
                cout << "Enter member name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter member ID: ";
                cin >> memberID;
                cout << "Is this member a staff? (1 for Yes, 0 for No): ";
                cin >> isStaff;

                if (isStaff) {
                    string position;
                    cout << "Enter staff position: ";
                    cin.ignore();
                    getline(cin, position);
                    members[memberCount] = new StaffMember(name, memberID, position);
                } else {
                    members[memberCount] = new Member(name, memberID);
                }

                memberCount++;
                cout << "Member added successfully." << endl;
                break;
            }
            case 6: {
                cout << endl << "------ Display Member Details ------" << endl;

                if (memberCount == 0) {
                    cout << "No members available." << endl;
                    break;
                }

                cout << "Staff Members:" << endl;
                bool staffExists = false;
                for (int i = 0; i < memberCount; ++i) {
                    StaffMember* staff = dynamic_cast<StaffMember*>(members[i]);
                    if (staff) {
                        staff->displayMember();
                        staffExists = true;
                    }
                }
                if (!staffExists) {
                    cout << "No staff members available." << endl;
                }

                cout << "\nGeneral Members:" << endl;
                bool generalExists = false;
                for (int i = 0; i < memberCount; ++i) {
                    StaffMember* staff = dynamic_cast<StaffMember*>(members[i]);
                    if (!staff) {
                        members[i]->displayMember();
                        generalExists = true;
                    }
                }
                if (!generalExists) {
                    cout << "No general members available." << endl;
                }
                break;
            }
            case 7: {
                cout << "Exiting program. Goodbye!" << endl;
                break;
            }
            default: {
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    } while (choice != 7);

    // Cleanup dynamically allocated memory
    for (int i = 0; i < memberCount; ++i) {
        delete members[i];
    }

    return 0;
}
