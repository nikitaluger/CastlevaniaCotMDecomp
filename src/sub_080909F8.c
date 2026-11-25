void sub_0801604C(void *);
void sub_080C31E8(void *, void *, s32, s32);
void sub_080C31E0(void *, s32);

/* Movement clamp: once the entity's current coordinate has reached its limit
 * on this axis, snap it to the limit, stop the motion, clear the step timer
 * and re-dispatch the command script with argument 1. */
void sub_080909F8(void *arg0) {
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    void *steer = (u8 *)work + 0x48;
    s32 pos = *(s32 *)((u8 *)work + 0x0C);
    s32 limit = *(s32 *)((u8 *)steer + 0x08);
    u8 zero;
    if (pos >= limit) {
        *(s32 *)((u8 *)work + 0x0C) = limit;
        *(s32 *)((u8 *)work + 0x14) = 0;
        zero = 0;
        *(s16 *)((u8 *)steer + 0x10) = 0;
        ((u8 *)((u8 *)arg0 + (*(s16 *)((u8 *)arg0 + 0x22)) * 2))[0x19] = zero;
        {
            s32 *scriptTable;
            scriptTable = (s32 *)0x08671BD0;
            sub_080C31E8(arg0 + 0x18, arg0 + 0x22, 1, *scriptTable);
        }
    }
}
