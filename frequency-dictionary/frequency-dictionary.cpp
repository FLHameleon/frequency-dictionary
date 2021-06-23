// Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <fstream>
#include <string>
#include <iostream>
#include <cstring> 
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>
#include <set>
#include <iterator>
#include<algorithm>

#include <windows.h>
using namespace std;

void sort_po_ybivaniy(string slovar)
{
	vector<pair<string, int>> ves_slov_test;
	//ves_slov_test.push_back(make_pair(word,n));
	vector<string> ves_slovar, otsort_slovar;
	int chethik, nom_slova, max_kolih = 0, nom_bykvi;
	string abzac, ceslo_str, slovo;

	ifstream in(slovar); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, abzac))
		{
			ves_slovar.push_back(abzac);
		}
	}
	in.close();     // закрываем файл


	for (nom_slova = 0; nom_slova < ves_slovar.size(); nom_slova++)//Заполняем парный вектор
	{
		nom_bykvi = ves_slovar[nom_slova].find(" ");
		ceslo_str = ves_slovar[nom_slova].substr(nom_bykvi + 1, ves_slovar[nom_slova].length() - nom_bykvi - 1);
		slovo = ves_slovar[nom_slova].substr(0, nom_bykvi);;

		ves_slov_test.push_back(make_pair(slovo, atoi(ceslo_str.c_str())));
		/*if (max_kolih < atoi(ceslo_str.c_str()))
			max_kolih = atoi(ceslo_str.c_str());*/

	}


	sort(ves_slov_test.begin(), ves_slov_test.end(), [](pair<string, int> a, pair<string, int> b) {return a.second > b.second; });




	ofstream out2;          // записываем окончательный результат в частотный словарь
	out2.open(slovar);
	if (out2.is_open())
	{
		nom_slova = 0;

		while (nom_slova < ves_slovar.size())
		{
			out2 << ves_slov_test[nom_slova].first + " " + to_string(ves_slov_test[nom_slova].second) + '\n';
			nom_slova++;
		}
	}
	out2.close();

}



void filter_slovar(string slovar, string black_list, string otfiltrovano)
{
	int nom_slova, nom_bykvi, hethik;
	vector<string> ispravl_prototip, ves_slovar;
	string filter;
	string ves_text, abzac, slovo;

	ifstream in(slovar); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, abzac))
		{
			ves_slovar.push_back(abzac);
		}
	}
	in.close();     // закрываем файл


	ifstream in2(black_list); // окрываем файл для чтения
	if (in2.is_open())
	{
		while (getline(in2, abzac))
		{
			filter += abzac + ' ';
		}
	}
	in.close();     // закрываем файл

	//cout << filter.find("оказывается");








	for (nom_slova = 0; nom_slova < ves_slovar.size(); nom_slova++)//происходит фильтрация слова из частотного словаря сопоставляются со словами черного списка
	{


		nom_bykvi = ves_slovar[nom_slova].find(" ");
		slovo = ves_slovar[nom_slova].substr(0, nom_bykvi);


		if (slovo.length() > 2 && filter.find(" " + slovo + " ") == string::npos)//4294967295 !!!!!!!!
		{
			ispravl_prototip.push_back(ves_slovar[nom_slova]);
		}

	}




	ofstream out2;          // записываем окончательный результат в частотный словарь
	out2.open(otfiltrovano);
	if (out2.is_open())
	{
		hethik = 0;

		while (hethik < ispravl_prototip.size())
			out2 << ispravl_prototip[hethik++] + '\n';
	}
	out2.close();




}



