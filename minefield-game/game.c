//
// Created by Yusuf Tekin on 11.01.2023.
//


#include "stdio.h"
#include "game.h"
#include "time.h"
#include "stdlib.h"


#define WIDTH 3
#define HEIGHT 3

typedef struct Area GameArea[WIDTH][HEIGHT];
typedef struct Point Point;
typedef struct Area Area;


int createRandomNumber();
void listOfGameArea(GameArea Area);
int pointControl(GameArea gameArea,Point point);

Point getPointFromUser();


int health = 5,allSafeAreaCount = 0,movesCount = 0,mineCount = 0;

int main() {
    srand(time(NULL));
    GameArea gameArea;

    printf("************************   Mayin Tarlasi   ************************\n\n");


    for (int width = 0; width < WIDTH; ++width) {
        for (int height = 0; height < HEIGHT; ++height) {
            Area area;
            area.isMined = createRandomNumber();
            area.isOpen = 0;
            gameArea[width][height] = area;
            if(area.isMined == 0){
                allSafeAreaCount++;
            }
            else {
                mineCount++;
            }
        }
    }

    printf("Toplam Mayin Sayisi: %d\n\n\n",mineCount);

    while(1) {
        if(allSafeAreaCount == 0 && health > 0) {
            printf("OYUN BITTI! KAZANDINIZ!!\n");
            printf("Yapilan Toplam Hamle Sayisi: %d",movesCount);
            break;
        }
        else if(health == 0) {
            printf("OYUN BITTI! HAKKIN KALMADI");
            break;
        }
        listOfGameArea(gameArea);
        Point currentPoint = getPointFromUser();
        pointControl(gameArea,currentPoint);
    }
    return 0;
}

Point getPointFromUser() {

    Point point;

    printf("X: ");
    scanf("%d",&point.x);

    printf("Y: ");
    scanf("%d",&point.y);

    point.x--;
    point.y--;

    movesCount++;

    return point;

}

int pointControl(GameArea gameArea,Point point) {

    int x = point.x,y = point.y;

    if(x < WIDTH && y < HEIGHT && x > -1 && y > -1) {
        Area* area = &gameArea[x][y];
        if(area->isMined == 1 && area->isOpen == 0) {
            health-=1;
            printf("Mayin'a bastin! Kalan Hak: %d\n",health);
        }
        else if(area->isMined == 0 && area->isOpen == 0) {
            allSafeAreaCount--;
        }
        area->isOpen = 1;

    }else {
        printf("Oyun alani disina ciktin!!\n\n");
        return 0;
    }
    return 1;

}

void listOfGameArea(GameArea Area) {

    for(int y = 0; y < HEIGHT;y++) {
        for(int x = 0; x < WIDTH; x++) {

            struct Area area = Area[x][y];


            area.isOpen == 1 ? (area.isMined ? printf("-") : printf("+")) : printf("*");

            if(x == WIDTH - 1) {
                printf("\n");
            }
        }
    }

}

int createRandomNumber(){
    return rand() % 2;
}