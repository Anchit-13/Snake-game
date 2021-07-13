#include <iostream>
#include <conio.h>
#include <ctime>
#include <cstdio>
//#include "Snake.h"
//#include "Food.h"

#define WIDTH 50
#define HEIGHT 25

using namespace std;

//#ifndef SNAKE_H
//#define SNAKE_H

#include <windows.h>
#include <vector>

//#define WIDTH 50
//#define HEIGHT 25

using namespace std;

class Snake
{
    private:
        COORD pos;
        int vel;
        char dir;
        int len;
        vector<COORD> body;

    public:
        Snake(COORD pos, int vel);

        void grow();
        void move_snake();
        void direction(char dir);

        vector<COORD> get_body();

        bool collided();
        bool eaten(COORD food);

        COORD get_pos();
};

//#endif // SNAKE_H

//#include "Snake.h"

Snake::Snake(COORD pos, int vel)
{
    this->pos = pos;
    this->vel = vel;

    dir = 'n';
    len = 1;

    body.push_back(pos);
}

void Snake::direction(char dir) { this->dir = dir; }
void Snake::grow() { len++; }
COORD Snake::get_pos() { return pos; }

vector<COORD> Snake::get_body() { return body; }

void Snake::move_snake()
{
    /*switch(dir)
    {
        case 'u': pos.Y -= vel; break;
        case 'd': pos.Y += vel; break;
        case 'l': pos.X -= vel; break;
        case 'r': pos.X += vel; break;
    }*/
    if(dir=='u'){

        if(pos.Y-vel<1){
            pos.Y=HEIGHT-1-(vel-(pos.Y-1));
        }
        else
            pos.Y-=vel;
    }
    else if(dir=='d'){

        if(pos.Y+vel>HEIGHT-2){
            pos.Y=(vel-(-pos.Y+HEIGHT-2));
        }
        else
            pos.Y+=vel;
    }
    else if(dir=='l'){

        if(pos.X-vel<1){
            pos.X=WIDTH-1-(vel-(pos.X-1));
        }
        else
            pos.X-=vel;
    }
    else if(dir=='r'){

        if(pos.X+vel>WIDTH-2){
            pos.X=(vel-(-pos.X+WIDTH-2));
        }
        else
            pos.X+=vel;
    }

    body.push_back(pos);
    if(body.size() > len) body.erase(body.begin());
}

bool Snake::collided()
{
    //if(pos.X < 1 || pos.X > WIDTH-2 || pos.Y < 1 || pos.Y > HEIGHT-2) return true;

    for(int i = 0; i < len-1; i++)
    {
        if(pos.X == body[i].X && pos.Y == body[i].Y) return true;
    }
    return false;
}

bool Snake::eaten(COORD food)
{
    if(pos.X == food.X && pos.Y == food.Y) return true;
    return false;
}

class Food
{
    private:
        COORD pos;

    public:
        void gen_food();

        COORD get_pos();
};

void Food::gen_food()
{
    pos.X = (rand() % (WIDTH - 2)) + 1;
    pos.Y = (rand() % (HEIGHT - 2)) + 1;
}

COORD Food::get_pos() { return pos; }

Snake snake({WIDTH/2, HEIGHT/2}, 1);
Food food;

int score;

void board()
{
    COORD snake_pos = snake.get_pos();
    COORD food_pos = food.get_pos();

    vector<COORD> snake_body = snake.get_body();

    cout << "SCORE : " << score << "\n\n";

    for(int i = 0; i < HEIGHT; i++)
    {
        cout << "\t\t#";
        for(int j = 0; j < WIDTH - 2; j++)
        {
            if(i == 0 || i == HEIGHT-1) cout << '#';

            else if(i == snake_pos.Y && j+1 == snake_pos.X) cout << '#';
            else if(i == food_pos.Y && j+1 == food_pos.X) cout << '@';

            else
            {
                bool isBodyPart = false;
                for(int k = 0; k < snake_body.size()-1; k++)
                {
                    if(i == snake_body[k].Y && j+1 == snake_body[k].X)
                    {
                        cout << 'o';
                        isBodyPart = true;
                        break;
                    }
                }

                if(!isBodyPart) cout << ' ';
            }
        }
        cout << "#\n";
    }
}

int main()
{
    int v, i;
    cin>>v;
    score = 0;
    srand(time(NULL));

    food.gen_food();

    int game_over = 0;

    while(!game_over)
    {
        board();

        if(kbhit())
        {
            switch(getch())
            {
                case 'w': snake.direction('u'); break;
                case 'a': snake.direction('l'); break;
                case 's': snake.direction('d'); break;
                case 'd': snake.direction('r'); break;
            }
        }
        for(i=0;i<v;i++){
        snake.move_snake();

        if(snake.collided()) game_over = 1;

        if(snake.eaten(food.get_pos()))
        {
            food.gen_food();
            snake.grow();
            score = score + 10;
        }
        }


        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0});
    }
}
