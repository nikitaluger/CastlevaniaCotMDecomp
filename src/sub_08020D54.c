extern u32 gScriptStepCallbackTable;
void setAnimationFrame(void *, void *, s32, s32);
void sub_080C31E0(void *, void *);
void sub_080C31E4(void *, void *, u32);

/* Detach every child held in the owner's three slots at work+0x58: mark each one
 * for deletion (bit 1 of its flags at +0x6C) and clear the slot pointer. */
void sub_08020E78(void *arg0) {
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u32 **slot = (u32 **)(work + 0x58);
    s32 remaining = 2;
    u32 zero = 0;
    u32 deleteBit = 2;
    do {
        u8 *child = (u8 *)*slot;
        if (child != NULL) {
            *(u16 *)(child + 0x6C) |= (u16)deleteBit;
            *slot = zero;
        }
        slot++;
        remaining--;
    } while (remaining >= 0);
}

/* Restart the actor on command table 0x0866D810: play animation 0, install the
 * table at +0x14, push one script step (+0x22), dispatch that step's handler
 * once, then pop the step again. */
void sub_08020D54(void *arg0) {
    u8 *obj = arg0;
    u8 baseOffset;
    s32 stepOffset;
    setAnimationFrame(*(void **)(obj + 0x38), (u8 *)*(void **)(obj + 0x3C) + 0x34, 0, 0);
    *(u32 *)(obj + 0x14) = 0x0866D810;
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) + 1;
    ((u8 *)(obj + (*(s16 *)(obj + 0x22)) * 2))[0x19]++;
    stepOffset = (*(s16 *)(obj + 0x22)) * 2;
    baseOffset = 0x18;
    sub_080C31E0(arg0, (void *)((u32 *)*(u32 **)(obj + 0x14))[((u8 *)(baseOffset + obj))[stepOffset]]);
    *(u16 *)(obj + 0x22) = *(u16 *)(obj + 0x22) - 1;
}

/* Initialise the pose block at work+0x48: set its u16 fields at +8 to 8 and at
 * +0x1C to 3, then clear the current step's progress byte and advance the script
 * step. */
void sub_08020AB4(void *arg0) {
    u8 *obj = (u8 *)arg0;
    u8 *pose = *(u8 **)(obj + 0x3C) + 0x48;
    void **stepFnTable;
    u8 zero;
    zero = 0;
    *(u16 *)(pose + 8) = 8;
    *(u16 *)(pose + 0x1C) = 3;
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
    stepFnTable = (void **)0x08671BB0;
    sub_080C31E4(obj + 0x18, obj + 0x22, (s32)*stepFnTable);
}

/* Reset the work block's velocity (+0x10/+0x14), play animation 0x2D and, when
 * the animator reports completion (bit 2), switch to the state handler at
 * +0x24. */
void sub_0802128A(void *arg0) {
    u8 *obj = (u8 *)arg0;
    u8 *work = *(u8 **)(obj + 0x3C);
    u8 *anim = work + 0x34;
    *(u32 *)(work + 0x14) = 0;
    *(u32 *)(work + 0x10) = 0;
    setAnimationFrame(*(void **)(obj + 0x38), anim, 0x2D, 0);
    if (*anim & 2) {
        sub_080C31E0(obj, *(void **)(obj + 0x24));
    }
}
