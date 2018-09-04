/*
This is the game logic for the Bull Cow Game.
This acts as the Model in the MVC pattern, and is
resoponsible for all game logic and data nessiary to play the game.
*/

#pragma once

#include "FBullCowGame.h"
#include <map>

// To make Syntax Unreal friendly
#define TMap std::map 
using int32 = int;

FBullCowGame::FBullCowGame(){ Reset(); }
FBullCowGame::~FBullCowGame(){}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }


EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	// if the guess isn't an isogram
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	// if the guess isn't all lowercase
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	// if the guess length is wrong
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
}

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,16},{7,20}};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 8;
	MyCurrentTry = 1;

	const FString HIDDEN_WORD = "planet";// This MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	bIsGameWon = false;

	return;
}

//receives a Vaild guess, increments turn, and returns count
FBullCowCount FBullCowGame::SumbitVaildGuess(FString GuessWord)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessWordLength = GuessWord.length();

	for (int32 HChar = 0; HChar < HiddenWordLength; HChar++)
	{
		for (int32 GChar = 0; GChar < GuessWordLength; GChar++)
		{
			// if the letters match
			if (MyHiddenWord[HChar] == GuessWord[GChar])
			{
				// if the letters are in the same place
				if (HChar == GChar)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == HiddenWordLength)
	{
		bIsGameWon = true;
	}
	else
	{
		bIsGameWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }

	// Setup out map
	TMap<char, bool> LetterSeen;

	// For all letters of the word
	for (auto Letter : Word)
	{
		Letter = tolower(Letter);// Handle mixed case

		if (LetterSeen[Letter]) { return false; }// we do NOT have an isogram
		else 
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	// For all letters of the word
	for (auto Letter : Word)
	{
		auto LowerLetter = tolower(Letter);
		if (Letter != LowerLetter) { return false; }// The letter isn't lower case
	}

	return true;
}