#pragma once
#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <cstdlib>
#include "iostream"
using namespace std;

#define SECTOR 4;

typedef struct date_time
{
	int day;
	int month;
	int year;

	int hour;
	int mins;
	int sec;
} date_time;

enum attribute {read, hidden, systems};


class file
{
private:
	string directory; //каталог
	string filename;  //имя
	string extention; //расширение
	date_time date_creation;
	bool atr[3]; //атрибут
	bool is_deleted;
	int num_sectors;
public:
	string getDirectory();
	void setDirectory(string d);
	string getFilename();
	void setFilename(string f);
	string getExtention();
	void setExtention(string e);
	date_time getDateTime();
	void setDateTime(date_time d);
	string getAttribute();
	void setAttribute(bool a[3]);
	bool getDeleted();
	void setDeleted(bool i);
	int getNumSectors();
	void setNumSectors(int n);

	void print_record();

	file();
	file(string d, string f, string e, date_time dt, int a, int n);
	~file();
};

void load_file(vector<file> &vect);
void print_v(vector<file> &v);
file input_record(bool &is_correct);
void add_record(vector<file> &v);
void delete_v(vector<file> &v);
void save_file(vector<file> &v);
void exchange_v(vector<file> &v);
void export_vector(vector<file> v);
vector<file> search(vector<file> &v);

//компараторы для сортировки и бинарного поиска
bool compare_direct_rec(file a,file b);
bool compare_direct(file a, string b);

bool compare_name_rec(file a,file b);
bool compare_name(file a, string b);

bool compare_date_rec(file a,file b);
bool compare_date(file a, date_time b);

bool compare_del_rec(file a, file b);
bool compare_del(file a, bool b);