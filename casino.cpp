#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int guess, number, attempts = 0, max_attempts = 5;
    int cash = 100; 
    int bet;

    srand(time(0)); 

    cout << "Welcome to the Casino Number Guessing Game!\n";
    cout << "You have $" << cash << " in chips.\n";

    while (cash > 0) {
        number = rand() % 10 + 1; 
        cout << "\nPlace your bet (You have $" << cash << "): ";
        cin >> bet;

        if (bet > cash || bet <= 0) {
            cout << "Invalid bet. Try again.\n";
            continue;
        }

        cout << "Guess the number between 1 and 10: ";
        cin >> guess;
        attempts++;

        if (guess == number) {
            cout << " You guessed right! You win $" << bet * 2 << "!\n";
            cash += bet*2;
        } else {
            cout << " Wrong guess! The number was " << number << ". You lose $" << bet*2 << ".\n";
            cash -= bet;
        }

        if (cash <= 0) {
            cout << "\nYou've run out of chips. Game over!\n";
        } else {
            char choice;
            cout << "Do you want to keep playing? (y/n): ";
            cin >> choice;
            if (choice != 'y' && choice != 'Y') {
                cout << "\nYou're leaving the casino with $" << cash << ".\n";
                break;
            }
        }
    }

    return 0;
}