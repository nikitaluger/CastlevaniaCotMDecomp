extern void allocWorkSlot(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void *gMainObjTimerCallbacks;

void sub_0805B808(void *arg0)
{
    s16 idx;
    u8 *base;
    u8 *p;
    s32 zero;

    allocWorkSlot(arg0, 0, 0x54, 0);

    if (*(u32 *)((u8 *)arg0 + 0x3C) == 0) {
        sub_080C31E0(arg0, *(void **)((u8 *)arg0 + 0x24));
        return;
    }

    p = *(u8 **)((u8 *)arg0 + 0x3C);
    p += 0x48;
    zero = 0;
    p[0] = 2;

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[idx * 2 + 0x19] = zero;

    {
        void **lit = &gMainObjTimerCallbacks;
        base = (u8 *)arg0 + 0x18;
        sub_080C31E4(base, (u8 *)arg0 + 0x22, *lit);
    }

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    ((u8 *)arg0)[idx * 2 + 0x19]++;

    idx = *(s16 *)((u8 *)arg0 + 0x22);
    base = base + idx * 2;
    sub_080C31E0(arg0, *(void **)(*(u32 *)((u8 *)arg0 + 0x14) + base[0] * 4));
}
