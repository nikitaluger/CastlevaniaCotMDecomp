extern void *spawnBudgetedEffect(s32, s32);

/* The spawn-object free-list pointer sits at the end of the game-state block. */
struct GameState { u8 _pad[0x1870]; u32 spawnPool; };
extern struct GameState gMainWorkspace;

struct Sprite { u8 _pad[2]; u16 flags; };
struct MotionState { u8 _pad[8]; u32 x; u32 y; };

/* Called when the sprite's animation reaches frame 7: spawn effect 0x11B just in
 * front of the actor, 24px above it, moving horizontally away from the facing
 * direction at 2px per frame. */
void sub_08045034(struct Sprite *sprite, struct MotionState *motion) {
    void *spawn = spawnBudgetedEffect(gMainWorkspace.spawnPool, 0x11B);
    s32 velocity;
    u32 x;
    if (!spawn) return;
    x = motion->x;
    if (sprite->flags & 0x10)
        *(u32 *)((u8 *)spawn + 0x4C) = x + 0x80000;
    else
        *(u32 *)((u8 *)spawn + 0x4C) = x + 0xFFF80000;
    *(u32 *)((u8 *)spawn + 0x5C) = motion->y + 0xFFE80000;
    if (sprite->flags & 0x10) velocity = 0x20000; else velocity = 0xFFFE0000;
    *(u32 *)((u8 *)spawn + 0x6C) = velocity;
}
