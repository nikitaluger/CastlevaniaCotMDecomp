void sub_080C31E4(void *, void *, u32);
extern u32 D_08671BB4[];

/* Command step: decrement the work-state timer at +0x48; when it expires,
 * clear the current script slot's byte and re-dispatch the script action. */
void sub_0804FE64(void *obj) {
    u16 *timer = (u16 *)((u8 *)*(void **)((u8 *)obj + 0x3C) + 0x48);
    *timer = (u16)(*timer - 1);
    if ((s16)*timer < 0) {
        *(u8 *)((u8 *)obj + (*(s16 *)((u8 *)obj + 0x22) * 2) + 0x17) = 0;
        {
            u32 *callback;
            callback = D_08671BB4;
            sub_080C31E4((u8 *)obj + 0x18, (u8 *)obj + 0x22, *callback);
        }
    }
}
