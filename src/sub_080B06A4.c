/* Set the "active" byte (+0x94) on every type-0x1A8 child object in the
 * entity's child list (+0x30, next pointer at +0x2C). */
void sub_080B06A4(void *entity)
{
    u8 *child = *(u8 **)((u8 *)entity + 0x30);

    if (child != NULL) {
        do {
            if (*(s16 *)child == 0x1A8) {
                *(s8 *)(child + 0x94) = 1;
            }
            child = *(u8 **)(child + 0x2C);
        } while (child != NULL);
    }
}
