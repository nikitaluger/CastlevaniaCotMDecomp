extern void sub_08008D18(void *);
extern s32 sub_08010440(void);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);

void sub_08010A50(u8 *arg0)
{
    s32 v = *(s32 *)(arg0 + 0x30);
    if (v == 0)
    {
        v = sub_08010440();
        *(s32 *)(arg0 + 0x3C) = v;
        if (v == 0)
        {
            s32 *lit;
            u8 *p18;
            *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = 0;
            lit = (s32 *)0x08671BD0;
            p18 = arg0 + 0x18;
            sub_080C31E8(p18, arg0 + 0x22, 3, (void *)*lit);
            *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
            p18 = p18 + *(s16 *)(arg0 + 0x22) * 2;
            sub_080C31E0(arg0, *(void **)(*(u32 *)(arg0 + 0x14) + *p18 * 4));
        }
        else
        {
            s32 *lit;
            u8 *p18;
            sub_08008D18(arg0);
            *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = (u8)v;
            lit = (s32 *)0x08671BB0;
            p18 = arg0 + 0x18;
            sub_080C31E4(p18, arg0 + 0x22, (void *)*lit);
            *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) += 1;
            p18 = p18 + *(s16 *)(arg0 + 0x22) * 2;
            sub_080C31E0(arg0, *(void **)(*(u32 *)(arg0 + 0x14) + *p18 * 4));
        }
    }
}
