extern void sub_0806A7AC(s32, s32, s32);
extern void *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_080C31E4(void *, void *, u32);
extern void sub_080C31E0(void *, void *);

extern u32 gMainObjTimerCallback;

/* Initialize a scripted actor: assign its kind, allocate a main object and
 * four child objects, DMA its graphics into VRAM, run the script callback,
 * then select the resulting object. */
void sub_08067880(void *script)
{
    void *obj;
    s32 i;
    void *p18;
    void *p22;

    {
        s32 mover = *(s32 *)((u8 *)script + 0x6C) + 4;
        sub_0806A7AC(*(s32 *)((u8 *)script + 0x38), mover, 0x19);
    }

    obj = sub_0806D2A0(script, 0x34, 0x0A, 0x12);
    if (obj != 0) {
        *(u16 *)((u8 *)obj + 0x7C) = 0;
    }

    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x084748BC;
        dma[1] = 0x06013000;
        dma[2] = 0x800000E0;
        (void)dma[2];
    }

    i = 0;
    p18 = (u8 *)script + 0x18;
    p22 = (u8 *)script + 0x22;
    do {
        obj = sub_0806D2A0(script, 0x2B, 0x0A, 0x12);
        if (obj != 0) {
            *(s32 *)((u8 *)obj + 0x7C) = i;
        }
        i++;
    } while (i <= 3);

    *(u8 *)((u8 *)script + *(s16 *)((u8 *)script + 0x22) * 2 + 0x19) = 0;

    sub_080C31E4(p18, p22, gMainObjTimerCallback);

    (*(u8 *)((u8 *)script + *(s16 *)((u8 *)script + 0x22) * 2 + 0x19))++;

    {
        s16 idx = *(s16 *)((u8 *)script + 0x22);
        u8 *p = (u8 *)p18 + idx * 2;
        sub_080C31E0(script, *(void **)(*(u32 *)((u8 *)script + 0x14) + *p * 4));
    }
}
