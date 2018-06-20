#include "stdafx.h"
#include "file.h"


file::file()
{
	directory = "";
	filename = "";
	extention = "";
	atr[0] = true;
	is_deleted = false;
	num_sectors = 1 * SECTOR;
}

file::file(string d, string f, string e, date_time dt, int a, int n)
{
	setDirectory(d);
	setFilename(f);
	setExtention(e);
	setDateTime(dt);
	setAttribute({ 0 });
	setDeleted(false);
	setNumSectors(n);
}

file::~file()
{
}

//путь к файлу
string file::getDirectory() {
	return directory;
}
void file::setDirectory(string d){
	if (d == "") throw  "Невозможно указать пустой путь";
	directory = d;

}

//имя файла
string file::getFilename() {
	return filename;
}
void file::setFilename(string f) {
	if (f == "") throw  "Невозможно указать пустое имя";
	filename = f;
}

//расширение
string file::getExtention() {
	return extention;
}
void file::setExtention(string e) {
	if (e == "") throw  "Невозможно указать пустое имя";
	extention = e;
}

//дата и время
date_time file::getDateTime() {
	return date_creation;
}
void file::setDateTime(date_time d) {
	if ((d.day < 1) || (d.day > 31) || (d.month < 1) || (d.month > 12)||(d.year < 1800) || (d.year > 2018) ||
		(d.hour < 1) || (d.hour > 24) || (d.mins < 1) || (d.mins > 60) || (d.sec < 1) || (d.sec > 60))
		throw "Неверная дата";
	date_creation = d;
}

//атрибут 
string file::getAttribute() {
	string result = "";
	if (atr[0]) result += "read";
	if (atr[1]) result = " hidden";
	if (atr[2]) result = " system";
	return result;
}
void file::setAttribute(bool a[3]) {
	atr[0] = a[0];
	atr[1] = a[1];
	atr[2] = a[2];
}
//признак удаления
bool file::getDeleted() {
	return is_deleted;
}
void file::setDeleted(bool i) {
	is_deleted = i;
}

//количество секторов
int file::getNumSectors() {
	return num_sectors/ SECTOR;
}
void file::setNumSectors(int n) {
	if (n < 1) throw "Количество должно быть положительным";
	num_sectors = n*SECTOR;
}

string date_to_str(date_time d) {
	string result;
	result = to_string(d.day) + "." + to_string(d.month) + "." + to_string(d.year) + "  " +
			to_string(d.hour) + "." + to_string(d.mins) + "." + to_string(d.sec);
	return result;
}

//печать 1 записи в консоль
void file::print_record()
{
	string del;
	getDeleted() ? del = "помечен" : del = "непомечен";
	std::cout << getDirectory() << "\t" << getFilename() << "\t" << getExtention()
		<< "\t\t" << date_to_str(getDateTime()) << "\t" << getAttribute() << "\t" << del
		<< "\t\t\t" << to_string(getNumSectors())<<endl; 
}

date_time str_to_date(string date,string  time) {
	date_time result;
	//date
	int i = 1;
	result.day = (int)(date[0]-'0');
	while (date[i] !='.') {
		result.day *= 10;
		result.day += (int)(date[i] - '0');
		i++;
	}
	i++;
	result.month = (int)(date[i] - '0');
	i++;
	while (date[i] != '.') {
		result.month *= 10;
		result.month += (int)(date[i] - '0');
		i++;
	}
	i++;
	result.year = (int)(date[i] - '0');
	i++;
	while (i<date.length()) {
		result.year *= 10;
		result.year += (int)(date[i] - '0');
		i++;
	}

	//time
	i = 1;
	result.hour = (int)(time[0] - '0');
	while (time[i] != '.') {
		result.hour *= 10;
		result.hour += (int)(time[i] - '0');
		i++;
	}
	i++;
	result.mins = (int)(time[i] - '0');
	i++;
	while (time[i] != '.') {
		result.mins *= 10;
		result.mins += (int)(time[i] - '0');
		i++;
	}
	i++;
	result.sec = (int)(time[i] - '0');
	i++;
	while (i<time.length()) {
		result.sec *= 10;
		result.sec += (int)(time[i] - '0');
		i++;
	}

	return result;
}

