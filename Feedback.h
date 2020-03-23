#pragma once
#include <string>
#include <fstream>

class Feedback
{
public:
	Feedback();
	Feedback(std::string s1, std::string s2, std::string s3, short unsigned int r);
	~Feedback();
	void show();
	void edit();
	unsigned short int getRating();
	std::string getName();
	std::string getSurname();
	std::string getText();
private:
	std::string name_;
	std::string surname_;
	std::string text_;
	short unsigned int rating_;
};

class Table 
{
public:
	Table();
	~Table();
	bool showOutFile(std::ifstream& f);
	bool load(std::ifstream& f);
	bool save(std::ofstream& f);
	void add(size_t n = 1);
	void remove(size_t n);
	void showAll();
	void sort();
	void find(std::string name, std::string surname);
	float performRating();
	Feedback& operator[](size_t i);
	size_t getSize();

private:
	void add(std::string s1, std::string s2, std::string s3, unsigned short r);
	size_t size_;
	Feedback* table_ = new Feedback[size_];
};

