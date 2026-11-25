/* Set the active flag (+0x74) of every child object in the entity's list
 * (+0x30, next at +0x2C) to bit 0 of the flags word at `flags`. */
void sub_08056BF0(void *entity, u16 *flags) {
    u8 *child;
    child = *(u8 **)((u8 *)entity + 0x30);
    if (child != NULL) {
        u8 active = 1;
        u16 bit = 1;
        do {
            u16 t;
            t = bit;
            t &= *(volatile u16 *)flags;
            if (t != 0) {
                *(u8 *)(child + 0x74) = active;
            } else {
                *(u8 *)(child + 0x74) = 0;
            }
            child = *(u8 **)(child + 0x2C);
        } while (child != NULL);
    }
}
