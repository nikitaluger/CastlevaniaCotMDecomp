extern void *sub_0805FAEC(s32 parent, s32 type);

/* Spawn a type-0x17D entity under `parent` and store `value` in its +0x4C
 * field (the first position/parameter word). */
void sub_0809C5FC(s32 parent, s32 value) {
    void *ent;

    ent = sub_0805FAEC(parent, 0x17D);
    if (ent != NULL) {
        *(s32 *)((u8 *)ent + 0x4C) = value;
    }
}
