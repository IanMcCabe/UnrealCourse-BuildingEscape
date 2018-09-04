/*
This is the console executable, that makes use of the BullCow.cs
This acts as a view in the MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once

#include <iostream>
#include <string>
#include <algorithm>
#include "Main.h"
#include "FBullCowGame.h"

// To make Syntax Unreal friendly
using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
FText GetVaildGuess();

FBullCowGame Game;// instantiates a new game, which we re-use across plays

// this is the entry point for our application
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());

	return 0;// exit the application
}

void PrintIntro()
{
	std::cout << "Welcome to Bulls and Cows, and fun word game." << std::endl;
	std::cout << "Bulls = correct letter, RIGHT place." << std::endl << "Cows = correct letter, WRONG place.\n";
	std::cout << std::endl;
	std::cout << "Can you guess the " << Game.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

void PrintGameSummary()
{
	if (Game.IsGameWon())
	{
		std::cout << "WELL DONE - YOU WIN!!!" << std::endl;
	}
	else
	{
		std::cout << "Better Luck Next Time!" << std::endl;
	}
	std::cout << std::endl;
	return;
}

// Plays a single game to completion
void PlayGame()
{
	Game.Reset();
	int32 MaxTries = Game.GetMaxTries();
	
	// Loop asking for guesses while the game
	// is NOT worn and there are still tries remaining
	while (!Game.IsGameWon() && Game.GetCurrentTry() <= Game.GetMaxTries())
	{
		FText Guess = GetVaildGuess();

		// submit vaild guess to the game
		FBullCowCount BullCowCount = Game.SumbitVaildGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();
	return;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again (y/n)?: ";
	FText response = "";
	std::getline(std::cin, response);
	std::cout << std::endl;

	// Transforms repsonse into lower charaters for comparison.
	transform(response.begin(), response.end(), response.begin(), ::tolower);
	
	if (response[0] == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}

// Loop continually until the user gives a vaild guess
FText GetVaildGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invaild_Status;

	do
	{
		int32 CurrentTry = Game.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << Game.GetMaxTries();
		std::cout << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		Status = Game.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters.\n" << std::endl;;
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << Game.GetHiddenWordLength() << " Letter word.\n" << std::endl;;
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters.\n" << std::endl;;
			break;
		default:
			// assume the guess is vaild
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

