#include "includes/ArrayStackTemplate.h"
#include "includes/Student.h"

int main()
{
    ArrayStack<double> stack;
    for (int i = 1; i < 10; i++)
    {
        stack.push(i);
    }
    stack.display();
    stack.pop();
    stack.pop();
    stack.pop();
    stack.display();

    ArrayStack<Student> stack2;
    stack2.push(Student(20183423, "최한나", "AI융합학부"));
    stack2.push(Student(20161649, "이진규", "AI융합학부"));
    stack2.push(Student(20173423, "홍길동", "컴퓨터공학과"));
    stack2.display();
    stack2.pop();
    stack2.pop();
    stack2.pop();
    stack2.display();
    return 0;
}