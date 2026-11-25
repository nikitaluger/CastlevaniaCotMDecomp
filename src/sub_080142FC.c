void sub_08062394(s32, u8);

void sub_080142C0(void *arg0, void *arg1) {
    void *r3 = *(void **)((u8 *)arg0 + 0x3C);
    u16 r2;
    if (r3 != NULL && arg1 != NULL) {
        r2 = *(u16 *)r3;
        if (!(0x20 & r2)) {
            if ((0x3 & r2) || (0x1 & *(u16 *)((u8 *)arg1 + 0x14))) {
                *(u16 *)r3 = (u16)(0x20 | r2);
                sub_08062394(0, *(u8 *)((u8 *)r3 + 0x1C));
            }
        }
    }
}

void sub_08014314(u16 *arg0, void *arg1) {
    if (0xC & *arg0) {
        *(u8 *)((u8 *)arg1 + 1) = 0;
    }
}

/* Run the object's display update with graphics set 0x8D, then restore the
 * object's own graphics set 0x57. */
void sub_080142FC(void *obj, void *arg1) {
    u8 *state = *(u8 **)((u8 *)obj + 0x3C);
    *(u16 *)(state + 0x1C) = 0x8D;
    sub_080142C0(obj, arg1);
    *(u16 *)(state + 0x1C) = 0x57;
}

extern vu32 D_02025FF0;

void sub_08014414(void *arg0) {
    void *head = *(void **)((u8 *)arg0 + 0x30);
    void *g = *(void **)((u8 *)&D_02025FF0 + 0x1870);
    void *node = head;
    void *ghead;
    void *tail;
    void *next;

    if (head != NULL) {
        do {
            *(void **)((u8 *)node + 0x28) = g;
            node = *(void **)((u8 *)node + 0x2C);
        } while (node != NULL);
        ghead = *(void **)((u8 *)g + 0x30);
        if (ghead != NULL) {
            tail = ghead;
            while ((next = *(void **)((u8 *)tail + 0x2C)) != NULL) {
                tail = next;
            }
            *(void **)((u8 *)tail + 0x2C) = head;
            *(void **)((u8 *)arg0 + 0x30) = NULL;
        }
    }
}
