extern u8 gGameStatus[];
void *sub_08001480(void *, s32);
void sub_080C31E0(void *, s32);

struct S_off2C { u8 pad[0x2C]; s32 frameCounter; };

/* Room ambient effect: on every fourth frame spawn effect 0x83 and hand it the
 * quarter-frame counter; if the current room is not 0x10D, abort the effect
 * through the actor's current handler. */
void sub_0808B098(void *arg0)
{
    u8 *actor = *(u8 **)((u8 *)arg0 + 0x6C);
    struct S_off2C *mover = (struct S_off2C *)(actor + 4);
    u8 *sys = gGameStatus;
    mover->frameCounter = mover->frameCounter + 1;
    if ((mover->frameCounter & 3) == 0) {
        void *effect = sub_08001480(arg0, 0x83);
        if (effect != NULL)
            *(s32 *)((u8 *)effect + 0x9C) = mover->frameCounter >> 2;
    }
    if (*(u16 *)(sys + 0x94) != 0x10D)
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
}
