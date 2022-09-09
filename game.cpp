#include<iostream>
#include<ctime>
#include<iostream>
#include<Windows.h>
#include <conio.h>   
#include<vector>

using namespace std;

class Player {
    int X;
    int Y;
    int Width;
    int Score = 0;
    int speed=1;

public:
    int getSpeed() {
        return speed;
    }
    void setSpeed(int s) {
        speed = s;
    }
    void setX(int x) {
        X = x;
    }
    void setY(int y) {
        Y = y;
    }
    int getX() {
        return X;
    }
    int getY() {
        return Y;
    }
    void setWidth(int w) {
        Width = w;
    }
    int getWidth() {
        return Width;
    }
    int getScore() {
        return Score;
    }
    void setScore(int s) {
        Score = s;
    }
    void Xplus() {
        X += speed;
    }
    void Xminus() {
        X -= speed;
    }
};

enum Direction { Up, Down, UpperLeft, UpperRight, LowerLeft, LowerRight };
struct Board {
    int Width;
    int Height;

};
struct Ball {
    int X;
    int Y;
    int speed;
    void Xplus() {
        X += speed;
    }
    void Xminus() {
        X -= speed;
    }
    void Yplus() {
       Y += speed;
    }
    void Yminus() {
        Y -= speed;
    }
};

class Game {

    Player player1, player2;
    Board board; Ball ball;
    Direction direction;
    int Count3 = 0;

    bool GameOver = false;
    void Draw() {

        for (int i = 0; i < board.Height; i++) {
            for (int j = 0; j < board.Width; j++) {
                if (i == 0 || i == board.Height - 1 || j == 0 || j == board.Width - 1)
                    cout << "@";
                else if (PlayerPosition(player1, i, j) || PlayerPosition(player2, i, j))
                    cout << "-";

                else if (BallPosition(i, j)) {
                    if (Count3)
                        cout << Count3--;
                    else
                        cout << "*";
                }
                else cout << " ";
            }
            cout << "\n";
        }
        cout << "player 1 (" << player1.getX() << " , " << player1.getY() << " )\tScore : " << player1.getScore() << endl;
        cout << "player 2 (" << player2.getX() << " , " << player2.getY() << " )\tScore : " << player2.getScore() << endl;
        cout << "Ball 1 (" << ball.X << " , " << ball.Y << " )\tSpeed : "<<ball.speed << endl;
        if (Count3)Sleep(500);
    }
    bool BallPosition(int i, int j) {
        return i == ball.Y && j == ball.X;
    }
    bool PlayerPosition(Player player, int i, int j) {
        if (abs(player.getX() - j) <= 2 && player.getY() == i)return 1;
        return 0;
    }
    bool checkLeft(Player &player) {
        if (player.getSpeed() > (player.getX() - player.getWidth() / 2) && player.getX() - player.getWidth() / 2 >= 1) {
            player.setSpeed(2);
            return 1;
          }
        

        return (player.getX() - player.getWidth() / 2 - player.getSpeed()) > 0;
    }
    bool checkRight(Player &player) {
        if (player.getSpeed() > (player.getX() - player.getWidth() / 2) && player.getX() - player.getWidth() / 2 >= 1) {
            player.setSpeed(1);
            return 1;
        }
        return (player.getX() + player.getWidth() / 2 + player.getSpeed()) < board.Width - 1;
    }
    void MoveBall() {
        if (!Count3) {
            while (ball.X!=player2.getX()) {
                if (player2.getX() < ball.X&&(rand()%5>=1)) {
                    player2.Xplus();
                    if (player2.getX() > ball.X)break;
                }
                else if((rand() % 5 >= 1)) { player2.Xminus();
                if (player2.getX() < ball.X)break;
                }
            }
        }
        //----------------------------------------
        if (!Count3)
            switch (direction)
            {
            case Up:
                ball.Yminus();
                break;
            case Down:
                ball.Yplus();
                break;
            case UpperLeft:
                ball.Xminus();
                ball.Yminus();
                break;
            case UpperRight:
                ball.Yminus();
                ball.Xplus();
                break;
            case LowerLeft:
                ball.Xminus();
                ball.Yplus();
                break;
            case LowerRight:
                ball.Yplus();
                ball.Xplus();
                break;

            }


        //----------------------------------------
        ballTouch(player1);
        ballTouch(player2);
    }
    void ballTouch(Player player) {
        if (ball.X<= 1) {
            if (direction == UpperLeft)
                direction = UpperRight;
            else if (direction == LowerLeft)
                direction = LowerRight;
        }
        if (ball.X >= board.Width - 2) {
            if (direction == UpperRight)
                direction = UpperLeft;
            else if (direction == LowerRight)
                direction = LowerLeft;
        }
        if (ball.Y <=1) {
            player2.setScore(player2.getScore() + 10);
            ReSet(1);
        }
        else if (ball.Y >= board.Height - 2) {
            player1.setScore(player1.getScore() + 10);
            ReSet(0);
        }
        if (abs(player.getY() - ball.Y) == 1 &&
            abs(ball.X - player.getX()) <= player.getWidth() / 2) {
            cout << "\a";
            if (player.getX() - ball.X == 0) {
                if (player.getY() > ball.Y) {
                    direction = Up;
                }
                else direction = Down;
            }
            else if (player.getX() - ball.X > 0) {
                if (player.getY() > ball.Y) {
                    direction = UpperLeft;
                }
                else direction = LowerLeft;

            }
            else if (player.getX() - ball.X < 0) {
                if (player.getY() > ball.Y) {
                    direction = UpperRight;
                }
                else direction = LowerRight;

            }
            if (player1.getSpeed() <= 3) {
                player1.setSpeed(player1.getSpeed() + 1);
            }
        }

    }
    void ReSet(int winner) {
        player1.setY(board.Height / 6);
        player1.setX(board.Width / 2);


        player2.setY(board.Height - board.Height / 6);
        player2.setX(board.Width / 2);

        ball.Y = board.Height / 2;
        ball.X = board.Width / 2;
        ball.speed = 1;
        Count3 = 3;
        if (winner == 1)
            direction = Up;
        else
            direction = Down;
        player1.setSpeed(1);
    }
    void Input() {
        if (!Count3)
            if (_kbhit()) {
                char input = _getch();
                switch (input) {
                case 'a':
                    if (checkLeft(player1))
                        player1.Xminus();
                    break;

                case 'd':
                    if (checkRight(player1))
                        player1.Xplus();
                    break;
             
                }
            }


    }
public:
    Game() {
        direction = Down;
        board.Height = 30;
        board.Width = 30;

        player1.setY(board.Height / 6);
        player1.setX(board.Width / 2);
        player1.setWidth(5);

        player2.setY(board.Height - board.Height / 6);
        player2.setX(board.Width / 2);
        player2.setWidth(5);

        ball.Y = board.Height / 2;
        ball.X = board.Width / 2;
        ball.speed = 1;
    }
    void Play() {
        int score;
        cout << "Enter max score to play : ";
        cin >> score;
        while (!GameOver) {
            Draw();
            Sleep(50);
            system("cls");
            Input();
            MoveBall();
            GameOver = max(player1.getScore(), player2.getScore()) >= score;

        }
        if (player1.getScore() > player2.getScore())
            cout << "Player 1 WINS!\n";
        else
            cout << "Player 2 WINS!\n";

        cout << "Press R to Play Again! : ";
        system("pause");
        if (_kbhit() && _getch() == 'r')
            GameOver = 0, ReSet(1), player1.setScore(0), player2.setScore(0), Play();
    }

};


int main()
{
    srand(time(0));
    Game game;
    game.Play();
}

