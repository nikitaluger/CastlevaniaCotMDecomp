/* twin of sub_080184E0 (both matched) */
s16 getSpriteFacingSign(void *);

/* Shifts the four-slot position/facing history, records the current position,
 * then copies the segment coordinates into the two linked follower objects. */
void sub_0801BC84(void *arg0) {
    u8 *self = (u8 *)arg0;
    u8 *obj = *(u8 **)(self + 0x3C);
    u8 *head = obj + 0x48;
    u8 *parent = *(u8 **)(self + 0x38);
    s32 count = 4;
    u8 *xHist = obj + 0xA8;
    u8 *yHist = obj + 0xB2;
    u8 *dirHist = obj + 0xBC;
    u16 *hist = (u16 *)(obj + 0xAE);
    s32 i;
    s32 off;
    s32 coord;

    do {
        i = count - 1;
        hist[1] = hist[0];
        hist[6] = hist[5];
        hist[11] = hist[10];
        hist--;
        count = i;
    } while (i > 0);

    off = i << 1;

    {
        u16 *dst = (u16 *)(xHist + off);
        coord = *(s32 *)(obj + 0x08);
        if (coord < 0) coord += 0xFFFF;
        *dst = (u16)(coord >> 16);
    }
    {
        u16 *dst = (u16 *)(yHist + off);
        coord = *(s32 *)(obj + 0x0C);
        if (coord < 0) coord += 0xFFFF;
        *dst = (u16)(coord >> 16);
    }
    *(u16 *)(dirHist + off) = getSpriteFacingSign(parent);

    {
        u8 *follower = *(u8 **)(self + 0x30);
        if (follower != 0) {
            u16 a;
            a = *(u16 *)(head + 0x66); *(u16 *)(follower + 0x4C) = a;
            a = *(u16 *)(head + 0x70); *(u16 *)(follower + 0x54) = a;
            a = *(u16 *)(head + 0x7A); *(u16 *)(follower + 0x5C) = a;
            follower = *(u8 **)(follower + 0x30);
            if (follower != 0) {
                a = *(u16 *)(head + 0x62); *(u16 *)(follower + 0x4C) = a;
                a = *(u16 *)(head + 0x6C); *(u16 *)(follower + 0x54) = a;
                a = *(u16 *)(head + 0x76); *(u16 *)(follower + 0x5C) = a;
            }
        }
    }
}
