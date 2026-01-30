#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class contactManager {
    private:
        static constexpr int name_width = 15;
        static constexpr int email_width = 30;
        static constexpr int role_width = 15;
        static constexpr int phone_number_width = 15;
        static constexpr int notes_width = 40;
        static constexpr char separator = ' ';
    public:
        static vector<contactManager*> persons;
        long long int phoneNumber;
        string name, email, role, notes;

        // constructor
        contactManager (long long int phoneNumber, string name, string email, string role, string notes = "") {
            this->phoneNumber = phoneNumber;
            this->name = name;
            this->email = email;
            this->role = role;
            this->notes = notes;
            cout << "Contact has been added sucessfully" << endl;
            persons.push_back(this);
        }

        static void printAll() {
            cout << endl;
            cout << left << setw(name_width) << setfill(separator) << "Name"
                << left << setw(email_width) << setfill(separator) << "Email"
                << left << setw(role_width) << setfill(separator) << "Role"
                << left << setw(phone_number_width) << setfill(separator) << "Phone Number"
                << right << setw(notes_width) << setfill(separator) << "Notes" 
            << endl;

            cout << string(name_width + email_width + role_width + phone_number_width + notes_width, '-') << endl;
            
            for (const auto& person : persons) {
                cout << left << setw(name_width) << setfill(separator) << person->name;
                cout << left << setw(email_width) << setfill(separator) << person->email;
                cout << left << setw(role_width) << setfill(separator) << person->role;
                cout << left << setw(phone_number_width) << setfill(separator) << person->phoneNumber;
                if (!person->notes.empty()) {
                    cout << right << setw(notes_width) << setfill(separator) << person->notes;
                } else {
                    cout << right << setw(notes_width) << setfill(separator) << "No additional notes have been added";
                }
                cout << endl;

            }
        }

        void addNote(string notes) {
            if (this->notes.empty()) {
                this->notes = notes;
            } else {
                cout << "This person already has a note, try .updateNotes() instead" << endl;
            }
        }

        void updateName(string newName) {
            this->name = newName;
            cout << "Name has been sucessfully updated!" << endl;
        }

        void updateEmail(string newEmail) {
            this->email = newEmail;
            cout << "Email has been sucessfully updated!" << endl;
        }

        void updateRole(string newRole) {
            this->role = newRole;
            cout << "Person's role has been sucessfully updated!" << endl;
        }

        void updatePhoneNumber(long long int newPhoneNumber) {
            this->phoneNumber = newPhoneNumber;
            cout << "Phone number has been sucessfully updated!" << endl;
        }

        void updateNotes(string newNotes) {
            this->notes = newNotes;
            cout << "Notes have been updated!" << endl;
        }

        void removeNotes() {
            if (!this->notes.empty()) {
                this->notes = "";
            } else {
                cout << "This person has no additional note!" << endl;
            }
        }

        void getDetails () {
            cout << endl;
            cout << "Name:         " << this->name << endl;
            cout << "Email:        " << this->email << endl;
            cout << "Role:         " << this->role << endl;
            cout << "Phone Number: " << this->phoneNumber << endl;
            if (!this->notes.empty()) {
                cout << "Notes:    " << this->notes << endl;
            } else {
                cout << "Notes:    No additional notes have been added" << endl;
            }
        }
};

vector<contactManager*> contactManager::persons;

int main () {
    contactManager person1(1123456789, "Ajay", "veerajay12@gmail.com", "Intern");
    contactManager person2(4545454545, "Mohan", "palmohan45@gmail.com", "Salesman", "Recently promoted");
    person1.updateRole("Employee");
    contactManager person3(7923441393, "Aazad", "shekharaazad13@gmail.com", "CA", "Has good experience");
    person3.getDetails();
    contactManager::printAll();
    return 0;
}
