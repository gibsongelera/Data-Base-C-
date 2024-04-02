#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Student {
    string name;
    string id;
    float gpa;
};

struct Node {
    Student data;
    Node* next;
    Node* prev;
};

class StudentDatabase {
private:
    Node* first;
    Node* last;
    int count;

public:
    StudentDatabase() : first(nullptr), last(nullptr), count(0) {}

    void createDatabase(const Student& student) {
        if (first == nullptr) {
            Node* newNode = new Node{student, nullptr, nullptr};
            first = newNode;
            last = newNode;
            count++;
        } else {
            cout << "You have already created the database.\n";
        }
    }

    void insertElement(const Student& student) {
    Node* newNode = new Node{student, nullptr, nullptr};

    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else if (student.id <= first->data.id) {
        newNode->next = first;
        first->prev = newNode;
        first = newNode;
    } else if (student.id >= last->data.id) {
        last->next = newNode;
        newNode->prev = last;
        last = newNode;
    } else {
        Node* current = first->next;
        while (current != nullptr && current->data.id < student.id) {
            current = current->next;
        }
        newNode->next = current;
        newNode->prev = current->prev;
        current->prev->next = newNode;
        current->prev = newNode;
    }
    count++;
}


   void deleteElement(const string& id) {
    Node* current = first;
    while (current != nullptr && current->data.id != id) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Student with ID " << id << " not found.\n";
        return;
    }

    if (current == first) {
        first = current->next;
    } else {
        current->prev->next = current->next;
    }

    if (current == last) {
        last = current->prev;
    } else {
        current->next->prev = current->prev;
    }

    delete current;
    count--;
}


    void searchElement(const string& id) {
    Node* current = first;
    while (current != nullptr && current->data.id != id) {
        current = current->next;
    }

    if (current == nullptr) {
        cout << "Student with ID " << id << " not found.\n";
    } else {
        cout << "Student found:\n";
        cout << "Name: " << current->data.name << endl;
        cout << "ID: " << current->data.id << endl;
        cout << "GPA: " << current->data.gpa << endl;
    }
}


int main() {
    StudentDatabase database;

    while (true) {
        cout << "\n======== Menu ========\n";
        cout << "1. Create Database\n";
        cout << "2. Insert Data\n";
        cout << "3. Delete Data\n";
        cout << "4. Search Data\n";
        cout << "5. Print Data\n";
        cout << "6. Save to File\n";
        cout << "7. Help\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "Enter student name: ";
                string name;
                cin >> name;

                cout << "Enter student ID: ";
                string id;
                cin >> id;

                cout << "Enter student GPA: ";
                float gpa;
                cin >> gpa;

                Student student{name, id, gpa};
                database.createDatabase(student);
                break;
            }
            case 2: {
                cout << "Enter student name: ";
                string name;
                cin >> name;

                cout << "Enter student ID: ";
                string id;
                cin >> id;

                cout << "Enter student GPA: ";
                float gpa;
                cin >> gpa;

                Student student{name, id, gpa};
                database.insertElement(student);
                break;
            }
            case 3: {
                cout << "Enter student ID to delete: ";
                string id;
                cin >> id;
                database.deleteElement(id);
                break;
            }
            case 4: {
                cout << "Enter student ID to search: ";
                string id;
                cin >> id;
                database.searchElement(id);
                break;
            }
            case 5:
                database.print();
                break;
            case 6: {
                cout << "Enter filename to save: ";
                string filename;
                cin >> filename;
                if (database.saveToFile(filename)) {
                    cout << "Data saved to " << filename << " successfully.\n";
                } else {
                    cout << "Failed to save data to " << filename << ".\n";
                }
                break;
            }
            case 7:
                database.help();
                break;
            case 8:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

