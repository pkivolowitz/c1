#pragma once
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <ncurses.h>

WINDOW * InitCurses();
void TakedownCurses();
void BeginUpdate();
void Refresh(WINDOW *, void (*CustomBorder)() = nullptr);
std::string GetTime();
