extern void advanceMotion(void *, s32);
extern void spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
extern void sub_0808DC40(s32, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Scripted projectile step: applies gravity, optionally sets high sprite flags,
 * emits a particle burst and, at a late script step, an effect and callback. */
void sub_08048CE4(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *sprite = *(void **)(self + 0x38);
    void *work = *(void **)(self + 0x3C);
    *(s16 *)((u8 *)sprite + 0x28) = 0;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) & 2) {
        *(u16 *)sprite = (u16)((*(u16 *)sprite & 0xFFF) | 0xE000);
    }
    advanceMotion(work, 0xB60);
    if (!(3 & *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19))) {
        spawnJitteredParticles(1, 1, *(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC), 0x80000, 0x80000);
    }
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0x28) {
        sub_0808DC40(*(s32 *)((u8 *)work + 8), *(s32 *)((u8 *)work + 0xC) + 0x140000, 8);
        sub_080C31E0(arg0, *(s32 *)(self + 0x24));
    }
}
