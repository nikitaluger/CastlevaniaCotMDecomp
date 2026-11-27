extern s32 sub_0805FEC8(u16);
extern void resetMapRender(void);
extern void setScreenTransition(u8);
extern void sub_08000E54(void *a, void *b, void *c, u32 d, u32 e);
extern void sub_080C31E4(void *a, void *b, u32 c);

extern s8 gMenuState[];
extern u8 D_080CB1AE[];
extern u8 gCameraState[];
extern u32 gPoseScriptCallbacks;

/* Resolve a graphics entry from the current state-byte pair; on success set up
 * the graphics state, upload two VRAM blocks selected by the globals, clear the
 * entity's pose byte and run its behaviour script. */
void sub_0800E7EC(u8 *self)
{
    u8 *entryTable;
    s8 *stateBytes;
    s32 entryIdx;
    s32 result;

    entryTable = D_080CB1AE;
    stateBytes = gMenuState;
    entryIdx = (stateBytes[0xFA] - 1) * 2;
    entryIdx += stateBytes[0xF9] * 20;
    result = sub_0805FEC8(*(u16 *)(entryTable + entryIdx));

    if (result == 0)
    {
        u32 gfxBase;
        vu16 *attrPtr;
        u16 attrs;
        u32 mask;

        resetMapRender();
        setScreenTransition(0);

        gfxBase = (u32)gCameraState;
        attrPtr = (vu16 *)(gfxBase + 0x1262);

        attrs = *attrPtr;
        mask = 0x0C;
        {
            u32 bits = mask;
            bits &= attrs;
            sub_08000E54((void *)1, (void *)0, (void *)((bits << 12) + 0x06000040), 0xFC0, 0x10);
        }
        attrs = *attrPtr;
        {
            u32 bits = mask & attrs;
            sub_08000E54((void *)1, (void *)0, (void *)((bits << 12) + 0x06000020), 0x20, 0x10);
        }

        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (u8)result;
        {
            u32 *fnaddr = &gPoseScriptCallbacks;
            sub_080C31E4(self + 0x18, self + 0x22, *fnaddr);
        }
    }
}
