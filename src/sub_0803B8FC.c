s32 getSpriteFacingSign(s32);
void spawnJitteredParticles(s32, s32, s32, s32, s32, s32);
void sub_0808DC40(s32, s32, s32);
void sub_080C31E0(void *, s32);
u8 sub_080C389C(u8, s32);

/* Advances this entity's effect timer: spawns a burst on frame 6 and a
 * follow-up effect after 0x3C frames, then dispatches the completion callback. */
void sub_0803B8FC(void *arg0) {
    s32 handle;
    void *state;

    handle = *(s32 *)((u8 *)arg0 + 0x38);
    state = *(void **)((u8 *)arg0 + 0x3C);
    *(u32 *)((u8 *)arg0 + 0x14) = 0x0866DF78;
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
    {
        u32 entryOffset = (u32)(((s16)*(u16 *)((u8 *)arg0 + 0x22)) * 2);
        u8 *entry = (u8 *)(entryOffset + (u32)arg0);
        entry[0x19] = entry[0x19] + 1;
    }
    {
        s32 entryOffset2 = ((s16)*(u16 *)((u8 *)arg0 + 0x22)) * 2;
        u8 *callbackArgs = (u8 *)arg0 + 0x18;
        u8 callbackIndex = *(callbackArgs + entryOffset2);
        u32 callbackTable = *(u32 *)((u8 *)arg0 + 0x14);
        sub_080C31E0(arg0, *(s32 *)(callbackTable + callbackIndex * 4));
    }
    *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    {
        u32 entryOffset = (u32)(((s16)*(u16 *)((u8 *)arg0 + 0x22)) * 2);
        u8 *entry = (u8 *)(entryOffset + (u32)arg0);
        if (sub_080C389C(entry[0x19], 6) == 1) {
            if (getSpriteFacingSign(handle) < 0) {
                spawnJitteredParticles(1, 1, *(s32 *)((u8 *)state + 0x08) + 0xFFF80000, *(s32 *)((u8 *)state + 0x0C) + 0xFFF00000, 0xA0000, 0x140000);
            } else {
                spawnJitteredParticles(1, 1, *(s32 *)((u8 *)state + 0x08) + 0x80000, *(s32 *)((u8 *)state + 0x0C) + 0xFFF00000, 0xA0000, 0x140000);
            }
        }
    }
    {
        u32 entryOffset = (u32)(((s16)*(u16 *)((u8 *)arg0 + 0x22)) * 2);
        u8 *entry = (u8 *)(entryOffset + (u32)arg0);
        if ((u32)entry[0x19] > 0x3C) {
            if (getSpriteFacingSign(handle) < 0) {
                sub_0808DC40(*(s32 *)((u8 *)state + 0x08) + 0xFFF40000, *(s32 *)((u8 *)state + 0x0C) + 0xFFEC0000, 8);
            } else {
                sub_0808DC40(*(s32 *)((u8 *)state + 0x08) + 0xC0000, *(s32 *)((u8 *)state + 0x0C) + 0xFFEC0000, 8);
            }
            sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        }
    }
}
