/* Sub-objects of a scripted effect: owner (collision flags), sprite (screen position),
   actor (world position/timer) and the outer effect object that ties them to a step script. */
struct EffectOwner {
    u8 flags0;          /* 0x00 */
    u8 flags1;          /* 0x01 */
    u8 pad02[2];
    u16 flags4;         /* 0x04 */
    u8 pad06[0xE];
    u16 flags14;        /* 0x14 */
};
struct EffectSprite {
    u16 state;          /* 0x00: low 12 bits = frame, high nibble = facing */
    u8 pad02[0x12];
    u32 screenX;        /* 0x14 */
    u32 screenY;        /* 0x18 */
};
struct EffectActor {
    u16 flags;          /* 0x00: bit 0 = remove */
    u8 pad02[6];
    u32 worldX;         /* 0x08 */
    u32 worldY;         /* 0x0C */
    u8 pad10[8];
    u32 life;           /* 0x18 */
    u8 pad1C[4];
    u16 timer;          /* 0x20 */
    s16 pose;           /* 0x22 */
    u8 pad24[4];
    struct EffectOwner *owner; /* 0x28 */
};
struct EffectObj {
    u8 pad00[2];
    u16 flags;                   /* 0x02: bit 0x8000 stops the script */
    u8 pad04[0x10];
    u32 scriptTable;             /* 0x14: per-step handler table */
    u8 scriptData[0xA];          /* 0x18 */
    s16 step;                    /* 0x22: current script step */
    u32 cleanupArg;              /* 0x24: argument for the cleanup callback */
    u8 pad28[0x10];
    struct EffectSprite *sprite; /* 0x38 */
    struct EffectActor *actor;   /* 0x3C */
};

extern u32 sub_0805F9B4(u32, u32);       /* actor inside camera bounds? */
extern s32 sub_080C36E4(u32, u32);       /* integer divide */
extern u32 sub_08016238(u32);            /* hit-test actor against global list */
extern void sub_08005E80(u32);           /* play sound effect */
extern void setAnimationFrame(u32, u32, u32, u32); /* set animation/frame control */
extern u32 sub_08013B5C(u32, u32);       /* advance actor's own AI */
extern void sub_080113A8(u32, u32);      /* request frame from frame control */
extern void sub_0801165C(u32, u32);      /* advance frame control velocity */
extern void sub_080C31E0(u32, u32);      /* cleanup / run script handler */

extern u8 gCameraState[];                  /* scroll-offset table */
extern u8 gMainWorkspace[];                  /* global game state */

/* Updates a scripted effect: advances the actor's pose/timer, handles its death and
   sound cues, runs one step of the effect's script, then projects the actor's world
   position into sprite screen space using the scroll-offset table. */
void sub_0802029C(struct EffectObj *eff) {
    struct EffectSprite *sprite = eff->sprite;
    struct EffectActor *actor = eff->actor;
    u8 *anim = (u8 *)actor + 0x34;
    s16 timer;
    s16 phase;

    actor->owner->flags1 |= 5;
    sprite->state = (sprite->state & 0xFFF) | ((actor->pose + 8) << 12);
    if (sub_0805F9B4(actor->worldX, actor->worldY) == 1) goto fail;
    timer = actor->timer;
    if (timer > 0) {
        phase = (s16)sub_080C36E4(timer, 3);
        if (phase == 0) goto set_d;
        if (phase == 1) goto set_c;
        goto after;
set_d:
        sprite->state = (sprite->state & 0xFFF) | 0xD000;
        goto after;
set_c:
        sprite->state = (sprite->state & 0xFFF) | 0xC000;
after:
        actor->timer--;
        actor->owner->flags4 |= 0x200;
        sub_08016238((u32)actor->owner);
    } else {
        if (sub_08016238((u32)actor->owner) != 0) {
            actor->timer = 30;
            actor->life--;
            setAnimationFrame((u32)sprite, (u32)anim, 0x17, 0);
            sub_08005E80(0x189);
            if ((s32)actor->life <= 0) actor->flags |= 1;
        }
    }
    if (actor->owner->flags14 & 1) {
        sub_08005E80(0x189);
        actor->flags |= 1;
    }
    if (actor->flags & 1) {
fail:
        sub_080C31E0((u32)eff, eff->cleanupArg);
        return;
    }
    if (sub_08013B5C((u32)sprite, (u32)actor) == 0) {
        eff->scriptTable = 0x0866D7E4;
        eff->step++;
        *(u8 *)((u8 *)eff + eff->step * 2 + 0x19) = *(u8 *)((u8 *)eff + eff->step * 2 + 0x19) + 1;
        sub_080C31E0((u32)eff, *(u32 *)((u8 *)eff->scriptTable + eff->scriptData[eff->step * 2] * 4));
        eff->step--;
        if ((eff->flags & 0x8000) != 0) {
            return;
        }
        sub_080113A8((u32)sprite, (u32)anim);
        sub_0801165C((u32)actor, 0x16C1);
    }
    {
        u8 *scrollTbl; u8 *scrollIdxPtr; u32 scrollIdx; u8 *xBase; u8 *yBase;
        scrollTbl = gCameraState; scrollIdxPtr = gMainWorkspace; scrollIdxPtr += 0x18A8;
        scrollIdx = ((u32)*scrollIdxPtr + 1) * 0x40;
        xBase = scrollTbl + 0x1278;
        sprite->screenX = actor->worldX - ((*(s32 *)(xBase + scrollIdx) + 0x8000) & 0xFFFF0000);
        scrollIdx = ((u32)*scrollIdxPtr + 1) * 0x40;
        yBase = scrollTbl + 0x127C;
        sprite->screenY = actor->worldY - ((*(s32 *)(yBase + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
