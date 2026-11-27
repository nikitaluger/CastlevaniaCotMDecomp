extern void sub_0800F370(s32);
extern u8 gGameStatus[];
extern u8 gMenuState[];
struct Pair0F124 { u32 a, b; };
struct Data0F124 { struct Pair0F124 p[4]; };
extern struct Data0F124 D_080CB1E0;

struct ByteField { u8 f; };

void sub_0800F124(s32 arg0) {
    s32 i = (u8)arg0;
    u8 *tbl = gGameStatus;
    s32 count;
    struct Data0F124 buf;
    u32 j = 0;
    u32 off;
    vu8 *p;

    buf = D_080CB1E0;
    count = 0;
    off = i * 32;
    do { do { do { p = gMenuState + 0x73 + off; } while (0); } while (0);
    for (; j < 32; j++) { ((struct ByteField *)p)->f |= 0xFF; p++; } } while (0);
    *(u8 *)(gMenuState + 0xF3 + i) = 0;
    if (i != 3) {
        *(u8 *)(count + off + (gMenuState + 0x73)) = 0;
        count++;
    }
    if (buf.p[i].a <= buf.p[i].b) {
        do { do { do { do { p = gMenuState  + off + 0x73 + count; } while (0); } while (0); } while (0); } while (0);
        for (j = buf.p[i].a; j <= buf.p[i].b; j++) {
            if (*(u8 *)(tbl + 0x384 + j) != 0) {
                *p = j;
                p++;
                count++;
            }
        }
    }
    *(u8 *)(gMenuState + 0xF3 + i) = count;
    do { sub_0800F370(i); } while (0);
}
