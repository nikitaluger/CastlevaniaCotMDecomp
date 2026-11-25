void sub_080160A0(s32, s32, s32, s32, void *);

/* Spawn or update a sub-effect for the entity: computes its velocity from the
 * entity position and the animator's part at animator+0x48, and for an effect
 * flagged as fixed-point (0x1000) copies its flags and its offset relative to
 * that part instead. */
void sub_080967BC(void *arg0, void *arg1)
{
    u8 *work = *(u8 **)((u8 *)arg0 + 0x3C);
    u8 *part = work + 0x48;

    if (*(u16 *)((u8 *)arg1) & 0x1000)
    {
        if (*(u16 *)((u8 *)arg1 + 2) & 1)
            *(u16 *)((u8 *)arg1 + 2) |= 0x400;

        if (*(s16 *)(part + 0x10) == 0)
        {
            *(s16 *)(part + 0x10) = 1;
            sub_080160A0(*(s32 *)(work + 8), *(s32 *)(work + 0xC),
                         *(s32 *)(part + 8), *(s32 *)(part + 0xC), arg1);
        }
        else
        {
            u8 *dest = *(u8 **)((u8 *)arg1 + 0x1C);
            u16 flags = *(u16 *)((u8 *)arg1 + 2);
            s32 zero = 0;
            u8 *destReload;
            *(u16 *)dest = flags;
            destReload = *(u8 *volatile *)((u8 *)arg1 + 0x1C);
            *(s32 *)(destReload + 4) = zero;
            *(s32 *)(destReload + 8) = zero;
            *(s32 *)(destReload + 0xC) = *(s32 *)(work + 8) - *(s32 *)(part + 8);
            *(s32 *)(destReload + 0x10) = *(s32 *)(work + 0xC) - *(s32 *)(part + 0xC);
        }
    }
    else
    {
        sub_080160A0(*(s32 *)(work + 8), *(s32 *)(work + 0xC),
                     *(s32 *)(part + 8), *(s32 *)(part + 0xC), arg1);
    }
}
