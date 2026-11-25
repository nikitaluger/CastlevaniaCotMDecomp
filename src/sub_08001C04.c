extern void sub_08001978(void *actor);

/* Script command: if the current step's flag byte (actor+0x19+step*2, where step
 * is the s16 at actor+0x22) is a multiple of 16, run the "wait 16 frames" handler. */
void sub_08001C04(void *actor) {
    s16 step = *(s16 *)((u8 *)actor + 0x22);
    u8 flag = *(u8 *)((u8 *)actor + step * 2 + 0x19);
    if (!(flag & 0xF)) {
        sub_08001978(actor);
    }
}
