#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "GofLApp.h"

char GAME_TITLE[] = "Game of Life with SDL2";
void backtrace();

static void sig_handler(int signum, siginfo_t *si, void *ctx)
{
	printf("Received signal %d, at address: 0x%lx\n", signum, (long)si->si_addr);
	backtrace();
}

static void setsig_handler()
{
	struct sigaction sa;
	sa.sa_flags = SA_SIGINFO | SA_RESETHAND;
	sigemptyset(&sa.sa_mask);
	sa.sa_sigaction = sig_handler;
	if (sigaction(SIGSEGV, &sa, NULL) == -1) {
		perror("setsig_handler");
		exit(EXIT_FAILURE);
	}
	if (sigaction(SIGABRT, &sa, NULL) == -1) {
		perror("setsig_handler");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	setsig_handler();

	GofLApp app;
	app.init(GAME_TITLE);
	app.run();
	return 0;
}
/* vim: set ts=4 sw=4 sts=4: */
