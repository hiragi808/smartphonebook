#include <iostream>
#include "ipj.h"
#include <clocale>

using namespace std;


int main() {
    setlocale(LC_ALL,"Russia");
    phonebook book;
    int choice;
    do {
        showmenu();
        cin >> choice;
        cin.clear();
        cin.ignore(1000, '\n');
        switch (choice) {
            case 1: {
                string name, phone, email;
                cout << "имя: ";
                getline(cin, name);
                cout << "телефон: ";
                getline(cin, phone);
                cout << "email (оставьте пустым, если не нужен): ";
                getline(cin, email);
                book.addcontact(name, phone, email);
                break;
            }
            case 2: {
                string name;
                cout << "имя для удаления: ";
                getline(cin, name);
                book.removecontact(name);
                break;
            }
            case 3: {
                string oldname, newname, newphone, newemail;
                cout << "какое имя изменить: ";
                getline(cin, oldname);
                cout << "новое имя: ";
                getline(cin, newname);
                cout << "новый телефон: ";
                getline(cin, newphone);
                cout << "новый email (оставьте пустым, если не нужен): ";
                getline(cin, newemail);
                book.editcontact(oldname, newname, newphone, newemail);
                break;
            }
            case 4: {
                string searchtext;
                cout << "что ищем: ";
                getline(cin, searchtext);
                vector<contact> found = book.searchbyname(searchtext);
                if (found.empty()) {
                    cout << "не найдено!\n";
                } else {
                    cout << "\nнайдено " << found.size() << " контактов:\n";
                    for (int i = 0; i < found.size(); i++) {
                        cout << i + 1 << ". " << found[i].name
                             << " (" << found[i].phone << ")\n";
                    }
                }
                break;
            }

            case 5:
                book.sortbyname();
                break;

            case 6:
                book.displayall();
                break;
            case 7: {
                cout << "\n--- Сохранение в файл ---\n";
                string filename;
                cout << "Введите имя файла для сохранения";
                getline(cin, filename);
                if (filename.empty()) {
                    filename = "contacts.txt";
                    cout << "Используется имя по умолчанию: " << filename << "\n";
                }
                book.savetofile(filename);
                break;
            }
            case 8: {
                cout << "\n--- Загрузка из файла ---\n";
                string filename;
                cout << "Введите имя файла для загрузки: ";
                getline(cin, filename);
                if (!filename.empty()) {
                    book.loadfromfile(filename);
                } else {
                    cout << "Ошибка: Имя файла не может быть пустым!\n";
                }
                break;
            }
            case 0:
                cout << "выход\n";
                break;
            default:
                cout << "неверный выбор!\n";
        }
    } while (choice != 0);

    return 0;
}