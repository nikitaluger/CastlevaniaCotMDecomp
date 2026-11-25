void sub_080C31E4(void *, void *, s32);

/* Work-area timer view: reload value at +0x16, countdown at +0x1A (i.e.
 * work+0x5E and work+0x62). */
struct Timer { u8 _pad[0x16]; u16 reload; u8 _pad2[2]; u16 count; };

/* Tick the entity's work timer down; when it goes below zero, reload it with
 * 0x1E, clear work+0x10 and advance the entity's command script. */
void sub_080171A4(void *arg0) {
    u8 *p = (u8 *)arg0;
    u8 *work = *(u8 **)(p + 0x3C);
    struct Timer *timer = (struct Timer *)(work + 0x48);
    s32 count;

    count = timer->count - 1;
    timer->count = count;
    if ((s32)((u16)count << 16) < 0) {
        *(u32 *)(work + 0x10) = 0;
        timer->reload = 0x1E;
        *(u8 *)(p + *(s16 *)(p + 0x22) * 2 + 0x19) = 0;
        {
            s32 *script = (s32 *)0x08671BB0;
            sub_080C31E4(p + 0x18, p + 0x22, *script);
        }
    }
}
