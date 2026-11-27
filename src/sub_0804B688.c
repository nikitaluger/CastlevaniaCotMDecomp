s32 spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);

/* Falling-particle emitter step (wide variant): every 6th tick spawn one
 * particle of kind 1 half a unit below the object with a wide random spread,
 * and after 60 ticks switch the entity to the next script handler at +0x24. */
void sub_0804B688(void *arg0) {
    void *motion;

    motion = *(void **)((u8 *)arg0 + 0x3C);
    if (sub_080C389C(*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19), 6) == 1) {
        spawnJitteredParticles(1, 1, *(s32 *)((u8 *)motion + 8), *(s32 *)((u8 *)motion + 0xC) + 0xFFF80000, 0x180000, 0xC0000);
    }
    if ((u32)*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) > 0x3C) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
