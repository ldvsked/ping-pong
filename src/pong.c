#include <stdio.h>
int otrisovka(int x, int y, int y1, int y2, int flag, int first_score, int second_score);
int left_raketka(int y, char left_raketka);
int right_raketka(int y, char right_raketka);
int ball_coordinate_x(int x, int p);  // изменение координаты х(изменение относительно полярности)
int ball_coordinate_y(int x, int p);  // изменение координаты у
int ball_pol_new_x(int x, int pol, int y_rak_l, int y_rak_r, int y_ball);  // изменение полярности х
int ball_pol_new_y(int y, int pol);  // изменение полярности у
int end_round(int x);
int score_left(int x, int score_left);  // если нью х столкнулся со стеной меняем счет  возвращаем счет
int score_right(int x, int score_right);

int ball_coordinate_x(int x, int p) {
    int itog_x;
    if (p == -1) {
        itog_x = x - 1;
    }
    if (p == 1) {
        itog_x = x + 1;
    }
    return itog_x;
}

int ball_coordinate_y(int y, int p) {
    int itog_y;
    if (p == -1) {
        itog_y = y - 1;
    }
    if (p == 1) {
        itog_y = y + 1;
    }
    return itog_y;
}

int ball_pol_new_x(int x, int pol, int y_rak_l, int y_rak_r, int y_ball) {
    int result = pol;
    if ((x == 11) && (y_rak_l == y_ball || (y_rak_l - 1) == y_ball || (y_rak_l + 1) == y_ball)) {
        result = 1;
    }
    if ((x == 69) && (y_rak_r == y_ball || (y_rak_r - 1) == y_ball || (y_rak_r + 1) == y_ball)) {
        result = -1;
    }
    return result;
}

int ball_pol_new_y(int y, int pol) {
    int result = pol;
    if (y == 23) {
        result = -1;
    }
    if (y == 1) {
        result = 1;
    }
    return result;
}

int end_round(int x) {
    int result = 0;
    if (x == 9 || x == 71) result = 1;
    return result;
}

int score_left(int x, int score_left) {
    if (x == 71) {
        score_left++;
    }
    return score_left;
}

int score_right(int x, int score_right) {
    if (x == 9) {
        score_right++;
    }
    return score_right;
}

int otrisovka(int x_ball, int y_ball, int y_raketka_left, int y_raketka_right, int flag, int first_score,
              int second_score) {
    int x_raketka_left = 10;
    int x_raketka_right = 70;
    int x_centre = 40;
    for (int y = 24; y >= 0; y--) {
        for (int x = 0; x < 80; x++) {
            // границы
            if (flag == 1 && (x == 2 && y == 22)) {
                printf("%d", first_score);
            } else if (flag == 1 && (x == 77 && y == 22)) {
                printf("%d", second_score);
            } else if (y == 24 || y == 0) {
                printf("_");
            } else if (x == 0 || x == 79) {
                printf("|");
            }
            // ракетка левая
            else if (x == x_raketka_left &&
                     (y == y_raketka_left || y == y_raketka_left - 1 || y == y_raketka_left + 1)) {
                printf("|");
            }  //  правая ракетка
            else if (x == x_raketka_right &&
                     (y == y_raketka_right || y == y_raketka_right - 1 || y == y_raketka_right + 1)) {
                printf("|");
            }
            // мяч
            else if (x == x_ball && y == y_ball) {
                printf("o");
            } else if (x == x_centre) {
                printf(":");
            }
            // пробел
            else
                printf(" ");
        }
        printf("\n");
    }
    return 0;
}

int left_raketka(int y, char moveLeft) {
    int result = y;
    if (moveLeft == 'a' && (result + 1 <= 22)) {
        result++;
    } else if (moveLeft == 'z' && (result - 1 >= 1)) {
        result--;
    }
    // scanf("\f")
    return result;
}

int right_raketka(int y, char moveRight) {
    int result = y;
    if (moveRight == 'k' && (result + 1 <= 22)) {
        result++;
    } else if (moveRight == 'm' && (result - 1 >= 1)) {
        result--;
    }
    return result;
}

int main() {
    int x_ball;
    int y_ball;
    int y_raketka_left;
    int y_raketka_right;
    int pol_x;
    int pol_y;
    int left_score = 0;
    int right_score = 0;
    while (left_score != 21 && right_score != 21) {
        int flag = 0;
        x_ball = 40;
        y_ball = 12;
        y_raketka_left = 12;
        y_raketka_right = 12;
        pol_x = 1;
        pol_y = 1;
        int first_step = 1;
        otrisovka(x_ball, y_ball, y_raketka_left, y_raketka_right, first_step, left_score, right_score);
        while (flag == 0) {
            first_step = 0;
            char move_left = ' ';
            char move_right = ' ';
            scanf("%c%c", &move_left, &move_right);
            while (getchar() != '\n');

            y_raketka_left = left_raketka(y_raketka_left, move_left);
            y_raketka_right = right_raketka(y_raketka_right, move_right);
            x_ball = ball_coordinate_x(x_ball, pol_x);
            y_ball = ball_coordinate_y(y_ball, pol_y);
            pol_x = ball_pol_new_x(x_ball, pol_x, y_raketka_left, y_raketka_right, y_ball);
            pol_y = ball_pol_new_y(y_ball, pol_y);
            otrisovka(x_ball, y_ball, y_raketka_left, y_raketka_right, first_step, left_score, right_score);
            flag = end_round(x_ball);
        }
        left_score = score_left(x_ball, left_score);
        right_score = score_right(x_ball, right_score);
    }
    if (left_score == 21) {
        printf("%d\n", left_score);
        printf("Поздравляем левого игрока с победой!!!\n");
    } else {
        printf("%d\n", right_score);
        printf("Поздравляем правого игрока с победой!!!\n");
    }
}
