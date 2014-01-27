#define BLOCK_AIR 0
#define BLOCK_WALL 1
#define BLOCK_CRATE 2
#define BLOCK_XFIRE 3
#define BLOCK_ZFIRE 4
#define BLOCK_CFIRE 5

bool SolidBlock(int BlockID) {
	if (BlockID == 0) {
		return false;
	} else {
		return true;
	}
}