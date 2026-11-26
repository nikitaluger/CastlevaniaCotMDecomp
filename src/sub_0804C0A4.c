void sub_0804C674(void *, void *, void *);
void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallback;

/* If the pose block is active, re-arm the script step: set a 360-frame delay,
 * give the actor a fresh random bounce direction and velocity, clear the
 * current script slot's counter and dispatch that step again. */
void sub_0804C0A4(u8 *obj)
{
    u8 *work = *(u8 **)(obj + 0x3C);
    u8 *pose = work + 0x48;

    if (*(s16 *)pose != 0)
    {
        u8 zero = 0;
        u16 delay = 0xB4;
        s32 *scriptTable;
        delay <<= 1;
        *(u16 *)(pose + 0x16) = delay;
        sub_0804C674(obj, pose + 0xC, work + 0x58);
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = zero;
        scriptTable = &gMainObjTimerCallback;
        sub_080C31E4(obj + 0x18, obj + 0x22, *scriptTable);
    }
}
