#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>    //  header file for gotoxy

COORD coord = {0 , 0}; // this is global variable

void gotoxy(int x , int y)
{
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE) , coord);
}

void textattr(int i)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE) , i);

}

void HighLighted_Line(void)
{
    char Line_arr[20] = "                   ";
    char Inserted_Char;
    int exit = 0;
    int Current_Position = 0;
    int End_of_Line = 0;
    int buffer = 0;
    printf("Please enter your line in the box:\n");
    do
    {
        /* start to print the highlighted word in the specific Location. */
        gotoxy(5, 5);
        textattr(0x4F);
        _cprintf("%s",Line_arr);
        /* condition to move curse with the letters. */
        if(Current_Position == 0)
           gotoxy(5 , 5);
        else
            gotoxy(5 + Current_Position - 1, 5);
        /* get insertion from the user. */
        Inserted_Char = getch();
        /* If condition to Inserted_Chareck if the user inserted special Inserted_Chararacter or normal letter to display it. */
        if(Inserted_Char == -32)
        {
            Inserted_Char = getch();
            switch(Inserted_Char)
            {
                /* Go to the End of the Line */
                case 71:
                    Current_Position = 0;
                    break;
                /* Move backward */
                case 75:
                    Current_Position--;
                    /* stop the curse in the start of the highlighted area. */
                    if(Current_Position < 0)
                        Current_Position = 0;
                    break;
                /* Move forward. */
                case 77:
                    /* stop curse at the end of the highlighted area. */
                    if(Current_Position < End_of_Line)
                    {
                        Current_Position++;
                        if(Current_Position > 19)
                            Current_Position = 19;
                    }

                    break;
                /* Go to the end of the line. */
                case 79:
                    if(End_of_Line <= 19)
                        Current_Position = End_of_Line;
                    else
                        Current_Position = 19;
                    break;
                /* Delete all data from insertion area. */
                case 83:
                    strcpy(Line_arr,"                   ");
                    Current_Position = 0;
                    End_of_Line = 0;
                    break;
            }
        }
        else
        {
            switch(Inserted_Char)
            {
                /* backspace Inserted_Charoose */
                case 8:
                    /* check if we are in the range of the helighted area. */
                    if(Current_Position > 0 && Current_Position < 19)
                    {
                        /* save the location to return to it */
                        buffer = Current_Position-1;
                        /* shafted all the string after remove the char. */
                        while(Current_Position < 19)
                        {

                            Line_arr[Current_Position-1] = Line_arr[Current_Position];
                            Current_Position++;
                        }
                        /* return to the position */
                        Current_Position = buffer;
                        /* update the location of the end of the line. */
                        End_of_Line--;
                    }
                    /* if we are in the limit of the highlighted area. */
                    else if(Current_Position == 19)
                    {
                        Line_arr[18] = ' ';
                        Current_Position = 18;
                        End_of_Line = 18;
                    }
                    break;
                /* Enter button */
                case 13:
                    exit = 1;
                    break;
                /* new Inserted_Chararacter in the line. */
                default:
                    /* check if we are in the limit of the highlighted area. */
                    if(Current_Position <= 18)
                    {
                        Line_arr[Current_Position] = Inserted_Char;
                        Current_Position++;
                    }
                    break;

            }
            /* update the end of the line position */
            if(Current_Position > End_of_Line)
            {
                End_of_Line = Current_Position;
            }
        }
    }while(exit == 0);
    /* to print the entered line. */
    gotoxy(0 , 8);
    textattr(0x07);
    _cprintf("your Line is: ", Line_arr);
    textattr(0x4F);
    _cprintf("%s",Line_arr);
    textattr(0x07);
}
