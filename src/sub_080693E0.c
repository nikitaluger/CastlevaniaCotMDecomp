struct GlobalFlagState { u8 pad[0x24]; u32 f24; u16 f28; };
extern struct GlobalFlagState gMainWorkspace;
extern u8 gGameStatus[];
extern u8 gCameraState[];
struct SpawnEntry { void *p0; void *p1; u8 rest[0x58 - 8]; };
struct SpawnEntryTable { u8 pad[0x18]; struct SpawnEntry entries[1]; };
extern struct SpawnEntryTable D_080E03A0;

void startEffectTimer(void *, s32, void *);
void sub_08005E80(s32);
void sub_080C31E8(void *, void *, s32, s32);

/* Advance an effect's two-step spawn sequence when its character/state condition
   holds: bind the matching entry pointer to the target and play a cue sound. */
s32 sub_080693E0(void *obj, void *unused, u8 *effect, void *target) {
    s32 phase;
    u32 stateTable = (u32)gGameStatus;
    u32 wordOffset;

    if (gMainWorkspace.f24 != 0 ?
        (gMainWorkspace.f28 & *(u16 *)(stateTable + 0x3BE)) :
        (wordOffset = 0x146C, *(u16 *)((u32)gCameraState + wordOffset) & *(u16 *)(stateTable + 0x3BE))) {
        phase = *(s32 *)(effect + 0x4C);
        switch (phase) {
        case 0: {
            *(s32 *)(effect + 0x40) = phase;
            *(s32 *)((u8 *)target + 0x0C) = (s32)D_080E03A0.entries[*(s32 *)(effect + 0x44)].p0;
            *(s32 *)(effect + 0x4C) = 1;
            *(s32 *)(effect + 0x50) = phase;
            startEffectTimer(effect + 0x28, 0, (void *)0x084FCA84);
            sub_08005E80(0x1C3);
            *(u8 *)(2 * (u32)(s16)*(u16 *)((u8 *)obj + 0x22) + (u32)obj + 0x19) = (u8)phase;
            {
                void **litPtr = (void **)0x08671BD0;
                sub_080C31E8((u8 *)obj + 0x18, (u8 *)obj + 0x22, 0x28, (s32)*litPtr);
            }
            return 1;
        }
        case 1: {
            *(s32 *)((u8 *)target + 0x0C) = (s32)D_080E03A0.entries[*(s32 *)(effect + 0x44)].p1;
            *(s32 *)(effect + 0x4C) = 2;
            *(s32 *)(effect + 0x50) = 0;
            startEffectTimer(effect + 0x28, 0, (void *)0x084FCA84);
            sub_08005E80(0x1C3);
            return 1;
        }
        default:
            return 0;
        }
    }
    return 0;
}
