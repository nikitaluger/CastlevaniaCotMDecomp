void sub_0801165C(void *, s32);
void sub_080113A8(void *, void *);
void sub_0804ACB0(void *, void *);
void sub_080C31E4(void *, void *, u32);

struct S_02025FF0_172C {
    u8 pad[0x172C];
    u32 v172C;
};
extern struct S_02025FF0_172C D_02025FF0;
extern u32 D_08671BB0;

/* Integrates the entity's motion, refreshes its sprite animation and sound,
 * then, once it passes the Y threshold, doubles its horizontal velocity and
 * advances the script step. */
void sub_0804AB48(void *entity) {
    void *sprite;
    void *work;
    void *anim;
    u32 *p;

    sprite = *(void **)((u8 *)entity + 0x38);
    work = *(void **)((u8 *)entity + 0x3C);
    anim = (u8 *)work + 0x34;
    sub_0801165C(work, 0);
    sub_080113A8(sprite, anim);
    sub_0804ACB0(work, sprite);
    if (*(s32 *)((u8 *)work + 0xC) > (s32)(D_02025FF0.v172C + 0xFFE50000)) {
        *(s32 *)((u8 *)work + 0x10) <<= 1;
        *(u8 *)((u8 *)entity + *(s16 *)((u8 *)entity + 0x22) * 2 + 0x19) = 0;
        p = &D_08671BB0;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *p);
    }
}
