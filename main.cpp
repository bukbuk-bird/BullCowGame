/* this is the console executable that makes use of the BullCow class This acts as the view in a MVC pattern and is responsible for all user interaction. For game logic, see the FBullCowGame Class. */

#include <iostream>
#include <string>
#include "FBullCowGame.h"

using FText = std::string;

void PrintIntro();
FText GetValidGuess();
void PlayGame();
bool AskToPlayAgain();

FBullCowGame BCGame; // Instantiate a new game

// entry point for the game

int main()
{

	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain);
	return 0; // exit the application
}


// Intro Method here
void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}


// Iterates through number of turns and asks for guesses
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// My loop for number of turns asking for guesses
	for (int32 count = 1; count <= MaxTries; count++){	// TODO change from FOR to WHILE
		FText Guess = GetValidGuess(); 

		// submit Valid Guess to the game and recieve counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << std::endl;
	}
	// TODO summarize game
}


bool AskToPlayAgain()
{
	std::cout << "do you want to play again? (y/n)";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');

}


// loop continually until player gives a valid guess 
FText GetValidGuess() 
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//Get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << ". enter your guess: ";
		std::getline(std::cin, Guess);

		// check status and get feedback
		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess must be an isogram.";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter your guess in lowercase letters.";
		default:
			//assuming the guess is valid
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK); //keep looping until we get no errors
	return Guess;
}


