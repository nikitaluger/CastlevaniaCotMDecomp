struct S_02025FF0_1870 { u8 _0x000[0x1870]; u32 v; };
extern struct S_02025FF0_1870 D_02025FF0;

/* Walk the object list at D_02025FF0+0x1870 and set bit 0 of the flags word
 * (node+0x3C) of every node whose type is in 0x1CC..0x1CE. */
void sub_080B9874(void) {
    void *deadR5; /* never initialised: only its liveness forces the dead r5 save */
    void *node = *(void **)((u8 *)(void *)D_02025FF0.v + 0x30);
    if (node != NULL) {
        do {
            do {
                u16 type = *(u16 *)node;
                if ((u16)(type - 0x1CC) <= 2) {
                    if (deadR5) {
                        u16 *flags = *(u16 **)((u8 *)node + 0x3C);
                        *flags |= 1;
                    } else {
                        u16 *flags = *(u16 **)((u8 *)node + 0x3C);
                        *flags |= 1;
                    }
                }
                if (1) { }
            } while (0);
            node = *(void **)((u8 *)node + 0x2C);
        } while (node != NULL);
    }
}
