void sub_080C31E0(void *, s32);

/* Walk the entity list at owner+0x30 and update every 0x18D entry via
 * sub_080C31E0, passing the entry's +0x24 value. */
void sub_080A2DC8(void *owner) {
    void *ent;

    ent = *(void **)((u8 *)owner + 0x30);
    if (ent != NULL) {
        do {
            if (*(s16 *)ent == 0x18D) {
                sub_080C31E0(ent, *(s32 *)((u8 *)ent + 0x24));
            }
            ent = *(void **)((u8 *)ent + 0x2C);
        } while (ent != NULL);
    }
}
