extern s32 syncViewPosition(s32, void *);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 D_080E0AD0[];
extern u8 *D_0866EB08[];

/* Begin the room transition selected by the current map mode: copy the old
 * scroll fractions and source position, take the new room's position and
 * scroll deltas from the map table, then clear the mode and raise the
 * display flags. */
void sub_0806D044(s32 arg0, s32 arg1, void *arg2)
{
    u32 mapState = (u32)gGameStatus;
    u32 gameState = (u32)gMainWorkspace;
    void *refPos = arg2;
    u32 *roomIndexPtr = (u32 *)(gameState + 0x000014BC);
    u32 roomEntry = (u32)(D_080E0AD0 + ((*roomIndexPtr) << 4));
    u32 mode;
    u8 **roomPtrTable;
    u8 *tile;
    u8 tileA;
    u8 tileB;
    u32 entryX;
    u32 entryY;

    mode = syncViewPosition(arg1, refPos);
    if (mode != 0) return;

    roomPtrTable = D_0866EB08;
    tile = (u8 *)(*(u32 *)((u8 *)roomPtrTable + (*(u8 *)(mapState + 0x94) << 2)) + (*(u8 *)(mapState + 0x95) << 1));
    tileA = *tile;
    *(u8 *)(gameState + 0x000014C6) = tileA;
    tileB = *(tile + 1);
    *(u8 *)(gameState + 0x000014C7) = tileB;
    *(u8 *)(mapState + 0x94) = *(u8 *)roomEntry;
    *(u8 *)(mapState + 0x95) = *(u8 *)(roomEntry + 1);

    tile = (u8 *)(*(u32 *)((u8 *)roomPtrTable + (*(u8 *)(mapState + 0x94) << 2)) + (*(u8 *)(mapState + 0x95) << 1));
    tileA = *tile;
    *(u8 *)(gameState + 0x000014C4) = tileA;
    tileB = *(tile + 1);
    *(u8 *)(gameState + 0x000014C5) = tileB;
    *(u32 *)(gameState + 0x000014C8) = (entryX = *(u32 *)(roomEntry + 4));
    *(u32 *)(gameState + 0x000014CC) = (entryY = *(u32 *)(roomEntry + 8));
    *(u32 *)(gameState + 0x000014D0) = entryX - *(u32 *)refPos;
    *(u32 *)(gameState + 0x000014D4) = entryY - *(u32 *)((u8 *)refPos + 4);
    *(u32 *)(gameState + (0xA6 << 5)) = *(u32 *)(roomEntry + 0x0C);
    *roomIndexPtr = mode;
    *(u32 *)(gameState + 0x000014B4) = 0x00000822;
    {
        u32 *displayFlags = (u32 *)(gameState + 0x00001844);
        u32 flags = *displayFlags;
        *displayFlags = flags | 0x04000000;
        *displayFlags = *displayFlags | 0x02000000;
    }
}
