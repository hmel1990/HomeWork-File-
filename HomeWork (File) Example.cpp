#include <iostream>
#include <fstream>    // ofstream, ifstream
#include <codecvt>    // работа с кодировками (запись иероглифов в файл)
#include <windows.h>
#include <iomanip>    // setw
#include <io.h>       // _A_ARCH and others
#include <direct.h>
using namespace std;

class FileStreamsDemo {
public:
	static const char* path; // file.txt в папке с проектом

	////////////////////////////////////////////////////////////////////////

	static void TextModeExample() {
		int choice;
		cout << "1. Write\n2. Read\n";
		cin >> choice;
		if (choice == 1)
		{
			ofstream out(path); // создаём выходной файловый поток и присоединяем к нему файл, который открывается на запись в текстовом режиме
			if (!out.is_open()) // если открытие файла завершилось неудачей - выходим
			{
				cout << "File Open Error (WRITE)\n";
				return;
			}
			out << 10 << ' ' << 123.5; // сохраняем данные в файл
			out << "This is a text file";
			out.close(); // закрываем файловый поток
		}
		else {
			int i;
			double d;
			char str[10];

			ifstream in(path); // создаём входной файловый поток и присоединяем к нему файл, который открывается на чтение в текстовом режиме
			if (!in.is_open()) // если открытие файла завершилось неудачей - выходим
			{
				cout << "File Open Error (READ)\n";
				return;
			}
			in >> i >> d; // считываем из файла данные в переменные
			cout << i << "\n";
			cout << d << "\n";
			while (!in.eof()) // цикл продолжается до тех пор, пока не наступит конец файла
			{
				in >> str; // считываем строку из файла по одному слову за одну итерацию цикла
				cout << str << ' ';
			}
			in.close(); // закрываем файловый поток
		}

		cout << "\nTextModeExample DONE!\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void CharByCharExample() {
		// создаём первый файл, из которого данные будут посимвольно читаться и записываться во второй файл
		ofstream create;
		create.open("C:\\1\\source.txt", ios::out | ios::trunc);
		// MODES:
		// http://www.cplusplus.com/reference/ios/ios_base/openmode/
		create << "This is a test string!";
		create.close();

		// создаём выходной файловый поток и присоединяем к нему файл, который открывается на запись в текстовом режиме
		ofstream out; // OUT OF PROGRAM - TO THE FILE
		out.open(path, ios::out | ios::trunc);

		// создаём входной файловый поток и присоединяем к нему файл, который открывается на чтение в текстовом режиме
		ifstream in; // IN PROGRAM - FROM THE FILE
		in.open("C:\\1\\source.txt", ios::in);
		if (!in) // если открытие файла завершилось неудачей - выходим
		{
			cout << "CharByCharExample Error!\n";
			return;
		}

		while (!in.eof()) // цикл продолжается до тех пор, пока не наступит конец файла
		{
			char s;
			in.get(s); // из входного потока считываем посимвольно текстовую информацию
			if (in.eof()) break; // если файл закончился - экстренно выходим
			cout << s; // выводим на экран считанный символ
			out.put(s); // записываем в выходной поток считанный символ
		}
		// закрываем файловые потоки
		out.close();
		in.close();

		cout << "\nCharByCharExample DONE!\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void StringByStringExample() {
		// создаём первый файл, из которого данные будут посимвольно читаться и записываться во второй файл
		// ofstream create;
		// create.open("C:\\1\\source.txt", ios::out | ios::trunc);
		// create << "This is a test string!";
		// create.close();

		// создаём выходной файловый поток и присоединяем к нему файл, который открывается на запись в текстовом режиме
		ofstream out; // OUT OF PROGRAM - TO THE FILE
		out.open(path, ios::out | ios::trunc);

		// создаём входной файловый поток и присоединяем к нему файл, который открывается на чтение в текстовом режиме (файл должен существовать)
		ifstream in; // IN PROGRAM - FROM THE FILE
		in.open("C:\\1\\source.txt", ios::in);
		if (!in) // если открытие файла завершилось неудачей - выходим
		{
			cout << "StringByStringExample Error!\n";
			return;
		}
		while (!in.eof()) // цикл продолжается до тех пор, пока не наступит конец файла
		{
			char buf[_MAX_PATH];
			in.getline(buf, _MAX_PATH);
			if (!in.fail())
			{
				cout << buf << "\n";
				out << buf << "\n";
			}
		}
		// закрываем файловые потоки
		out.close();
		in.close();

		cout << "\nStringByStringExample DONE!\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void StringReadingExample() {
		ofstream book_file("BOOKINFO.DAT");

		book_file << "Язык программирования C++, " << "четвёртая редакция" << "\n";
		book_file << "Издательство: Фабула" << "\n";
		book_file << "Цена: 1279.95 гривен" << "\n";

		ifstream input_file("BOOKINFO.DAT");
		char one[64], two[64], three[64];

		/*
		input_file >> one; // читаем по одному слову
		input_file >> two;
		input_file >> three;
		*/

		
		input_file.getline(one, sizeof(one)); // читаем по одной строке
		input_file.getline(two, sizeof(two));
		input_file.getline(three, sizeof(three));

		cout << one << "\n";
		cout << two << "\n";
		cout << three << "\n";
		

		char line[64];
		while (!input_file.eof()) {
			input_file.getline(line, sizeof(line));
			cout << line << "\n";
		}

		cout << "\nStringReadingExample DONE!\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void BinaryArrayExample() {
		const int size = 10;
		int A[size] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

		// открывается  файл на запись в бинарном режиме: если файл не существует - он будет создан, если файл существует - он будет усечён до нулевой длины
		ofstream out("array.txt", ios::binary | ios::trunc | ios::out);

		out.write((char*)&size, sizeof(size)); // в файл сохраняется размерность массива
		out.write((char*)A, sizeof(A)); // в файл сохраняется массив
		out.close(); // файловый поток закрывается

		// открывается  файл на чтение в бинарном режиме: при этом файл должен существовать
		ifstream in("array.txt", ios::binary | ios::in);
		int count;
		in.read((char*)&count, sizeof(count)); // считываем размер массива в переменную

		int* p = new int[count]; // выделяем память под массив данных
		in.read((char*)p, sizeof(int) * count); // считываем из файла массив
		in.close(); // файловый поток закрывается

		for (int i = 0; i < count; i++)
		{
			cout << p[i] << '\t'; // показываем на экран считанный массив
		}
		delete[] p;

		cout << "\nBinaryArrayExample DONE!\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void StructToFileExample() {
		struct Student {
			char name[20];
			char surname[20];
			int age;
			double average;
		};

		int n;
		cout << "1. Write\n2. Read\n";
		cin >> n;
		if (n == 1) {
			ofstream out("student.txt", ios::binary | ios::out | ios::trunc); // создаём выходной файловый поток и присоединяем к нему файл, который открывается на запись
			if (!out.is_open()) // если открытие файла завершилось неудачей - выходим
			{
				cout << "StructToFileExample Error (WRITE)\n";
				return;
			}

			int a = 100;
			double d = 40.5;
			bool b = true;

			Student st;
			st.age = 35;
			st.average = 11.5;
			strcpy_s(st.name, 10, "John");
			strcpy_s(st.surname, 10, "Doe");

			// http://www.cplusplus.com/reference/istream/istream/seekg/
			// http://www.cplusplus.com/reference/ostream/ostream/seekp/

			// естественно, на практике не нужно будет писать данные в файл такими "прыжками" - код просто демонстрирует функции seekp seekg
			out.seekp(sizeof(Student), ios::beg); // смещаем файловый указатель в выходном потоке на размер структуры от начала	
			out.write((char*)&a, sizeof(a)); // записываем int-значение в поток
			out.write((char*)&b, sizeof(b)); // записываем bool-значение в поток	

			out.seekp(0, ios::beg); // смещаем файловый указатель в выходном потоке в начало
			out.write((char*)&st, sizeof(st)); // записываем структуру в поток

			out.seekp(5, ios::cur); // смещаем файловый указатель в выходном потоке на 5 позиций вперед от текущей позиции
			out.write((char*)&d, sizeof(d)); // записываем double-значение в поток
			out.close(); // закрываем выходной файловый поток
		}
		else {
			ifstream in("student.txt", ios::binary | ios::in); // создаём входной файловый поток и присоединяем к нему файл, который открывается на чтение в текстовом режиме
			if (!in.is_open()) // если открытие файла завершилось неудачей - выходим
			{
				cout << "StructToFileExample Error (READ)\n";
				return;
			}

			in.seekg(sizeof(Student), ios::beg); // смещаем файловый указатель во входном потоке на размер структуры  от начала	
			int a;
			in.read((char*)&a, sizeof(a)); // считываем из потока int-значение
			cout << "\n" << a << "\n" << "\n";
			bool b;
			in.read((char*)&b, sizeof(b)); // считываем из потока bool-значение
			cout << b << "\n" << "\n";
			in.seekg(0, ios::beg); // смещаем файловый указатель во входном потоке на начало
			Student st;
			in.read((char*)&st, sizeof(Student)); // считываем из потока структуру
			cout << st.name << "\n" << st.surname << "\n" << st.age << "\n" << st.average << "\n" << "\n";
			in.seekg(-8, ios::end); // смещаем файловый указатель во входном потоке на 8 позиций назад от конца
			double d;
			in.read((char*)&d, sizeof(d)); // считываем из потока double-значение
			cout << d << "\n";
			in.close(); // закрываем входной поток
		}

		cout << "\nStructToFileExample DONE!\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void FileSizeExample() {
		ifstream in("C:\\1\\1.jpg", ios::binary | ios::in);
		if (!in) {
			cout << "FileSizeExample Error!\n";
			return;
		}

		in.seekg(0, ios::end);
		cout << "Size of file: " << in.tellg() << " B\n\n";
		in.close();

		cout << "\nFileSizeExample DONE!\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void UnicodeExample() {
		setlocale(0, "");
		ofstream outFile(path, ios::binary);

		if (!outFile) {
			cout << "Ошибка открытия файла для записи!\n";
			return;
		}

		wstring_convert<codecvt_utf8<wchar_t>> converter;
		string utf8str = converter.to_bytes(L"иероглифы: 你好, 世界");

		outFile.write(utf8str.c_str(), utf8str.size());

		outFile.close();

		cout << "Данные успешно записаны в файл.\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void Practice() {
		cout << "Напишите программу, которая показывает на экране консоли меню,\n";
		cout << "состоящее из двух пунктов. При выборе пункта 1 в двоичный файл\n";
		cout << "записывается (либо дописывается в конец) один объект классового\n";
		cout << "типа Person. При выборе пункта 2 - на экране отображается\n";
		cout << "содержимое полей всех объектов из этого файла.\n";
	}

