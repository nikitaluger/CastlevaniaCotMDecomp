extern void sub_0800F370(s32);
extern u8 D_02025368[];
extern u8 D_020278D0[];
struct Pair0F124 { u32 a, b; };
struct Data0F124 { struct Pair0F124 p[4]; };
extern struct Data0F124 D_080CB1E0;

struct ByteField { u8 f; };

void sub_0800F124(s32 arg0) {
    s32 i = (u8)arg0;
    u8 *tbl = D_02025368;
    s32 count = 0;
    struct Data0F124 buf;
    u32 j = 0;
    u32 off;
    vu8 *p;

    buf = D_080CB1E0;
    off = i * 32;
    p = D_020278D0 + 0x73 + off;
    for (; j < 32; j++) { ((struct ByteField *)p)->f |= 0xFF; p++; }
    *(u8 *)(D_020278D0 + 0xF3 + i) = 0;
    if (i != 3) {
        *(u8 *)(count + off + (D_020278D0 + 0x73)) = 0;
        count++;
    }
    if (buf.p[i].a <= buf.p[i].b) {
        p = D_020278D0 + 0x73 + off + count;
        for (j = buf.p[i].a; j <= buf.p[i].b; j++) {
            if (*(u8 *)(tbl + 0x384 + j) != 0) {
                *p = j;
                p++;
                count++;
            }
        }
    }
    *(u8 *)(D_020278D0 + 0xF3 + i) = count;
    sub_0800F370(i);
}
