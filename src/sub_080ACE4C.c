extern s32 sub_080C2F24(s32, s32);
extern void sub_080B0900(void *);

/* While the target's flag is clear, bump the object's tick counter and, every
 * 240th tick, set that flag. */
void sub_080ACE4C(void *obj) {
    s32 count;

    if (*(u8 *)((s8 *)*(void **)((s8 *)obj + 0xC) + 0x4C) == 0) {
        count = *(s32 *)((s8 *)obj + 0x18) + 1;
        *(s32 *)((s8 *)obj + 0x18) = count;
        if (sub_080C2F24(count, 0xF0) == 0) {
            sub_080B0900(*(void **)((s8 *)obj + 0xC));
        }
    }
}
