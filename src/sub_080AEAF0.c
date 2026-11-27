void sub_080C31E4(void *, void *, s32);
extern u16 gCrossfadeGfxState[4];
struct S_D_18BC { u8 _0[0x18BC]; u16 v; };
extern struct S_D_18BC gMainWorkspace;

/* Set the display's alpha-blend levels from the object's fade counter at +0x50
 * and raise the global fade flag; when the script reaches step 0xF0, step on. */
void sub_080AEAF0(void *arg0) {
    u8 *self = arg0;
    u8 blendLevel;
    u8 *step;
    s32 *eventPtr;
    s32 stepOffset;
    gCrossfadeGfxState[2] = 0xFD << 6;
    blendLevel = *(u8 *)(self + 0x50);
    gCrossfadeGfxState[3] = (u16)(blendLevel | ((0x10 - blendLevel) << 8));
    gMainWorkspace.v = 1;
    stepOffset = *(s16 *)(self + 0x22) * 2;
    step = (u8 *)(stepOffset + (u32)self);
    if (*(u8 *)(step + 0x19) == 0xF0) {
        *(u8 *)(step + 0x19) = 0;
        eventPtr = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *eventPtr);
    }
}
