#pragma once
#include <string>
#include <algorithm>

// Make the program more Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

struct FBullCowCount 
{
	int32 bulls = 0;
	int32 cows = 0;
};

enum class EWordStatus
{
	OK, 
	Not_Isogram ,
	Wrong_Length,
	Not_Lowercase,
	Invalid_Status
};

class FBullCowGame 
{
public: 
	FBullCowGame(); 
	~FBullCowGame();

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWorldLength() const;
	bool IsGameWon() const;

	void Reset(); 
	EWordStatus CheckGuessValidity(FString) const; 

	FBullCowCount SubmitValidGuess(FString);

private:
	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;

	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;
};