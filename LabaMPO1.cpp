#include <iostream>
#include <fstream>
#include <string>
#include "Feedback.h"
#include "check.h"
#include "windows.h"

int main()
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    Table table;
    int command;
    int n;
    std::string name;
    std::string surname;
    std::ifstream read;
    std::ofstream write;
    std::cout << "Приложение для просмотра отзывов пользователей\n\n";
    while (true) {
        std::cout << "Введите номер для выполнения соотвеисвующей функции:\n";
        std::cout << "1  - добавить отзыв\n";
        std::cout << "2  - найти отзыв по именю и фамилии\n";
        std::cout << "3  - изменить отзыв\n";
        std::cout << "4  - вывести общую оценку пользователей\n";
        std::cout << "5  - отсортировать отзывы пользователей\n";
        std::cout << "6  - вывести все данные\n";
        std::cout << "7  - удалить отзыв\n";
        std::cout << "8  - просмотр данных из файла без их записи в приложение\n";
        std::cout << "9  - запись данных из файла и их просмотр\n";
        std::cout << "10 - сохранение данных в файл\n";
        std::cout << "0  - выйти из программы\n\n";
        command = checkNumber(10, "номер исполняемой функции");
        system("cls");
        switch (command) {
        case 1:
            std::cout << "Функция осуществляет добавление отзыва.\n" << 
                         "Запрашивает у пользователя ввод всех данных,"<<
                         " необходимых для написания отзыва.\n\n";
            table.add();
            std::cout << "\nОтзыв был успешно добавлен!\n";
            break;
        case 2:
            std::cout << "Функция осуществляет поиск отзывов по введенным" <<
                         " имени и фамилии.\n";
            name = checkString("имя пользователя");
            surname = checkString("фамилию пользователя");
            std::cout << '\n';
            table.find(name, surname);
            break;
        case 3:
            std::cout << "Функция осуществляет редактирование выбранного отзыва.\n" <<
                         "Отзыв выбирается по порядковому номеру в списке.\n\n";
            std::cout << "Количество отзывов: " << table.getSize() << '\n';
            std::cout << "Введите порядковый номер изменяемого отзыва: ";
            n = checkNumber(table.getSize(), "номер");
            if (n == 0) 
                std::cout << "0 - не порядковое число, выйдите и зайдите нормально!\n";
            else {
                std::cout << "Изменяемый отзыв:\n";
                table[n - 1].show();
                table[n - 1].edit();
                std::cout << "\nИзмененный отзыв:\n";
                table[n - 1].show();
            }
            break;
        case 4:
            std::cout << "Общая оценка данного приложения: " << table.performRating() << '\n';
            break;
        case 5:
            table.sort();
            std::cout << "Отсортированные данные пользоваталей по оценке:\n\n";
            table.showAll();
            break;
        case 6:
            std::cout << "Все отзывы пользователей: \n\n";
            table.showAll();
            break;
        case 7:
            std::cout << "Функция осуществляет удаление выбранного отзыва.\n" <<
                         "Отзыв выбирается по порядковому номеру в списке.\n\n";
            std::cout << "Количество отзывов: " << table.getSize() << '\n';
            std::cout << "Введите порядковый номер удаляемого отзыва: ";
            n = checkNumber(table.getSize(), "номер");
            if (n == 0)
                std::cout << "0 - не порядковое число, выйдите и зайдите нормально!\n";
            else {
                table[n - 1].show();
                std::cout << "Вы уверены, что хотите удалить этот отзыв? (введите \"да\" для удаления)\n";
                std::string s;
                std::cin >> s;
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                if (s == "да") {
                    table.remove(n - 1);
                    std::cout << "Отзыв успешно удален!\n";
                }
                else {
                    std::cout << "Вы подарили данному отзыву вторую жизнь! Спасибо!\n";
                }
            }
            break;
        case 8:
            std::cout << "Функция выводит все данные из файла на экран.\n";
            if (table.showOutFile(read) == true)
                std::cout << "Все данные были успешно прочитаны из файла!\n";
            else
                std::cout << "Произошел троллинг\n";
            break;
        case 9:
            std::cout << "Функция записывает все данные из файла в приложение.\n";
            if (table.load(read) == true) 
                std::cout << "Все данные были успешно загружены из файла!\n";
            else
                std::cout << "Ошибка в значениях внутри файла или файл не был найден!\n";
            break;
        case 10:
            std::cout << "Функция записывает все данные в файл (сохранение).\n";
            if (table.save(write) == true)
                std::cout << "Все данные были успешно загружены в файл!\n";
            else
                std::cout << "Произошел троллинг\n";
            break;
        case 0:
            system("cls");
            system("pause");
            return 0;
        }
        system("pause");
        system("cls");
    }
}
