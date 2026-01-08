#include <iostream>
#include "Employee.cpp"
using namespace std;

int main()
{
    EmployeeQueue pq;

    // Create 12 employees
    CIO* c1 = new CIO("Alice", 1, 24);
    c1->calculateSalary();
    CIO* c2 = new CIO("Brian", 2, 18);
    c2->calculateSalary();

    ProjectManager* pm1 = new ProjectManager("Carol", 3, 30);
    pm1->calculateSalary();
    ProjectManager* pm2 = new ProjectManager("David", 4, 12);
    pm2->calculateSalary();

    Backend* bd1 = new Backend("Eve", 5, 36, "Senior", ".Net");
    bd1->calculateSalary();
    Backend* bd2 = new Backend("Frank", 6, 24, "Middle", "Spring");
    bd2->calculateSalary();

    Frontend* fd1 = new Frontend("Grace", 7, 18, "Junior", "React");
    fd1->calculateSalary();
    Frontend* fd2 = new Frontend("Hank", 8, 30, "Middle", "Angular");
    fd2->calculateSalary();

    Database* db1 = new Database("Ivy", 9, 24, "Senior");
    db1->calculateSalary();
    Database* db2 = new Database("Jack", 10, 12, "Junior");
    db2->calculateSalary();

    DevOps* de1 = new DevOps("Karen", 11, 36, "Middle");
    de1->calculateSalary();

    Tester* t1 = new Tester("Leo", 12, 18, "Senior");
    t1->calculateSalary();

    pq.push(c1); pq.push(c2);
    pq.push(pm1); pq.push(pm2);
    pq.push(bd1); pq.push(bd2);
    pq.push(fd1); pq.push(fd2);
    pq.push(db1); pq.push(db2);
    pq.push(de1); pq.push(t1);

    cout << "Employees sorted by salary (descending):\n";
    pq.print();

    delete c1; delete c2;
    delete pm1; delete pm2;
    delete bd1; delete bd2;
    delete fd1; delete fd2;
    delete db1; delete db2;
    delete de1; delete t1;

    return 0;
}