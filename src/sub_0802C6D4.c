extern s32 sub_08014990(void *);
extern void sub_0808DBB4(s32, s32, s32);
extern u8 D_080CEA40[];

/* Spawn the falling effect at the owner's position plus velocity-table entry
 * `variant` (8-byte s32 {dx,dy} entries); the X offset is mirrored when the
 * owner faces left. */
void sub_0802C6D4(void *arg0, void *arg1, s32 variant) {
    u8 *table;
    s32 offset;
    s32 dx;
    s32 dy;
    table = D_080CEA40;
    offset = variant * 8;
    dx = *(u32 *)(table + offset);
    table += 4;
    dy = *(u32 *)(table + offset);
    if (sub_08014990(arg0) > 0) {
        dx = -dx;
    }
    sub_0808DBB4(((s32 *)arg1)[2] + dx, ((s32 *)arg1)[3] + dy, 8);
}
