extern u8 D_0866D69C[];
void _call_via_r1(void *, void *);

/* Script command: reset the work object's counters, install the command table
 * D_0866D69C, advance the script step, bump its counter and dispatch the
 * command handler, then restore the previous step index. */
void sub_0801B55C(void *arg0)
{
    u8 *actor = (u8 *)arg0;
    u8 *work = *(u8 **)(actor + 0x3C);
    s16 step;

    *(u32 *)(work + 0x14) = 0;
    *(u32 *)(work + 0x10) = 0;
    *(u32 *)(work + 0x68) = 0;
    *(u32 *)(actor + 0x14) = (u32)D_0866D69C;
    *(u16 *)(actor + 0x22) = *(u16 *)(actor + 0x22) + 1;

    step = *(s16 *)(actor + 0x22);
    *(u8 *)(actor + step * 2 + 0x19) = *(u8 *)(actor + step * 2 + 0x19) + 1;

    step = *(s16 *)(actor + 0x22);
    {
        s32 off = step * 2;
        u8 *cmdBase = actor + 0x18;
        _call_via_r1(arg0, *(void **)((u8 *)*(void **)(actor + 0x14) + *(u8 *)(cmdBase + off) * 4));
    }

    *(u16 *)(actor + 0x22) = *(u16 *)(actor + 0x22) - 1;
}
