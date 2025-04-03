#include <iostream>
#include <vector>
#include <string>
#include <list>
#include "DiagonalList.h"

using namespace std;

char Load_Game_Board(vector<vector<char>>& board, int& columns, int& rows, int& current_whites, int& current_blacks, char& current_player, int& special_number, int& size, int& start_whites, int& start_blacks, bool& is_okay) {
    cin >> size >> special_number >> start_whites >> start_blacks;
    cin >> current_whites >> current_blacks >> current_player;

    columns = size * 2 - 1 + size * 2 - 2;
    rows = size * 2 - 1;

    board.resize(rows);
    for (int i = 0; i < rows; ++i) {
        board[i].resize(columns);
    }

    int sign = 0;
    char sign_char = ' ';

    int number_of_whites_on_board = 0, number_of_blacks_on_board = 0, number_of_chars = 0, difference = 1, how_chars_should_be = size;
    bool is_correct_number_of_chars = true;

    sign = getchar();

    for (int i = 0; i < rows; i++) {

        int j = 0;
        sign = 0;

        while (sign != '\n' && sign != '\xff')
        {

            sign = getchar();
            sign_char = (char)sign;

            if (sign_char == 'W') number_of_whites_on_board++;
            else if (sign_char == 'B') number_of_blacks_on_board++;

            if (sign_char == 'W' || sign_char == 'B' || sign_char == '_') number_of_chars++;

            if (sign == '\n' || sign == '\xff')
            {
                j--;
            }
            else if (j < columns)
            {
                board[i][j] = sign_char;
            }

            j++;

        }

        if (j < columns)
        {
            while (j < columns)
            {
                board[i][j] = ' ';
                j++;
            }
        }

        if (number_of_chars != how_chars_should_be)
        {
            is_correct_number_of_chars = false;
        }

        if (how_chars_should_be == rows) difference = -1;
        how_chars_should_be = how_chars_should_be + difference;
        number_of_chars = 0;

    }

    if (!is_correct_number_of_chars)
    {
        cout << "WRONG_BOARD_ROW_LENGTH" << endl;
        columns = 0; rows = 0;
    }
    else if (number_of_whites_on_board > (start_whites - current_whites))
    {
        cout << "WRONG_WHITE_PAWNS_NUMBER" << endl;
        columns = 0; rows = 0;
    }
    else if (number_of_blacks_on_board > (start_blacks - current_blacks))
    {
        cout << "WRONG_BLACK_PAWNS_NUMBER" << endl;
        columns = 0; rows = 0;
    }
    else is_okay = true;

    return current_player;
}

void Generate_Board_Points(int size, vector<vector<string>>& board_points)
{

    int columns = size * 2 + size * 2 + 1;
    int rows = size * 2 + 1;

    board_points.resize(rows + 2);
    for (int i = 0; i < rows; ++i) {
        board_points[i].resize(columns + 4);
    }


    char letter = 'a';
    int number = 1, x = 1, y = 0, difference = 0, end = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            board_points[i][j] = ' ';
        }
    }

    for (int i = (rows / 2); i < rows; i++)
    {
        number = 1;

        x = difference;
        y = i;

        for (int j = 0; j <= i; j++)
        {
            board_points[y][x] = letter + to_string(number);
            number++;
            y--;
            x++;
        }
        letter++;
        difference++;
        end = i;
    }

    for (int i = (difference + 1); i < (difference + size * 2); i = i + 2)
    {
        number = 1;
        y = rows - 1;
        x = i;

        for (int j = 0; j < end; j++)
        {
            board_points[y][x] = letter + to_string(number);
            number++;
            y--;
            x++;
        }
        letter++;
        end--;
    }

}

