extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Entity state block (the pointer at entity+0x3C). +0x10/+0x14 are step
 * counters, +0x34 is the sprite/animation descriptor driven by setAnimationFrame. */
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

/* Refresh the state's sprite descriptor in mode 0x17; if the descriptor
 * reports completion (bit 1), run the entity's pending update callback. */
void sub_08050730(struct Entity *entity)
{
    s32 spriteId = entity->sprite;
    struct State *state = entity->state;
    void *sprite = (u8 *)state + 0x34;
    setAnimationFrame(spriteId, sprite, 0x17, 0);
    if (2 & *(u8 *)sprite) {
        sub_080C31E0(entity, entity->update);
    }
}