void rez_shit_spisok_slov(string istohnik_str, string hastotn_slovar_str)//Создание частотного словаря
{

	////////////////////////////////////////////////Создание переменных
	string abzac, ves_text, str_bykv_i_prob = "", slovo;

	vector<string> list_vseh_slov, hastotniy_slovar;////Векторы строк перовой все слова что есть в тексте, во второй частотный словарь
	int hethik = 0, hethik2 = 0, kolih_slov = 0;


	ves_text = "";

	ifstream in(istohnik_str); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, abzac))
		{
			ves_text += abzac + ' ';
		}
	}
	in.close();     // закрываем файл


	transform(ves_text.begin(), ves_text.end(), ves_text.begin(), tolower); // Делаем все буквы маленькими

	for (int i = 0; i < ves_text.length(); i++)
		if ((int(ves_text[i]) < int('а') || int(ves_text[i]) > int('я')) && (int(ves_text[i]) < int('a') || int(ves_text[i]) > int('z')) && (ves_text[i] != ' ')) //избавляемся ото всех знаков препинания и цифр
		{
			ves_text.erase(i, 1);
			i--;
		}

	str_bykv_i_prob = ves_text;



	///////////////////////////////////////////////////////////////////////////////для разбиения текста по пробелу вачале запишем в фаил

	ofstream out;          // поток для записи
	out.open(hastotn_slovar_str); // окрываем файл для записи
	if (out.is_open())
	{
		out << str_bykv_i_prob;
	}
	out.close();


	slovo = "";


	set<string> set_poly_slovar; //////////////////////Создаем множество в котором избавимся от повторений и отсортируем все слова

	ifstream in2(hastotn_slovar_str); // окрываем файл для чтения и записываем в множество икключая повторения и сортируем
	if (in2.is_open())
	{

		while (in2 >> slovo)
		{

			set_poly_slovar.insert(slovo);////добавление в множество отсер повторений
			list_vseh_slov.push_back(slovo);////добавление в первый массив строк всех слов
		}

	}

	in2.close();     // закрываем файл

	set<string>::iterator ik;////////все множество записываем во второй массив строк
	hethik = 0;
	for (ik = set_poly_slovar.begin(); ik != set_poly_slovar.end(); ++ik)
	{
		hastotniy_slovar.push_back(*ik);
		hethik++;
	}

	//hastotniy_slovar = filter(hastotniy_slovar);
	//list_vseh_slov = filter(list_vseh_slov);

	hethik = 0;
	while (hethik < hastotniy_slovar.size())///////////////считаем количество каждого слова в тексте
	{
		hethik2 = 0;
		kolih_slov = 0;
		while (hethik2 < list_vseh_slov.size())
		{
			if (hastotniy_slovar[hethik] == list_vseh_slov[hethik2])
				kolih_slov++;
			hethik2++;

		}
		hastotniy_slovar[hethik] += (' ' + to_string(kolih_slov) + '\n');/////вносим даные через пробел во второй массив строк
		hethik++;
	}

	ofstream out2;          // записываем окончательный результат в частотный словарь
	out2.open(hastotn_slovar_str); // 
	if (out2.is_open())
	{
		hethik = 0;

		while (hethik < hastotniy_slovar.size())
			out2 << hastotniy_slovar[hethik++];
	}
	out2.close();

}

void cast_slovar(string obr_texsta, string rezyltat_slovar)
{
	string otfiltrovan_slov, black_spisok, rezyltat_posle_filrra;//obr_texsta, rezyltat_slovar, 

	//obr_texsta = "rus_text2.txt";
	//rezyltat_slovar = "chastotniy_slovar.txt";

	black_spisok = "black_list_ANSI.txt";
	rezyltat_posle_filrra = "slovar_posle_filtra.txt";

	rez_shit_spisok_slov(obr_texsta, rezyltat_slovar);//Создание частотного словаря

	filter_slovar(rezyltat_slovar, black_spisok, rezyltat_posle_filrra);//Фильтруем частотный словарь
	sort_po_ybivaniy(rezyltat_posle_filrra);//Сортируем частотный словарь по убыванию


}



int main(int argc, char* argv[])
{

	setlocale(LC_CTYPE, "");
	SetConsoleCP(1251);// установка кодовой страницы win-cp 1251 в поток ввода
	SetConsoleOutputCP(1251); // установка кодовой страницы win-cp 1251 в поток вывода

	string stroka1, stroka2;


	if (argv[1] && argv[2])
	{
		cast_slovar(argv[1], argv[2]);

	}
	else
	{
		cout << "Not a command line" << endl;
		cout << "Enter the name of the encoded text file 1251 (ANSI) ";
		cin >> stroka1;
		cout << "Enter the name of the frequency dictionary ";
		cin >> stroka2;

		cast_slovar(stroka1, stroka2);
	}




	cout << "Program OFF";
	cin.get();
	cin.get();
	return 0;

}
