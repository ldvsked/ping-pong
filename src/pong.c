#include <stdio.h>
int otrisovka(int x,int y,int y1,int y2);
int left_raketka(int y);
int right_raketka(int y);
int ball_coordinate_x(int x,int p);//изменение координаты х
int ball_coordinate_y(int x,int p);//изменение координаты у
int ball_pol_new_x(int x,int pol);//изменение полярности х
int ball_pol_new_y(int y,int pol);//изменение полярности у
int end_round(int x);
int score_left(int x , int score_left);// если нью х столкнулся со стеной меняем счет  возвращаем счет 
int score_right(int x,int score_right);



int main(){
    int height = 25;
    int weight = 80;
    int x_ball;
    int y_ball;
    int y_raketka_left;
    int y_raketka_right;
    int pol_x ;
    int pol_y;
    int flag = 0;//end 
    int left_score;
    int right_score;
    while (left_score!=21 || right_score!=21){
        x_ball = 40;
        y_ball = 12;
        y_raketka_left = 12;
        y_raketka_right = 12;
        pol_x = 1;
        pol_y = 1;
        otrisovka(x_ball,y_ball,y_raketka_left,y_raketka_right);
        while(flag == 0){
            y_raketka_left =left_raketka(y_raketka_left);
            y_raketka_right = right_raketka(y_raketka_right);
            x_ball = ball_coordinate_x(x_ball,pol_x);
            y_ball = ball_coordinate_y(y_ball,pol_y);
            pol_x = ball_pol_new_x(x_ball,pol_x);
            pol_y = ball_coordinate_y(y_ball,pol_y);
            otrisovka(x_ball,y_ball,y_raketka_left,y_raketka_right);
            flag = end_round(x_ball);
         }
         left_score = score_left(x_ball,left_score);
         right_score = score_right(x_ball,right_score);
        

    }
}


int ball_pol_new_x(int x,int pol){
    int result = pol;
    if (x == 10){
        result = 1;
    }
    if (x == 70){
        result = -1;
    }
    return result;
}
 /*int end_round(int x)
 {
    if () //врезался
 }*/


