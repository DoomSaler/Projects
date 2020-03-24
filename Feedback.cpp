#pragma warning (disable: 6385)
#include "Feedback.h"
#include "check.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

//======================================
//Êëàññ îòçûâà
//======================================

Feedback::Feedback():name_(""), surname_(""), text_(""), rating_(0) {}

Feedback::Feedback(std::string s1, std::string s2, std::string s3, 
                   short unsigned int r) : name_(s1), surname_(s2),
                   text_(s3), rating_(r) 
{}

Feedback::~Feedback() {}

void Feedback::show()
{
    std::cout << "Èìÿ è ôàìèëèëÿ ïîëüçîâàòåëÿ: " << name_ << " " << surname_ <<'\n';
    std::cout << "Îöåíêà, ïîñòàâëåííàÿ ïîëüçîâàòåëåì: " << rating_ << " èç 10\n";
    std::cout << "Òåêñò êîììåíòàðèÿ:\n" << text_ << "\n\n";
}

void Feedback::edit()
{
    std::string name;
    name = checkString("èìÿ");
    std::string surname;
    surname = checkString("ôàìèëèþ");
    unsigned short int rating;
    rating = checkNumber(10, "îöåíêó (îò 0 äî 10)");
    std::cout << "Ââåäèòå òåêñò êîììåíòàðèÿ:\n";
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::string text;
    getline(std::cin, text, '\n');
    name_ = name;
    surname_ = surname;
    rating_ = rating;
    text_ = text;
}

unsigned short int Feedback::getRating()
{
    return rating_;
}

std::string Feedback::getName()
{
    return name_;
}

std::string Feedback::getSurname()
{
    return surname_;
}

std::string Feedback::getText()
{
    return text_;
}

//======================================
//Êëàññ áàçû îòçûâîâ
//======================================

Table::Table() : size_(0) {}

Table::~Table()
{
    delete[] table_;
}

bool Table::save(std::ofstream& f)
{
    f.open("Base.txt");
    if (f.is_open()) {
        f.clear();
        for (size_t i = 0; i < size_; i++)
            f << table_[i].getName() << '|' << table_[i].getSurname() << '|' <<
            table_[i].getRating() << '|' << table_[i].getText() << "|\n";
        f.close();
    }
    else return false;
    return true;
}

bool Table::load(std::ifstream& f)
{
    // Íåíàâèæó ýòó ôóíêöèþ
    size_ = 0;
    delete[] table_;
    table_ = NULL;
    f.open("Base.txt");
    if (f.is_open()) {
        while (!f.eof()) {
            int errors = 0;
            std::string name;
            getline(f, name, '|');
            if (name.length() == 0) {
                f.close();
                return true;
            }
            errors += checkFileString(name);
            std::string surname;
            getline(f, surname, '|');
            errors += checkFileString(surname);
            std::string str;
            getline(f, str, '|');
            std::istringstream iss(str);
            int rating;
            iss >> rating;
            if (rating < 0 || rating > 10)
                errors++;
            if (errors > 0) {
                std::cout << "Îáíàðóæåíà îøèáêà! Âûïîëíåíèèå äàëüøå íåâîçìîæíî!";
                return false;
            }
            std::string text;
            getline(f, text, '|');
            f.get();
            add(name, surname, text, rating);
        }
        f.close();
        return true;
    }
    else {
        f.close();
        return false;
    }
}

bool Table::showOutFile(std::ifstream& f)
{
    f.open("Base.txt");
    if (f.is_open()) {
        while (!f.eof()) {
            std::string name;
            getline(f, name, '|');
            if (name.length() == 0) {
                f.close();
                return true;
            }
            std::string surname;
            getline(f, surname, '|');
            std::string str;
            getline(f, str, '|');
            std::istringstream iss(str);
            int rating;
            iss >> rating;
            std::string text;
            getline(f, text, '|');
            f.get();
            Feedback feedback(name, surname, text, rating);
            feedback.show();
        }
        f.close();
        return true;
    }
    else { 
        f.close();
        return false;
    }
}

void Table::add(size_t n)
{
    size_t currentSize = size_;
    Feedback* temp;
    size_ += n;
    temp = new Feedback[size_];
    for (size_t i = 0; i < size_ - n; i++)
        temp[i] = table_[i];
    delete[] table_; 
    table_ = temp;
    for (size_t i = currentSize; i < size_; i++) {
        std::string name;
        name = checkString("èìÿ ïîëüçîâàòåëÿ");
        std::string surname;
        surname = checkString("ôàìèëèþ ïîëüçîâàòåëÿ");
        short unsigned int rating;
        rating = checkNumber(10, "îöåíêó (îò 0 äî 10)");
        std::cout << "Ââåäèòå îòçûâ:\n";
        std::cin.ignore(std::cin.rdbuf()->in_avail());
        std::string text;
        getline(std::cin, text, '\n');
        Feedback feedback(name, surname, text, rating);
        table_[i] = feedback;
    }
}

void Table::add(std::string s1, std::string s2, std::string s3, unsigned short r)
{
    size_t currentSize = size_;
    Feedback* temp;
    size_ += 1;
    temp = new Feedback[size_];
    for (size_t i = 0; i < size_ - 1; i++)
        temp[i] = table_[i];
    delete[] table_;
    table_ = temp;
    Feedback feedback(s1, s2, s3, r);
    table_[size_ - 1] = feedback;
}


void Table::remove(size_t n)
{
    Feedback* temp;
    size_--;
    temp = new Feedback[size_];
    for (size_t i = 0; i < size_ + 1; i++)
        if (i < n)
            temp[i] = table_[i];
        else if (i > n)
            temp[i-1] = table_[i];
    delete[] table_;
    table_ = temp;
}

float Table::performRating()
{
    float s;
    s = 0;
    for (size_t i = 0; i < size_; i++) 
        s += static_cast<float>(table_[i].getRating());
    return s / size_;
}

void Table::sort()
{
    for (size_t j = 1; j < size_; j++)
        for (size_t i = 0; i < size_ - 1; i++)
            if (table_[i].getRating() < table_[i + 1].getRating()) {
                Feedback a = table_[i];
                table_[i] = table_[i + 1];
                table_[i + 1] = a;
            }
}

void Table::find(std::string name, std::string surname)
{
    for (size_t i = 0; i < size_; i++)
        if (table_[i].getName() == name && table_[i].getSurname() == surname) {
            std::cout << "Íîìåð: " << i + 1 << '\n';
            table_[i].show();
        }
}

void Table::showAll()
{
    for (size_t i = 0; i < size_; i++) {
        std::cout << "Íîìåð: " << i + 1 << '\n';
        table_[i].show();
    }
}

Feedback& Table::operator[](size_t i)
{
    return table_[i];
}

size_t Table::getSize()
{
    return size_;
}
