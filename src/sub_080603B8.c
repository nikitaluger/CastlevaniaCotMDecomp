extern void decompressToVram(void *, void *);

/* Main game state (gCameraState) fields touched by the loader routines. */
struct S_02021E90_local {
    u8 pad_0[0x1262];
    u16 bgControl;          /* BGxCNT value; bits 8..12 select the screen block */
    u8 pad_1264[0x1F0];
    s32 frameCounter;
    u8 pad_1458[4];
    u8 graphicsFlags;
};
extern struct S_02021E90_local gCameraState;

/* Load a tilemap: decompress the blob at 0x084427D8 into the BG screen block
 * named by the current BG control value, mark the graphics state busy and
 * report the next script step (2). */
s32 sub_080603B8(void)
{
    void *vramDest;
    gCameraState.frameCounter += 1;
    gCameraState.graphicsFlags |= 8;
    vramDest = (void *)(((gCameraState.bgControl & 0x1F00) << 3) + 0x06000C80);
    decompressToVram((void *)0x084427D8, vramDest);
    return 2;
}
