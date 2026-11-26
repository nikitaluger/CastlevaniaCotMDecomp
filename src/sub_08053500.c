extern s32 sub_08005820(s32);
extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_080C31E4(void *, void *, u32);

/* Parameter block written at collision+0x18 when a spawned effect is created. */
struct SpawnEffect {
    u32 f0;
    u32 f4;
    u32 f8;
    u32 fC;
    u32 f10;
    u32 f14;
    s16 f18;
    u16 f1A;
    u32 f1C;
    u8 _pad[0x24 - 0x20];
    u32 f24;
    u32 f28;
};

/* Finishes a projectile's attack animation: once pose 5 has run its course,
 * initializes a spawned effect's parameters and fires the end callback. */
void sub_08053500(void *entity) {
    void *sprite;
    void *motion;
    void *child;
    u8 *collision;
    struct SpawnEffect *params;
    s32 zero;
    u32 *callback;

    sprite = *(void **)((u8 *)entity + 0x38);
    motion = *(void **)((u8 *)entity + 0x3C);
    collision = (u8 *)motion + 0x34;
    child = *(void **)((u8 *)motion + 0x28);
    zero = 0;
    *(u8 *)((u8 *)child + 1) = zero;
    setAnimationFrame(sprite, collision, 5, zero);
    if (*collision & 2) {
        params = (struct SpawnEffect *)((u8 *)collision + 0x18);
        *(u32 *)((u8 *)motion + 0x4C) = 0x4800;
        params->f4 = sub_08005820(0x10000);
        params->f8 = 0x4800;
        params->fC = 0x4800;
        params->f10 = zero;
        params->f14 = 0x100;
        params->f1C = sub_08005820(0xB5) + 0x168;
        params->f1A = 8 | params->f1A;
        params->f18 = zero;
        params->f24 = zero;
        params->f28 = zero;
        *(u8 *)((u8 *)entity + ((s32)*(s16 *)((u8 *)entity + 0x22) * 2) + 0x19) = 0;
        callback = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *callback);
    }
}
