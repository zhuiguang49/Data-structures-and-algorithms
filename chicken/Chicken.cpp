#include <iostream>
#include <cstring>

using namespace std;

class Chicken
{
    private:
        int age = 24;
        char *name = nullptr;
    public:
        Chicken() : age(24), name(nullptr) {}
        Chicken(int _age) : age(_age), name(nullptr) {}
        Chicken(int _age, const char *_name) : age(_age) 
        {
            if (_name != nullptr) 
            {
                int len = strlen(_name) + 1;
                name = new char[len];
                strcpy(name, _name); 
            }
        }
        Chicken(const Chicken &other) : age(other.age) 
        {
            if (other.name != nullptr) 
            {
                int len = strlen(other.name) + 1;
                name = new char[len];
                strcpy(name, other.name);
            }
            else
            {
                name = nullptr;
            }
        }
        Chicken &operator=(const Chicken &other)
        {
            if (this == &other) 
                return *this;
            delete[] name;
            age = other.age;
            if (other.name != nullptr)
            {
                int len = strlen(other.name) + 1;
                name = new char[len];
                strcpy(name, other.name);
            }
            else
            {
            name = nullptr;
            }
            return *this; 
        }
        ~Chicken()
        {
            delete[] name;
        }
        void setAge(int _age)
        {
            age = _age;
        }
        void setName(const char *_name)
        {
            delete[] name; 
            if (_name != nullptr)
            {
                int len = strlen(_name) + 1;
                name = new char[len];
                strcpy(name, _name);
            }
            else
            {
                name = nullptr;
            }
        }
        const char *getName() const
        {
            return name;
        }
        const int &getAge() const
        {
            return age;
        }
};

int main()
{
    Chicken c1(24, "Kunkun");
    Chicken c2 = c1; 
    Chicken c3;
    c3 = c1; 
    cout << "Hi, everyone! My name is " << c1.getName() << ", I am " << c1.getAge() << " years old." << endl;
    cout << "Hi, everyone! My name is " << c2.getName() << ", I am " << c2.getAge() << " years old." << endl;
    cout << "Hi, everyone! My name is " << c3.getName() << ", I am " << c3.getAge() << " years old." << endl;
    return 0;
}