void Check_Place(vector<vector<string>>& board_points, int& go_x, int& go_y, int& x, int& y, const string start, const string end, int size)
{
    int columns = size * 2 + size * 2 + 1;
    int rows = size * 2 + 1;
    bool is_wrong_destination_index = false, is_wrong_start_index = true, is_start_index_exist = false, is_destination_index_exist = false, is_destination_index_on_start = false;

    go_x = 0;
    go_y = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (board_points[i][j] == start)
            {
                if (board_points[rows / 2][0] == end)
                {
                    is_destination_index_on_start = true;
                }
                else if (board_points[rows / 2][columns - 1] == end)
                {
                    is_destination_index_on_start = true;
                }
                else if (board_points[0][(columns - (size * 2 + 1)) / 2] == end)
                {
                    is_destination_index_on_start = true;
                }
                else if (board_points[0][columns - ((columns - (size * 2 + 1)) / 2)] == end)
                {
                    is_destination_index_on_start = true;
                }
                else if (board_points[rows - 1][columns - ((columns - (size * 2 + 1)) / 2)] == end)
                {
                    is_destination_index_on_start = true;
                }
                else if (board_points[rows - 1][(columns - (size * 2 + 1)) / 2] == end)
                {
                    is_destination_index_on_start = true;
                }

                if (i == (rows / 2) && j == 0)
                {
                    if (board_points[i][j + 2] == end)
                    {
                        y = i - 1;
                        x = j - 2 + 2;
                        go_x = 2;
                        go_y = 0;
                    }
                    else is_wrong_destination_index = true;

                    is_wrong_start_index = false;
                }
                else if (i == (rows / 2) && j == (columns - 1))
                {
                    if (board_points[i][j - 2] == end)
                    {
                        y = i - 1;
                        x = j - 2 - 2;
                        go_x = -2;
                        go_y = 0;
                    }
                    else is_wrong_destination_index = true;
                    is_wrong_start_index = false;
                }
                else if (i == 0 && j == ((columns - (size * 2 + 1)) / 2))
                {
                    if (board_points[i + 1][j + 1] == end)
                    {
                        y = i - 1 + 1;
                        x = j - 2 + 1;
                        go_x = 1;
                        go_y = 1;
                    }
                    else is_wrong_destination_index = true;

                    is_wrong_start_index = false;
                }
                else if (i == 0 && j == (columns - ((columns - (size * 2 + 1)) / 2)))
                {
                    if (board_points[i + 1][j - 1] == end)
                    {
                        y = i - 1 + 1;
                        x = j - 2 - 1;
                        go_x = -1;
                        go_y = 1;
                    }
                    else is_wrong_destination_index = true;

                    is_wrong_start_index = false;
                }
                else if (i == (rows - 1) && j == (columns - ((columns - (size * 2 + 1)) / 2)))
                {
                    if (board_points[i - 1][j - 1] == end)
                    {
                        y = i - 1 - 1;
                        x = j - 2 - 1;
                        go_x = -1;
                        go_y = -1;
                    }
                    else is_wrong_destination_index = true;

                    is_wrong_start_index = false;
                }
                else if (i == (rows - 1) && j == ((columns - (size * 2 + 1)) / 2))
                {
                    if (board_points[i - 1][j + 1] == end)
                    {
                        y = i - 1 - 1;
                        x = j - 2 + 1;
                        go_x = 1;
                        go_y = -1;
                    }
                    else is_wrong_destination_index = true;

                    is_wrong_start_index = false;
                }
                else if (i == (rows - 1))
                {
                    if (board_points[i - 1][j + 1] == end)
                    {
                        y = i - 1 - 1;
                        x = j - 2 + 1;
                        go_x = 1;
                        go_y = -1;
                    }
                    if (board_points[i - 1][j - 1] == end)
                    {
                        y = i - 1 - 1;
                        x = j - 2 - 1;
                        go_x = -1;
                        go_y = -1;
                    }
                    else is_wrong_destination_index = true;

                    for (int k = 0; k < columns; k++)
                    {
                        if (board_points[i][k] == end)
                        {
                            is_destination_index_on_start = true;
                        }
                    }

                    is_wrong_start_index = false;
                }
                else if (i == 0)
                {
                    if (board_points[i + 1][j + 1] == end)
                    {
                        y = i - 1 + 1;
                        x = j - 2 + 1;
                        go_x = 1;
                        go_y = 1;
                    }
                    if (board_points[i + 1][j - 1] == end)
                    {
                        y = i - 1 + 1;
                        x = j - 2 - 1;
                        go_x = -1;
                        go_y = 1;
                    }
                    else is_wrong_destination_index = true;

                    for (int k = 0; k < columns; k++)
                    {
                        if (board_points[i][k] == end)
                        {
                            is_destination_index_on_start = true;
                        }
                    }

                    is_wrong_start_index = false;
                }

                int i0 = rows / 2 + 1;
                int j0 = 1;
                while (i0 < rows)
                {
                    if (board_points[i0][j0] == start)
                    {
                        if (board_points[i0][j0 + 2] == end)
                        {
                            y = i0 - 1;
                            x = j0 - 2 + 2;
                            go_x = 2;
                            go_y = 0;
                        }
                        if (board_points[i0 - 1][j0 + 1] == end)
                        {
                            y = i0 - 1 - 1;
                            x = j0 - 2 + 1;
                            go_x = 1;
                            go_y = -1;
                        }
                        else is_wrong_destination_index = true;
                        is_wrong_start_index = false;

                    }
                    if (board_points[i0][j0] == end)
                    {
                        is_destination_index_on_start = true;
                    }
                    j0++;
                    i0++;
                }

                i0 = rows / 2 - 1;
                j0 = 1;
                while (i0 >= 0)
                {
                    if (board_points[i0][j0] == start)
                    {
                        if (board_points[i0][j0 + 2] == end)
                        {
                            y = i0 - 1;
                            x = j0 - 2 + 2;
                            go_x = 2;
                            go_y = 0;
                        }
                        if (board_points[i0 + 1][j0 + 1] == end)
                        {
                            y = i0 - 1 + 1;
                            x = j0 - 2 + 1;
                            go_x = 1;
                            go_y = 1;
                        }
                        else is_wrong_destination_index = true;
                        is_wrong_start_index = false;

                    }
                    if (board_points[i0][j0] == end)
                    {
                        is_destination_index_on_start = true;
                    }
                    j0++;
                    i0--;
                }

                i0 = rows / 2 + 1;
                j0 = columns - 1;
                while (i0 < rows)
                {
                    if (board_points[i0][j0] == start)
                    {
                        if (board_points[i0][j0 - 2] == end)
                        {
                            y = i0 - 1;
                            x = j0 - 2 - 2;
                            go_x = -2;
                            go_y = 0;
                        }
                        if (board_points[i0 - 1][j0 - 1] == end)
                        {
                            y = i0 - 1 - 1;
                            x = j0 - 2 - 1;
                            go_x = -1;
                            go_y = -1;
                        }
                        if (board_points[i0][j0] == end)
                        {
                            is_destination_index_on_start = true;
                        }
                        else is_wrong_destination_index = true;
                        is_wrong_start_index = false;

                    }
                    j0--;
                    i0++;
                }

                i0 = rows / 2 - 1;
                j0 = columns - 1;
                while (i0 >= 0)
                {
                    if (board_points[i0][j0] == start)
                    {
                        if (board_points[i0][j0 - 2] == end)
                        {
                            y = i0 - 1;
                            x = j0 - 2 - 2;
                            go_x = -2;
                            go_y = 0;
                        }
                        if (board_points[i0 + 1][j0 + 1] == end)
                        {
                            y = i0 - 1 + 1;
                            x = j0 - 2 + 1;
                            go_x = 1;
                            go_y = 1;
                        }
                        else is_wrong_destination_index = true;
                        is_wrong_start_index = false;

                    }
                    if (board_points[i0][j0] == end)
                    {
                        is_destination_index_on_start = true;
                    }
                    j0--;
                    i0--;


                }

            }
        }
    }


    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (board_points[i][j] == start)
            {
                is_start_index_exist = true;
                break;
            }
        }
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            if (board_points[i][j] == end)
            {
                is_destination_index_exist = true;
                break;
            }
        }
    }


    if (is_start_index_exist == false)
    {
        cout << "BAD_MOVE_" << start << "_IS_WRONG_INDEX" << endl;
    }
    else if (is_destination_index_exist == false)
    {
        cout << "BAD_MOVE_" << end << "_IS_WRONG_INDEX" << endl;
    }
    else if (is_wrong_start_index)
    {
        cout << "BAD_MOVE_" << start << "_IS_WRONG_STARTING_FIELD" << endl;
    }
    else if (is_destination_index_on_start)
    {
        cout << "BAD_MOVE_" << end << "_IS_WRONG_DESTINATION_FIELD" << endl;
    }
    else if (is_wrong_destination_index && is_destination_index_exist)
    {
        cout << "UNKNOWN_MOVE_DIRECTION" << endl;
    }

}

