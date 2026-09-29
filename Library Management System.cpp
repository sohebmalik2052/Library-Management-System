#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Book
{
    int id;
    string title;
    string author;
    bool issued;
};

// Add a new book
void addBook()
{
    Book b;

    cout << "\nEnter Book ID: ";
    cin >> b.id;
    cin.ignore();

    cout << "Enter Book Title: ";
    getline(cin, b.title);

    cout << "Enter Author Name: ";
    getline(cin, b.author);

    b.issued = false;

    ofstream file("books.txt", ios::app);

    if (!file)
    {
        cout << "\nError opening file!\n";
        return;
    }

    file << b.id << "|"
         << b.title << "|"
         << b.author << "|"
         << b.issued << "\n";

    file.close();

    cout << "\nBook added successfully!\n";
}

// Display all books
void displayBooks()
{
    ifstream file("books.txt");

    if (!file)
    {
        cout << "\nNo books found.\n";
        return;
    }

    string line;
    bool found = false;

    cout << "\n========== LIBRARY BOOKS ==========\n";

    while (getline(file, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        if (p1 == string::npos ||
            p2 == string::npos ||
            p3 == string::npos)
        {
            continue;
        }

        Book b;

        b.id = stoi(line.substr(0, p1));
        b.title = line.substr(p1 + 1, p2 - p1 - 1);
        b.author = line.substr(p2 + 1, p3 - p2 - 1);
        b.issued = stoi(line.substr(p3 + 1));

        cout << "\nBook ID    : " << b.id;
        cout << "\nTitle      : " << b.title;
        cout << "\nAuthor     : " << b.author;
        cout << "\nStatus     : "
             << (b.issued ? "Issued" : "Available");

        cout << "\n-----------------------------------\n";

        found = true;
    }

    file.close();

    if (!found)
        cout << "No books found.\n";
}

// Search for a book
void searchBook()
{
    int searchId;

    cout << "\nEnter Book ID to search: ";
    cin >> searchId;

    ifstream file("books.txt");

    if (!file)
    {
        cout << "\nNo books found.\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');

        if (p1 == string::npos)
            continue;

        int id = stoi(line.substr(0, p1));

        if (id == searchId)
        {
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            string title =
                line.substr(p1 + 1, p2 - p1 - 1);

            string author =
                line.substr(p2 + 1, p3 - p2 - 1);

            bool issued =
                stoi(line.substr(p3 + 1));

            cout << "\nBook Found!";
            cout << "\nBook ID : " << id;
            cout << "\nTitle   : " << title;
            cout << "\nAuthor  : " << author;
            cout << "\nStatus  : "
                 << (issued ? "Issued" : "Available");
            cout << "\n";

            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nBook ID not found.\n";
}

// Issue a book
void issueBook()
{
    int searchId;

    cout << "\nEnter Book ID to issue: ";
    cin >> searchId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    if (!file || !temp)
    {
        cout << "\nError opening file!\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');

        if (p1 == string::npos)
            continue;

        int id = stoi(line.substr(0, p1));

        if (id == searchId)
        {
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            string title =
                line.substr(p1 + 1, p2 - p1 - 1);

            string author =
                line.substr(p2 + 1, p3 - p2 - 1);

            bool issued =
                stoi(line.substr(p3 + 1));

            found = true;

            if (issued)
            {
                cout << "\nBook is already issued!\n";
                temp << line << "\n";
            }
            else
            {
                temp << id << "|"
                     << title << "|"
                     << author << "|1\n";

                cout << "\nBook issued successfully!\n";
            }
        }
        else
        {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "\nBook ID not found.\n";
}

// Return a book
void returnBook()
{
    int searchId;

    cout << "\nEnter Book ID to return: ";
    cin >> searchId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    if (!file || !temp)
    {
        cout << "\nError opening file!\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');

        if (p1 == string::npos)
            continue;

        int id = stoi(line.substr(0, p1));

        if (id == searchId)
        {
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            string title =
                line.substr(p1 + 1, p2 - p1 - 1);

            string author =
                line.substr(p2 + 1, p3 - p2 - 1);

            bool issued =
                stoi(line.substr(p3 + 1));

            found = true;

            if (!issued)
            {
                cout << "\nBook is already available!\n";
                temp << line << "\n";
            }
            else
            {
                temp << id << "|"
                     << title << "|"
                     << author << "|0\n";

                cout << "\nBook returned successfully!\n";
            }
        }
        else
        {
            temp << line << "\n";
        }
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (!found)
        cout << "\nBook ID not found.\n";
}

// Delete a book
void deleteBook()
{
    int searchId;

    cout << "\nEnter Book ID to delete: ";
    cin >> searchId;

    ifstream file("books.txt");
    ofstream temp("temp.txt");

    if (!file || !temp)
    {
        cout << "\nError opening file!\n";
        return;
    }

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');

        if (p1 == string::npos)
            continue;

        int id = stoi(line.substr(0, p1));

        if (id == searchId)
        {
            found = true;
            continue;
        }

        temp << line << "\n";
    }

    file.close();
    temp.close();

    remove("books.txt");
    rename("temp.txt", "books.txt");

    if (found)
        cout << "\nBook deleted successfully!\n";
    else
        cout << "\nBook ID not found.\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n========================================\n";
        cout << "         LIBRARY MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Add Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book\n";
        cout << "4. Issue Book\n";
        cout << "5. Return Book\n";
        cout << "6. Delete Book\n";
        cout << "7. Exit\n";
        cout << "========================================\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                addBook();
                break;

            case 2:
                displayBooks();
                break;

            case 3:
                searchBook();
                break;

            case 4:
                issueBook();
                break;

            case 5:
                returnBook();
                break;

            case 6:
                deleteBook();
                break;

            case 7:
                cout << "\nThank you for using Library Management System!\n";
                break;

            default:
                cout << "\nInvalid choice! Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}
