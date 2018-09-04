/*
The game logic (not view code or direct user interaction)
The game is a simple guess the word game based on mastermind.
*/

#pragma once

#include <string>

// To make Syntax Unreal friendly
using FString = std::string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus
{
	Invaild_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame
{
public:
	FBullCowGame();// constructor
	~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;

	void Reset();
	FBullCowCount SumbitVaildGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
};