	////////////////////////////////////////////////////////////////////////

	static void ShowFilesInDirectory(const char* path, const char* mask) {
		// FILE ATTRIBUTES:

		/*	_A_ARCH
			Archive.Set whenever the file is changedand cleared by the BACKUP command.Value: 0x20.

			_A_HIDDEN
			Hidden file.Not generally seen with the DIR command, unless you use the / AH option.Returns information about normal files and files that have this attribute.Value: 0x02.

			_A_NORMAL
			Normal.File has no other attributes set and can be read or written to without restriction.Value: 0x00.

			_A_RDONLY
			Read - only.File cannot be opened for writingand a file that has the same name cannot be created.Value: 0x01.

			_A_SUBDIR
			Subdirectory.Value: 0x10.

			_A_SYSTEM
			System file.Not ordinarily seen with the DIR command, unless the / A or /A:S option is used.Value : 0x04.

			*/

			// system("mode con cols=150 lines=50");

		const int ATTRIB_LENGTH = 32;

		char* fullpath = new char[FILENAME_MAX];

		strcpy_s(fullpath, FILENAME_MAX - 1, path);
		strcat_s(fullpath, FILENAME_MAX - 1, mask);

		// https://docs.microsoft.com/en-us/cpp/c-runtime-library/filename-search-functions?view=vs-2019
		_finddata_t fileinfo;

		long long snapshot = _findfirst(fullpath, &fileinfo);
		long long success = snapshot;

		while (success != -1) {
			if (strcmp(fileinfo.name, ".") != 0 &&
				strcmp(fileinfo.name, "..") != 0) {
				if (fileinfo.attrib & _A_SUBDIR) {
					// cout << "Folder! - ";
					// cout << fileinfo->name << "\n";

					char newpath[FILENAME_MAX];
					strcpy_s(newpath, FILENAME_MAX - 1, path);
					strcat_s(newpath, FILENAME_MAX - 1, fileinfo.name);
					strcat_s(newpath, FILENAME_MAX - 1, "\\");
					ShowFilesInDirectory(newpath, mask);
				}
				else {
					// total++;
					char attributes[ATTRIB_LENGTH + 1];
					_itoa_s(fileinfo.attrib, attributes, ATTRIB_LENGTH, 2);
					printf("%032s - ", attributes);
					cout << path << fileinfo.name << "\n";
				}
			}
			success = _findnext(snapshot, &fileinfo);
		}

		_findclose(snapshot);

		delete[] fullpath;
	}

