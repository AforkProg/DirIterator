#include <iostream>
#include <regex>
#include <string>
#include <filesystem>
#include <fstream>
using namespace std;
namespace fs = filesystem;
int main()
{
	int check = 0;
	string find;
	cout << "Enter device. (For example: device_ABC): ";
	cin >> find;
	if (find == "?" || find == "$" || find == "^" || find == "*" || find == "(" || find == ")" || find == ":" || find == "_" || find == "+")
	{
		cout << "Error. wut is this symbol?" << endl;
		system("pause");
		return 0;
	}
	for (auto& p : fs::directory_iterator("logs"))
	{
		string dock;
		fstream dockRead(p.path(), std::ios::in);
		while (getline(dockRead, dock))
		{
			string str = dock;
			cmatch result;
			regex regular(find);
			if (regex_search(str.c_str(), result, regular))
			{
				check++;
				string path = p.path().string();
				cmatch resultPath;
				regex regPath("(log_)""(.)""(.+)""([\\s])""(.+)""([)])""(.txt)");
				if (regex_search(path.c_str(), resultPath, regPath))
				{
					cout << "date: " << resultPath[3] << " time: " << resultPath[5] << "-";
				}
				string str = dock;
				cmatch result;
				regex regular("([\\d]+)""(:)""([a-z]+)""(.+)""(:)""([\\d]+)");
				if (regex_search(str.c_str(), result, regular))
				{
					cout << result[1] << "  " << result[3] << result[4] << "  " << "result: " << result[6] << endl;
				}
			}

		}
		dockRead.close();
	}
	if (check == 0)
		cout << "Error. This device is not exist\n";
	system("pause");
	return 0;
}