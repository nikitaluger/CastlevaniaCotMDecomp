s32 getSpriteFacingSign(s32);
s32 sub_080C31E0(s32, s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Dispatch the current script command through the actor's jump table, then,
 * once a countdown expires, set the movement direction and end the step. */
void sub_0802A630(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *source;
    u8 *actor;
    u8 *motion;
    u8 command;
    u32 dispatchTable;

    source = *(void **)(self + 0x38);
    actor = *(void **)(self + 0x3C);
    motion = actor + 0x48;

    *(u32 *)(self + 0x14) = 0x0866DAB4;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    {
        u8 *stepPtr;
        stepPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        *(u8 *)(stepPtr + 0x19) = *(u8 *)(stepPtr + 0x19) + 1;
    }
    {
        s32 stepOffset;
        u8 *scriptData;
        stepOffset = (s32)(s16)(*(s16 *)(self + 0x22)) * 2;
        scriptData = self + 0x18;
        scriptData += stepOffset;
        command = *scriptData;
    }
    dispatchTable = *(u32 *)(self + 0x14);
    sub_080C31E0((s32)self, *(u32 *)((u8 *)dispatchTable + command * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    {
        if ((s32)(*(u16 *)motion = *(u16 *)motion - 1) << 16 < 0) {
            u32 *dispatchArg;
            u8 zero;
            u8 *stepPtr;
            s32 direction;
            *(u16 *)(motion + 0x02) = 0;
            direction = getSpriteFacingSign((s32)source);
            if (direction > 0)
                direction = 0x8000;
            else
                direction = 0xFFFF8000;
            *(u32 *)(actor + 0x10) = direction;
            stepPtr = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
            zero = 0;
            *(u8 *)(stepPtr + 0x19) = zero;
            dispatchArg = (u32 *)0x08671BD0;
            sub_080C31E8(self + 0x18, self + 0x22, 1, *dispatchArg);
        }
    }
}
