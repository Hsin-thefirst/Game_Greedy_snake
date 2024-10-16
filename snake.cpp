#include <iostream>
#include <unistd.h>
#include <vector>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <time.h>
#include <cctype>

int randint(int n, int m)
{
    time_t t;
    srand((unsigned) time(&t)); 
    if (rand() % m +1 <= n)
    return n;
    else if (rand() % m + 1 >= m)
    return m;
    else
    return (rand() % m + 1);
}

struct snakee
{
    int length = 1;
    int pos_x = 5;
    int pos_y = 5;
    int pos__x = 4;
    int pos__y = 5;
    int speed = 5*length;
    char shape = 'O';
    char direction = 'D';
    std::vector<std::vector<int>> body = {{pos__y, pos__x},{pos_y,pos_x}} ;
}snake;

struct foodd
{
    int pos_x = randint(3, 17);
    int pos_y = randint(3, 7);
    char shape = 'Q';
}food;

struct mapp
{
    int width = 20;
    int length = 10;
    std::vector <std::string> shape = 
    {
     "--------------------\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "--------------------\n"  //\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r
     };
}map;

void print(std::vector<std::string> & map, int length)
{ 

    std::cout << "\033c";
    for (int i = 0; i < length; i++)
    {
        std::cout << map[i];
    }
}

char keyboard_input()
{
    if (_kbhit())
    {
    using namespace std;
    char temp;
    temp = getch();
    return toupper(temp); 
    }
}

void change_direction(char temp)
{
    if (temp == snake.direction)
    ; //warning : if the current direction is opposite the input ,do nothing
    else if ((temp == 'A' && snake.direction == 'D')||
    (temp == 'W' &&  snake.direction == 'S') ||
    (temp == 'D' &&  snake.direction == 'A') ||
    (temp == 'S' &&  snake.direction == 'W'))
    ;
    else
        {
            switch (temp)
            {
                case 'W': 
                    //--snake.pos_y;
                    snake.direction = 'W';
                    break;
                //turn up
                case 'S':
                    //++snake.pos_y;
                    snake.direction = 'S';
                    break;
                case 'A':
                    //--snake.pos_x;
                    snake.direction = 'A';
                    break;
                case 'D':
                    //++snake.pos_x;
                    snake.direction = 'D';
                    break;
            }
        }
}

void get_food(std::vector<std::vector<int>> & body)
{
    for (int i = 0; i < snake.body.size(); i++)
    {    
        if (snake.body[i][1] == food.pos_x && snake.body[i][0] == food.pos_y)
    {
        // body plus one 
        int new_pos_y = body[body.size()-1][0] - (body[body.size() -2][0] - body[body.size()-1][0]);
        int new_pos_x = body[body.size()-1][1] - (body[body.size() -2][1] - body[body.size()-1][1]);
        body.push_back({new_pos_y,new_pos_x});
        food.pos_x = randint(2, 17);
        food.pos_y = randint(2, 7);
        //food refresh
        map.shape[food.pos_y][food.pos_x] = food.shape;
    }}
}
bool if_break()
{
    bool defaullt = true;
    for (int i = 0; i< snake.body.size()-1; i++)
    {
        if (snake.body[snake.body.size()-1] == snake.body[i] )
        {defaullt = false;
        break;}
    }
    return defaullt;
}
int main()
{   
    std::cout <<"This is Greedy Snake 1.1 !\nIf you have any advice or bugs to report, PLZ contact me\nCopytight: Hsin(Do NOT use it for business porpose)";
    std::cout <<"\nRules :\npress w to turn up, a to turn left, d to turn right, s to turn down\n(Press any to start)\n\n\n\n\n\nUpdate journal\n------------\n1.1\nfix the bug that the food sometimes gets in the wall;\nfix the bug that the food will disappear if it gets refreshed in the snake's body;\nyou can see your scores now;\nacknowledgement:TS1989-jpg, who discovered a bug in 1.0";
    std::cin.get();
    LOOP:using namespace std;
    bool judge = true;
    map.shape[food.pos_y][food.pos_x] = food.shape;
    while(judge)
    {
        judge = if_break();
        //check if get the food
        char input = keyboard_input();
        get_food(snake.body);
        snake.body[snake.body.size() -1][0] = snake.pos_y;
        snake.body[snake.body.size() -1][1] = snake.pos_x;
        for (int i = 0; i < snake.body.size(); i++)
        {
            map.shape[snake.body[i][0]][snake.body[i][1]] = snake.shape;
        }
        print(map.shape,map.length);
        map.shape[snake.body[0][0]][snake.body[0][1]] = ' '; // erase the trace
        for (int i = 0; i < snake.body.size()-1; i++)
        {
            snake.body[i] = snake.body[i+1];
        }
        // go forward
        change_direction(input);
        if (snake.direction == 'W')
        --snake.pos_y;
        if (snake.direction == 'S')
        ++snake.pos_y;
        if (snake.direction == 'A')
        --snake.pos_x;
        if (snake.direction == 'D')
        ++snake.pos_x;
        snake.body[snake.body.size() -1][0] = snake.pos_y;
        snake.body[snake.body.size() -1][1] = snake.pos_x;
        // if get the boundary , let it be anouther side
        if (snake.pos_x >= 19)
        snake.pos_x = 1;
        else if (snake.pos_x <= 0)
        snake.pos_x = 18;
        else if (snake.pos_y <= 0)
        snake.pos_y = 8;
        else if (snake.pos_y >= 9)
        snake.pos_y = 1;
        snake.body[snake.body.size() -1][0] = snake.pos_y;
        snake.body[snake.body.size() -1][1] = snake.pos_x;
        // delay for 1 sec
        sleep(1);
    } 
    cout << "GAME OVER"<< endl<< "Your scores: "<< snake.body.size() - 2<< endl<<"Would you want to try again?(y/n):"<< endl;
    char ans;
    cin >> ans;
    if (ans == 'y')
    {
    snake.pos_x = 3;
    snake.pos_y = 3;
    snake.pos__x = 2;
    snake.pos__y = 3;
    snake.body = {{snake.pos__y, snake.pos__x},{snake.pos_y,snake.pos_x}} ;
    map.shape = {
     "--------------------\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "|                  |\n",
     "--------------------\n"  //\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r\033[A\r
     };
    goto LOOP;}
    else if (ans == 'n')
    {cout << "GOODBYE!(press any letter to end)";
    cin.get();
    }
    return 0;
}
