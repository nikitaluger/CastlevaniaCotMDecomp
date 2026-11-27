void advanceMotion(struct Work *work, s32 gravity);

struct Work {
    u8 pad_0x00[0x08];
    s32 x;                  /* +0x08 */
    s32 y;                  /* +0x0C */
    s32 vx;                 /* +0x10 */
    s32 vy;                 /* +0x14 */
};

struct Entity {
    u8 pad_0x00[0x22];
    s16 scriptIndex;        /* +0x22: current script entry index */
};

/* Once the current action has been active for more than 11 frames, advance
 * the work object's position by its velocity (without applying gravity). */
void sub_08040424(struct Entity *entity) {
    struct Work *work;
    u8 *slot;
    work = *(struct Work **)((u8 *)entity + 0x3C);
    slot = (u8 *)((s32)(*(s16 *)((u8 *)entity + 0x22)) * 2 + (u32)entity);
    if (slot[0x19] > 0xB) {
        advanceMotion(work, 0);
    }
}
