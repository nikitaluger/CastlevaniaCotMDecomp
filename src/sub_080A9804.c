extern s32 sub_08013B5C(void *, void *);
extern void sub_08011528(s32, void *);

/* Display/animation state block referenced by the entity at +0x3C; the
 * movement track lives at +0x34 within it. */
struct DisplayState {
    u8 _0[0x34];
    u8 track[1];
};

struct Entity {
    u8 _0[0x38];
    s32 spriteAttrs;             /* 0x38 */
    struct DisplayState *state;  /* 0x3C */
};

/* If the display-state handler did not consume this frame, advance the
 * entity's movement track one step. */
void sub_080A9804(struct Entity *entity)
{
    s32 spriteAttrs = entity->spriteAttrs;
    void *state = entity->state;
    void *track = (u8 *)state + 0x34;

    if (sub_08013B5C((void *)spriteAttrs, state) == 0)
    {
        sub_08011528(spriteAttrs, track);
    }
}
