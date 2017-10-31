/*This is my class file. It's where my methods are defined. */
#include "FBullCowGame.h"
#pragma once
#include <map>

//makes syntax unreal friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }//default constructor


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const {
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,5}, {6,5} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // must be an isogram

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const // checks if guess is isogram of correct length
{
	if (!bIsIsogram(Guess)) 	// if the guess isn't an isogram, 
	{
		return EGuessStatus::Not_Isogram;	
	}
	else if (!bIsLowerCase(Guess)) 	// if the guess isn't lowercase, TODO write function 
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) 	//if the guess length is wrong
	{
		return EGuessStatus::Wrong_Length;
	}
	else	//otherwise
	{
		return EGuessStatus::OK;
	}

}

// receives a VALID guess, incriments turn, and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

											  // loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		// compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; // incriment bulls
				}
				else {
					BullCowCount.Cows++; // must be a cow
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

/* Function to allow players to choose a word length
FString FBullCowGame::SelectWordLength(FString Length)
{
	std::cout << "Would you like the hidden word to be 3,4 or 5 characters long?";
	FText Length = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');

	if (Length == 3)
		return 3;
	else if (Length == 4)
		return 4;
	else
		return 5;

} */

bool FBullCowGame::bIsIsogram(FString Word) const
{
	if (Word.length() <= 1) {return true;}// treat 0 and 1 letter words as isograms
	TMap<char, bool> LetterSeen; //set up our map
	for (auto Letter : Word) //for all letters of the word
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) { //loop through all letters of the word
			return false;
		}
		else {
			LetterSeen[Letter] = true; 
		}
	}
	return true; // for cases where player enters 0 or 1 letter words
}

bool FBullCowGame::bIsLowerCase(FString Word) const
{
	if (Word == "\O") { return true; }
	if (Word == "      ") { return true; }
	for (auto Letter : Word) {
		if (!islower(Letter)) { 
			return false;
		}
		else {
			return true;
		}
	}
	return false;
}


