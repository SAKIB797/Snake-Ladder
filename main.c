#include <stdio.h>
#include <stdlib.h> // for rand function
#include <string.h> // for adding mode in score board by strcpy
#include <time.h>   // for date and time

struct ScoreBoard
{
    char mode[50];
    int round;
    char p1_name[25];
    char p2_name[15];
} gamePlay;

int rollDice()
{
    // rand() function for random integer
    return (rand() % 6) + 1;
    // dice value always remains between 1-6
}

// draw the game table
// update the game table after every round
void displayBoard(int player1Position, int player2Position)
{
    printf("|-------------------------------------------------|\n");
    printf("| Snakes: 99 to 1, 65 to 40, 25 to 9              |\n");
    printf("| Ladders: 13 to 42, 60 to 83, 70 to 93           |\n");
    printf("|-------------------------------------------------|\n");
    printf("|   %s's Position: %-3d | %s's Position: %-3d|\n", gamePlay.p1_name, player1Position, gamePlay.p2_name, player2Position);
    printf("|-------------------------------------------------|\n");

    int row, col, cellValue;

    for (row = 10; row >= 1; row--)
    {
        printf("|");
        for (col = 1; col <= 10; col++)
        {
            cellValue = row % 2 == 0 ? row * 10 - col + 1 : row * 10 - 10 + col;

            if (cellValue == player1Position)
                printf(" P1 ");
            else if (cellValue == player2Position)
                printf(" P2 ");
            else
                printf(" %-3d", cellValue);

            printf("|");
        }
        printf("\n");
    }

    printf("---------------------------------------------------\n");
}

// Main Function Start Here
int main()
{
    srand(time(NULL)); // Initialize random seed

    int player1Position = 0, player2Position = 0, currentPlayer = 0;
    char choice;

    // Game title and other information
    printf("|-------------------------------------------------|\n");
    printf("|              SNAKE AND LADDER GAME              |\n");
    printf("|      Author: Iftekhar Hossain - B220101024      |\n");
    printf("|    Collaborator: Nusrat Jahan - B220101022      |\n");
    printf("|           Inspiration: GeeksforGeeks            |\n");
    printf("|-------------------------------------------------|\n");



    // Player name selection
    printf("\n> Player 1 name: ");
    scanf(" %[^\n]", gamePlay.p1_name);
    printf("> Player 2 name: ");
    scanf(" %[^\n]", gamePlay.p2_name);

    // Mode selection
    int mode;
    printf("Select game mode:\n");
    printf("1. Limited round\n2. Unlimited round\n> ");
    scanf(" %d", &mode);

    // Round selection for limited mode
    int no_of_round;
    if (mode == 1)
    {
        printf("You selected limited mode\nHow many rounds do you want to play?\n> ");
        scanf(" %d", &no_of_round);
        strcpy(gamePlay.mode, "Limited round mode");
        gamePlay.round = no_of_round;
    }
    else
    {
        strcpy(gamePlay.mode, "Unlimited round Mode");
    }

    // Start game round
    while (1)
    {

        // for limited mode
        if (mode == 1 )
        {
            if(no_of_round)
                no_of_round--;
            else
                break;
        }

        // Command for rolling the dice or quit the game
        printf("\nPlayer %d, press 'r' to roll the dice or 'q' to quit: ", currentPlayer + 1);
        scanf(" %c", &choice);

        if (choice == 'q')
        {
            printf("Game ended by user.\n");
            break;
        }
        else if (choice != 'r')
        {
            printf("Invalid input. Please try again.\n");
            continue;
        }

        // Roll the dice
        int dice = rollDice();
        printf("Player %d rolled the dice: %d\n", currentPlayer + 1, dice);

        // Check the current player and update their position
        if (currentPlayer == 0) // For player 1 when currentPlayer value is 0
        {
            int newPosition = player1Position + dice;
            if (newPosition == 99)
                newPosition = 1;
            else if (newPosition == 65)
                newPosition = 40;
            else if (newPosition == 25)
                newPosition = 9;
            else if (newPosition == 13)
                newPosition = 42;
            else if (newPosition == 60)
                newPosition = 83;
            else if (newPosition == 70)
                newPosition = 93;

            player1Position = newPosition;

            if (player1Position >= 100)
            {
                break;
            }
        }
        else // For player 2 when currentPlayer value is 1
        {
            int newPosition = player2Position + dice;
            if (newPosition == 99)
                newPosition = 1;
            else if (newPosition == 65)
                newPosition = 40;
            else if (newPosition == 25)
                newPosition = 9;
            else if (newPosition == 13)
                newPosition = 42;
            else if (newPosition == 60)
                newPosition = 83;
            else if (newPosition == 70)
                newPosition = 93;

            player2Position = newPosition;

            if (player2Position >= 100)
            {
                break;
            }
        }

        // display updated game board
        displayBoard(player1Position, player2Position);
        // Toggle player turn (0 for player 1, 1 for player 2)
        currentPlayer = (currentPlayer + 1) % 2;
    }

    // Game result
    if (choice != 'q')
    {
        if (player1Position > player2Position)
            printf("\n%s wins!\n", gamePlay.p1_name);
        else if (player1Position == player2Position)
            printf("\n Draw!\n Play again\n");
        else
            printf("\n%s wins!\n", gamePlay.p2_name);
    }

    // For current date and time setup
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);

    // Open file in append mode
    FILE *score = fopen("scores.txt", "a");

    // Entering data in file
    fprintf(score, "Score Board\n------------------\n");
    fprintf(score, "%s", asctime(tm_info)); // Current date and time
    fprintf(score, "Game mode: %s\n", gamePlay.mode);
    if (mode == 1)
        fprintf(score, "Number of round: %d\n", gamePlay.round);

    fprintf(score, "Player 1 name: %s\nPlayer 2 name: %s\n", gamePlay.p1_name, gamePlay.p2_name);  // write players name in file
    fprintf(score, "Player 1 score: %d\nPlayer 2 score: %d\n", player1Position, player2Position); // write players score in file

    if(choice != 'q')  // write in file if game not ended by the user, It means the continuity of the game until a player win or draw.
    {
        if (player1Position > player2Position)
            fprintf(score, "Result: %s wins!\n", gamePlay.p1_name);
        else if (player1Position == player2Position)
            fprintf(score, "Result: Draw! Play again\n");
        else
            fprintf(score, "Result: %s wins!\n", gamePlay.p2_name);
    }
    else // write if game ended by the players
    {
        fprintf(score,"Game ended by user.\n");
    }
    fprintf(score, "\n\n");

    fclose(score); // Close the file

    return 0;
}
