#pragma once
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <mutex>
#include <string>
#include <ncurses.h>
#include <cassert>

WINDOW * InitCurses();
void TakedownCurses();
void BeginUpdate();
void Refresh(WINDOW *, void (*CustomBorder)(WINDOW *) = nullptr);
std::string GetTime();
