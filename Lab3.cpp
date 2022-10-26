// Victor Pueyo Siska
// This is my Lab 3 (BlackJack)
// I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include <iostream>
#include <ctime>
#include <iomanip>
#include <windows.h>

using namespace std;

void PrintHeaders();
void showCard(int&, int, int, int, int, char);
void gotoxy(int, int);
void firstCards(int[], int[]);
void Deal_Two_Cards(int&, int[], int[], int);
void dealer(int[], int[], int);
void WinTieLoss(int[]);
void showTotal(int, int, int[]);


int main()
{
    int cards[52], dup[52] = { 0 }, i, j, suit, number = 15, num, row = 2, totals[8] = { 0 }, value;
    char next_game = 'Y', letter = ' ';
    
    //Changes the color of the background (A = Green) and as well as the letters color (0 = Black).
    system("COLOR A0");
    
    srand(time(NULL));

    //The do while will run as long as the player says he wants to keep playing, by putting (Y) when asked
    do
    {
        // Clears the screen.
        system("cls");

        for (i = 0; i < 52; i++)
        {
            dup[i] = 0;
        }
        
        for (i = 0; i < 8; i++)
        {
            totals[i] = 0;
        }

        for (i = 0; i < 52; i++)
        {
            num = rand() % 52;

            while (dup[num])
            {
                num = rand() % 52;
            }

            cards[i] = num;
            dup[num] = 1;
        }

        PrintHeaders();
        firstCards(cards, totals);

        for (i = 1; i < 8; i++)
        {
            Deal_Two_Cards(number, cards, totals, i);
        }

        dealer(cards, totals, number);
        
        WinTieLoss(totals);

        //Makes a sound if you go over.
        Beep(200, 100);
        Beep(600, 500);

        gotoxy(10, 15);

        cout << "Would you like to play again? Please enter (Y / N): ";
        cin >> next_game;

    } while (next_game == 'Y');

    system("cls");

    cout << "Thank you for playing!" << endl << endl;
    
    system("pause");
    return 0;
    
    /* 
    // Displays all the cards it is and its value.
    for (i = 0; i < 52; i++)
    {
        cout << setw(3) << cards[i];
        cout << setw(2) << char(cards[i] / 13 + 3);
        
        switch (cards[i] % 13)
        {
            case 0: cout << setw(3) << 'A' << setw(3) << 1;
                break;
            case 10: cout << setw(3) << 'J' << setw(3) << 10;
                break;
            case 11: cout << setw(3) << 'Q' << setw(3) << 10;
                break;
            case 12: cout << setw(3) << 'K' << setw(3) << 10;
                break;
            default: cout << setw(3) << ' ' << setw(3) << cards[i] % 13 + 1;
        }
        cout << endl;
    }
    */
    
    // loop with a call to a function to deal cards to a player
    // call a function to finish the dealer
}

//This funtion diplays the header: Dealer, Player1, Player2...
void PrintHeaders()
{
    cout << setw(2) << "D" << setw(10) << " P1" << setw(9) << "P2" << setw(9) << "P3" << setw(9) << "P4"
        << setw(9) << "P5" << setw(9) << "P6" << setw(9) << "P7" << endl;

    cout << setw(3) << "==" << setw(9) << "==" << setw(9) << "==" << setw(9) << "==" << setw(9) << "=="
        << setw(9) << "==" << setw(9) << "==" << setw(9) << "==";

}

//This function shows the type of card it is. The if statements checks if it is a J, Q, K or A and how much it it represents as a number.
//The second if displays the icon of each. 
void showCard(int& number, int i, int row, int num, int suit, char letter)
{
    if (number == 0 || number > 9)
    {
        switch (number)
        {
        case 0:
            letter = 'A';
            number = 1;
            break;
        case 10:
            letter = 'J';
            number = 10;
            break;
        case 11:
            letter = 'Q';
            number = 10;
            break;
        case 12:
            letter = 'K';
            number = 10;
            break;
        }
    }
    else
    {
        number++;
    }

    gotoxy((i % 8) * 9, row);

    if (letter == ' ')
        cout << setw(2) << number << char(suit) << endl;
    else
        cout << setw(2) << letter << char(suit) << endl;

    return;
}

//This function let's you to write whereever you want. There is not any need to follow the line. 
void gotoxy(int h, int w)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (INVALID_HANDLE_VALUE != hConsole)
    {
        COORD pos = { h, w };
        SetConsoleCursorPosition(hConsole, pos);
    }
    return;
}

