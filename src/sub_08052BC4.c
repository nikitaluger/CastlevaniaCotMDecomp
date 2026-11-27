extern u32 gScriptStepCallbackTable[];

void setAnimationFrame(s32, void *, u16, u8);
void stepAnimationTrack(s32, void *);
void advanceMotion(void *, s32);
void sub_080C31E4(void *, void *, s32);

/* Advances the entity's animation and physics; when the animation ends it sets
 * the work object's resource bytes, launches the object downward with a new
 * animation frame and runs the next script step. */
void sub_08052BC4(u8 *arg0) {
    u8 *self = arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *work = *(u8 **)(self + 0x3C);
    u8 *animator = work + 0x34;
    s32 zero;

    stepAnimationTrack(sprite, animator);
    advanceMotion(work, 0);

    if (*animator & 2) {
        u8 *block;
        block = *(u8 **)(work + 0x28);
        zero = 0;
        block[2] = 8;
        block = *(u8 **)(work + 0x28);
        block[3] = 1;
        *(s32 *)(work + 0x10) = zero;
        *(s32 *)(work + 0x14) = 0x2800;
        setAnimationFrame(sprite, animator, 0x0F, 1);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = zero;
        {
            u32 *scriptHandlers = gScriptStepCallbackTable;
            sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
        }
    }
}
