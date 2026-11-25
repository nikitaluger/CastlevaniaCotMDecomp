extern void sub_08011368(s32, void *, s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_080C364C(s32, s32);
extern u32 sub_08005820(u32);

/* Advance an effect driven by the body's animator and part state: when the
 * animator reaches its mark, reset the part's phase counter, compute a
 * fixed-point phase and store the callback's result; tick a countdown and,
 * when it expires, pick a new random value, clear the part's step flag and
 * advance the entity's script. */
void sub_0801E44C(void *arg0)
{
    u8 *self = (u8 *)arg0;
    s32 sprite = *(s32 *)(self + 0x38);
    u8 *body = *(u8 **)(self + 0x3C);
    u8 *anim = body + 0x34;
    u8 *part = body + 0x48;
    u16 zero1;

    sub_08011368(sprite, anim, 0, 1);

    if (*(u8 *)(anim + 1) == 1 && *(s32 *)(anim + 4) == 1)
        *(u16 *)(part + 4) = 0;

    {
        s32 *callbackTable = (s32 *)0x08671BFC;
        s32 phase = sub_080C364C(*(s16 *)(part + 4) << 16, 0x24);
        *(s32 *)(part + 0) = sub_080C31E0(phase, *callbackTable) * 2;
    }

    *(u16 *)(part + 4) = *(u16 *)(part + 4) + 1;
    {
        s32 timer = *(u16 *)(part + 6);
        timer -= 1;
        *(u16 *)(part + 6) = timer;
        if ((timer << 16) < 0)
        {
            *(u16 *)(part + 0x2A) = sub_08005820(2);
            zero1 = 0;
            *(u16 *)(part + 0xC) = zero1;
            *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = (u8)*(u16 *)(part + 0xC);
            {
                s32 *scriptTable = (s32 *)0x08671BD0;
                sub_080C31E8(self + 0x18, self + 0x22, 1, *scriptTable);
            }
        }
    }
}
