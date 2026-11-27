extern s32 gMenuState;
extern u8 D_0083FC00;
extern s32 sub_08005F1C(u16 id);
extern void stopAllSounds(void);
extern void sub_080C08D0(s32 mode);
extern void sub_080C31E4(void *state, void *step, s32 data);

void sub_0800A524(u8 *arg0)
{
    s32 *animStep;
    s32 result;
    s32 status;

    if (gMenuState != 1)
    {
        if (sub_08005F1C(0x15C) != 0)
            return;

        result = sub_08005F1C(1);
        if (result != 0)
            return;

        stopAllSounds();

        if (gMenuState != 5)
            sub_080C08D0((u32)&D_0083FC00 & 0xF0000);

        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = result;

        animStep = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *animStep);
        return;
    }

    status = sub_08005F1C(0x159);
    if (status == 0)
    {
        *(u8 *)(arg0 + *(s16 *)(arg0 + 0x22) * 2 + 0x19) = status;
        animStep = (s32 *)0x08671BB0;
        sub_080C31E4(arg0 + 0x18, arg0 + 0x22, *animStep);
    }
}