//загрузка вектора из текстового файла 
void load_file(vector<file> &vect) {
	//vector<file>::iterator it = vect.begin(); 

	file f;
	string fname;
	ifstream in;
	std::cout << "Введите имя файла\n";
	cin >> fname;
	if (fname == "") throw "Имя не должно быть пустым";

	in.open(fname, ios::in);
	if (!in.is_open()) {
		throw "Не удалось открыть файл!\n";
	}
	if (in.eof()) {
		throw "Файл пуст!\n";
	}
	string tmp_direct, tmp_name, tmp_ext, tmp_date, tmp_time, tmp_atr, tmp_del, tmp_num;
	string tmp_str;
	bool a[3];
	while (!in.eof())
	{
		//in.read((char*)&f, sizeof(file)); 
		in >> tmp_direct >> tmp_name >> tmp_ext >> tmp_date >> tmp_time  ;
		in >> tmp_str;

		if (tmp_atr == "read") a[0] = true;
		else a[0] = false;
		if (tmp_atr == "hidden") a[1] = true;
		else a[1] = false;
		if (tmp_atr == "system") a[2] = true;
		else a[2] = false;

		in >> tmp_str;
		if (tmp_atr == "hidden") a[1] = true;
		else a[1] = false;
		if (tmp_atr == "system") a[2] = true;
		else a[2] = false;

		in >> tmp_str;
		if (tmp_atr == "system") a[2] = true;
		else a[2] = false;

		in >> tmp_del >> tmp_num;
		f.setDirectory(tmp_direct);
		f.setFilename(tmp_name);
		f.setExtention(tmp_ext);

		f.setDateTime(str_to_date(tmp_date, tmp_time));


		if (tmp_del == "помечен") f.setDeleted(true);
		else f.setDeleted(false);
		f.setNumSectors(stoi(tmp_num));
		vect.push_back(f);
	}
	in.close();
}

//печать вектора в консоль
void print_v(vector<file> &v) {
	std::cout << "Директория\tИмя\tРасширение\t\tДата\tАтрибут\tПризнак удаления\tКол-во выд. секторов"<< endl;
	for (vector<file>::iterator it = v.begin(); it != v.end(); it++) (*it).print_record();
}

//проверка вхождения записи с данным именем
bool contains(vector<file> v, string s) {
	for (vector<file>::iterator it = v.begin(); it != v.end(); it++) {
		if ((*it).getFilename() == s) return true;
	}
	return false;
}

//ввод даты
date_time input_date(bool &is_correct) {
	date_time result;
	int tmp_int;
	std::cout << "Введите дату созданию:\n";

	std::cout << "Введите число:\n";
		cin >> tmp_int;
		result.day = tmp_int;
		std::cout << "Введите месяц:\n";
		cin >> tmp_int;
		result.month = tmp_int;
		std::cout << "Введите год:\n";
		cin >> tmp_int;
		result.year = tmp_int;
		std::cout << "Введите часы:\n";
		cin >> tmp_int;
		result.hour = tmp_int;;
		std::cout << "Введите минуты:\n";
		cin >> tmp_int;
		result.mins = tmp_int;
		std::cout << "Введите секунды:\n";
		cin >> tmp_int;
		result.sec = tmp_int;

	return result;
}
//ввод 1 записи с консоли 
file input_record(bool &is_correct) {
	file f;
	string tmp_string;
	bool a[3];
	try {
		cout << "Введите путь к файлу\n";
		cin >> tmp_string;
		f.setDirectory(tmp_string);

		cout << "Введите имя файла\n";
		cin >> tmp_string;
		f.setFilename(tmp_string);

		cout << "Расширение файла:\n";
		cin >> tmp_string;
		f.setExtention(tmp_string);

		int tmp_int;
		f.setDateTime(input_date(is_correct));

		cout << "Введите индекс атрибута:\n";
		do {
			cout << "Только на чтение:\n1-Да\n0-Нет\n";
			cin >> tmp_int;
		} while ((tmp_int<0) || (tmp_int>1));
		a[0] = tmp_int;
		do {
			cout << "Скрытый:\n1-Да\n0-Нет\n";
			cin >> tmp_int;
		} while ((tmp_int<0) || (tmp_int>1));
		a[1] = tmp_int;
		do {
			cout << "Системный:\n1-Да\n0-Нет\n";
			cin >> tmp_int;
		} while ((tmp_int<0) || (tmp_int>1));
		a[2] = tmp_int;
		f.setAttribute(a);

		cout << "Количество выделенных сеторов:\n";
		cin >> tmp_int;
		f.setNumSectors(tmp_int);
	}
	catch (char *s) {
		is_correct = false;
	}
	return f;
}

//добавить запись
void add_record(vector<file> &v) {
	file f;
	bool is_correct = true;
	f = input_record(is_correct);
	
	if (contains(v, f.getFilename() )) throw "Файл с таким именем уже существует.\n";
	if (!is_correct) throw "Невозможно добавить файл! Возможно часть данных введена неверно." 
							"Все поля обязаны быть непустыми, а дата и время соответствующими\n";
	
	v.insert(v.end(), f);
	std::cout << "Запись добавлена!" << endl;
}

