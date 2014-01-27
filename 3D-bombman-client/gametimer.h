#include "render.h"
clock_t LastGameTick = clock();
int FramesCount = 0;
void Gametimer() {
	double Diff = clock() - LastGameTick;
	Diff = Diff / CLOCKS_PER_SEC;
	if (Diff > 1 / FramesPerSecond) {
		LastGameTick = clock();
		KeyBoardUpdate(Diff);
		UpdateBombs(Diff);
		display();
		FramesCount++;
	}
	else {
		std::this_thread::sleep_for(std::chrono::milliseconds(1 / (long long)FramesPerSecond - (long long)Diff));
	}
}