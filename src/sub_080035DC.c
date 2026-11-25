struct ObjectFlags {
    u8 pad[0x2A];
    u8 flags;
};

/* Clear all flags (the highlight/visible bits) on a sprite/actor object. */
void sub_080035DC(struct ObjectFlags *obj) {
    obj->flags = 0;
}