//удалить запись
void delete_v(vector<file> &v) {
	if (v.empty()) throw "Вектор пуст\n";
	string name;
	std::cout << "Введите имя файла, который нужно удалить:\n";
	cin >> name;
	if (name =="") throw "Имя не должно быть пустым\n";
	if (!contains(v, name)) throw "Такого номера нет!\n";

	vector<file>::iterator it = v.begin();
	while ((*it).getFilename() != name && it != v.end()) it++;
	v.erase(it);
	std::cout << "Файл удалён!" << endl;
}

void exchange_v(vector<file> &v) {
	if (v.empty()) throw "Вектор пуст\n";
	string name;
	std::cout << "Введите имя файла, данные о котором надо заменить:\n ";
	cin >> name;
	if (name == "") throw "Имя не должно быть пустым\n";
	if (!contains(v, name)) throw "Такого номера нет!\n";

	vector<file>::iterator it = v.begin();
	while ((*it).getFilename() != name && it != v.end()) it++;

	string tmp_string;
	date_time tmp_date;
	int tmp_int;
	bool is_correct_date,tmp_bool;

	int choise;
	std::cout << "1 - Изменить директорию\n";
	std::cout << "2 - Изменить имя\n";
	std::cout << "3 - Изменить расширение\n";
	std::cout << "4 - Изменить дату создания\n";
	std::cout << "5 - Изменить атрибут\n";
	std::cout << "6 - Пометить на удаление/восстановить\n";
	std::cout << "7 - Изменить количество выделенных секторов\n";
	std::cout << "0 - Выход\n";
	cin >> choise;
	
	switch (choise) {
	case 0: break;
	case 1: {
		cin >> tmp_string;
		try {
			std::cout << "Введите новые данные:\n";
			(*it).setDirectory(tmp_string);
		}
		catch (char *s) {
			throw s;
		}
	}
		break;
	case 2: {
		std::cout << "Введите новые данные:\n";
		cin >> tmp_string;
		try {
			(*it).setFilename(tmp_string);
		}
		catch (char *s) {
			throw s;
		}
	}
		break;
	case 3: {
		std::cout << "Введите новые данные:\n";
		cin >> tmp_string;
		try {
			(*it).setDirectory(tmp_string);
		}
		catch (char *s) {
			throw s;
		}
	}
		break;
	case 4:
	{
		std::cout << "Введите новые данные:\n";
		tmp_date = input_date(is_correct_date);
		if (!is_correct_date) throw "Неверная дата.";
	}
		break;
	case 5: {
		bool a[3];
		cout << "Введите индекс атрибута:\n";
		do {
			cout << "Только на чтение:\n1-Да\n0-Нет\n";
			cin >> tmp_int;
		} while ((tmp_int<0) || (tmp_int>1));
		a[0] = tmp_int;
		do {
			cout << "Скрытый:\n1-Да\n0-Нет\n";
			cin >> tmp_int;
		} while ((tmp_int<0) || (tmp_int>1));
		a[1] = tmp_int;
		do {
			cout << "Системный:\n1-Да\n0-Нет\n";
			cin >> tmp_int;
		} while ((tmp_int<0) || (tmp_int>1));
		a[2] = tmp_int;
		(*it).setAttribute(a);
	}
			break;
	case 6: {
		std::cout << "Введите новые данные:\n";
		tmp_bool = (*it).getDeleted();
		(*it).setDeleted(!tmp_bool); 
	}
		break;
	case 7: {
		std::cout << "Введите новые данные:\n";
		cin >> tmp_int;
		try {
			(*it).setNumSectors(tmp_int);
			break;
		}
		catch (char *s) {
			throw s;
		}
	}
		break;
	default:
		std::cout << "\nНеверный ввод, введите число от 0 до 7\n";
	
	}
	std::cout << "Данные изменены.\n";
}

//сохранить запись в текстовый файл
void save_file(vector<file> &v) {
	string fname;
	std::cout << "Введите имя файла\n";
	cin >> fname;
	if (fname == "") throw "Имя не должно быть пустым\n";

	ofstream f;
	f.open(fname, ios::out);
	for (vector<file>::iterator it = v.begin(); it != v.end(); it++)
	{
		string del;
		(*it).getDeleted() ? del = "помечен" : del = "непомечен";
		f << (*it).getDirectory() << "\t" << (*it).getFilename() << "\t" << (*it).getExtention() << "\t\t" 
			<< date_to_str((*it).getDateTime()) << "\t" << (*it).getAttribute() << "\t" << del
			<< "\t" << (*it).getNumSectors() << endl;
		
		//f.write((char*)&(it), sizeof(file));
	}
}

void export_vector(vector<file> v) {
	char print_choise;
	std::cout << "1.На экран\n2.В файл\n";
	cin >> print_choise;
	switch (print_choise) {
	case '1':print_v(v);
		break;
	case '2':save_file(v);
		break;
	default: std::cout << "\nНеверный ввод\n";
	}
}

