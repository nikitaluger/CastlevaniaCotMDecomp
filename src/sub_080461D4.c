extern void setAnimationFrame(void *, void *, s32, s32);
extern void sub_08047164(void *, void *, void *, void *);
extern void sub_080C31E4(void *, void *, s32);
extern s16 D_080CF864[][1]; /* per-variant animation ids */

/* Timed spawner update: marks its auxiliary state active, and after 20 frames
 * plays the animation selected by the object's variant byte, emits the related
 * children, clears the frame counter and advances the script. */
void sub_080461D4(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *view;
    u8 *work;
    u8 *anim;
    u8 *aux;
    s32 *scriptHandlers;

    view = *(void **)(self + 0x38);
    work = *(u8 **)(self + 0x3C);
    anim = work + 0x34;
    aux = work + 0x48;
    *(u8 *)(*(u32 *)(aux + 4) + 1) = 1;
    if (*((u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self) + 0x19) == 0x14) {
        setAnimationFrame(view, anim, D_080CF864[*(u8 *)(self + 0x4C)][0], 0);
        sub_08047164(arg0, work, aux, view);
        *((u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self) + 0x19) = 0;
        scriptHandlers = (s32 *)0x08671BB0;
        sub_080C31E4(self + 0x18, self + 0x22, *scriptHandlers);
    }
}
