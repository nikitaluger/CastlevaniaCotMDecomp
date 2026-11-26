extern void setAnimationFrame(void *, void *, s32, s32);
extern s32 sub_08014990(void *);
extern void sub_0804C674(void *, void *, void *);
extern void sub_080C31E8(void *, void *, s32, void *);
extern void *D_08671BD8;

void sub_0804C3F0(void *arg0)
{
    u8 *r6;
    void *r7;
    u8 *r4;
    u8 *r8;
    s32 v;
    s16 idx;

    r7 = *(void **)((u8 *)arg0 + 0x38);
    r6 = *(u8 **)((u8 *)arg0 + 0x3C);
    r4 = r6 + 0x34;
    r8 = r6 + 0x48;

    setAnimationFrame(r7, r4, 5, 0);

    do { if (r4[0] & 2) {
        s32 res;

        sub_0804C674(arg0, r6 + 0x54, r6 + 0x58);

        res = sub_08014990(r7);
        v = 0xE000;
        if (res < 0) {
            v = 0xA000;
        }
        *(s32 *)(r8 + 0x20) = v;

        idx = *(s16 *)((u8 *)arg0 + 0x22);
        ((u8 *)arg0)[idx * 2 + 0x17] = 0;

        {
            void **litp = &D_08671BD8;
            void *a0 = (u8 *)arg0 + 0x18;
            void *a1 = (u8 *)arg0 + 0x22;
            sub_080C31E8(a0, a1, 1, *litp);
        }
    } } while (0);
}
