extern void sub_080063D4(void *, void *);

/* Main game state (D_02021E90) fields touched by the loader routines. */
struct S_02021E90_local {
    u8 pad_0[0x1262];
    u16 bgControl;          /* BGxCNT value; bits 8..12 select the screen block */
    u8 pad_1264[0x1F0];
    s32 frameCounter;
    u8 pad_1458[4];
    u8 graphicsFlags;
};
extern struct S_02021E90_local D_02021E90;

/* Load a tilemap: decompress the blob at 0x084427D8 into the BG screen block
 * named by the current BG control value, mark the graphics state busy and
 * report the next script step (2). */
s32 sub_080603B8(void)
{
    void *vramDest;
    D_02021E90.frameCounter += 1;
    D_02021E90.graphicsFlags |= 8;
    vramDest = (void *)(((D_02021E90.bgControl & 0x1F00) << 3) + 0x06000C80);
    sub_080063D4((void *)0x084427D8, vramDest);
    return 2;
}
