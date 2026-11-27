extern void stepDelayTimer(void *a, void *b);
extern void playSound(s32 a);
extern void *spawnEntity(s32 a, s32 b, s32 c, s32 d);
extern s32 sub_0806D450(void *a, void *b, void *c);
extern void sub_080C31E0(void *a, void *b);

void sub_08080920(void *arg0)
{
    u8 *r6 = (u8 *)arg0;
    u8 *r8 = *(u8 **)(r6 + 0x6C) + 4;
    u8 *r5 = *(u8 **)(r6 + 0x38);
    u8 *r4 = r8;

    if (sub_0806D450(r6, r5, r4) > 0) {
        sub_080C31E0(r6, *(void **)(r6 + 0x24));
        return;
    }
    *(s32 *)(r4 + 0x10) = *(s32 *)(r4 + 0x10) - 1;
    *(s32 *)(r5 + 0x14) = *(s32 *)(r5 + 0x14) + 0x8000;
    *(s32 *)(r5 + 0x18) = (s32)((u32)*(s32 *)(r5 + 0x18) + 0xFFFF0000u);
    if (!(*(s32 *)(r4 + 0x10) & 7)) {
        void *ret = spawnEntity(*(s32 *)(r6 + 0x28), 0x67, 0x0A, 0x12);
        if (ret != NULL) {
            *(s32 *)((u8 *)ret + 0x9C) = (*(s32 *)(r4 + 0x10) >> 3) & 0x0F;
        }
    }
    if (*(s32 *)(r4 + 0x10) == 0) {
        sub_080C31E0(r6, *(void **)(r6 + 0x24));
        return;
    }
    {
        u8 *r7 = (u8 *)0x02025FF0;
        *(u16 *)(r5 + 0x00) = *(u16 *)(r7 + 0x18C2);
        stepDelayTimer(r8 + 0x1C, r5);
        *(s32 *)(r4 + 0x14) = *(s32 *)(r4 + 0x14) - 1;
        if (*(s32 *)(r4 + 0x14) == 0) {
            playSound(0x15F);
            *(s32 *)(r4 + 0x14) = 0x28;
        }
        if (*(u8 *)(r7 + 0x173A) == 0x1C ||
            (*(u8 *)(r7 + 0x14ED) == 0 && *(s32 *)(r7 + 0x10) != 0)) {
            sub_080C31E0(r6, *(void **)(r6 + 0x24));
        }
    }
}
