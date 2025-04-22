#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits> 
using std::cout;
using std::endl;
using std::cin;
using std::string;

void show_menu() {
    cout << "\nМеню:\n";
    cout << "[1] Вывести все задачи\n";
    cout << "[2] Добавить задачу\n";
    cout << "[3] Добавить заметку к задаче\n";
    cout << "[4] Найти задачу\n";
    cout << "[5] Удалить задачу\n";
    cout << "[6] Выход\n";
    cout << "Выберите действие: ";   
}

void add_task() {
    string new_task;
    cin.ignore();
    cout << "Введите задачу: " << endl;
    getline(cin, new_task);

    if (new_task.empty()) {
        cout << "Ошибка: задача не может быть пустой!\n";
        return;
    }

    std::ofstream out("task.txt", std::ios::app);
    if (!out) {
        cout << "Ошибка: не удалось открыть файл!\n";
        return;
    }

    out << new_task << "\n\n";
    cout << "Задача успешно добавлена!\n";
}

void show_task() {
    std::ifstream in("task.txt");
    if (!in) {
        cout << "Файл не открылся или задач нет.\n";
        return;
    }

    std::vector<std::vector<string>> all;
    string current_task;
    int currtask = -1;
    while (getline(in, current_task)) {
        if (!current_task.empty()) {
            if (currtask == -1 || all.empty()) {
                all.push_back({});
                currtask++;
            }
            all[currtask].push_back(current_task);
        }
        else if (currtask >= 0 && !all[currtask].empty()) {
            all.push_back({});
            currtask++;
        }
    }
    if (all.empty() || (all.size() == 1 && all[0].empty())) {
        cout << "Нет задач для отображения.\n";
        return;
    }

    for (size_t i = 0; i < all.size(); ++i) {
        if (!all[i].empty()) {
            cout << "Задача [" << i << "]: " << all[i][0] << "\n";
            
            if (all[i].size() > 1) {
                cout << "Заметки:\n";
                for (size_t j = 1; j < all[i].size(); ++j) {
                    cout << "  - " << all[i][j] << "\n";
                }
            }
            else {
                cout << " (нет заметок)\n";
            }
        }
    }
}

void delete_task() {
    show_task();
    cout << "\nВведите номер задачи для удаления: ";
    int ind;
    cin >> ind;

    std::ifstream in("task.txt");
    if (!in) {
        cout << "Файл не открылся!\n";
        return;
    }

    std::vector<std::vector<string>> all;
    string current_task;
    int currtask = -1;

    while (getline(in, current_task)) {
        if (!current_task.empty()) {
            if (currtask == -1 || all.empty()) {
                all.push_back({});
                currtask++;
            }
            all[currtask].push_back(current_task);
        }
        else if (currtask >= 0 && !all[currtask].empty()) {
            all.push_back({});
            currtask++;
        }
    }

    if (ind < 0 || ind >= static_cast<int>(all.size())) {
        cout << "Неверный номер задачи!\n";
        return;
    }

    all.erase(all.begin() + ind);

    std::ofstream out("task.txt");
    for (const auto& task : all) {
        for (const auto& line : task) {
            out << line << "\n";
        }
        out << "\n";
    }

    cout << "Задача удалена!\n";
}

void add_note() {
    std::ifstream in("task.txt");
    if (!in) {
        cout << "Файл не открылся или задач нет.\n";
        return;
    }

    std::vector<std::vector<string>> notepertask;
    string current_task;
    int currtask = -1;
    while (getline(in, current_task)) {
        if (!current_task.empty()) {
            if (currtask == -1 || notepertask.empty()) {
                notepertask.push_back({});
                currtask++;
            }
            notepertask[currtask].push_back(current_task);
        }
        else if (currtask >= 0 && !notepertask[currtask].empty()) {
            notepertask.push_back({});
            currtask++;
        }
    }

    show_task();
    
    cout << "Введите номер задачи: ";
    int now;
    cin >> now;
    
    if (now < 0 || now >= static_cast<int>(notepertask.size())) {
        cout << "Неверный номер задачи!\n";
        return;
    }

    cout << "Введите заметку: ";
    string new_note;
    cin.ignore();
    getline(cin, new_note);

    notepertask[now].push_back(new_note);

    std::ofstream out("task.txt");
    for (const auto& task : notepertask) {
        for (const auto& line : task) {
            out << line << "\n";
        }
        out << "\n";
    }

    cout << "Заметка добавлена к задаче " << now << "!\n";
}
void find_task(){
	// открыть файл , записать в массив вектор , проходить по каждой из задачей , если сторовокй функцией поиск штдекса того что он ищет != 0 то мы выводим эту функнкию + все её заметки.
	std::ifstream in("task.txt");
    if (!in) {
        cout << "Файл не открылся или задач нет.\n";
        return;
    }
    std::vector<std::vector<string>> all;
    string current_task;
    int currtask = -1;
    while (getline(in, current_task)) {
        if (!current_task.empty()) {
            if (currtask == -1 || all.empty()) {
                all.push_back({});
                currtask++;
            }
            all[currtask].push_back(current_task);
        }
        else if (currtask >= 0) {
            all.push_back({});
            currtask++;
        }
    }
	in.close();
	std::cout << "Введите поиск задачи\n";
	string new_find;
    cin.ignore();
    getline(cin, new_find);

    if (all.empty() || (all.size() == 1 && all[0].empty())) {
        cout << "Нет задач для отображения.\n";
        return;
    }
	int flag = 0;
	for (size_t i = 0; i < all.size(); ++i){
        if (!all[i].empty()) {
            size_t pos = all[i][0].find(new_find);
            if (pos != std::string::npos) {
                flag = 1;
                std::cout << "Задача [" << i << "]: " << all[i][0] << "\n";

                if (all[i].size() > 1) {
                    std::cout << "Заметки:\n";
                    for (size_t j = 1; j < all[i].size(); ++j) {
                        std::cout << "  - " << all[i][j] << "\n";
                    }
                } else {
                    std::cout << " (нет заметок)\n";
                }
            }
        }
	}   
	if (flag == 0){
		std::cout << "Такой задачи не найдено, увы...\n";
	}
}
