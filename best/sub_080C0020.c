extern vu32 D_03007FF0;
typedef void (*Fn)(void);
extern void sub_080C0010(void);
void sub_080C0020(s32 unused, u8 *self) {
    if (self[0] & 0x80) {
        u8 *node = *(u8 **)(self + 0x20);
        if (node != NULL) {
            s32 z = 0;
            do {
                if (node[0] != 0) {
                    u8 b = node[1];
                    if (b & 7) {
                        Fn fp = *(Fn *)(D_03007FF0 + 0x2C);
                        sub_080C0010();
                    }
                    node[0] = z;
                }
                *(s32 *)(node + 0x2C) = z;
                node = *(u8 **)(node + 0x34);
            } while (node != NULL);
        }
        *(u8 **)(self + 0x20) = node;
    }
}
