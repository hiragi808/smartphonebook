//
// Created by macbook on 04.01.26.
//
#include "ipj.h"
#include <iostream>
#include <fstream>

using namespace std;
// 1. добавление контакта
void phonebook::addcontact(string name, string phone, string email) {
    contact newcontact(name, phone, email);
    contacts.push_back(newcontact);
    cout << "контакт '" << name << "' добавлен!\n";
}
// 2. удаление контакта
bool phonebook::removecontact(string name) {
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].name == name) {
            contacts.erase(contacts.begin() + i);
            cout << "контакт '" << name << "' удален!\n";
            return true;
        }
    }
    cout << "контакт с именем '" << name << "' не найден!\n";
    return false;
}

// 3. изменение контакта
bool phonebook::editcontact(string oldname, string newname,string newphone, string newemail) {
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].name == oldname) {
            contacts[i].name = newname;
            contacts[i].phone = newphone;
            contacts[i].email = newemail;
            cout << "контакт изменен!\n";
            cout << "было: " << oldname << "\n";
            cout << "стало: " << newname << "\n";
            return true;
        }
    }
    cout << "контакт с именем '" << oldname << "' не найден!\n";
    return false;
}

// 4. поиск по имени
vector<contact> phonebook::searchbyname(string part) {
    vector<contact> results;
    for (int i = 0; i < contacts.size(); i++) {
        string fname = contacts[i].name;
        if (!(fname.find(part))) {
            results.push_back(contacts[i]);
        }
    }

    return results;
}

// 5. сортировка по имени
void phonebook::sortbyname() {

}

// 6. показ всех контактов
void phonebook::displayall() {
    if (contacts.empty()) {
        cout << "телефонная книга пуста!\n";
        return;
    }

    cout << "\n=== телефонная книга ===\n";
    cout << "всего: " << contacts.size() << " контактов\n";

    for (int i = 0; i < contacts.size(); i++) {
        cout << i + 1 << ". "
             << "имя: " << contacts[i].name << " | "
             << "тел: " << contacts[i].phone << " | "
             << "email: " << contacts[i].email << "\n";
    }
}