	////////////////////////////////////////////////////////////////////////

	static long long DirectorySize(const char* path) {
		long long size = 0;
		char find[MAX_PATH];
		strcpy_s(find, MAX_PATH, path);
		strcat_s(find, MAX_PATH, "\\*.*");
		_finddata_t f;
		long long handle = _findfirst(find, &f);
		long long result = handle;
		while (result != -1) {
			if (strcmp(f.name, ".") == 0 || strcmp(f.name, "..") == 0)
			{
				result = _findnext(handle, &f);
				continue;
			}
			if (f.attrib & 1 << 4) // f.attrib & _A_SUBDIR
			{
				strcpy_s(find, MAX_PATH, path);
				strcat_s(find, MAX_PATH, "\\");
				strcat_s(find, MAX_PATH, f.name);
				size += DirectorySize(find);
			}
			else
				size += f.size;
			result = _findnext(handle, &f);
		}
		_findclose(handle);
		return size;
	}

	////////////////////////////////////////////////////////////////////////

	static void CreateRenameRemove() {
		setlocale(0, "");
		cout << "Введите путь к файлу для удаления: ";
		char pathname[256];
		cin >> pathname;
		if (remove(pathname) == -1) perror("Open: ");
		else cout << "Файл успешно удалён!\n";

		cout << "Введите путь к папке для создания: ";
		cin >> pathname;
		if (_mkdir(pathname) == -1) perror("Open: ");
		else cout << "Папка успешно создана!";

		cout << "Введите путь к папке для удаления: ";
		cin >> pathname;
		if (_rmdir(pathname) == -1) cout << "Ошибка удаления папки!";
		else cout << "Папка успешно удалена!";

		char oldpath[MAX_PATH], newpath[MAX_PATH];
		cout << "Введите путь к файлу, который требуется переименовать: ";
		cin >> oldpath;
		cout << "Введите новый путь (и/или имя файла): ";
		cin >> newpath;
		if (rename(oldpath, newpath) == -1) perror("Open: ");
		else cout << "Файл успешно переименован!";
	}

