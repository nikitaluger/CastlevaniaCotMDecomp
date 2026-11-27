/* Mode-specific per-frame entity update: in mode 0x35 rebase a script pointer
 * and raise a global counter for a particular animation state; in mode 0x25
 * advance a 6-bit frame counter and, on wrap, spawn a trail and signal a
 * state change. */
struct D02025FF0_S_850B4 {
    u8 _p0[0x14ED];
    u8 a_14ED;
    u8 _p1[0x14F0 - 0x14EE];
    u8 a_14F0;
    u8 _p2[0x1754 - 0x14F1];
    s32 a_1754;
    u8 _p3[0x1780 - 0x1758];
    u32 arr_1780[1];
};
extern struct D02025FF0_S_850B4 gMainWorkspace;
extern u8 gGameStatus[];
extern u8 D_0845806C[];
s32 spawnEntity(s32, s32, s32, s32);
void recordSpawnEvent(void);

void sub_080850B4(s32 actor, void *ctrl) {
    u32 *globals = (u32 *)gGameStatus;
    u32 animPtr;
    u32 frameCounter;
    s32 trail;
    if (gMainWorkspace.a_14ED != 0x35) {
        animPtr = *(u32 *)((u8 *)ctrl + 0x30);
        if (animPtr == (u32)D_0845806C) {
            *(u32 *)((u8 *)ctrl + 0x30) = animPtr - 0x28;
        }
    }
    switch (gMainWorkspace.a_14ED) {
    case 0x25:
        frameCounter = (*(u32 *)((u8 *)ctrl + 0xB8) + 1) & 0x3F;
        *(u32 *)((u8 *)ctrl + 0xB8) = frameCounter;
        if (frameCounter == 0) {
            globals[0xC0]++;
            trail = spawnEntity(actor, 0x34, 0x0A, 0x12);
            if (trail != 0) {
                *(u16 *)(trail + 0x7C) = (u16)frameCounter;
            }
            recordSpawnEvent();
        }
        break;
    case 0x35:
        {
            u16 animState = *(u16 *)((u8 *)ctrl + 0x2C);
            if (animState == 1 || animState == 3) {
                if (*(u16 *)((u8 *)ctrl + 0x2A) == 1) {
                    if (gMainWorkspace.a_1754 <= 4) {
                        gMainWorkspace.a_1754 = 5;
                    }
                }
            }
        }
        break;
    }
}
