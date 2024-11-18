#include <iostream>
#include<fstream>
#include <cstdlib>
#include<string>
using namespace std;


class my_class_file
{
private:
	string filenames[7] = { "who.txt", "where.txt", "when.txt", "with_whom.txt", "what_doing.txt", "what_happened.txt", "moral.txt" };
public:

	static string read_random_line(const string* filenames, int element_of_array)
	{
		ifstream file(filenames[element_of_array]);
		string line;
		srand(time(0));
		int t = rand() % 10 + 1;

		if (!file.is_open()) {
			cout << "Не удалось открыть файл: " << filenames[element_of_array] << "\n";
			return "";
		}

		for (int i = 0; i < t; i++)
		{
			getline(file, line);
		}
		return line;
	}

	void show_funny_expression()
	{
		setlocale(0,"");
		for (int i = 0; i < 7; i++)
		{
			cout << read_random_line(filenames, i)<< " ";
		}
	}

	
};


int main()
{
	my_class_file play;
	play.show_funny_expression();	
}