void Print_Game_Board(vector<vector<char>>& board, int columns, int rows, int current_whites, int current_blacks, char current_player, int special_number, int size, int start_whites, int start_blacks) {

    if (columns == 0 && rows == 0)
    {
        cout << "EMPTY_BOARD" << endl;
    }
    else {
        cout << size << " " << special_number << " " << start_whites << " " << start_blacks << endl;
        cout << current_whites << " " << current_blacks << " " << current_player << endl;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                cout << board[i][j];
            }
            cout << endl;
        }
    }
}

char Make_Move(vector<vector<char>>& board, int go_x, int go_y, int x, int y, char current_player, int rows, int columns, int& current_whites, int& current_blacks)
{
    int x0 = x, y0 = y, how_many = 0, is_place = false;

    while (x >= 0 && x < columns && y >= 0 && y < rows)
    {
        if (board[y][x] == '_')
        {
            is_place = true;
            go_x = -go_x;
            go_y = -go_y;
            break;
        }

        x = x + go_x;
        y = y + go_y;
        how_many++;
    }

    if (is_place)
    {
        for (int i = 0; i < how_many; i++)
        {
            board[y][x] = board[y + go_y][x + go_x];
            x = x + go_x;
            y = y + go_y;
        }
        board[y0][x0] = current_player;
        if (current_player == 'W')
        {
            current_whites--;
            current_player = 'B';
        }
        else if (current_player == 'B')
        {
            current_blacks--;
            current_player = 'W';
        }

    }

    return current_player;
}

