#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

// ------------------- Abstract Employee -------------------
class Employee {
protected:
    string name;
    int id;
    string position;
    int experience; // months
    double salary;

public:
    Employee(string n, int i, string pos, int exp)
        : name(n), id(i), position(pos), experience(exp), salary(0) {
    }

    virtual void calculateSalary() = 0;

    double getSalary() const { return salary; }

    virtual void print() const {
        cout << "Name: " << name << ", ID: " << id
            << ", Position: " << position
            << ", Experience: " << experience
            << ", Salary: " << salary << endl;
    }

    virtual ~Employee() {}
};

// ------------------- Positions -------------------
class CIO : public Employee {
public:
    CIO(string n, int i, int exp) : Employee(n, i, "CIO", exp) {}
    void calculateSalary() override { salary = 10000 + experience * 50; }
};

class ProjectManager : public Employee {
public:
    ProjectManager(string n, int i, int exp) : Employee(n, i, "PM", exp) {}
    void calculateSalary() override { salary = 8000 + experience * 40; }
};

class Developer : public Employee {
protected:
    string level;
    string technology;
public:
    Developer(string n, int i, string pos, int exp, string lvl, string tech)
        : Employee(n, i, pos, exp), level(lvl), technology(tech) {
    }
};

class Backend : public Developer {
public:
    Backend(string n, int i, int exp, string lvl, string tech)
        : Developer(n, i, "BD", exp, lvl, tech) {
    }

    void calculateSalary() override {
        double base = 3000;
        if (level == "Middle") base += 1000;
        else if (level == "Senior") base += 2000;
        salary = base + experience * 30;
    }
};

class Frontend : public Developer {
public:
    Frontend(string n, int i, int exp, string lvl, string tech)
        : Developer(n, i, "FD", exp, lvl, tech) {
    }

    void calculateSalary() override {
        double base = 2800;
        if (level == "Middle") base += 900;
        else if (level == "Senior") base += 1800;
        salary = base + experience * 25;
    }
};

class Engineer : public Employee {
protected:
    string level;
public:
    Engineer(string n, int i, string pos, int exp, string lvl)
        : Employee(n, i, pos, exp), level(lvl) {
    }
};

class Database : public Engineer {
public:
    Database(string n, int i, int exp, string lvl)
        : Engineer(n, i, "DB", exp, lvl) {
    }

    void calculateSalary() override {
        double base = 3500;
        if (level == "Middle") base += 1000;
        else if (level == "Senior") base += 2000;
        salary = base + experience * 30;
    }
};

class DevOps : public Engineer {
public:
    DevOps(string n, int i, int exp, string lvl)
        : Engineer(n, i, "DE", exp, lvl) {
    }

    void calculateSalary() override {
        double base = 3200;
        if (level == "Middle") base += 900;
        else if (level == "Senior") base += 1800;
        salary = base + experience * 25;
    }
};

class Tester : public Employee {
protected:
    string level;
public:
    Tester(string n, int i, int exp, string lvl)
        : Employee(n, i, "TST", exp), level(lvl) {
    }

    void calculateSalary() override {
        double base = 2500;
        if (level == "Middle") base += 500;
        else if (level == "Senior") base += 1000;
        salary = base + experience * 20;
    }
};

// ------------------- Custom Priority Queue -------------------
class EmployeeQueue {
private:
    vector<Employee*> queue;  // store pointers
public:
    void push(Employee* e) {
        queue.push_back(e);
        sort(queue.begin(), queue.end(), [](const Employee* a, const Employee* b) {
            return a->getSalary() > b->getSalary(); // descending salary
            });
    }

    void pop() {
        if (!queue.empty()) {
            queue.erase(queue.begin());
        }
    }

    void print() {
        for (auto e : queue) e->print();
    }

    bool empty() { return queue.empty(); }

    size_t size() const { return queue.size(); }
};