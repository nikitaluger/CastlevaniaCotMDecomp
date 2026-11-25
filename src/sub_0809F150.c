extern void sub_08005E80(s32);
extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, s32 c);

/* Finish an active effect: mark it finished, clear its value, play one of two
 * sounds, then advance the effect script by one step. */
void sub_0809F150(u8 *self)
{
    if (*(u8 *)(self + 0x74) == 0)
        return;

    {
        u8 *p70 = self + 0x70;
        s32 zero = 0;
        *p70 = 1;
        *(s32 *)(self + 0x5C) = zero;
    }

    if (*(u8 *)(self + 0x6C) != 0)
        sub_08005E80(0x16D);
    else
        sub_08005E80(0x16C);

    {
        u8 *animList;
        s32 *cbTable;
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        cbTable = (s32 *)0x08671BB0;
        animList = self + 0x18;
        sub_080C31E4(animList, self + 0x22, *cbTable);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        animList = animList + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(self, *(void **)((u32)*animList * 4 + *(u32 *)(self + 0x14)));
    }
}
