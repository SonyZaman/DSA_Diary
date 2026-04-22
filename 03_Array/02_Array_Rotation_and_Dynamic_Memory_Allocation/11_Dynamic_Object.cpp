#include <bits/stdc++.h>
using namespace std;

class Student
{
public:
    string name;

    Student(const string &n)
    {
        name = n;
    }

    void show()
    {
        cout << "Name: " << name << endl;
    }
};

int main()
{
    Student *s = new Student("Rahat");

    s->show();

    delete s;   // free object memory

    return 0;
}