//компараторы для сортировки и бинарного поиска
bool compare_direct_rec(file a, file b) {
	return (a.getDirectory() < b.getDirectory() );
}
bool compare_direct(file a, string b) {
	return a.getDirectory() < b;
}

bool compare_name_rec(file a, file b) {
	return (a.getFilename() < b.getFilename());
}
bool compare_name(file a, string b) {
	return (a.getFilename() < b);
}

bool compare_date_rec(file a, file b) {
	return(a.getDateTime().year < b.getDateTime().year) ||
		((a.getDateTime().year == b.getDateTime().year) && (a.getDateTime().month < b.getDateTime().month)) ||
		((a.getDateTime().year == b.getDateTime().year) && (a.getDateTime().month == b.getDateTime().month)
			&& (a.getDateTime().day < b.getDateTime().day));;
}
bool compare_date(file a, date_time b) {
	return(a.getDateTime().year < b.year) ||
		((a.getDateTime().year == b.year) && (a.getDateTime().month < b.month)) ||
		((a.getDateTime().year == b.year) && (a.getDateTime().month == b.month) && (a.getDateTime().day < b.day));
}

bool compare_del_rec(file a, file b) {
	return(a.getDeleted()<b.getDeleted());
}
bool compare_del(file a, bool b) {
	return (a.getDeleted()<b);
}

vector<file> search(vector<file> &v) {
	vector<file> results;
	vector<file>::iterator v_it = v.begin();
		
	int choise, type;
	do
	{
		std::cout << "Выберите критерий поиска:\n1.Каталог\n2.Название\n3.Дата создания\n4.Признак удаления\n";
		cin >> choise;
	} while (choise < 1 || choise>4);
	do
	{
		std::cout << "Выберите алгоритм поиска:\n1.Последовательный\n2.Двоичный\n";
		cin >> type;
	} while (type < 1 || type>2);
	std::cout << "Введите запрос:";
	switch (type)
	{
	case 1:
	{
		switch (choise)
		{
		case 1:
		{
			string strquery;
			cin >> strquery;
			while (v_it != v.end())
			{
				if ((*v_it).getDirectory() == strquery)
					results.push_back(*v_it);
				v_it++;
			}
		} break;
		case 2:
		{
			string strquery;
			cin >> strquery;
			while (v_it != v.end())
			{
				if ((*v_it).getFilename() == strquery) 
					results.push_back(*v_it);
				v_it++;
			}
		} break;
		case 3:
		{
			bool is_correct;
			date_time datequery;
			do {
				datequery = input_date(is_correct);
			} while(!is_correct);
			while (v_it != v.end())
			{
				if( ( (*v_it).getDateTime().day == datequery.day) && ((*v_it).getDateTime().month == datequery.month) &&
					((*v_it).getDateTime().year == datequery.year))
					results.push_back(*v_it);
				v_it++;
			}
		} break;
		case 4:
		{
			int answ;
			bool delquery;
			do {
				std::cout << "0-Помечен\n1-Не помечен";
				cin >> answ;
			} while ((answ<0)||(answ>1));
			delquery = answ;
			while (v_it != v.end())
			{
				if ((*v_it).getDeleted() == delquery);
				v_it++;
			}
		} break;
		}

	} break;
	case 2:
	{
		switch (choise)
		{
		case 1:
		{
			string strquery;
			cin >> strquery;
			sort(v.begin(), v.end(), compare_direct_rec);
			v_it = lower_bound(v.begin(), v.end(), strquery, compare_direct);
			while ((*v_it).getDirectory()==strquery) {
				results.push_back(*v_it);
				v_it++;
			}	
		} break;
		case 2:
		{
			string strquery;
			cin >> strquery;
			sort(v.begin(), v.end(), compare_name_rec);
			v_it = lower_bound(v.begin(), v.end(), strquery, compare_name);
			results.push_back(*v_it);
		} break;
		case 3:
		{
			bool is_correct;
			date_time datequery;
			do {
				datequery = input_date(is_correct);
			} while (!is_correct);
			sort(v.begin(), v.end(), compare_date_rec);
			v_it = lower_bound(v.begin(), v.end(), datequery, compare_date);
			while( ((*v_it).getDateTime().day == datequery.day && (*v_it).getDateTime().month == datequery.month &&
				(*v_it).getDateTime().year == datequery.year) ) {
				results.push_back(*v_it);
				v_it++;
			}
		} break;
		case 4:
		{
			int answ;
			bool delquery;
			do {
				std::cout << "0-Помечен\n1-Не помечен";
				cin >> answ;
			} while ((answ<0) || (answ>1));
			delquery = answ;
			sort(v.begin(), v.end(), compare_del_rec);
			v_it = lower_bound(v.begin(), v.end(), delquery, compare_del);
			while ((*v_it).getDeleted()==delquery) {
				results.push_back(*v_it);
				v_it++;
			}
		} break;
		}
	} break;
	}
	return results;
}
