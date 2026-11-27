/* Updates an entity's aim: mirrors its graphic toward the target, advances its
   animation, then, while the global mode is active and the target is in range,
   stores the aim angle and calls the entity's behavior callback. */
extern void sub_080148D8(s32, s32);
extern void sub_0809E278(s32, s32, void *, void *);
extern s32 sub_0801459C(void *, s32);
extern s32 getAngleFromDelta(s32, s32);
extern void sub_080C31E4(void *, void *, s32);

struct AimGameState {
    u8 _0[0x3C];
    u16 mode;
    u8 _3E[0x174C - 0x3E];
    s32 targetX;
};
extern struct AimGameState gMainWorkspace;

struct AimWork {
    u16 flags;
    u8 _02[6];
    s32 posX;
    s32 posY;
    u8 _10[0x34 - 0x10];
    u8 anim[0x48 - 0x34];
};

struct AimEffect {
    u8 _0[0x11];
    u8 active;
    u8 _12[0x2E - 0x12];
    u16 angle;
};

void sub_0809CDD4(u8 *entity) {
    u8 *gfx;
    struct AimWork *work;
    u8 *anim;
    struct AimEffect *effect;
    s32 angle;

    gfx = *(u8 **)(entity + 0x38);
    work = *(struct AimWork **)(entity + 0x3C);
    anim = work->anim;
    effect = (struct AimEffect *)((u8 *)work + 0x48);
    *(u8 *)((u8 *)work + 0x89) = 0;
    sub_080148D8((s32)gfx, work->posX);
    sub_0809E278((s32)gfx, (s32)anim, (u8 *)work, (u8 *)effect);

    if (gMainWorkspace.mode != 0) {
        if (sub_0801459C(work, 0x700000) != 0 || (work->flags & 2) != 0) {
            effect->active = 1;
            angle = getAngleFromDelta(0x01000000 - work->posY, gMainWorkspace.targetX - work->posX);
            {
                u8 zero = 0;
                effect->angle = angle;
                *(u8 *)(entity + *(s16 *)(entity + 0x22) * 2 + 0x19) = zero;
            }
            {
                s32 *callback = (s32 *)0x08671BB0;
                sub_080C31E4(entity + 0x18, entity + 0x22, *callback);
            }
        }
    }
}
