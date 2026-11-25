/* Configure a spawned object: set its +0x6C flag byte and write the two
 * position/parameter words at +0x4C and +0x5C. */
void sub_080A5734(void *obj, s32 x, s32 y) {
    if (obj != NULL) {
        *(s8 *)((s8 *)obj + 0x6C) = 1;
        *(s32 *)((s8 *)obj + 0x4C) = x;
        *(s32 *)((s8 *)obj + 0x5C) = y;
    }
}
