void sub_080A0244(s32, s32);
void sub_080C31E4(void *, void *, s32);

/* When this object is in mode 2 or higher, put its six attached objects into
 * mode 2, clear their flags, and run the next script command. */
void sub_0809F6E0(void *arg0)
{
    u8 *entity = (u8 *)arg0;
    u8 *motion = *(u8 **)(entity + 0x3C);
    u8 *children = motion + 0x48;

    if (*(u8 *)(entity + 0x6C) > 1)
    {
        u32 i;
        u8 *flag94;
        u8 *flag95;
        u8 *flag96;
        void *scriptBase;
        void *scriptIdx;
        s32 *child;
        i = 0;
        flag94 = motion + 0x94;
        flag96 = motion + 0x96;
        flag95 = motion + 0x95;
        scriptBase = entity + 0x18;
        scriptIdx = entity + 0x22;
        child = (s32 *)children;

        do
        {
            sub_080A0244(*child++, 2);
            i++;
        } while (i <= 5);

        *flag94 = 0;
        *flag96 = 0;
        *flag95 = 0;
        *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = 0;
        sub_080C31E4(scriptBase, scriptIdx, *(s32 *)0x08671BB0);
    }
}
