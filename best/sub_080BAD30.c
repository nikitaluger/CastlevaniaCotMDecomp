s32 sub_080BE8D4(void);
s32 sub_080BE938(void);
void sub_080988B8(void *);
extern u32 D_08102ED4[];
extern u32 D_08102EE0[];

void sub_080BAD30(void *arg0) {
    u8 *self = (u8 *)arg0;
    u32 r5 = *(u32 *)(self + 0x3C);
    u32 r4 = r5 + 0x48;
    u32 r6 = *(u32 *)(self + 0x4C);
    u32 t, u;
    *(u32 *)(r4 + 0x5C) = sub_080BE8D4();
    *(u32 *)(r4 + 0x60) = sub_080BE938();
    t = (u32)&D_08102ED4[0];
    t = *(u32 *)((u8 *)t + *(u32 *)(r4 + 0x5C) * 4);
    *(u32 *)(r5 + 0x08) = t;
    u = (u32)&D_08102EE0[0];
    *(u32 *)(r5 + 0x0C) = *(u32 *)((u8 *)u + *(u32 *)(r4 + 0x60) * 4);
    sub_080988B8((void *)r6);
}
