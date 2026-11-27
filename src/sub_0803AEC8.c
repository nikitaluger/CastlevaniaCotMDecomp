extern void stepAnimationTrack(s32, void *);
extern void sub_080C31E0(void *, s32);

/* Entity state block (the pointer at entity+0x3C). +0x34 is the
 * sprite/animation descriptor advanced by stepAnimationTrack. */
struct State {
    u8 _0[0x10];
    u32 f10;
    u32 f14;
    u8 _18[0x34 - 0x18];
    u8 anim[0xC];
};

struct Entity {
    u8 _0[0x24];
    s32 update;              /* 0x24: pending update callback, invoked via sub_080C31E0 */
    u8 _28[0x10];
    s32 sprite;              /* 0x38: sprite/animation owner */
    struct State *state;     /* 0x3C: per-entity state block */
};

/* Advance the state's sprite descriptor via stepAnimationTrack; if the descriptor
 * reports completion (bit 1), run the entity's pending update callback. */
void sub_0803AEC8(struct Entity *entity)
{
    s32 spriteId = entity->sprite;
    struct State *state = entity->state;
    void *sprite = (u8 *)state + 0x34;
    stepAnimationTrack(spriteId, sprite);
    if (2 & *(u8 *)sprite) {
        sub_080C31E0(entity, entity->update);
    }
}
