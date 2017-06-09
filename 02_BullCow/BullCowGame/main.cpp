/*
	This is a console executable, that makes use of the BullCow class.
	
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "main.h"
#include "FBullCowGame.h"

FBullCowGame BCGame;

int main() 
{
	PrintIntro();
	do {
		PlayGame();
	} while (WantsToPlayAgain());
	PrintOutro();
	
	return 0;
}

void PrintIntro() 
{
	int32 word_length = BCGame.GetHiddenWorldLength();
	std::cout << "Welcome to Bulls & Cows." << std::endl;
	std::cout << "Can you guess the " << word_length << " letter isogram I'm thinking of?" << std::endl;
}

void PrintOutro()
{
	std::cout << "Thanks for playing the game, see you soon!" << std::endl;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "Contratulations, you've won in " << BCGame.GetCurrentTry()-1 << " rounds.\n";
	}
	else
	{
		std::cout << "Sorry, you've lost.\n";
	}
}

void PlayGame() 
{
	BCGame.Reset();

	int32 MaxTries = BCGame.GetMaxTries();
	FString guess;
	FBullCowCount BullCowCount;
	bool won = false;

	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		guess = GuessValidWord();
		BullCowCount = BCGame.SubmitValidGuess(guess);
		std::cout << "Bulls: " << BullCowCount.bulls << " Cows: " << BullCowCount.cows << "\n\n";
	}

	PrintGameSummary();
}

FString GuessValidWord()
{
	FString guess;
	EWordStatus status = EWordStatus::Invalid_Status;
	do {
		int32 CurrentTry = BCGame.GetCurrentTry();
		FString message = "";

		std::cout << "\n\nTry #" << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: " << std::endl;
		getline(std::cin, guess);
	
		status = BCGame.CheckGuessValidity(guess);
		switch (status) {
			case EWordStatus::Not_Isogram:
				message = "Please enter a word without repeating characters.\n";
				break;
			case EWordStatus::Not_Lowercase:
				message = "Please enter all lowercase characters.\n";
				break;
			case EWordStatus::Wrong_Length:
				message = "Please enter a " + std::to_string(BCGame.GetHiddenWorldLength()) + " letter word.\n";
				break;
			default:
				message = "Your guess is " + guess + "\n";
		}
		std::cout << message << std::endl;
	} while (status != EWordStatus::OK);
	return guess;
}

 

bool WantsToPlayAgain() 
{
	FString answer = "";
	bool wants_to_play = false;
	std::cout << "Do you want to play again? (yes/no)" << std::endl;
	while (answer != "yes" ^ answer == "no"){
		getline(std::cin, answer);
		if (answer == "yes") {
			wants_to_play = true;
		} else {
			if (answer == "no") {
				wants_to_play = false;
			} else {
				std::cout << "Please answer with yes/no" << std::endl;
			}
		}
	}

	return wants_to_play;
}