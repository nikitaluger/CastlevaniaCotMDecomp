extern void sub_0800223C(void *entity);

/* Script command: if the current step's flag byte (entity+0x19+step*2, where step
 * is the s16 at entity+0x22) is a multiple of 8, run the "wait" handler. */
void sub_0800238C(void *entity) {
    s16 step = *(s16 *)((u8 *)entity + 0x22);
    u8 flag = *(u8 *)((u8 *)entity + step * 2 + 0x19);
    if (!(flag & 7)) {
        sub_0800223C(entity);
    }
}
