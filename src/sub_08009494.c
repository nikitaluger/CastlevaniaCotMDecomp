extern u16 D_03000830[];
extern u16 D_080CAA00[]; /* command-script word table */
void resetMapRender(void);
void setLayerTilemap(int a, int b);
extern void (*D_08671BD0[])(void*, void*, int);

/* Script command handler: advance the object's script cursor, copy the next
 * script word to object+8, then point BG layer 1 at the tilemap encoded in the
 * following word (high byte + low byte << 5) and advance the cursor again. */
void sub_08009494(void *arg0)
{
    u32 *obj = (u32 *)arg0;
    u32 word;
    u32 offsetHigh;
    u32 offsetLow;
    obj[1] = obj[1] + 1;
    word = D_080CAA00[obj[1]];
    obj[2] = word;
    obj[1] = obj[1] + 1;
    word = D_080CAA00[obj[1]];
    offsetHigh = word >> 8;
    offsetLow = word & 0xFF;
    resetMapRender();
    setLayerTilemap(1, offsetHigh + (offsetLow << 5));
    obj[1] = obj[1] + 1;
}
