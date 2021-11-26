#pragma once
#include <sstream>
#include <iomanip>
#include <thread>
#include <chrono>
#include <mutex>
#include <ncurses.h>

void InitCurses();
void TakedownCurses();
void BeginUpdate();
void Refresh(void (*CustomBorder)() = nullptr);
