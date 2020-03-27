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
	cout << "Enter device: ";
	cin >> find;
	if (find == "?" || find == "$" || find == "^" || find == "*" || find == "(" || find == ")" || find == ":" || find == "_" || find == "+")
	{
		cout << "Error. wut is this symbol?" << endl;
		system("pause");
		return 0;
	}
	else
	{
		string checkFind = find;
		cmatch result;
		regex regular("garbage");
		if (regex_search(checkFind.c_str(), result, regular))
		{
			cout << "" << endl;
			system("pause");
			return 0;
		}
	}
	for (auto& p : fs::directory_iterator("logs"))
	{
		string dock;
		fstream dockRead(p.path(), std::ios::in);
		while (getline(dockRead, dock))
		{
			string str = dock;
			cmatch result;
			regex regular("([\\d]+)""(:)""(.+)""(:)""([\\d]+)");
			if (regex_search(str.c_str(), result, regular))
			{
				if (result[3] == find)
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
					regex regular("([\\d]+)""(:)""(.+)""(:)""([\\d]+)");
					if (regex_search(str.c_str(), result, regular))
					{
						cout << result[1] << "  " << result[3] << "  " << "result: " << result[5] << endl;
					}
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