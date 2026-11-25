extern void sub_0800223C(void *actor);
extern s32 sub_080C389C(u8 value, s32 divisor);

/* "Wait 7 frames" script command: the current step's frame counter
 * (actor+0x19 + step*2, step at actor+0x22) is reduced modulo 7 each frame;
 * when it divides evenly, sub_0800223C advances the actor's script. */
void sub_08002364(void *actor) {
    if ((sub_080C389C(*(u8 *)((u8 *)actor + *(s16 *)((u8 *)actor + 0x22) * 2 + 0x19), 7) << 0x18) == 0) {
        sub_0800223C(actor);
    }
}
