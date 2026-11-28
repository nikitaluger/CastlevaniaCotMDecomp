void *spawnVariant2Effect(s32, s32, u32);
void sub_080C31E0(void *, u32);

/* Scripted object header: the handler run by the command script sits at 0x24,
 * sprite object at 0x38 and the work/animation state at 0x3C. */
struct MainObj {
    u8 pad_0x00[0x24];
    u32 updateCb;
    u8 pad_0x28[0x38 - 0x28];
    u32 sprite;
    u32 work;
};

/* Per-frame update: spawn the variant-2 effect at the work block's position
 * (x at +8, y at +0xC) with parameter 8, then dispatch this object's script
 * handler at +0x24. */
void sub_0804D724(struct MainObj *arg0) {
    void *work = (void *)arg0->work;
    spawnVariant2Effect(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC), 8);
    sub_080C31E0(arg0, arg0->updateCb);
}
