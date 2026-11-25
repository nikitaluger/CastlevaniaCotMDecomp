void sub_08010D50(void *, void *, void *, u8);
extern void sub_08010D84(void *, void *, void *, u8);

/* Switch anim to a different frame: fetch its 4-byte descriptor and start
 * forward (direction >= 0) or reverse playback; if unchanged, refresh the mode. */
void sub_08011408(void *obj, void *anim, u16 frame, s32 direction, u8 mode) {
    u8 *st = (u8 *)anim;
    s16 curFrame = *(s16 *)(st + 0x0E);
    u8 m = mode;
    u16 f = frame;
    if (curFrame != (s16)f) {
        *(s16 *)(st + 0x0E) = (s16)f;
        if (direction >= 0) {
            sub_08010D50(obj, anim, (void *)(*(s32 *)*(s32 **)(st + 8) + (s16)f * 4), m);
        } else {
            sub_08010D84(obj, anim, (void *)(*(s32 *)*(s32 **)(st + 8) + (s16)f * 4), m);
        }
    } else {
        st[0] = (st[0] & 2) | m;
    }
}

void sub_08010D50(void *arg0, void *arg1, void *arg2, u8 arg3) {
    u8 *a1 = (u8 *)arg1;
    u8 *a2 = (u8 *)arg2;
    u8 a3 = arg3;
    u16 val = *(u16 *)a2;
    *(u16 *)(a1 + 2) = val;
    *(u32 *)(a1 + 4) = 0;
    a1[1] = 1;
    a1[0] = a3;
    *(u16 *)((u8 *)arg0 + 0x28) = *(u16 *)(a2 + 2);
    if ((s16)(val << 0) == 0) {
        a1[1] = 0;
        a1[0] = a3 | 2;
    }
}
