s32 isOutsideCameraBounds(s32, s32);
struct S_02025FF0_18A8 { u8 _0[0x18A8]; u8 v; };
extern struct S_02025FF0_18A8 gMainWorkspace;
extern u8 gCameraState[];

/* Place the sprite at the entity's world position (work+8/+0xC) relative to
 * the current camera, and set/clear its in-view highlight bit (0x40 at
 * sprite+0x2A) according to isOutsideCameraBounds. */
void sub_080144FC(void *arg0, void *arg1)
{
    u8 *sprite = (u8 *)arg1;
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    u8 *highlight;

    if (isOutsideCameraBounds(*(s32 *)((u8 *)work + 0x08), *(s32 *)((u8 *)work + 0x0C)) == 1) {
        highlight = sprite + 0x2A;
        *highlight = 0xBF & *highlight;
    } else {
        int newHighlight;
        highlight = sprite + 0x2A;
        newHighlight = 0x40 | *highlight;
        *highlight = newHighlight;
    }
    {
        u8 *base = gCameraState;
        u32 off = (gMainWorkspace.v + 1) * 0x40;
        u8 *camX = base + 0x1278;
        *(s32 *)(sprite + 0x14) = *(s32 *)((u8 *)work + 0x08) - ((*(s32 *)(camX + off) + 0x8000) & 0xFFFF0000);
    }
    {
        u8 *base = gCameraState;
        u32 off = (gMainWorkspace.v + 1) * 0x40;
        u8 *camY = base + 0x127C;
        *(s32 *)(sprite + 0x18) = *(s32 *)((u8 *)work + 0x0C) - ((*(s32 *)(camY + off) + 0xFFFF8000) & 0xFFFF0000);
    }
}
