#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "DiagonalList.h"
using namespace std;

DiagonalListElement::DiagonalListElement() {
    this->x = 0;
    this->y = 0;
    this->go_x = 0;
    this->go_y = 0;
    this->next = nullptr;
    this->player = 'W';

    this->first_point = "NULL";
    this->last_point = "NULL";
}

DiagonalListElement::DiagonalListElement(int x, int y, int go_x, int go_y, vector<string> new_points, char player, string first_point, string last_point) {
    this->x = x;
    this->y = y;
    this->go_x = go_x;
    this->go_y = go_y;
    this->next = nullptr;
    this->player = player;

    points = new_points;
    this->first_point = first_point;
    this->last_point = last_point;
}

DiagonalListElement::~DiagonalListElement() {

}

DiagonalList::DiagonalList()
{
    this->first_diagonal = nullptr;
}

DiagonalList::~DiagonalList()
{
    DiagonalListElement* current = first_diagonal;
    while (current != nullptr)
    {
        DiagonalListElement* next = current->next;
        delete current;
        current = next;
    }
}

void DiagonalList::Add_Diagonal(int x, int y, int go_x, int go_y, vector<string> new_points, char player, string first_point, string last_point)
{
    DiagonalListElement* new_diagonal = new DiagonalListElement(x, y, go_x, go_y, new_points, player, first_point, last_point);

    if (first_diagonal == nullptr)
    {
        first_diagonal = new_diagonal;
    }
    else {

        DiagonalListElement* current = first_diagonal;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = new_diagonal;
    }

}

void DiagonalList::Clear()
{
    DiagonalListElement* current = first_diagonal;
    while (current != nullptr)
    {
        DiagonalListElement* next = current->next;
        delete current;
        current = next;
    }
    first_diagonal = nullptr;
}

void DiagonalList::Print() const
{
    DiagonalListElement* current = first_diagonal;
    while (current != nullptr)
    {
        cout << "x: " << current->x << " y: " << current->y << " go_x: " << current->go_x << " go_y: " << current->go_y << " first_point: " << current->first_point << " last_point: " << current->last_point << endl;
        for (size_t i = 0; i < current->points.size(); i++)
        {
            cout << current->points[i] << endl;;
        }

        current = current->next;
    }
}

Diagonals_With_Same_Points::Diagonals_With_Same_Points()
{
    this->x = 0;
    this->y = 0;
    this->go_x = 0;
    this->go_y = 0;
    this->player = 'W';

    this->first_point = "NULL";
    this->last_point = "NULL";
}

Diagonals_With_Same_Points::~Diagonals_With_Same_Points()
{

}

void Diagonals_With_Same_Points::Set_Variables(string new_first_point, string new_last_point, char new_player, int new_x, int new_y, int new_go_x, int new_go_y)
{
    this->x = new_x;
    this->y = new_y;
    this->go_x = new_go_x;
    this->go_y = new_go_y;
    this->player = new_player;

    this->first_point = new_first_point;
    this->last_point = new_last_point;
}