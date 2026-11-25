/* Camera/scroll transition for an entity: mark the scroll blocked, reset the
 * trail counter, set up the screen offsets, spawn an object, trigger a VRAM DMA
 * copy and a sound, then dispatch the entity's state callbacks. */
struct S_040000D4 {
    vu32 f0;
    vu32 f4;
    vu32 f8;
};
extern struct S_040000D4 D_040000D4;
extern void *D_08671BB0;
extern void sub_0806A7AC(void *, void *, s32);
extern void *sub_0806D2A0(void *, s32, s32, s32);
extern void sub_0808D2FC(u32);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);

void sub_08067544(u8 *entity) {
    u8 *cam = *(u8 **)(entity + 0x6C);
    u8 *pos = cam + 4;
    u8 *view = *(u8 **)(entity + 0x38);
    u32 zero;
    void *spawned;
    u32 dmaControl;
    u8 *statePtr;
    s32 offset = 0xC0 << 15;
    sub_0806A7AC(view, pos, 0x57);
    *(u32 *)(cam + 0xBC) = 0;
    zero = 0;
    *(u32 *)(cam + (0x84 << 1)) = *(u32 *)(pos + 4);
    *(u32 *)(cam + (0x88 << 1)) = *(u32 *)(pos + 4) + offset - *(u32 *)(view + 0x18);
    spawned = sub_0806D2A0(entity, 0x34, 0xA, 0x12);
    if (spawned != 0) *(u16 *)((u8 *)spawned + 0x7C) = (u16)zero;
    D_040000D4.f0 = 0x08473838;
    D_040000D4.f4 = 0x06013000;
    D_040000D4.f8 = 0x80000400;
    dmaControl = D_040000D4.f8;
    sub_0808D2FC(*(u32 *)(view + 0x14));
    (entity + *(s16 *)(entity + 0x22) * 2)[0x19] = (u8)zero;
    {
        void **callback = &D_08671BB0;
        statePtr = entity + 0x18;
        sub_080C31E4(statePtr, entity + 0x22, *callback);
    }
    {
        u8 *stateBytePtr = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
        stateBytePtr[0x19] = (u8)(stateBytePtr[0x19] + 1);
    }
    {
        s32 stateIndex = *(s16 *)(entity + 0x22) * 2;
        u8 stateValue = *(statePtr + stateIndex);
        void **callbackTable = *(void **)(entity + 0x14);
        void *callbackFn = callbackTable[stateValue];
        sub_080C31E0(entity, callbackFn);
    }
}
