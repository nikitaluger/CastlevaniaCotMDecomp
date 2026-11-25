/* Wakes the boss's part group: walks the child list and raises bit 0 of the
 * sub-object flags of every child whose actor type is 0x1C2.
 * (The dead `if` and nested do-while are agbcc codegen anchors, not logic.) */
void sub_080B722C(void *entity)
{
    void *unused;
    u8 *self;
    void *node;
    u16 *flags;

    self = (u8 *)entity;
    node = *(void **)(self + 0x30);
    if (node != NULL) {
        do {
            do {
                if ((*(s16 *)(((u8 *)node) + 0)) == 0x1C2) {
                    if (unused) {
                        flags = *(u16 **)(((u8 *)node) + 0x3C);
                        *flags |= 1;
                    } else {
                        flags = *(u16 **)(((u8 *)node) + 0x3C);
                        *flags |= 1;
                    }
                }
                if (1) { }
            } while (0);
            node = *(void **)(((u8 *)node) + 0x2C);
        } while (NULL != node);
    }
}
