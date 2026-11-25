extern void sub_08011368(s32, void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* When the animation controller reports bit 2, clear the work state words and
 * re-run the current script step. */
void sub_08053D08(u8 *obj)
{
    s32 gfx = *(s32 *)(obj + 0x38);
    u8 *work = *(u8 **)(obj + 0x3C);

    sub_08011368(gfx, work + 0x34, 0x0A, 1);
    if (*(u16 *)(work + 0x02) & 4)
    {
        s16 idx;
        s32 *scriptTable;
        *(u32 *)(work + 0x10) = 0;
        *(u32 *)(work + 0x48) = 0;
        idx = *(s16 *)(obj + 0x22);
        *(u8 *)(obj + idx * 2 + 0x19) = 0;
        scriptTable = (s32 *)0x08671BB0;
        sub_080C31E4(obj + 0x18, obj + 0x22, *scriptTable);
    }
}
