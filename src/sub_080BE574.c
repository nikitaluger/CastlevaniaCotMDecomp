struct ModeObject {
    u8 pad[0x5C];
    s32 mode;
};

/* Read the companion/effect object's mode word at +0x5C. */
s32 sub_080BE574(struct ModeObject *obj) {
    return obj->mode;
}
