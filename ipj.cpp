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
    int n = contacts.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (contacts[j].name > contacts[j+1].name) {
                // Меняем местами
                contact t = contacts[j];
                contacts[j] = contacts[j+1];
                contacts[j+1] = t;
            }
        }
    }
    cout << "контакты отсортированы по имени!\n";
}

// 6. сохранение в файл
void phonebook::savetofile(string filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "ошибка открытия файла!\n";
        return;
    }
    for (int i = 0; i < contacts.size(); i++) {
        file << contacts[i].name << ","
             << contacts[i].phone << ","
             << contacts[i].email << "\n";
    }
    file.close();
    cout << "сохранено " << contacts.size() << " контактов\n";
}

// 7. загрузка из файла
bool phonebook::loadfromfile(string filename) {
    ifstream file(filename);
    if (!file) {
        cout << "Ошибка! Фаил не открыт." << filename << endl;
        return false;
    }

    contacts.clear();

    //читаем файл
    string line;
    while (getline(file, line)) {
        int comma1 = line.find(',');//если не найдет то вернет -1
        int comma2 = -1;
        if (comma1 != -1) {
            comma2 = line.find(',', comma1 + 1);
        }
        if (comma1 != -1 && comma2 != -1) {
            contact c(line.substr(0, comma1),
                     line.substr(comma1 + 1, comma2 - comma1 - 1),
                     line.substr(comma2 + 1));
            contacts.push_back(c);
        }
    }
    }
// 8. показ всех контактов
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

