// Line Editor
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "LineHnSLinkedList.h"

class LineEditor : public l_hn_s_linked_list
{
public:
    void Display(std::ostream *os);
    void InsertLine();
    void DeleteLine();
    void ReplaceLine();
    void LoadFile(std::string fname);
    void SaveFile(std::string fname);
};

void LineEditor::Display(std::ostream *os = &std::cout)
{
    int i = 0;
    for (node *p = getHead(); p != nullptr; p = p->getLink(), i++)
    {
        // for 문은 , 을 통해서 여러가지 증가 조건을 동시에 실행시킬 수 있습니다.
        // 여기서는 i를 증가시킴과 동시에 p의 다음 노드를 불러옵니다.
        std::cerr << i << "";
        p->display(os);
    }
}

void LineEditor::InsertLine()
{
    int position;
    std::string line;
    std::cout << " 입력행 번호: ";
    std::cin >> position;
    std::cin.sync();
    std::cin.clear();
    std::cout << " 입력할 내용: ";
    getline(std::cin, line);
    insert(position, new node(line));
}

void LineEditor::DeleteLine()
{
    int position;
    std::cout << " 삭제행 번호: ";
    std::cin >> position;
    remove(position);
}

void LineEditor::ReplaceLine()
{
    int position;
    std::string line;
    std::cout << "  변경행 번호: ";
    std::cin >> position;
    std::cin.sync(); // 버퍼에 남아있는 개행문자를 처리해줍니다
    std::cin.clear();
    std::cout << "  변경할 내용 : ";
    getline(std::cin, line);
    replace(position, new node(line));
}

void LineEditor::LoadFile(std::string fname)
{
    std::ifstream ifs(fname);
    std::string line;
    while (std::getline(ifs, line))
    {
        insert(size(), new node(line));
    }
    ifs.close();
}

void LineEditor::SaveFile(std::string fname)
{
    std::ofstream ofs(fname);
    if (ofs.good())
    {
        Display(&ofs);
        ofs.close();
    }
}