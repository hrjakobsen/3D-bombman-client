#include "render.h"
clock_t LastGameTick = clock();
int FramesCount = 0;
void Gametimer() {
	double Diff = clock() - LastGameTick;
	Diff = Diff / CLOCKS_PER_SEC;
	if (Diff > .1 / 20) {
		LastGameTick = clock();
		display();
		FramesCount++;




	}
	else {
		std::this_thread::sleep_for(std::chrono::milliseconds(1 / (long long)20 - (long long)Diff));
	}
}
