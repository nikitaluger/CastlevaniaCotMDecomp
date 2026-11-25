extern void sub_08011368(void *, void *, s32, s32); /* set animation frame */
extern void _call_via_r1(void *, s32);
extern void sub_080C31E4(void *, void *, u32); /* _call_via_r2 */

/* Animation command: play animation 8 and count the u16 timer at work+0x4C
 * down; when it underflows, preset the work state word to 0x16C1, clear the
 * current step and run the next command. */
void sub_08053CB4(void *arg0) {
    void *sprite;
    u8 *work;
    u8 *anim;
    u8 *timer;
    s32 count;
    u32 *stream;

    sprite = *(void **)((u8 *)arg0 + 0x38);
    work = *(u8 **)((u8 *)arg0 + 0x3C);
    anim = work + 0x34;
    timer = work + 0x48;
    sub_08011368(sprite, anim, 8, 0);
    count = *(u16 *)(timer + 4) - 1;
    *(u16 *)(timer + 4) = count;
    if (count << 16 < 0) {
        *(u32 *)(work + 0x48) = 0x000016C1;
        *(u8 *)((u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0) + 0x19) = 0;
        stream = (u32 *)0x08671BB0;
        sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *stream);
    }
}
