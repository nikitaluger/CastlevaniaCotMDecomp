u16 sub_08005820(s32);
void sub_0805030C(void *, void *);
void sub_080C31E4(void *, void *, s32);

extern u32 D_08671BB0[];

/* On animation state 5/count 1, roll random values, shuffle the actor's 10-slot table, then end the state. */
void sub_0804FCB0(void *arg0)
{
    u8 *self = (u8 *)arg0;
    void *entity = *(void **)(self + 0x3C);
    void *anim = (u8 *)entity + 0x34;
    void *drops = (u8 *)entity + 0x48;
    u8 *cbArg1;
    u8 *cbArg0;
    s32 i;

    if (*(u8 *)((u8 *)anim + 1) == 5 && *(s32 *)((u8 *)anim + 4) == 1)
    {
        *(u16 *)drops = 0;
        *(u16 *)((u8 *)drops + 4) = 0;
        *(u16 *)((u8 *)drops + 6) = sub_08005820(3);
        *(u16 *)((u8 *)drops + 8) = sub_08005820(3);

        cbArg0 = self + 0x18;
        cbArg1 = self + 0x22;
        i = 9;
        do
        {
            u16 rndA = sub_08005820(0x0A);
            u16 rndB = sub_08005820(0x0A);
            void *pa = (u8 *)drops + (((s32)(rndA << 16) >> 15) + 0x0A);
            void *pb = (u8 *)drops + (((s32)(rndB << 16) >> 15) + 0x0A);
            sub_0805030C(pa, pb);
            i--;
        } while (i >= 0);

        {
            s32 slot = *(s16 *)(self + 0x22);
            *(u8 *)(self + slot * 2 + 0x19) = 0;
        }
        sub_080C31E4(cbArg0, cbArg1, D_08671BB0[0]);
    }
}
