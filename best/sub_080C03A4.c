extern u8 D_00000009;

void sub_080BF7C8(void);
void sub_080C0614(s32);
void sub_080C076C(s32);
void sub_080C08D0(s32);
void sub_080C0A44(void *, s32, u8);
void sub_080C2F1C(s32, s32, s32);

void sub_080C03A4(void)
{
    u16 n;
    sub_080C2F1C((s32)(void*)sub_080BF7C8 & ~1, 0x030041D0, 0x04000100);
    sub_080C076C(0x03003090);
    sub_080C0614(0x030040D0);
    sub_080C08D0(0x0083FC00);
    n = (u16)((u32)&D_00000009);
    if (n != 0)
    {
        void *base = (void *)0x08106DCC;
        u32 offset = 0;
        s32 count = n;
        void *ptr = base;
        do
        {
            void *obj = *(void **)ptr;
            u32 base4 = (u32)base + 4;
            s32 arg1 = *(s32 *)(offset + base4);
            u8 arg2 = *(u8 *)((u8 *)ptr + 8);
            sub_080C0A44(obj, arg1, arg2);
            *(s32 *)((u8 *)obj + 0x18) = 0x03003000;
            ptr = (void *)((u8 *)ptr + 0xC);
            offset += 0xC;
            count--;
        }
        while (count != 0);
    }
}
