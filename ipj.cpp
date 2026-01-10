//
// Created by macbook on 04.01.26.
//
#include "ipj.h"
#include <iostream>
#include <fstream>
#include <cctype>
// функция для очистки строки от лишних пробелов в начале и конце
string clearspace(string str) {
    // если строка пустая, сразу возвращаем пустую строку
    if (str.empty()) {
        return "";
    }
    // находим первый не пробел
    int start = 0;
    while (start < str.length()) {
        char c = str[start];
        // проверяем является ли символ пробельным
        if (c != ' ' && c != '\n') {
            break;
        }
        start++;
    }
    int end = str.length() - 1;
    while (end >= 0) {
        char c = str[end];
        if (c != ' ' && c != '\n') {
            break;
        }
        end--;
    }
    // если все пробелы
    if (start > end) {
        return "";
    }
    // возвращаем подстроку от start до end включительно
    return str.substr(start, end - start + 1);
}
bool validname(string name) {
    if (name.empty() || name.length() > 100) return false;
    // имя должно содержать только буквы, пробелы, дефисы
    for (char c : name) {
        if (!isalpha(c) && c != ' ' && c != '-'  && c != '.') {
            return false;
        }
    }
    return true;
}
bool validphone(string phone) {
    if (phone.empty() || phone.length() > 21) return false;
    // только цифры, плюс, скобки, дефисы
    for (char c : phone) {
        if (!isdigit(c) && c != '+' && c != '(' && c != ')' && c != '-' && c != ' ') {
            return false;
        }
    }
    return true;
}
bool validmail(string mail) {
    // email не обязателен
    mail=clearspace(mail);
    if (mail.empty()) {
        return true;
    }
    // должен содержать ровно один символ '@'
    int aсount = 0;
    for (int i = 0; i < mail.length(); i++) {
        if (mail[i] == '@') {
            aсount++;
        }
    }
    // Должен быть ровно один символ '@'
    if (aсount != 1) {
        return false;
    }
    int apos = mail.find('@');
    // '@' не может быть первым или последним символом
    if (apos == 0 || apos == mail.length() - 1) {
        return false;
    }
    return true;
}
using namespace std;
// 1. добавление контакта
void phonebook::addcontact(string name, string phone, string email) {
    // очистка от лишних пробелов
    name = clearspace(name);
    phone = clearspace(phone);
    email = clearspace(email);

    // Проверка ввода
    if (name.empty()) {
        cout << "Ошибка: Имя не может быть пустым!\n";
        return;
    }
    if (!validname(name)) {
        cout << "Ошибка: Некорректное имя! Используйте только буквы, пробелы, дефисы и апострофы.\n";
        return;
    }
    if (!validphone(phone)) {
        cout << "Ошибка: Некорректный номер телефона! Должен содержать минимум 5 цифр.\n";
        return;
    }
    // проверка на дубликат имени
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].name == name) {
            cout << "Ошибка: Контакт с именем '" << name << "' уже существует!\n";
            return;
        }
    }
    contact newcontact(name, phone, email);
    contacts.push_back(newcontact);
    cout << "контакт '" << name << "' добавлен!\n";
}
// 2. удаление контакта
bool phonebook::removecontact(string name) {
    name = clearspace(name);
    if (name.empty()) {
        cout << "Ошибка: Имя для удаления не может быть пустым!\n";
        return false;
    }
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
    oldname = clearspace(oldname);
    newname = clearspace(newname);
    newphone = clearspace(newphone);
    newemail = clearspace(newemail);
    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].name == oldname) {
            contacts[i].name = newname;
            contacts[i].phone = newphone;
            contacts[i].email = newemail;
            if (oldname.empty()) {
                cout << "Ошибка: Старое имя не может быть пустым!\n";
                return false;
            }

            if (newname.empty()) {
                cout << "Ошибка: Новое имя не может быть пустым!\n";
                return false;
            }

            if (!validname(newname)) {
                cout << "Ошибка: Некорректное новое имя!\n";
                return false;
            }

            if (!validphone(newphone)) {
                cout << "Ошибка: Некорректный новый номер телефона!\n";
                return false;
            }
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
    part=clearspace(part);
    for (int i = 0; i < contacts.size(); i++) {
        string fname = contacts[i].name;
        if ((fname.find(part))!=-1) {
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

// 7. сохранение в файл
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

// 8. загрузка из файла
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


