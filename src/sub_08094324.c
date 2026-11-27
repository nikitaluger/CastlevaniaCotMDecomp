void freeMotionTracker(void);

/* A state block hanging off an entity: a linked object in the global object
 * list that gets released, and a saved update handler called with the entity. */
struct State {
    u8 unk0[0x24];
    void (*update)(void *);
    u8 unk28[0x10];
    void *linked;
};

/* Release the entity's linked object, then run its saved update handler. */
void sub_08094324(void *entity) {
    struct State *state = *(struct State **)((s8 *)entity + 0x3C);

    if (state->linked != 0) {
        freeMotionTracker();
    }
    state->update(entity);
}
