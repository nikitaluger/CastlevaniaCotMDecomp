extern s16 sub_080C2F20(s32, s32);

/* Scale the +0xE motion parameter by 5/4 on every type-0x19B child of an entity. */
void sub_080A8B70(void *entity) {
    u8 *child;
    u8 *obj;

    child = *(u8 **)((u8 *)entity + 0x30);
    if (child != NULL) {
        do {
            if (*(s16 *)child == 0x19B) {
                obj = *(u8 **)(child + 0x3C);
                *(s16 *)(*(u8 **)(obj + 0x28) + 0xE) =
                    sub_080C2F20(*(s16 *)(*(u8 **)(obj + 0x28) + 0xE) * 5, 4);
            }
            child = *(u8 **)(child + 0x2C);
        } while (child != NULL);
    }
}
