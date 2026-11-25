extern void sub_08001978(void *actor);
extern s32 sub_080C389C(u8 value, s32 divisor);

/* "Wait 10 frames" script command: the current step's frame counter
 * (actor+0x19 + step*2, step at actor+0x22) is reduced modulo 10 each frame;
 * when it divides evenly, sub_08001978 advances the actor's script. */
void sub_08001B14(void *actor) {
    if ((sub_080C389C(*(u8 *)((u8 *)actor + *(s16 *)((u8 *)actor + 0x22) * 2 + 0x19), 0xA) << 0x18) == 0) {
        sub_08001978(actor);
    }
}
