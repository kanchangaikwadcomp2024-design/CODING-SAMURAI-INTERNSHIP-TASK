#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    int secretNumber, guess;
    int attempts = 0;

    // Seed random generator
    srand((unsigned)time(NULL));

    // Random number between 1 and 100
    secretNumber = rand() % 100 + 1;

    cout << "===== Number Guessing Game =====" << endl;
    cout << "I have selected a number between 1 and 100." << endl;

    while (true) {
        cout << "Enter your guess: ";
        cin >> guess;

        attempts++;

        if (guess > secretNumber) {
            cout << "Too high! Try again.\n";
        }
        else if (guess < secretNumber) {
            cout << "Too low! Try again.\n";
        }
        else {
            cout << "Correct! 🎉\n";
            cout << "You guessed it in " << attempts << " attempts.\n";
            break;
        }
    }

    return 0;
}
