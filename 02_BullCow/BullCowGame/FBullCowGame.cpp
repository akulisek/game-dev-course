#pragma once

#include "FBullCowGame.h"
#include <math.h>
#include <map>

FBullCowGame::FBullCowGame()
{
	Reset();
}

FBullCowGame::~FBullCowGame()
{
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWorldLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	return (pow(MyHiddenWord.length()-1,2) / 2);
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString guess) const
{
	if (!IsIsogram(guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess))
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWorldLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else {
		return EWordStatus::OK;
	}
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount; 

	int32 WordLength = MyHiddenWord.length();
	for (int32 i = 0; i < WordLength; i++)
	{
		if (guess[i] == MyHiddenWord[i])
		{
			BullCowCount.bulls++;
		}
		else
		{
			BullCowCount.cows++;
		}
	}
	if (BullCowCount.bulls == WordLength) 
	{
		bGameIsWon = true;
	} 
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString string) const
{
	TMap<char, bool> CharacterSeen;
	int32 CharacterOccurences[255] = {} ;
	bool ValidIsogram = true;
	for (char character : string)
	{
		character = tolower(character);
		if (CharacterSeen[character])
		{
			ValidIsogram = false;
			break;
		}
		else
		{
			CharacterSeen[character] = true;
		}

	}
	return ValidIsogram;
}

bool FBullCowGame::IsLowercase(FString string) const
{
	// returns as soon as it finds an uppercase character
	return (!std::any_of(string.begin(), string.end(), isupper)) ? true : false;
}

