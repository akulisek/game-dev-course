#pragma once
#include <iostream>
#include <string>

using FString = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintOutro();
void PrintGameSummary();
FString GuessValidWord();
bool WantsToPlayAgain();