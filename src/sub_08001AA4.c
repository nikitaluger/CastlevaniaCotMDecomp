extern void sub_08001978(void *actor);
extern s32 sub_080C389C(u8 value, s32 divisor);

/* Script command: if the current step's flag byte (actor+0x19+step*2, where step
 * is the s16 at actor+0x22) is zero modulo 7, run the "wait 16 frames" handler. */
void sub_08001AA4(void *actor) {
    s16 step = *(s16 *)((u8 *)actor + 0x22);
    u8 flag = *(u8 *)((u8 *)actor + step * 2 + 0x19);
    if ((sub_080C389C(flag, 7) << 0x18) == 0) {
        sub_08001978(actor);
    }
}
