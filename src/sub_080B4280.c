typedef s32 M2C_UNK;
M2C_UNK sub_08005E80(s32);
M2C_UNK setObjectAnimation(s32, s32, s32, s32);
M2C_UNK advanceAnimTrack(s32, s32);
M2C_UNK sub_080B716C(s32);
M2C_UNK sub_080C31E4(void *, void *, s32);

struct FrameWord { u8 _0x0[2]; u16 value; };
struct FrameWordVolatile { u8 _0x0[2]; volatile u16 value; };

#define FRAME_ADDR(p, pp) ((((*(s16 *)((s8 *)(p) + 0xE) + *(u8 *)((s8 *)(p) + 1)) * 4) + *(pp)) - 4)
#define READ_FRAME(p, pp) (((struct FrameWord *)FRAME_ADDR(p, pp))->value)
#define READ_FRAME_VOLATILE(p, pp) (((struct FrameWordVolatile *)FRAME_ADDR(p, pp))->value)

/* Entity update: watches the animation frame, plays sounds for frames 0x3A/0x3F
 * (activating two helpers on the latter), and advances the script when flagged. */
void sub_080B4280(void *arg0)
{
    s32 gfx;
    u32 oldFrame;
    s32 stateAddr;
    s32 *frameTable;
    s32 *aux;
    void *body;
    u16 newFrame;
    u16 checkFrame;
    int pStepCounter;

    gfx = *((s32 *)(((s8 *)arg0) + 0x38));
    body = *((void **)((s8 *)arg0) + 0x3C / 4);
    stateAddr = (s32)body + 0x34;
    aux = (s32 *)((s8 *)body + 0x48);
    frameTable = *(s32 **)((s8 *)stateAddr + 8);
    oldFrame = READ_FRAME(stateAddr, frameTable);
    setObjectAnimation(gfx, stateAddr, 0x47, 0);
    advanceAnimTrack(gfx, stateAddr);
    frameTable = *(s32 **)((s8 *)stateAddr + 8);
    newFrame = READ_FRAME_VOLATILE(stateAddr, frameTable);
    if (oldFrame != newFrame) {
        s32 *frameTable2;
        if (newFrame == 0x3A) {
            sub_08005E80(0x192);
        }
        frameTable2 = *(s32 **)((s8 *)stateAddr + 8);
        checkFrame = READ_FRAME(stateAddr, frameTable2);
        if (oldFrame != checkFrame && checkFrame == 0x3F) {
            sub_08005E80(0x193);
            sub_080B716C(*(aux + 1));
            sub_080B716C(*(aux + 2));
        }
    }
    if (2 & *((u8 *)((s8 *)stateAddr + 0))) {
        *((s8 *)(((s8 *)(((*((s16 *)(((s8 *)arg0) + 0x22))) * 2) + arg0)) + 0x19)) = 0;
        pStepCounter = 0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + ((unsigned int)0x22), *((s32 *)pStepCounter));
    }
}