	////////////////////////////////////////////////////////////////////////

	static void LogicalDrives() {
		cout << "Drives list:\n";
		int drivesBitMask = GetLogicalDrives();
		char drive = 'A';
		char root[4] = {};
		int type = 0;

		while (drivesBitMask) {
			if (drivesBitMask & 1) {
				cout << "Drive " << drive << ": is present. ";
				sprintf_s(root, "%c:\\", 256, drive);
				type = GetDriveTypeA(root);
				switch (type) {
				case DRIVE_UNKNOWN:
					cout << "Drive type is unknown!";
					break;
				case DRIVE_CDROM:
					cout << "Drive is CD-ROM";
					break;
				case DRIVE_REMOTE:
					cout << "Drive is Remote disk";
					break;
				case DRIVE_REMOVABLE:
					cout << "Drive is Removable";
					break;
				case DRIVE_NO_ROOT_DIR:
					cout << "Root path to drive is invalid";
					break;
				case DRIVE_FIXED:
					cout << "Drive is fixed. HDD, for example";
					break;
				case DRIVE_RAMDISK:
					cout << "Drive is a RAM disk";
					break;
				}

				cout << "\n";
			}

			drive++;
			drivesBitMask >>= 1;
		}
	}

	////////////////////////////////////////////////////////////////////////

	static void Test() {
		// TextModeExample();
		// CharByCharExample();
		// StringByStringExample();
		// StringReadingExample();
		// BinaryArrayExample();
		// StructToFileExample();
		// FileSizeExample();
		UnicodeExample();
		// Practice();
		// ShowFilesInDirectory("C:\\1\\", "*.*");
		// cout << "Directory size: " << DirectorySize("C:\\1\\") / 1024 / 1024 << " MB\n";
		// CreateRenameRemove();
		// LogicalDrives();
	}
};

const char* FileStreamsDemo::path = "file.txt";

int main() {
	system("title File Streams CPP");
	system("color 0F");

	FileStreamsDemo::Test();
	Sleep(INFINITE);
}