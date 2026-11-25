struct S_02025FF0_7274 { u8 _0[0x14F4]; u32 f14F4; };
extern struct S_02025FF0_7274 D_02025FF0;
extern s32 sub_0806A7AC(s32, s32, s32);
extern void *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, s32);

/* Entity setup: configures sprite graphics, allocates a helper object, DMA-loads
   tile data into VRAM, then starts the entity script and dispatches its handler. */
void sub_08067274(void *entity) {
    u8 *obj = (u8 *)entity;
    s32 spriteId = *(s32 *)(obj + 0x6C) + 4;
    s32 sprite = *(s32 *)(obj + 0x38);
    D_02025FF0.f14F4 = 0x8C << 2;
    sub_0806A7AC(sprite, spriteId, 0x19);
    {
        void *child = sub_0806D2A0(entity, 0x34, 0x0A, 0x12);
        if (child != 0) {
            *(u16 *)((u8 *)child + 0x7C) = 0;
        }
    }
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x084740AC;
        dma[1] = 0x06013000;
        dma[2] = 0x80000400;
        (void)dma[2];
    }
    *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) = 0;
    {
        const u32 *scriptId = (const u32 *)0x08671BB0;
        void *scriptPtr = obj + 0x18;
        sub_080C31E4(scriptPtr, obj + 0x22, *scriptId);
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) += 1;
        scriptPtr = (u8 *)scriptPtr + *(s16 *)(obj + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)(*(u32 *)(obj + 0x14) + *(u8 *)scriptPtr * 4));
    }
}
