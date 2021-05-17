#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;
char getRandomLowerCharacters()
{
    return rand() % 25 + 97;
}
char getRandomUpperCharacters()
{
    return rand() % 25 + 65;
}
char getRandomDigit()
{
    return rand() % 10 + 48;
}
char getRandomSpecialCharacters()
{
    char special[] = {'@', '&', '$', '#'};
    return special[rand() % 5];
}
int main()
{
    srand(time(0));

    int length, randInt, p = 0, count[4];
    cout << "Enter length of password : ";
    cin >> length;
    char *password = new char[length + 1];
    password[length] = '\0';
    for (int i = 0; i < 4; i++)
    {
        if (i <= length % 4)
            count[i] = length / 4 + 1;
        else
            count[i] = length / 4;
    }
    while (p != length)
    {
        randInt = rand() % 4;
        if (count[randInt] != 0)
        {
            switch (randInt)
            {
            case 0:
                password[p++] = getRandomUpperCharacters();
                break;
            case 1:
                password[p++] = getRandomLowerCharacters();
                break;
            case 2:
                password[p++] = getRandomDigit();
                break;
            case 3:
                password[p++] = getRandomSpecialCharacters();
                break;
            }
            count[randInt] -= 1;
        }
    }
    for (int i = 0; i < length; i++)
    {
        cout << password[i];
    }

    return 0;
}