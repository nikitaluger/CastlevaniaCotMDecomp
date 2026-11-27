extern void createChildObject(void *a, s32 b);
extern void sub_08005E80(s32 a);
extern void sub_0806D930(void *a);

struct S_02025368 {
    u8 pad0[0x2C4];
    u32 stats;
    u8 pad1[0x2FC - 0x2C8];
    s16 phase;
    u8 pad2[2];
    u32 u300;
};
extern struct S_02025368 gGameStatus;

/* Advance to the next phase: recompute derived stats, play the phase-change
 * sound, and spawn a child effect on the entity. */
void sub_08072018(void *entity)
{
    gGameStatus.phase++;
    sub_0806D930(&gGameStatus.stats);
    sub_08005E80(0x74);
    createChildObject(entity, 0x2E);
}
