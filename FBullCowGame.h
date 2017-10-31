/* Game logic (no direct user interaction here) simple word game based on "mastermind" */
#pragma once
#include <string>

// makes the syntax unreal friendly
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
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const; 
	
	void Reset();  
	FBullCowCount SubmitValidGuess(FString Guess);
	/* FString SelectWordLength(int32 Length); */

private:
	// see constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsIsogram(FString) const;
	bool bGameIsWon;
	bool bIsLowerCase(FString) const;


};