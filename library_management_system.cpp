#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Book {
    int id;
    string title;
    string author;
    bool isIssued;

    Book(int bookId, string bookTitle, string bookAuthor) : id(bookId), title(bookTitle), author(bookAuthor), isIssued(false) {}
};
class Library {
private:
    vector<Book> books;

    int findBookIndexById(int id) {
        for (size_t i = 0; i < books.size(); i++) {
            if (books[i].id == id) {
                return i;
            }
        }
        return -1;
    }

public:
    void addBook(int id, string title, string author) {
        books.push_back(Book(id, title, author));
    }

    void searchBookById(int id) {
        int index = findBookIndexById(id);
        if (index != -1) {
            displayBookDetails(books[index]);
        } else {
            cout << "Book not found." << endl;
        }
    }

    void searchBookByTitle(string title) {
        for (const auto& book : books) {
            if (book.title == title) {
                displayBookDetails(book);
                return;
            }
        }
        cout << "Book not found." << endl;
    }

    void issueBook(int id, string student) {
        int index = findBookIndexById(id);
        if (index != -1 && !books[index].isIssued) {
            books[index].isIssued = true;
            cout << "Book issued to " << student << "." << endl;
        } else {
            cout << "Book is either not found or already issued." << endl;
        }
    }

    void returnBook(int id) {
        int index = findBookIndexById(id);
        if (index != -1 && books[index].isIssued) {
            books[index].isIssued = false;
            cout << "Book returned." << endl;
        } else {
            cout << "Book is either not found or wasn't issued." << endl;
        }
    }

    void listAllBooks() {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.title < b.title;
        });
        for (const auto& book : books) {
            displayBookDetails(book);
        }
    }

    void deleteBook(int id) {
        int index = findBookIndexById(id);
        if (index != -1) {
            books.erase(books.begin() + index);
            cout << "Book deleted." << endl;
        } else {
            cout << "Book not found." << endl;
        }
    }

    void displayBookDetails(const Book& book) {
        cout << "ID: " << book.id << ", Title: " << book.title
             << ", Author: " << book.author
             << ", Status: " << (book.isIssued ? "Issued" : "Available") << endl;
    }
};
int main() {
    Library lib;
    int choice, id;
    string title, author, student;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Search Book by ID\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. List All Books\n";
        cout << "7. Delete Book\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                lib.addBook(id, title, author);
                break;
            case 2:
                cout << "Enter book ID: ";
                cin >> id;
                lib.searchBookById(id);
                break;
            case 3:
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                lib.searchBookByTitle(title);
                break;
            case 4:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, student);
                lib.issueBook(id, student);
                break;
            case 5:
                cout << "Enter book ID: ";
                cin >> id;
                lib.returnBook(id);
                break;
            case 6:
                lib.listAllBooks();
                break;
            case 7:
                cout << "Enter book ID: ";
                cin >> id;
                lib.deleteBook(id);
                break;
            case 8:
                cout << "Exiting system." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
