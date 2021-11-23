#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <thread>
#include "slide_puzzle.h"

using std::this_thread::sleep_for;

int slide[MAX_LEVEL][MAX_LEVEL];
int level = D_LEVEL;
Point NoNumberPoint(D_LEVEL - 1, D_LEVEL - 1);

void swap_num(Point move) {
    int temp = slide[NoNumberPoint.y][NoNumberPoint.x];
    slide[NoNumberPoint.y][NoNumberPoint.x] = slide[move.y][move.x];
    slide[move.y][move.x] = temp; 
    NoNumberPoint = move;
}

void shuffle() {
    Point move(-1, -1);
    for (int i = 0; i < SHUFFLE_ITERATION; i++) {
        switch (rand() % 4) {
        case 0:move.x = NoNumberPoint.x; move.y = NoNumberPoint.y + 1; break;
        case 1:move.x = NoNumberPoint.x; move.y = NoNumberPoint.y - 1; break;
        case 2:move.x = NoNumberPoint.x + 1; move.y = NoNumberPoint.y; break;
        case 3:move.x = NoNumberPoint.x - 1; move.y = NoNumberPoint.y; break;
        }

        if (move.x < 0 || move.x >= level || move.y < 0 || move.y >= level) {
            i--;
            continue;
        }

        swap_num(move);
    }
}

void change() {
    Point move(-1, -1);
    if (_getch() == 0xE0) {
        switch (_getch()) {
        case 0x48:move.x = NoNumberPoint.x; move.y = NoNumberPoint.y + 1; break;
        case 0x50:move.x = NoNumberPoint.x; move.y = NoNumberPoint.y - 1; break;
        case 0x4B:move.x = NoNumberPoint.x + 1; move.y = NoNumberPoint.y; break;
        case 0x4D:move.x = NoNumberPoint.x - 1; move.y = NoNumberPoint.y; break;
        }
    }

    if (move.x < 0 || move.x >= level || move.y < 0 || move.y >= level) {
        return;
    }

    swap_num(move);
}

bool result_judge() {
    bool judge = true;
    for (int i = 0; i < level; i++)
        for (int j = 0; j < level; j++)
            if (slide[i][j] != i * level + j + 1) judge = false;
    return judge;
}

void print_bar() {
    printf("+");
    for (int j = 0; j < level; j++)printf("--+");
    printf("\n");
}

void print() {
    printf("SLIDE PUZZLE\n\n");
    for (int i = 0; i < level; i++) {
        //print_bar();
        for (int j = 0; j < level; j++) {
            if (slide[i][j] == level * level) printf("   ");
            else printf("%3d", slide[i][j]);
        }
        printf("\n");
    }
    //print_bar();
}

int main(void) {
    srand((unsigned int)time(NULL));
    bool start_judge;

    do {
        system("cls");
        start_judge = true;
        for (int i = 0; i < level; i++)
            for (int j = 0; j < level; j++)
                slide[i][j] = i * level + j + 1;
        NoNumberPoint.x = level - 1; NoNumberPoint.y = level - 1;

        shuffle();
        print();
        printf("\nシャッフル : Sキー\n");
        printf("レベル変更 : A or Dキー\n");
        printf("  スタート : その他のキー\n");

        switch (_getch()) {
        case's':start_judge = false; break;
        case'a':level--; start_judge = false;  break;
        case'd':level++; start_judge = false;  break;
        }

        if (level < D_LEVEL)level = MAX_LEVEL;
        else if (level > MAX_LEVEL)level = D_LEVEL;
    } while (!start_judge);

    for (int count = 3; count > 0; count--) {
        system("cls");
        for (int i = 0; i < 9; i++) {
            printf("%d ", count);
            sleep_for(std::chrono::milliseconds(100));
        }
    }

    system("cls");
    printf("スタート!\n\n");
    sleep_for(std::chrono::milliseconds(1000));

    clock_t start, end;

    start = clock();
    while (1) {
        system("cls");
        print();                    //盤面表示
        if (result_judge()) break;  //クリア判定
        printf("\n経過時間：%.2f秒\n", (double)(clock() - start) / CLOCKS_PER_SEC);
        printf("　　操作：矢印キー\n");
        change();                   //数字入れ替え
    }
    end = clock();

    printf("\nクリア!\n");
    printf("クリア時間：% .2f秒\n", (double)(end - start) / CLOCKS_PER_SEC);
    

    for (int i = 0; i < 3; i++)_getch();
}
