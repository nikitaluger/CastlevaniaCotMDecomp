void sub_080C31E0(void *, void *);
void sub_080C31E8(void *, void *, s32, u32);

/* Count down the object's timer; when it expires, dispatch the child's
   handler and restart the object's script at step zero. */
void sub_08017380(void *arg0) {
    u8 *field = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x48;
    s32 timeLeft = *(u16 *)(field + 0x16) - 1;
    u32 *scriptFn;
    *(u16 *)(field + 0x16) = timeLeft;
    if ((timeLeft << 16) < 0) {
        void *child = *(void **)((u8 *)arg0 + 0x30);
        if (child != NULL) {
            sub_080C31E0(child, *(void **)((u8 *)child + 0x24));
        }
        *(u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0 + 0x17) = 0;
        scriptFn = (u32 *)0x08671BD8;
        sub_080C31E8((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 0, *scriptFn);
    }
}
