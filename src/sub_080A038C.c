extern u32 D_02025FF0[];

/* Walk the object list rooted at D_02025FF0+0x1870 and set bit 0 of the
 * animation flags of the first child of every object with id 0x184. */
void sub_080A038C(void)
{
    void *unused;
    u32 off = 0x1870;
    void *list = *(void **)((u8 *)D_02025FF0 + off);
    void *obj = *(void **)((u8 *)list + 0x30);
    if (obj != NULL) {
        do {
            do {
                if (*(s16 *)((s8 *)obj + 0) == 0x184) {
                    void *child = *(void **)((u8 *)obj + 0x30);
                    if (unused) {
                        u16 *flags = *(u16 **)((u8 *)child + 0x3C);
                        *flags |= 1;
                    } else {
                        u16 *flags = *(u16 **)((u8 *)child + 0x3C);
                        *flags |= 1;
                    }
                }
                if (1) { }
            } while (0);
            obj = *(void **)((u8 *)obj + 0x2C);
        } while (obj != NULL);
    }
}