int Check_Diagonals(DiagonalList& diagonal_list, int rows, int columns, int special_number, vector<vector<char>>& board, vector<vector<string>>& board_points)
{
    diagonal_list.Clear();

    int x = 0, y = (rows / 2), how_many = 0, number_of_diagonals = 0, x0 = x, x_start = -1, y_start = -1, number_of_points = 0;
    vector<string> points;
    char current_player = 'W';
    string first_point, last_point;

    while (y >= 0)
    {
        how_many = 0, number_of_points = 0;
        x = x0;
        x_start = -1, y_start = -1;
        points.clear();

        while (x < columns)
        {
            if (x_start == -1 && y_start == -1 && (board[y][x] == 'W' || board[y][x] == 'B'))
            {
                x_start = x;
                y_start = y;
                first_point = board_points[y + 1][x + 2];
                number_of_points = 1;
            }
            else if (board[y][x] == ' ' || board[y][x] == '_')
            {
                x_start = -1;
                y_start = -1;
                number_of_points = 0;
            }

            if (board[y][x] == current_player)
            {
                how_many++;
                number_of_points++;
            }
            else
            {
                how_many = 1;
                number_of_points++;
                current_player = board[y][x];
            }

            if (how_many == special_number && (current_player == 'W' || current_player == 'B'))
            {
                last_point = board_points[y + 1][x + 2];
                x = x + 2;
                while (x < columns && board[y][x] != ' ' && board[y][x] != '_')
                {
                    number_of_points++;
                    x = x + 2;
                }
                x = x - 2;
                for (int i = (number_of_points - 1); i >= 0; i--)
                {
                    points.push_back(board_points[y + 1][x + 2]);
                    if (i > 0)
                    {
                        x = x - 2;
                    }
                }
                diagonal_list.Add_Diagonal(x_start, y_start, 2, 0, points, current_player, first_point, last_point);
                number_of_diagonals++;
                break;
            }
            x = x + 2;
        }
        x0++;
        y--;
    }

    y = (rows / 2) + 1;
    x0 = 0;

    while (y < rows)
    {
        x = x0;
        how_many = 0, number_of_points = 0;;
        x_start = -1, y_start = -1;
        points.clear();

        while (x < columns)
        {
            if (x_start == -1 && y_start == -1 && (board[y][x] == 'W' || board[y][x] == 'B'))
            {
                x_start = x;
                y_start = y;
                first_point = board_points[y + 1][x + 2];
                number_of_points = 1;
            }
            else if (board[y][x] == ' ' || board[y][x] == '_')
            {
                x_start = -1;
                y_start = -1;
                number_of_points = 0;
            }

            if (board[y][x] == current_player)
            {
                how_many++;
                number_of_points++;
            }
            else
            {
                how_many = 1;
                number_of_points++;
                current_player = board[y][x];
            }

            if (how_many == special_number && (current_player == 'W' || current_player == 'B'))
            {
                last_point = board_points[y + 1][x + 2];
                x = x + 2;
                while (x < columns && board[y][x] != ' ' && board[y][x] != '_')
                {
                    number_of_points++;
                    x = x + 2;
                }
                x = x - 2;
                for (int i = (number_of_points - 1); i >= 0; i--)
                {
                    points.push_back(board_points[y + 1][x + 2]);
                    if (i > 0)
                    {
                        x = x - 2;
                    }
                }
                diagonal_list.Add_Diagonal(x_start, y_start, 2, 0, points, current_player, first_point, last_point);
                number_of_diagonals++;
                break;
            }
            x = x + 2;
        }
        x0++;
        y++;
    }

    int y0 = (rows / 2);
    x0 = 0;

    while (y0 < rows)
    {
        x = x0;
        y = y0;
        how_many = 0;

        if (y0 < (rows - 1))
        {
            x_start = -1, y_start = -1, number_of_points = 0;
            points.clear();
            while (y >= 0)
            {
                if (x_start == -1 && y_start == -1 && (board[y][x] == 'W' || board[y][x] == 'B'))
                {
                    x_start = x;
                    y_start = y;
                    first_point = board_points[y + 1][x + 2];
                    number_of_points = 1;
                }
                else if (board[y][x] == ' ' || board[y][x] == '_')
                {
                    x_start = -1;
                    y_start = -1;
                    number_of_points = 0;
                }

                if (board[y][x] == current_player)
                {
                    how_many++;
                    number_of_points++;
                }
                else
                {
                    how_many = 1;
                    number_of_points++;
                    current_player = board[y][x];
                }

                if (how_many == special_number && (current_player == 'W' || current_player == 'B'))
                {
                    last_point = board_points[y + 1][x + 2];
                    x++;
                    y--;
                    while (x < columns && y >= 0 && board[y][x] != ' ' && board[y][x] != '_')
                    {
                        number_of_points++;
                        x++;
                        y--;
                    }
                    x--;
                    y++;
                    for (int i = (number_of_points - 1); i >= 0; i--)
                    {
                        points.push_back(board_points[y + 1][x + 2]);
                        if (i > 0)
                        {
                            y++;
                            x--;
                        }
                    }
                    diagonal_list.Add_Diagonal(x_start, y_start, 1, -1, points, current_player, first_point, last_point);
                    number_of_diagonals++;
                    break;
                }
                y--;
                x++;
            }
        }
        else {

            while (x0 < columns)
            {
                x = x0;
                y = y0;
                x_start = -1, y_start = -1, number_of_points = 0;
                points.clear();
                while (y >= 0 && x < columns)
                {
                    if (x_start == -1 && y_start == -1 && (board[y][x] == 'W' || board[y][x] == 'B'))
                    {
                        x_start = x;
                        y_start = y;
                        first_point = board_points[y + 1][x + 2];
                        number_of_points = 1;
                    }
                    else if (board[y][x] == ' ' || board[y][x] == '_')
                    {
                        x_start = -1;
                        y_start = -1;
                        number_of_points = 0;
                    }

                    if (board[y][x] == current_player)
                    {
                        how_many++;
                        number_of_points++;
                    }
                    else
                    {
                        how_many = 1;
                        number_of_points++;
                        current_player = board[y][x];
                    }

                    if (how_many == special_number && (current_player == 'W' || current_player == 'B'))
                    {
                        last_point = board_points[y + 1][x + 2];
                        x++;
                        y--;
                        while (x < columns && y >= 0 && board[y][x] != ' ' && board[y][x] != '_')
                        {
                            number_of_points++;
                            x++;
                            y--;
                        }
                        x--;
                        y++;
                        for (int i = (number_of_points - 1); i >= 0; i--)
                        {
                            points.push_back(board_points[y + 1][x + 2]);
                            if (i > 0)
                            {
                                y++;
                                x--;
                            }
                        }
                        diagonal_list.Add_Diagonal(x_start, y_start, 1, -1, points, current_player, first_point, last_point);
                        number_of_diagonals++;
                        break;
                    }
                    y--;
                    x++;
                }
                x0++;
            }
        }
        y0++;
        x0++;
    }

    y0 = (rows / 2), x0 = (columns - 1);

    while (y0 < rows)
    {
        x = x0;
        y = y0;
        how_many = 0;

        if (y0 < (rows - 1))
        {
            x_start = -1, y_start = -1, number_of_points = 0;
            points.clear();
            while (y >= 0)
            {
                if (x_start == -1 && y_start == -1 && (board[y][x] == 'W' || board[y][x] == 'B'))
                {
                    x_start = x;
                    y_start = y;
                    first_point = board_points[y + 1][x + 2];
                    number_of_points = 1;
                }
                else if (board[y][x] == ' ' || board[y][x] == '_')
                {
                    x_start = -1;
                    y_start = -1;
                    number_of_points = 0;
                }

                if (board[y][x] == current_player)
                {
                    how_many++;
                    number_of_points++;
                }
                else
                {
                    how_many = 1;
                    number_of_points++;
                    current_player = board[y][x];
                }

                if (how_many == special_number && (current_player == 'W' || current_player == 'B'))
                {
                    last_point = board_points[y + 1][x + 2];
                    x--;
                    y--;
                    while (x >= 0 && y >= 0 && board[y][x] != ' ' && board[y][x] != '_')
                    {
                        number_of_points++;
                        x--;
                        y--;
                    }
                    x++;
                    y++;
                    for (int i = (number_of_points - 1); i >= 0; i--)
                    {
                        points.push_back(board_points[y + 1][x + 2]);
                        if (i > 0)
                        {
                            y++;
                            x++;
                        }
                    }
                    diagonal_list.Add_Diagonal(x_start, y_start, -1, -1, points, current_player, first_point, last_point);
                    number_of_diagonals++;
                    break;
                }
                y--;
                x--;
            }
        }
        else {

            while (x0 >= 0)
            {
                x = x0;
                y = y0;
                x_start = -1, y_start = -1, number_of_points = 0;
                points.clear();
                while (y >= 0 && x >= 0)
                {
                    if (x_start == -1 && y_start == -1 && (board[y][x] == 'W' || board[y][x] == 'B'))
                    {
                        x_start = x;
                        y_start = y;
                        first_point = board_points[y + 1][x + 2];
                        number_of_points = 1;
                    }
                    else if (board[y][x] == ' ' || board[y][x] == '_')
                    {
                        x_start = -1;
                        y_start = -1;
                        number_of_points = 0;
                    }

                    if (board[y][x] == current_player)
                    {
                        how_many++;
                        number_of_points++;
                    }
                    else
                    {
                        how_many = 1;
                        number_of_points++;
                        current_player = board[y][x];
                    }

                    if (how_many == special_number && (current_player == 'W' || current_player == 'B'))
                    {
                        last_point = board_points[y + 1][x + 2];
                        x--;
                        y--;
                        while (x >= 0 && y >= 0 && board[y][x] != ' ' && board[y][x] != '_')
                        {
                            number_of_points++;
                            x--;
                            y--;
                        }
                        x++;
                        y++;
                        for (int i = (number_of_points - 1); i >= 0; i--)
                        {
                            points.push_back(board_points[y + 1][x + 2]);
                            if (i > 0)
                            {
                                y++;
                                x++;
                            }
                        }
                        diagonal_list.Add_Diagonal(x_start, y_start, -1, -1, points, current_player, first_point, last_point);
                        number_of_diagonals++;
                        break;
                    }
                    y--;
                    x--;
                }
                x0--;
            }
        }


        y0++;
        x0--;
    }

    return number_of_diagonals;
}

