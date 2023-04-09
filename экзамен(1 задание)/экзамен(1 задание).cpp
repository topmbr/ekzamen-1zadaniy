#include <fstream>
#include <string>
#include <filesystem>
#include <iostream>

using namespace std;
namespace fs = std::filesystem;

class FileManager {
protected:
    string currentPath;
public:
    FileManager() {
        currentPath = fs::current_path().string();
    }

    virtual void showContents() {
        cout << "Содержание " << currentPath << ":" << endl;
        for (auto& entry : fs::directory_iterator(currentPath)) {
            cout << entry.path() << endl;
        }
    }

    virtual void createDirectory(string name) {
        fs::create_directory(currentPath + "\\" + name);
        cout << "Каталог успешно создан" << endl;
    }

    virtual void createFile(string name, string content) {
        ofstream file(currentPath + "\\" + name);
        file << content;
        file.close();
        cout << "Файл успешно создан" << endl;
    }

    virtual void deleteDirectory(string name) {
        fs::remove_all(currentPath + "\\" + name);
        cout << "Каталог успешно удален" << endl;
    }

    virtual void deleteFile(string name) {
        fs::remove(currentPath + "\\" + name);
        cout << "Файл успешно удален" << endl;
    }

    virtual void renameDirectory(string oldName, string newName) {
        fs::rename(currentPath + "\\" + oldName, currentPath + "\\" + newName);
        cout << "Каталог успешно переименован" << endl;
    }

    virtual void renameFile(string oldName, string newName) {
        fs::rename(currentPath + "\\" + oldName, currentPath + "\\" + newName);
        cout << "Файл успешно переименован" << endl;
    }

    virtual void copyDirectory(string source, string destination) {
        fs::copy(currentPath + "\\" + source, currentPath + "\\" + destination);
        cout << "Каталог успешно скопирован" << endl;
    }

    virtual void copyFile(string source, string destination) {
        fs::copy(currentPath + "\\" + source, currentPath + "\\" + destination);
        cout << "Файл успешно скопирован" << endl;
    }

    virtual void moveDirectory(string source, string destination) {
        fs::rename(currentPath + "\\" + source, currentPath + "\\" + destination);
        cout << "Каталог успешно перемещен" << endl;
    }

    virtual void moveFile(string source, string destination) {
        fs::rename(currentPath + "\\" + source, currentPath + "\\" + destination);
        cout << "Файл успешно перемещен" << endl;
    }

    virtual void getDirectorySize(string name) {
        long long size = 0;
        for (auto& entry : fs::recursive_directory_iterator(currentPath + "\\" + name)) {
            if (!fs::is_directory(entry)) {
                size += fs::file_size(entry);
            }
        }
        cout << "Размер " << name << " каталога " << size << " байты." << endl;
    }

    virtual void getFileSize(string name) {
        long long size = fs::file_size(currentPath + "\\" + name);
        cout << "Размер " << name << " файла " << size << " байты." << endl;
    }
};
void main() {
    setlocale(LC_ALL, "rus");
    FileManager fm;
    int c;
    string name, content, source, destination;
    do {
        cout << endl << "Выберите вариант:" << endl;
        cout << "1. Показать содержимое текущего каталога" << endl;
        cout << "2. Создать каталог" << endl;
        cout << "3. Создать фаил" << endl;
        cout << "4. Удалить каталог" << endl;
        cout << "5. Удалить фаил" << endl;
        cout << "6. Переименовать каталог" << endl;
        cout << "7. Переименовать фаил" << endl;
        cout << "8. Копировать каталог" << endl;
        cout << "9. Копировать фаил" << endl;
        cout << "10. Переместить каталог" << endl;
        cout << "11. Переместить фаил" << endl;
        cout << "12. Получить размер каталога" << endl;
        cout << "13. Получить размер фаила" << endl;
        cout << "0. Выход" << endl;
        while (!(cin >> c) || (cin.peek() != '\n'))
        {
            cin.clear();
            while (cin.get() != '\n');
            cout << "Error! Write number: ";
        }


        switch (c) {
        case 1:
            fm.showContents();
            break;
        case 2:
            cout << "Введите имя каталога для создания: ";
            cin >> name;
            fm.createDirectory(name);
            break;
        case 3:
            cout << "Введите имя файла для создания : ";
            cin >> name;
            cout << "Введите содержимое файла: ";
            cin.ignore();
            getline(cin, content);
            fm.createFile(name, content);
            break;
        case 4:
            cout << "Введите имя каталога для удаления: ";
            cin >> name;
            fm.deleteDirectory(name);
            break;
        case 5:
            cout << "Введите имя файла для удаления: ";
            cin >> name;
            fm.deleteFile(name);
            break;
        case 6:
            cout << "Введите имя каталога для переименования: ";
            cin >> name;
            cout << "Введите новое имя каталога: ";
            cin >> content;
            fm.renameDirectory(name, content);
            break;
        case 7:
            cout << "Введите имя файла для переименования: ";
            cin >> name;
            cout << "Введите новое имя файла: ";
            cin >> content;
            fm.renameFile(name, content);
            break;
        case 8:
            cout << "Введите имя каталога для копирования: ";
            cin >> source;
            cout << "Введите имя целевого каталога: ";
            cin >> destination;
            fm.copyDirectory(source, destination);
            break;
        case 9:
            cout << "Введите имя файла для копирования: ";
            cin >> source;
            cout << "Введите имя нужного файла: ";
            cin >> destination;
            fm.copyFile(source, destination);
            break;
        case 10:
            cout << "Введите имя каталога для перемещения: ";
            cin >> source;
            cout << "Введите имя нужного каталога: ";
            cin >> destination;
            fm.moveDirectory(source, destination);
            break;
        case 11:
            cout << "Введите имя файла для перемещения: ";
            cin >> source;
            cout << "Введите имя нужного файла: ";
            cin >> destination;
            fm.moveFile(source, destination);
            break;
        case 12:
            cout << "Введите имя каталога, чтобы получить размер: ";
            cin >> name;
            fm.getDirectorySize(name);
            break;
        case 13:
            cout << "Введите имя файла, чтобы получить размер: ";
            cin >> name;
            fm.getFileSize(name);
            break;
        case 0:
            cout << "Выход" << endl;
            exit(0);
        default:
            cout << "Неверный вариант. Попробуйте еще раз" << endl;
        }
    } while (c != 0);
}