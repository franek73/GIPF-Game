#pragma once
#include <iostream>
#include <vector>
#include <string>
using namespace std;

class DiagonalListElement
{
public:
    vector<string> points;
    int x, y, go_x, go_y;
    char player;
    string first_point, last_point;

    DiagonalListElement* next;

    DiagonalListElement();
    DiagonalListElement(int x, int y, int go_x, int go_y, vector<string> new_points, char player, string first_point, string last_point);
    ~DiagonalListElement();
};

class DiagonalList
{
public:
    DiagonalListElement* first_diagonal;

    DiagonalList();
    ~DiagonalList();
    void Add_Diagonal(int x, int y, int go_x, int go_y, vector<string> new_points, char player, string first_point, string last_point);
    void Clear();
    void Print() const;
};

class Diagonals_With_Same_Points {
public:
    string first_point, last_point;
    char player;
    int x, y, go_x, go_y;

    Diagonals_With_Same_Points();
    ~Diagonals_With_Same_Points();
    void Set_Variables(string new_first_point, string new_last_point, char new_player, int new_x, int new_y, int new_go_x, int new_go_y);

};