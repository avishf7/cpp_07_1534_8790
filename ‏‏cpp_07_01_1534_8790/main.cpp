#include "main.h"
using namespace std;
int main()
{
	string fileName;
	char* f;

	cout << "Enter the file name:" << endl;
	cin >> fileName;

	openF(fileName);

	return 0;
}
void openF(string fName)
{
	fstream newFile(fName, ios::binary | ios::out);

	if (!newFile)
		throw "faild to open file";

	newFile.write((char*)&Student::emptyStudent._id, sizeof(int));
	for (int i = 0; i < 10; ++i)
		newFile.write((char*)&Student::emptyStudent, sizeof(Student));
	newFile.close();
}