void Delete_All_Diagonals(DiagonalList& diagonal_list, int rows, int columns, vector<vector<char>>& board, int& current_whites, int& current_blacks)
{
    int blacks_to_delete = 0, whites_to_delete = 0;
    if (diagonal_list.first_diagonal != nullptr)
    {
        DiagonalListElement* current = diagonal_list.first_diagonal;
        while (current != nullptr)
        {
            int x = current->x, y = current->y, go_x = current->go_x, go_y = current->go_y;
            char current_player = current->player;

            while (x >= 0 && x < columns && y >= 0 && y < rows && board[y][x] != '_')
            {
                if (board[y][x] == 'W' && current_player == 'W')
                {
                    current_whites++;
                }
                else if (board[y][x] == 'B' && current_player == 'B')
                {
                    current_blacks++;
                }
                else if (board[y][x] == 'B' && current_player == 'W')
                {
                    current_blacks++;
                    blacks_to_delete++;
                }
                else if (board[y][x] == 'W' && current_player == 'B')
                {
                    current_whites++;
                    whites_to_delete++;
                }

                board[y][x] = '_';
                y = y + go_y;
                x = x + go_x;
            }

            current = current->next;
        }

    }

    current_blacks = current_blacks - blacks_to_delete;
    current_whites = current_whites - whites_to_delete;

    diagonal_list.Clear();
}

