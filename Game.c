#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#define LOADING_TIME 5

/*
Cenk Ergen 
040170035
EHB 110E HomeWork  
*/

char loadingScreen[7][58] = {
    {" ______ _    _  _____ _____ _______ _______      ________ "},
    {"|  ____| |  | |/ ____|_   _|__   __|_   _\\ \\    / /  ____|"},
    {"| |__  | |  | | |  __  | |    | |    | |  \\ \\  / /| |__   "},
    {"|  __| | |  | | | |_ | | |    | |    | |   \\ \\/ / |  __|  "},
    {"| |    | |__| | |__| |_| |_   | |   _| |_   \\  /  | |____ "},
    {"|_|     \\____/ \\_____|_____|  |_|  |_____|   \\/   |______|"},
    {"                   Cenk Ergen 040170035                   "}
};
int location[2][2];         //  Location of the Policeman and the Thief
int turnCount;              //  Number of Game Turns Passed
int botLocation[];
char map[18][18] = {        //  A Blank of the Game Map
        {" ________________ "},
        {"|        |       |"},
        {"|                |"},
        {"|   |         |  |"},
        {"|   |         |  |"},
        {"|                |"},
        {"|      ---       |"},
        {"|      |         |"},
        {"|                 "},
        {"|          |     |"},
        {"|   ---    |     |"},
        {"|     |    |     |"},
        {"|          |-    |"},
        {"|                |"},
        {"|                |"},
        {"|  ---           |"},
        {"|                |"},
        {"|________________|"}


    };
char mapTemp[18][18];       //  Cached Map that Contains the Thief and Policeman Icons

void ArrayPrint();

void wait(int duration) {
    double startTime = time(NULL);
    while(duration > (time(NULL) - startTime)){};
}

void loading() {
    ArrayPrint(7, 58, loadingScreen);
    wait(LOADING_TIME);
}

int WinLoseCheck() {        //  Function Used to Check the Win/Lose Conditions
    if (location[0][0] == 8 && location[0][1] == 16)    //  Check for the Player's Location Compared to the Escape Square
        return 1;
    else if(location[1][0] == location[0][0] && location[1][1] == location[0][1])      // Checks if the Player and the Thief are on the Same Square
        return 2;
    else
        return 0;
}

int DifficultySelector() {  //  Difficulty Selector
    selection:{
    system("clear");
    int selection = NULL;
    printf("PLease Select a Difficulty:\n1.Normal\n2.Hard\n");
    scanf("%d", &selection);
    if (selection != 1 && selection != 2) {
        printf("\n\nmake a valid selection. \n Press Enter to continue.\n");
        getchar();
        goto selection;
    }
    system("clear");
    return selection;
    }   
}

void ArrayPrint(int rowMax, int columnMax,char arr[rowMax][columnMax]) {      //  Two dimensional array printer
    for(int row = 0; row < rowMax; row++) {
        for(int column = 0; column < columnMax; column++) {
            printf("%c", arr[row][column]);
        }
    printf("\n");
    }
}

void PCHardMove() {     //  Intelligent Computer Move Calculations
    start:{
    float distance[4];
    float smallest = 1000000;
    int index = 0;
    //  Calculations of every possible move's relative distance to the Players Current Location (In Manhattan Distance)
    distance[0]    =   abs(location[0][0] - (location[1][0] + 1)) + abs(location[0][1] - location[1][1]); //up
    distance[1]  =   abs(location[0][0] - (location[1][0] - 1)) + abs(location[0][1] - location[1][1]);   //down 
    distance[2]  =   abs(location[0][0] - location[1][0]) + abs(location[0][1] - (location[1][1] - 1));   //left
    distance[3] =   abs(location[0][0] - location[1][0]) + abs(location[0][1] - (location[1][1] + 1));    //right
    //  Collision check for the PC, since the map is confined the distance to player cant be larger than 1000000, by setting the non-feasable to 1000000 PC avoid collisions
    //  because there has to be a feasable square in the map By design
    if(mapTemp[location[1][0] + 1][location[1][1]] != ' ')  distance[0] = 1000000;
    if(mapTemp[location[1][0] - 1][location[1][1]] != ' ')  distance[1] = 1000000;
    if(mapTemp[location[1][0]][location[1][1] - 1] != ' ')  distance[2] = 1000000;
    if(mapTemp[location[1][0]][location[1][1] + 1] != ' ')  distance[3] = 1000000;    
    for (int i = 0; i < 4; i++) {
        if (distance[i] < smallest) {
            smallest = distance[i];
            index = i;
        }
        else if (distance[i] == smallest) { //  Randomizer for the conditions where the distances are the same 
            int test = rand() % 2;
            if(test == 1) {
                smallest = distance[i];
                index = i;
            }
        }
    }
    switch (index)      //  Updates players position
    {
    case 0:
                location[1][0] += 1;
        break;
    case 1:
                location[1][0] -= 1;
        break;
    case 2:
                location[1][1] -= 1;
        break;
    case 3:
                location[1][1] += 1;
        break;
    default:
        break;
    }
    }
}

//Cenk Ergen

