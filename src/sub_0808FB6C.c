void sub_08015974(void);

/* A state block hanging off an entity: a linked object in the global object
 * list that gets released, and a saved update handler called with the entity. */
struct State {
    u8 unk0[4];
    void *linked;
    void (*update)(void *);
};

/* Release the entity's linked object, then run its saved update handler. */
void sub_0808FB6C(void *entity) {
    struct State *state = *(struct State **)((s8 *)entity + 0x3C);

    if (state->linked != 0) {
        sub_08015974();
    }
    state->update(entity);
}
