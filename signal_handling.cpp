#include "signal_handling.hpp"

void SIGINT_handler(int s __attribute__((unused))) {
	extern bool keep_going;
	keep_going = false;
}

void SetSignalHandlers(struct sigaction &sigIntHandler) {
	sigIntHandler.sa_handler = SIGINT_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, nullptr);
}
