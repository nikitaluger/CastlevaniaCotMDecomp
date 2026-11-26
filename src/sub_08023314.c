/* Advances a timed effect: drives animation frame 0, derives a value from a frame
 * counter divided by 36 through a table function, then clears state and calls an
 * end callback when the countdown expires. */
extern void setAnimationFrame(s32, void *, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);

void sub_08023314(void *obj)
{
    u8 *objBytes = (u8 *)obj;
    s32 owner = *(s32 *)(objBytes + 0x38);
    u8 *work = *(u8 **)(objBytes + 0x3C);
    u8 *anim = work + 0x34;
    u8 *fx = work + 0x48;
    u16 zero;

    setAnimationFrame(owner, anim, 0, 1);

    if (*(u8 *)(anim + 1) == 1 && *(s32 *)(anim + 4) == 1)
        *(u16 *)(fx + 4) = 0;

    {
        s32 *valueFuncs = (s32 *)0x08671BFC;
        s32 scaled = sub_080C364C(*(s16 *)(fx + 4) << 16, 0x24);
        *(s32 *)(fx + 0) = sub_080C31E0(scaled, *valueFuncs) * 2;
    }

    *(u16 *)(fx + 4) = *(u16 *)(fx + 4) + 1;
    {
        s32 countdown = *(u16 *)(fx + 6);
        countdown -= 1;
        *(u16 *)(fx + 6) = countdown;
        if ((countdown << 16) < 0)
        {
            zero = 0;
            *(u16 *)(fx + 0xC) = zero;
            *(u8 *)(objBytes + *(s16 *)(objBytes + 0x22) * 2 + 0x19) = (u8)*(u16 *)(fx + 0xC);
            {
                s32 *endFuncs = (s32 *)0x08671BD0;
                sub_080C31E8(objBytes + 0x18, objBytes + 0x22, 1, *endFuncs);
            }
        }
    }
}
