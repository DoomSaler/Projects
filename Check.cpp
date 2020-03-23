#include "check.h"
#include <iostream>
#include <string>

std::string checkString(std::string c)
{
    std::cout << "������� " << c << " (������ ���������� � ��������� �����" << 
                 " � �� ��������� ����������� �/��� �����):\n";
    std::string name;
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    getline(std::cin, name, '\n');
    bool isError = false;
    while (true) {
        if (!(name[0] >= 'A' && name[0] <= 'Z') && !(name[0] >= '�' && name[0] <= '�'))
            isError = true;
        else if (isError == false) {
            for (size_t i = 1; i < name.size(); i++)
                if (!(name[i] >= 'a' && name[i] <= 'z') && !(name[i] >= '�' && name[i] <= '�')) {
                    isError = true;
                    break;
                }
        }
        if (isError == false)
            return name;
        else {
            std::cout << "������� " << c << " ���������: \n";
            std::cin.ignore(std::cin.rdbuf()->in_avail());
            getline(std::cin, name, '\n');
            isError = false;
        }
    }
}

short unsigned int checkNumber(int a, std::string c)
{
    std::cout << "������� "<< c << ":\n";
    short unsigned int number;
    std::cin >> number;
    while (std::cin.fail() || number < 0 || number > a)
    {
        std::cin.clear();
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::cout << "������� " << c << " ���������:\n";
        std::cin >> number;
    }
    return number;
}

int checkFileString(std::string name)
{
    if (!(name[0] >= 'A' && name[0] <= 'Z') && !(name[0] >= '�' && name[0] <= '�'))
        return 1;
    for (size_t i = 1; i < name.size(); i++)
        if (!(name[i] >= 'a' && name[i] <= 'z') && !(name[i] >= '�' && name[i] <= '�'))
            return 1;
    return 0;
}