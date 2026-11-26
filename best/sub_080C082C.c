s32 sub_080C364C(s32, u32);
void sub_080C0A08(void);

void sub_080C082C(s32 arg0)
{
    u32 r2;
    void *r4;
    s32 r6;
    u16 r5;
    u32 idx;
    s32 res;
    u16 *timer;

    r2 = (u32)arg0;
    r4 = *(void **)0x03007FF0;
    r2 = (r2 & 0xF0000) >> 16;
    *(u8 *)((u8 *)r4 + 8) = (u8)r2;
    idx = r2 - 1;
    r5 = *(u16 *)((u8 *)0x0810C8DE + (idx << 1));
    r6 = 0;
    *(u32 *)((u8 *)r4 + 0x10) = r5;
    *(u8 *)((u8 *)r4 + 0x0B) = (u8)sub_080C364C(0x630, r5);
    res = sub_080C364C(0x91D1B * r5 + 0x1388, 0x2710);
    *(u32 *)((u8 *)r4 + 0x14) = res;
    *(u32 *)((u8 *)r4 + 0x18) = (sub_080C364C(0x01000000, res) + 1) >> 1;
    *(vu16 *)0x04000102 = r6;
    timer = (u16 *)0x04000100;
    *timer = (u16)(-sub_080C364C(0x44940, r5));
    sub_080C0A08();
    {
        volatile u8 *v = (volatile u8 *)0x04000006;
        do {} while (*v == 0x9F);
    }
    {
        volatile u8 *v = (volatile u8 *)0x04000006;
        do {} while (*v != 0x9F);
    }
    *(vu16 *)0x04000102 = 0x80;
}
