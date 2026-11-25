/* Walk the entity list at owner+0x30 and clear the +0x9C flag on every 0x19B
 * entry. */
void sub_080AACCC(void *owner) {
    void *ent;

    ent = *(void **)((u8 *)owner + 0x30);
    if (ent != NULL) {
        do {
            if (*(s16 *)ent == 0x19B) {
                *(s8 *)((u8 *)ent + 0x9C) = 0;
            }
            ent = *(void **)((u8 *)ent + 0x2C);
        } while (ent != NULL);
    }
}
