#include <iostream>
#import <conio.h>
using namespace std;



struct snake_part {
    int x,y;
    snake_part* next;
    snake_part* prev;
};

void print_field(char** field,int field_height, int field_width){
    for (int i = 0; i < field_height; i++ ){
        for (int j = 0; j < field_width; j++){
          cout << field[i][j];
        }
        cout << "|\n";
    }
    for (int j = 0; j < field_width;j++){
        cout << "-";
    }
}
void clear_field (char** field, int field_height, int field_width){
    for (int i = 0; i < field_height; i++){
        for (int j = 0; j < field_width;j++){
            field[i][j] = ' ';
        }
    }
}


int main(){

    int field_width,field_height;

    do {
        system("cls");
        cout << "Enter field width - ";
        cin >> field_width;
        cout << "Enter field height - ";
        cin >> field_height;
    } while((field_width <= 5) or (field_height <= 5));

    char** field = new char* [field_height];
    for (int i = 0; i < field_height; i++) {
        field[i] = new char[field_width];
    }

    clear_field(field,field_height,field_width);

    system ("cls");
    for (int i = 0; i < field_height; i++){
        for (int j = 0; j < field_width;j++){
            cout << field[i][j];
        }
        cout<<endl;
    }

    snake_part snake;
    snake_part* snake_head = &snake;

    snake.x = rand() % field_width;
    snake.x = rand() % field_height;
    snake.next = nullptr;
    snake.prev = nullptr;

    bool alive = true;
    char symbol;
    int current_length = 0;
    int apple_x, apple_y;

    apple_x = rand() %field_width;
    apple_y = rand() %field_height;

    snake_part* snake_current = snake_head;


    int snake_x_prev,snake_y_prev;

    int snake_length = 1;

    while (alive){

        snake_x_prev = snake.x;
        snake_y_prev = snake.y;

        symbol = getch();
        if ((symbol == 'w') or (symbol == 'W')) {
            snake.y -= 1;
            if (snake.y < 0) snake.y = field_height - 1;
        }
        if ((symbol == 's') or (symbol == 'S')) {
            snake.y = (snake.y + 1) % field_height;
        }
        if ((symbol == 'a') or (symbol == 'A')) {
            snake.x -= 1;
            if (snake.x < 0) snake.x = field_width - 1;
        }
        if ((symbol == 'd') or (symbol == 'D')) {
            snake.x = (snake.x + 1) % field_width;
        }

        snake_current = snake_head;

        if (snake_length > 1){
            snake_current = snake_current->next;
            while (snake_current->next != nullptr){
                if (field[snake.y][snake.x] == '@'){
                    alive = false;
                    break;
                }
                snake_current = snake_current->next;
            }
        }

        if (!alive) break;

        if ((snake.x == apple_x) and (snake.y == apple_y)){
            do{
                apple_x = rand() % field_width;
                apple_y = rand() % field_height;

            }while((field[apple_y][apple_x] != ' '));

            snake_current = snake_head;

            while(snake_current->next != nullptr) snake_current = snake_current->next;
            snake_current->next = new snake_part;
            snake_current->next->x = snake_x_prev;
            snake_current->next->y = snake_y_prev;
            snake_current->next->prev = snake_current;
            snake_current->next->next = nullptr;
            snake_length++;
        }

        snake_current = snake_head;

        if (snake_length > 1){
            while(snake_current->next != nullptr) snake_current = snake_current->next;
            while(snake_current != snake_head->next){

                snake_current->x = snake_current->prev->x;
                snake_current->y = snake_current->prev->y;
                snake_current = snake_current->prev;
            }
            snake_current->x = snake_x_prev;
            snake_current->y = snake_y_prev;
        }



        snake_current = snake_head;

        current_length = 0;

        clear_field(field,field_height,field_width);

        field[apple_y][apple_x] = 'b';

        while (snake_current != nullptr){

            if (current_length == 0) field[snake_current-> y][snake_current-> x] = 'O';
            else field[snake_current-> y][snake_current-> x] = '@';

            current_length++;
            snake_current = snake_current -> next;
        }
        system ("cls");

        cout << "Your current score - "<< snake_length <<endl;
        print_field(field, field_height, field_width);

    }
    cout << "\n GAME OVER! YOUR SCORE - "<< snake_length<< endl;

    return 0;
}