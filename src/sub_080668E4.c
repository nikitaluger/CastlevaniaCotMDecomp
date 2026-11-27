extern s32 setEntityForm(s32, s32, s32);
extern void *spawnEntity(void *, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern void sub_080C31E0(void *, s32);

extern u32 gMainObjTimerCallbacks[];

/* Spawns an entity's finishing effect: starts effect 0x56, creates a child
 * object, DMA-loads a tile graphic into VRAM, then fires the end callback and
 * advances the animation frame. */
void sub_080668E4(void *entity) {
    u8 *self = (u8 *)entity;
    s32 effectParam = *(s32 *)(self + 0x6C) + 4;
    s32 sprite = *(s32 *)(self + 0x38);
    setEntityForm(sprite, effectParam, 0x56);
    {
        void *child = spawnEntity(entity, 0x34, 0x0A, 0x12);
        if (child != 0) {
            *(u16 *)((u8 *)child + 0x7C) = 0;
        }
    }
    {
        volatile u32 *dma = (volatile u32 *)0x040000D4;
        dma[0] = 0x08473344;
        dma[1] = 0x06013000;
        dma[2] = 0x80000040;
        (void)dma[2];
    }
    *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
    {
        const u32 *callback = (const u32 *)0x08671BB0;
        void *frameByte = self + 0x18;
        sub_080C31E4(frameByte, self + 0x22, *callback);
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) += 1;
        frameByte = (u8 *)frameByte + *(s16 *)(self + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)(*(u32 *)(self + 0x14) + *(u8 *)frameByte * 4));
    }
}
