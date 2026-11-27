extern s32 getSpriteFacingSign(void *);
extern void sub_0808DBB4(s32, s32, s32);
extern u8 D_080CEB38[];

/* Spawn a falling effect at work->pos plus entry `offsetIndex` of the 16.16
 * (dx, dy) offset table; the X offset is mirrored when the sprite faces left. */
void sub_0803010C(void *sprite, void *work, s32 offsetIndex) {
    u8 *table;
    s32 off;
    s32 dx;
    s32 dy;
    table = D_080CEB38;
    off = offsetIndex * 8;
    dx = *(u32 *)(table + off);
    table += 4;
    dy = *(u32 *)(table + off);
    if (getSpriteFacingSign(sprite) > 0) {
        dx = -dx;
    }
    sub_0808DBB4(((s32 *)work)[2] + dx, ((s32 *)work)[3] + dy, 8);
}
