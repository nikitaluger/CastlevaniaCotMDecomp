extern void *sub_08001480(void *parent, s32 kind);

/* Spawns one child object of kind 0x20E under `parent` and stores the given
 * pointer (a motion vector) at +0x3C. Returns the object, or NULL. */
void *sub_0808E9EC(void *parent, s32 data) {
    void *obj = sub_08001480(parent, 0x20E);
    if (obj == NULL) return NULL;
    *(s32 *)((u8 *)obj + 0x3C) = data;
    return obj;
}
