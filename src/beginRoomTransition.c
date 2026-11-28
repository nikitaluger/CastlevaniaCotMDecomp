extern s32 syncViewPosition(s32, void *);
extern u8 gGameStatus[];
extern u8 gMainWorkspace[];
extern u8 gRoomEntryTable[];
extern u8 *gMapTileRows[];

/* Begin the room transition selected by the current map mode: copy the old
 * scroll fractions and source position, take the new room's position and
 * scroll deltas from the map table, then clear the mode and raise the
 * display flags. */
/* Apply the pending map room change once the view has synced: copy the tile bytes at the old and new map coordinates into the transition state, load the room record's entry position and deltas, clear the pending room id and raise the map redraw flags. */ void beginRoomTransition(s32 arg0, s32 arg1, void *arg2)
{
    u32 mapState = (u32)gGameStatus;
    u32 gameState = (u32)gMainWorkspace;
    void *viewPos = arg2;
    u32 *pendingRoomId = (u32 *)(gameState + 0x000014BC);
    u32 roomRecord = (u32)(gRoomEntryTable + ((*pendingRoomId) << 4));
    u32 syncMode;
    u8 **tileRows;
    u8 *tileWord;
    u8 tileLo;
    u8 tileHi;
    u32 roomX;
    u32 roomY;

    syncMode = syncViewPosition(arg1, viewPos);
    if (syncMode != 0) return;

    tileRows = gMapTileRows;
    tileWord = (u8 *)(*(u32 *)((u8 *)tileRows + (*(u8 *)(mapState + 0x94) << 2)) + (*(u8 *)(mapState + 0x95) << 1));
    tileLo = *tileWord;
    *(u8 *)(gameState + 0x000014C6) = tileLo;
    tileHi = *(tileWord + 1);
    *(u8 *)(gameState + 0x000014C7) = tileHi;
    *(u8 *)(mapState + 0x94) = *(u8 *)roomRecord;
    *(u8 *)(mapState + 0x95) = *(u8 *)(roomRecord + 1);

    tileWord = (u8 *)(*(u32 *)((u8 *)tileRows + (*(u8 *)(mapState + 0x94) << 2)) + (*(u8 *)(mapState + 0x95) << 1));
    tileLo = *tileWord;
    *(u8 *)(gameState + 0x000014C4) = tileLo;
    tileHi = *(tileWord + 1);
    *(u8 *)(gameState + 0x000014C5) = tileHi;
    *(u32 *)(gameState + 0x000014C8) = (roomX = *(u32 *)(roomRecord + 4));
    *(u32 *)(gameState + 0x000014CC) = (roomY = *(u32 *)(roomRecord + 8));
    *(u32 *)(gameState + 0x000014D0) = roomX - *(u32 *)viewPos;
    *(u32 *)(gameState + 0x000014D4) = roomY - *(u32 *)((u8 *)viewPos + 4);
    *(u32 *)(gameState + (0xA6 << 5)) = *(u32 *)(roomRecord + 0x0C);
    *pendingRoomId = syncMode;
    *(u32 *)(gameState + 0x000014B4) = 0x00000822;
    {
        u32 *displayFlags = (u32 *)(gameState + 0x00001844);
        u32 flags = *displayFlags;
        *displayFlags = flags | 0x04000000;
        *displayFlags = *displayFlags | 0x02000000;
    }
}
