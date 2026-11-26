extern void setAnimationFrame(s32, void *, s32, s32);
extern void sub_080C31E0(void *, s32);

/* Entity state block (the pointer at entity+0x3C). +0x10/+0x14 are step
 * counters cleared when the state restarts; +0x34 is the animation block
 * driven by setAnimationFrame. */
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

/* Set the state's animation to frame 0x26; if the animation is already
 * finished, run the entity's pending update callback. */
void sub_08021630(struct Entity *entity)
{
    s32 sprite = entity->sprite;
    struct State *state = entity->state;
    void *anim = (u8 *)state + 0x34;
    setAnimationFrame(sprite, anim, 0x26, 0);
    if (2 & *(u8 *)anim)
        sub_080C31E0(entity, entity->update);
}

/* Restart the state (clear both step counters at +0x10/+0x14), set its
 * animation to frame 0x2D, then run the update callback if it is finished. */
void sub_0802165C(struct Entity *entity)
{
    s32 sprite = entity->sprite;
    struct State *state = entity->state;
    void *anim = (u8 *)state + 0x34;
    state->f14 = 0;
    state->f10 = 0;
    setAnimationFrame(sprite, anim, 0x2D, 0);
    if (2 & *(u8 *)anim)
        sub_080C31E0(entity, entity->update);
}