void PlayerMove() {     //  Player Input Handler
    start: {
        char c;                                         
        if (turnCount == 0) c = 'a';
        while ((c = getchar()) != '\n' && c != EOF) { }   //Function is used to clear the char buffer before continuing the process 
        char move = getchar();
        if (move == 'e') exit(0);
        switch (move)                                   //  Handler for the Player Input / Collision Check
        {
        case 'w':
            if(mapTemp[location[0][0] - 1][location[0][1]] == ' ')
                location[0][0] -= 1;
            else {
                printf("make a valid move. Press enter to proceed\n");
                getchar();
                goto start;
            }
            break;
        case 's':
            if(mapTemp[location[0][0] + 1][location[0][1]] == ' ')
                location[0][0] += 1;
            else {
                printf("make a valid move. Press enter to proceed\n");
                getchar();
                goto start;
            }
            break;
        case 'a':
            if(mapTemp[location[0][0]][location[0][1] - 1] == ' ')
                location[0][1] -= 1;
            else {
                printf("make a valid move. Press enter to proceed\n");
                getchar();
                goto start;
            }
            break;
        case 'd':
            if(mapTemp[location[0][0]][location[0][1] + 1] == ' ')
                location[0][1] += 1;
            else {
                printf("make a valid move. Press enter to proceed\n");
                getchar();
                goto start;
            }
            break;
        default:
            printf("make a valid move\n");
            goto start;
            break;
        }
    }
}

void PCMove() {     //  Random Move Calculator for Computer
    start: {
        srand(time(NULL));
        int move = rand()%4;
        switch (move)
        {
        case 0:
            if(mapTemp[location[1][0] - 1][location[1][1]] == ' ')
                location[1][0] -= 1;
            else {
                goto start;
            }
            break;
        case 1:
            if(mapTemp[location[1][0] + 1][location[1][1]] == ' ')
                location[1][0] += 1;
            else {

                goto start;
            }
            break;
        case 2:
            if(mapTemp[location[1][0]][location[1][1] - 1] == ' ')
                location[1][1] -= 1;
            else{
                goto start;
            }
            break;
        case 3:
            if(mapTemp[location[1][0]][location[1][1] + 1] == ' ')
                location[1][1] += 1;
            else {
                goto start;
            }
            break;
        default:
            break;
        }
    }
}

void LoadMap() {       //   Injects policeman and thief locations into the map and loads it
    system("clear");
    for(int row = 0; row < 18; row++) {
        for(int column = 0; column < 18; column++) {
            mapTemp[row][column] = map[row][column];
        }
    }
    mapTemp[location[0][0]][location[0][1]] = 'T';
    mapTemp[location[1][0]][location[1][1]] = 'P';
    ArrayPrint(18, 18, mapTemp);      //Prints the map to the screen
}

//Cenk Ergen

void CharacterSpawner() {       //  Random spawn location generator for thief and policeman
    srand(time(NULL));
    int locationTemp[2];
    int testThief = 0, testPolice = 0;
    thief:
    {
    int thief = 0;
    while (testThief != 1) {
        locationTemp[0] = rand()%16 + 1;
        locationTemp[1] = rand()%16 + 1;
        if (map[locationTemp[0]][locationTemp[1]] != ' ') goto thief;   //  PLayer Wall Clip Check
        if(abs(locationTemp[0] - 8) + abs(locationTemp[1] - 16) > 15) {
            testThief = 1;
            location[0][0] = locationTemp[0];
            location[0][1] = locationTemp[1];    
        }
    }
    }
    police:
    {
    while (testPolice != 1) {
        locationTemp[0] = rand()%16 + 1;
        locationTemp[1] = rand()%16 + 1;
        if (map[locationTemp[0]][locationTemp[1]] != ' ') goto police;  //  PC Wall Clip Check
        if(abs(locationTemp[0] - location[0][0]) + abs(locationTemp[1] - location[0][1]) > 15) {
            location[1][0] = locationTemp[0];
            location[1][1] = locationTemp[1];
            testPolice = 1;
        }
    }
    }
}

int Engine() {      // Game engine 
    int difficulty = DifficultySelector();
    printf("Use W,A,S,D + Enter to move. Input 'E' to exit...Press enter to proceed");
    char c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    getchar();
    CharacterSpawner();
    LoadMap();
    int gameResult = 0;
    while (gameResult == 0) { 
        LoadMap();
        PlayerMove();
        gameResult = WinLoseCheck();
        if (difficulty == 1)  PCMove();
        else PCHardMove();
        gameResult = WinLoseCheck();
        LoadMap();
        turnCount++;
    }
    return gameResult;
}

//Cenk Ergen

void main() {
    loading();
    gameStart:{
        int result = Engine();
        switch (result)
        {
        case 1:
           printf("congragulations. Your score is %d\n\n\n", (3000 - (turnCount * 10)));
           break;
        case 2:
          printf("try again\n");
           break;
        default:
           break;
        }
    printf("Would you like to play again?   y/n\n");
    char nextGame;
    char c;
    while ((c = getchar()) != '\n' && c != EOF) { }
    nextGame = getchar();
        switch (nextGame){
            case 'y':
                goto gameStart;
                break;
            case 'n':
                exit(0);
                break;
            default:
                break;
        }
    }
}