extern void sub_0801165C(s32, s32);
extern void sub_080146D0(s32, s32, s32);
extern s32 sub_080148D8(s32, s32);
extern s32 sub_08040A1C(s32, s32, s32, s32);
extern void setAnimationFrame(s32, s32, s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s16 D_080CF474[];
extern u32 gMainObjTimerCallback;

/* One frame of a scripted projectile: integrate its heading-driven velocity,
 * add gravity, resolve a ground collision, and after a delay play an effect,
 * bounce, reset the script timer and dispatch the script callback. */
void sub_0803FCD0(void *script) {
    void *sprite;
    void *body;
    void *anim;
    void *extra;
    s32 collided;
    sprite = *(void**)((char*)script + 0x38);
    body = *(void**)((char*)script + 0x3C);
    anim = (void*)((char*)body + 0x34);
    extra = (void*)((char*)body + 0x48);
    sub_0801165C(body, 0);
    *(s32*)((char*)extra+4) += 0x100;
    sub_080146D0(body, *(s32*)((char*)extra+4), 0x4000);
    *(s32*)((char*)body+0x14) += *(s32*)((char*)body+0x14) >> 2;
    collided = sub_08040A1C(sprite, anim, body, extra);
    sub_080148D8(sprite, *(s32*)((char*)body+0x08));
    if (collided != 0) {
        if (*(u8*)((char*)script + *(s16*)((char*)script+0x22)*2 + 0x19) > 0xA0) {
            s16 effect = D_080CF474[*(u8*)((char*)script+0x4C)];
            setAnimationFrame(sprite, anim, effect, 0);
            *(s32*)((char*)body+0x0C) += 0x10000;
            *(u8*)((char*)script + *(s16*)((char*)script+0x22)*2 + 0x19) = 0;
            {
                u32 *pd = &gMainObjTimerCallback;
                sub_080C31E4((char*)script+0x18, (char*)script+0x22, *pd);
            }
        }
    }
}
