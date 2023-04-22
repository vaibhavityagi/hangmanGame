#include <iostream>
#include <string.h>
#include <fstream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <vector>
using namespace std;

void welcome()
{
     cout << "\t\t\t*********************" << endl
          << "\t\t\t  Hangman: The Game  " << endl
          << "\t\t\t*********************" << endl;

     cout << endl;

     cout << "\t\t\t    INSTRUCTIONS \n\nSave the man from hanging by correctly guessing the letters in the code word.\n\n"
          << "You have 6 tries to guess the code word. With every incorrect guess the man gets closer to death.\n"
          << endl;
     cout << "You get a hint at the second last guess. But it will reduce one life!" << endl
          << endl;

     system("PAUSE");
     system("CLS");
}

void defaultSketch()
{
     cout << "\t\t\t+-------+" << endl
          << "\t\t\t|\t|" << endl
          << "\t\t\t\t|" << endl
          << "\t\t\t\t|" << endl
          << "\t\t\t\t|" << endl
          << "\t\t\t**********" << endl;
}

void firstError()
{
     cout << "\t\t\t+-------+" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t  O\t|" << endl
          << "\t\t\t\t|" << endl
          << "\t\t\t\t|" << endl
          << "\t\t\t**********" << endl;
}

void secondError()
{
     cout << "\t\t\t+-------+" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t  O\t|" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t   \t|" << endl
          << "\t\t\t**********" << endl;
}

void thirdError()
{
     cout << "\t\t\t+-------+" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t  O\t|" << endl
          << "\t\t\t /|\t|" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t   \t|" << endl
          << "\t\t\t**********" << endl;
}

void fourthError()
{
     cout << "\t\t\t+-------+" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t  O\t|" << endl
          << "\t\t\t /|\\\t|" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t   \t|" << endl
          << "\t\t\t**********" << endl;
}

void fifthError()
{
     cout << "\t\t\t+-------+" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t  O\t|" << endl
          << "\t\t\t /|\\\t|" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t /\t|" << endl
          << "\t\t\t**********" << endl;
}

void sixthError()
{
     cout << "\t\t\t+-------+" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t  O\t|" << endl
          << "\t\t\t /|\\\t|" << endl
          << "\t\t\t  |\t|" << endl
          << "\t\t\t / \\\t|" << endl
          << "\t\t\t**********" << endl;
}

void drawMan(int err)
{
     switch (err)
     {
     case 1:
          firstError();
          break;
     case 2:
          secondError();
          break;
     case 3:
          thirdError();
          break;
     case 4:
          fourthError();
          break;
     case 5:
          fifthError();
          break;
     case 6:
          sixthError();
          break;
     default:
          defaultSketch();
     }
}

int randomNumber(int choice)
{
     /*
     level 1 -> 1-158
     level 2 -> 159 - 456
     level 3 -> 457 - 669
     */
     srand(time(NULL));
     int random;

     if (choice == 1)
          random = (rand() % (158 - 1 + 1)) + 1;
     else if (choice == 2)
          random = (rand() % (456 - 159 + 1)) + 159;
     else
          random = (rand() % (669 - 457 + 1)) + 457;
     return random;
}

string randomWord(int choice)
{
     int randomNum = randomNumber(choice);
     int counter = 1;
     string line, word;
     ifstream file("wordList.txt");
     while (getline(file, line))
     {
          if (randomNum == counter)
          {
               word = line;
               break;
          }
          counter++;
     }
     return word;
}

char hint(string w, vector<char> &guess)
{
     // cout << "inside\n";
     int index = 0;
     for (int i = 0; i < guess.size(); i++)
     {
          if (guess[i] == '_')
          {
               index = i;
               break;
          }
     }
     for (int i = 0; i < w.length(); i++)
     {
          return w[index];
     }
}

void gameOver(string word)
{
     system("CLS");
     cout << "\t\t    The word was " << word << endl
          << endl;
     ;
     cout << "\t\t\tGAME OVER!" << endl
          << endl;
     sixthError();
     cout << endl;

     cout << "You couldn't save the man from hanging." << endl;
}

void youWon()
{
     system("CLS");
     cout << "\t\t\tYOU WON!" << endl
          << endl;
     cout
         << "\t\t\t    O" << endl
         << "\t\t\t   /|\\" << endl
         << "\t\t\t    |" << endl
         << "\t\t\t   / \\" << endl
         << "\t\t\t**********" << endl
         << endl;
     cout << "You saved the man from hanging!" << endl;
}

int main()
{
     welcome();

     int choice;
     cout << "\t\t\tChoose the level" << endl
          << endl;
     cout << "\t\t\t1. Easy" << endl
          << "\t\t\t2. Medium" << endl
          << "\t\t\t3. Hard" << endl;
     cin >> choice;

     system("CLS");

     string word = randomWord(choice);
     vector<char> guess;
     vector<char> incorrectLetters;

     cout << "The word to be guessed has " << word.length() << " letters" << endl;
     for (int i = 0; i < word.length(); i++)
     {
          guess.push_back('_');
          cout << "_ ";
     }

     cout << endl
          << endl;

     defaultSketch();

     int tryC = 0;
     int win = 0;

     while (tryC != 6 && win < word.length())
     {
          char letter;
          cout << "Enter the letter: ";
          cin >> letter;

          int flag = 0;

          // iterating over the word letter by letter
          for (int i = 0; i < word.length(); i++)
          {
               if (word[i] == letter)
               {
                    guess[i] = letter;
                    win++;
               }
               else
                    flag++;
          }

          // the letter is not present in the word
          if (flag == word.length())
          {
               tryC++;
               incorrectLetters.push_back(letter);
          }

          // hint if given when there is only one try left
          int once = 0;
          if (tryC == 4 && once == 0)
          {
               system("CLS");

               char h;
               cout << "Do you want a hint? (Y/N) ";
               cin >> h;
               cout << endl;
               if (h == 'Y' || h == 'y')
               {
                    cout << hint(word, guess) << " is one of the letters" << endl;
                    tryC++;
               }
               else
               {
                    cout << "You choose to not opt for a hint" << endl;
                    once++;
               }
               cout << endl;
               system("PAUSE");
          }

          system("CLS");

          cout << "Tries left: " << 6 - tryC << endl;

          cout << "Incorrect letters: ";
          for (auto l : incorrectLetters)
               cout << l << " ";

          cout << endl;

          // printing the word being guessed
          for (auto l : guess)
               cout << l << " ";

          cout << endl
               << endl;

          drawMan(tryC);

          cout << endl;
     }

     if (tryC >= 6)
     {
          gameOver(word);
     }
     else
          youWon();

     return 0;
}