//This function makes each player start with their first two cards. The dealer just gets one card. 
void firstCards(int cards[], int totals[])
{
    int  row = 2, number, num, suit;
    char letter = ' ';

    for (int i = 0; i < 16; i++)
    {
        if (i == 8)
        {
            row++;
        }

        num = cards[i];
        suit = (num / 13) + 3;
        number = num % 13;

        if (i != 8)
        {
            showCard(number, i, row, num, suit, letter);
            showTotal(i, number, totals);
        }
        else
        {
            gotoxy((i % 8) * 9, row);
            cout << setw(2) << "??" << endl;
        }
    }

    return;
}

//This function deals the second hard, r as many cards as the player wishes. He will be asked each time if they want another card. 
void Deal_Two_Cards(int& track, int cards[], int totals[], int i)
{
    int row = 4, number, suit, num;
    char letter = ' ', next_card;

    //Each player will be asked if they want another card as long as the total is under 21. If they do not want another one, they can typE
    //(N) and it will skip to the next player. 
    if (totals[i] < 21)
    {
        gotoxy(56, 21);
        cout << ' ';

        gotoxy(0, 21);
        cout << "Player " << i << ", would you like to take another card? (Y / N): ";
        cin >> next_card;
    }
    else
    {
        next_card = 'N';
    }

    // This while loop keeps you in the loop until you enter what I asked for.
    while (next_card != 'Y' && next_card != 'N')
    {
        if (totals[i] < 21)
        {
            gotoxy(56, 21);
            cout << ' ';

            gotoxy(0, 21);
            cout << "Player " << i << ", would you like to take another card? (Y / N): ";
            cin >> next_card;
        }
        else
        {
            next_card = 'N';
        }
    }

    //If the players total is less than 21, the player can ask for as many cards as he wishes by putting (N). Once he is asked. 
    while (next_card == 'Y')
    {
        num = cards[track];
        suit = (num / 13) + 3;
        number = num % 13;
        letter = ' ';

        showCard(number, i, row, num, suit, letter);
        showTotal(i, number, totals);


        if (totals[i] < 21)
        {
            gotoxy(56, 21);
            cout << ' ';

            gotoxy(0, 21);
            cout << "Player " << i << ", would you like to take another card? (Y / N): ";
            cin >> next_card;
        }
        else
        {
            next_card = ' ';
        }

        //If the player goes over 21. He is out and the word "OVER!" will be displayed on top of the total, making a beep at the same time.
        if (totals[i] > 21)
        {
            gotoxy((i % 8 * 9), 19);
            cout << "OVER!!";

            //This part makes the sound.
            Beep(700, 300); 
            Beep(500, 100);

            gotoxy(0, 21);
            cout << "                                                            ";
        }

        track++;
        row++;
    }

    return;
}

//This function is for the dealer, he will get cards until he is over 16. 
void dealer(int cards[], int totals[], int j)
{
    int row = 3, i = 0, suit, number, num;
    char letter = ' ';

    gotoxy(0, 21);
    
    cout << "                                                            ";

    while (totals[0] < 17)
    {
        num = cards[j];
        suit = (num / 13) + 3;
        number = num % 13;

        showCard(number, 0, row, num, suit, letter);
        showTotal(0, number, totals);

        j++;
        row++;
    }

    return;
}

// This function determines who won/lost/tied
void WinTieLoss(int totals[])
{
    for (int i = 1; i < 8; i++)
    {
        //Each player's total will be compared to the dealers total. The if statements are to check if you have a higher total, same or lower.
        //If it is higher than the dealers, you won. If it is lower, you lost. If it is the same, you tied.
        if (totals[0] < 22)
        {
            if (totals[i] > totals[0] && totals[i] < 22)
            {
                gotoxy((i % 8) * 9, 21);
                cout << "WIN!" << endl;
            }

            if (totals[i] < totals[0] || totals[i] > 21)
            {
                gotoxy((i % 8) * 9, 21);
                cout << "LOST!" << endl;
            }

            if (totals[i] == totals[0])
            {
                gotoxy((i % 8) * 9, 21);
                cout << "TIE!" << endl;
            }
        }

        //These if statements checks if the the dealer went over 21.
        if (totals[0] > 21)
        {
            if (totals[i] < 22)
            {
                gotoxy((i % 8) * 9, 21);
                cout << "WIN!" << endl;
            }

            if (totals[i] > 21)
            {
                gotoxy((i % 8) * 9, 21);
                cout << "LOST!" << endl;
            }
        }
    }

    return;
}

//This function displays each players total. 
void showTotal(int i, int number, int totals[])
{
    totals[i % 8] += number;

    gotoxy((i % 8) * 9, 20);

    cout << setw(3) << totals[i % 8] << endl;

    return;
}