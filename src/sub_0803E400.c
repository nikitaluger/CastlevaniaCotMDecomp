s32 spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
s32 sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);

/* Falling-particle emitter step: every 6th tick spawn one particle of kind 1
 * slightly below the object's position, and after 60 ticks switch the entity
 * to the next script handler stored at +0x24. */
void sub_0803E400(void *arg0) {
    void *motion;

    motion = *(void **)((u8 *)arg0 + 0x3C);
    if (sub_080C389C(*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19), 6) == 1) {
        spawnJitteredParticles(1, 1, *(s32 *)((u8 *)motion + 8), *(s32 *)((u8 *)motion + 0xC) + 0xFFF00000, 0xE0000, 0x100000);
    }
    if ((u32)*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) > 0x3C) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
    }
}
