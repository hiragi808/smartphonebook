//
// Created by macbook on 04.01.26.
//
#ifndef IPROJECT_IPJ_H
#define IPROJECT_IPJ_H
#include <string>
#include <vector>
using namespace std;
void showmenu();
string clearspace(string str);
bool validname(string name);
bool validphone(string phone);
bool validmail(string mail);
// структура контакта
struct contact {
    string name;
    string phone;
    string email;
    contact(string n,string p,string e) {
        name = n;
        phone = p;
        email = e;
    }
};
// структура телефонной книги
struct phonebook {
    vector<contact> contacts;  // список контактов

    void addcontact(string name, string phone, string email);

    bool removecontact(string name);

    bool editcontact(string oldname, string newname,
                     string newphone, string newemail);
    vector<contact> searchbyname(string part);

    void sortbyname();

    void savetofile(string filename);

    bool loadfromfile(string filename);

    void displayall();
};
#endif //IPROJECT_IPJ_H