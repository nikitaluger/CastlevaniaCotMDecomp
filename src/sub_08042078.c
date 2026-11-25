extern void sub_08015974(void);
extern void sub_080161F0(void);
extern void sub_08016678(void *);
extern void sub_080C31E0(void *, s32);
extern void sub_080113A8(void *, void *);
extern void sub_08042130(void *, void *);
extern void sub_080C31E8(void *, void *, s32, s32);

/* Per-frame actor update: refresh the sprite animation from the work state and
 * its parameter set; when the animation state's bit 1 is set, clear the
 * sprite's busy flag and the current script step, then switch the actor to its
 * next script handler. */
void sub_08042078(void *actor) {
    void *sprite = *(void **)((u8 *)actor + 0x38);
    void *work = *(void **)((u8 *)actor + 0x3C);
    void *state = (u8 *)work + 0x34;
    void *anim = (u8 *)work + 0x48;
    sub_080113A8(sprite, state);
    sub_08042130(anim, sprite);
    if (2 & *(u8 *)state) {
        *(u8 *)((u8 *)*(void **)((u8 *)anim + 4) + 1) = 0;
        *(u8 *)((u8 *)actor + (*(s16 *)((u8 *)actor + 0x22)) * 2 + 0x19) = 0;
        {
            s32 *handlerTable = (s32 *)0x08671BD0;
            sub_080C31E8(actor + 0x18, actor + 0x22, 2, *handlerTable);
        }
    }
}