bool Check_Diagonals_With_Same_Points(DiagonalList& diagonal_list, int rows, int columns, vector<vector<char>>& board, int& current_whites, int& current_blacks)
{
    list<Diagonals_With_Same_Points> same_points_list;

    Diagonals_With_Same_Points same_point;

    bool is_good_move = true;

    if (diagonal_list.first_diagonal != nullptr)
    {
        DiagonalListElement* start = diagonal_list.first_diagonal;
        while (start != nullptr)
        {
            DiagonalListElement* current = diagonal_list.first_diagonal;
            while (current != nullptr)
            {
                if (current != start)
                {
                    for (size_t i = 0; i < current->points.size(); i++)
                    {
                        for (size_t y = 0; y < start->points.size(); y++)
                        {
                            if (current->points[i] == start->points[y])
                            {
                                same_point.Set_Variables(start->first_point, start->last_point, start->player, start->x, start->y, start->go_x, start->go_y);
                                same_points_list.push_back(same_point);
                                same_point.Set_Variables(start->first_point, start->last_point, start->player, start->x, start->y, start->go_x, start->go_y);
                                same_points_list.push_back(same_point);
                                break;
                            }
                        }
                    }
                }
                current = current->next;
            }
            start = start->next;
        }
    }

    if (same_points_list.empty() == false)
    {
        int blacks_to_delete = 0, whites_to_delete = 0;
        char player, sign, table[50];
        int i = 0, sign_int;
        string start, end;

        sign_int = (char)getchar();
        sign = (char)sign_int;
        player = sign;

        if (player == 'w') player = 'W';
        else if (player == 'b') player = 'B';

        sign_int = (char)getchar();
        sign_int = (char)getchar();

        while (sign != '\n')
        {
            sign_int = (char)getchar();
            sign = (char)sign_int;
            if (sign == ' ')
            {
                table[i] = '\0';
                start = string(table);
                i = 0;
            }
            else
            {
                table[i] = sign;
                i++;
            }
        }
        if (i > 0)
        {

            table[i - 1] = '\0';
        }
        else table[i] = '\0';
        end = string(table);

        bool is_correct_index = false;

        DiagonalListElement* current = diagonal_list.first_diagonal;
        while (current != nullptr)
        {
            int x = current->x, y = current->y, go_x = current->go_x, go_y = current->go_y;
            char current_player = current->player;
            string first_point = current->first_point, last_point = current->last_point;

            if ((first_point == start && last_point == end) || (first_point == end && last_point == start))
            {
                is_correct_index = true;
                if (current_player == player)
                {
                    while (x >= 0 && x < columns && y >= 0 && y < rows && board[y][x] != '_')
                    {
                        if (board[y][x] == 'W' && current_player == 'W')
                        {
                            current_whites++;
                        }
                        else if (board[y][x] == 'B' && current_player == 'B')
                        {
                            current_blacks++;
                        }
                        else if (board[y][x] == 'B' && current_player == 'W')
                        {
                            current_blacks++;
                            blacks_to_delete++;
                        }
                        else if (board[y][x] == 'W' && current_player == 'B')
                        {
                            current_whites++;
                            whites_to_delete++;
                        }

                        board[y][x] = '_';
                        y = y + go_y;
                        x = x + go_x;
                    }
                    is_good_move = true;
                }
                else
                {
                    cout << "WRONG_COLOR_OF_CHOSEN_ROW" << endl;
                    is_good_move = false;
                }
                break;
            }

            current = current->next;
        }

        if (is_correct_index == false)
        {
            cout << "WRONG_INDEX_OF_CHOSEN_ROW" << endl;
            is_good_move = false;
        }

        current_blacks = current_blacks - blacks_to_delete;
        current_whites = current_whites - whites_to_delete;

    }

    same_points_list.clear();

    return is_good_move;
}

