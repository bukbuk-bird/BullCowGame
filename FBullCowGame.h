#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_String,
	Not_Lowercase

};

class FBullCowGame 
{
public:
	FBullCowGame(); //constructor
	
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool bIsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; //TODO make a more rich return value
	
	void Reset();  // TODO make a more rich return value
	FBullCowCount SubmitValidGuess(FString Guess);




// ignore for now. focus on interface above
private:
	// see constructor for initialization
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	bool bIsIsogram(FString);

};