void setAnimationFrame(void *, void *, s32, s32);
void sub_080113A8(void *, void *);
void sub_080C31E4(void *, void *, s32);

/* Advance the actor's sprite animation; when the script step reads 0x28,
 * fix the actor's size at 0x80x0x80, switch to animation 0x21 and step on. */
void sub_080A46AC(void *arg0) {
    void *actor = *(void **)((u8 *)arg0 + 0x38);
    void *anim = (u8 *)*(void **)((u8 *)arg0 + 0x3C) + 0x34;
    sub_080113A8(actor, anim);
    if (*(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) == 0x28) {
        s32 zero = 0;
        *(u16 *)((u8 *)actor + 4) = 0x80;
        *(u16 *)((u8 *)actor + 6) = 0x80;
        setAnimationFrame(actor, anim, 0x21, 0);
        *(u8 *)((u8 *)arg0 + *(s16 *)((u8 *)arg0 + 0x22) * 2 + 0x19) = (u8)zero;
        {
            s32 *lit = (s32 *)0x08671BB0;
            sub_080C31E4((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *lit);
        }
    }
}