int main()
{
    vector<vector<char>> board;
    vector<vector<string>> board_points;
    DiagonalList diagonal_list;
    string command;
    int columns = 0, i = 0, rows = 0, current_whites = -1, current_blacks = -1, special_number = 0, sign_int = 0, size = 0, start_whites = 0, start_blacks = 0, number_of_diagonals = 0;
    char current_player = 'W', sign, table[50];
    sign = (char)sign_int;
    bool is_in_progress = true, is_okay = false;

    while (sign_int != '\xff')
    {
        sign_int = getchar();
        sign = (char)sign_int;

        if (sign_int == '\n' || sign == ' ' || sign_int == '\xff')
        {
            table[i] = '\0';
            command = string(table);
            i = 0;
        }
        else
        {
            table[i] = sign;
            i++;
        }

        if (command == "LOAD_GAME_BOARD" || command == "l")
        {
            current_player = Load_Game_Board(board, columns, rows, current_whites, current_blacks, current_player, special_number, size, start_whites, start_blacks, is_okay);
            Generate_Board_Points(size, board_points);
            is_in_progress = true;
            number_of_diagonals = Check_Diagonals(diagonal_list, rows, columns, special_number, board, board_points);
            if (is_okay)
            {
                if (number_of_diagonals == 1)
                {
                    cout << "ERROR_FOUND_" << number_of_diagonals << "_ROW_OF_LENGTH_K" << endl;
                }
                else if (number_of_diagonals > 1)
                {
                    cout << "ERROR_FOUND_" << number_of_diagonals << "_ROWS_OF_LENGTH_K" << endl;
                }
                else cout << "BOARD_STATE_OK" << endl;
            }

            is_okay = false;
            command = " ";
        }

        if (command == "PRINT_GAME_BOARD" || command == "p")
        {
            Print_Game_Board(board, columns, rows, current_whites, current_blacks, current_player, special_number, size, start_whites, start_blacks);
            command = " ";
        }

        if (command == "PRINT_GAME_STATE" || command == "s")
        {
            if (current_whites == 0)
            {
                cout << "white_win";
            }
            else if (current_blacks == 0)
            {
                cout << "black_win";
            }
            else if (is_in_progress)
            {
                cout << "in_progress";
            }
            else  cout << "bad_move";

            command = " ";
        }

        if (command == "DO_MOVE" || command == "d")
        {
            if (is_in_progress)
            {
                int x, y, go_x, go_y;
                char player_before = current_player;
                string start, end;
                sign = '#';

                while (sign != '\n' && sign != ' ')
                {
                    sign_int = (char)getchar();
                    sign = (char)sign_int;
                    if (sign == '-')
                    {
                        table[i] = '\0';
                        start = string(table);
                        i = 0;
                    }
                    else
                    {
                        table[i] = sign;
                        i++;
                    }
                }
                if (i > 0)
                {

                    table[i - 1] = '\0';
                }
                else table[i] = '\0';
                end = string(table);

                Check_Place(board_points, go_x, go_y, x, y, start, end, size);
                if (go_x != 0 || go_y != 0)
                {
                    current_player = Make_Move(board, go_x, go_y, x, y, current_player, rows, columns, current_whites, current_blacks);
                    if (current_player == player_before)
                    {
                        cout << "BAD_MOVE_ROW_IS_FULL" << endl;
                        is_in_progress = false;
                    }
                    else
                    {
                        number_of_diagonals = Check_Diagonals(diagonal_list, rows, columns, special_number, board, board_points);
                        bool is_good_move = Check_Diagonals_With_Same_Points(diagonal_list, rows, columns, board, current_whites, current_blacks);
                        if (is_good_move)
                        {
                            cout << "MOVE_COMMITTED" << endl;
                            number_of_diagonals = Check_Diagonals(diagonal_list, rows, columns, special_number, board, board_points);
                            Delete_All_Diagonals(diagonal_list, rows, columns, board, current_whites, current_blacks);
                        }
                        else is_in_progress = false;

                    }
                }

            }
            i = 0;
            table[i] = '\0';
            command = " ";


        }

        if (command == "k")
        {
            for (int k = 0; k < rows + 2; k++)
            {
                for (int j = 0; j < columns + 4; j++)
                {
                    cout << board_points[k][j];
                }
                cout << endl;
            }

            diagonal_list.Print();

            command = " ";
        }

        if (current_whites == 0)
        {
            is_in_progress = false;
        }
        if (current_blacks == 0)
        {
            is_in_progress = false;
        }

    }
}