#define BLOCK_AIR 0
#define BLOCK_WALL 1
#define BLOCK_CRATE 2
#define BLOCK_XFIRE 3
#define BLOCK_ZFIRE 4
#define BLOCK_CFIRE 5

bool SolidBlock(int BlockID) {
	if (BlockID == BLOCK_AIR || BlockID == BLOCK_XFIRE || BlockID == BLOCK_ZFIRE || BlockID == BLOCK_CFIRE) {
		return false;
	} else {
		return true;
	}
} 