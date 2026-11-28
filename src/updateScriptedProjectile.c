/* Sub-objects of a scripted projectile: owner (collision flags), sprite (screen
   position), actor (world position/timer) and the outer object that ties them
   to a step script. */
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

extern s32 isOutsideCameraBounds(u32, u32); /* 1 when off camera */
extern s32 signedRemainder(u32, u32);          /* integer divide */
extern u32 hitTestEntities(u32);            /* hit-test actor against global list */
extern void playSound(u32);                 /* play sound effect */
extern void setAnimationFrame(u32, u32, u32, u32); /* set animation/frame control */
extern u32 updateObjectDisplayState(u32, u32);     /* advance actor's own AI */
extern void stepAnimationTrack(u32, u32);    /* request frame from frame control */
extern void advanceMotion(u32, u32);         /* advance frame control velocity */
extern void _call_via_r1(u32, u32);          /* call the handler in r1 with eff in r0 */

extern u8 gCameraState[];              /* scroll-offset table */
extern u8 gMainWorkspace[];            /* global game state */
extern u8 gProjectileScriptHandlers[]; /* Thumb handlers indexed by script step */

/* Updates one scripted projectile: sets facing from the actor's pose, culls it
   when it leaves the camera, counts down its timer (changing frame at thirds),
   handles hits/life and sound cues, runs one script step, advances its animation
   and motion, and projects its world position onto the sprite using the scroll
   table. */
void updateScriptedProjectile(struct EffectObj *eff) {
    struct EffectSprite *sprite = eff->sprite;
    struct EffectActor *actor = eff->actor;
    u8 *animTrack = (u8 *)actor + 0x34;
    s16 timer;
    s16 phase;

    actor->owner->flags1 |= 5;
    sprite->state = (sprite->state & 0xFFF) | ((actor->pose + 8) << 12);
    if (isOutsideCameraBounds(actor->worldX, actor->worldY) == 1) goto fail;
    timer = actor->timer;
    if (timer > 0) {
        phase = (s16)signedRemainder(timer, 3);
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
        hitTestEntities((u32)actor->owner);
    } else {
        if (hitTestEntities((u32)actor->owner) != 0) {
            actor->timer = 30;
            actor->life--;
            setAnimationFrame((u32)sprite, (u32)animTrack, 0x17, 0);
            playSound(0x189);
            if ((s32)actor->life <= 0) actor->flags |= 1;
        }
    }
    if (actor->owner->flags14 & 1) {
        playSound(0x189);
        actor->flags |= 1;
    }
    if (actor->flags & 1) {
fail:
        _call_via_r1((u32)eff, eff->cleanupArg);
        return;
    }
    if (updateObjectDisplayState((u32)sprite, (u32)actor) == 0) {
        eff->scriptTable = (u32)gProjectileScriptHandlers;
        eff->step++;
        *(u8 *)((u8 *)eff + eff->step * 2 + 0x19) = *(u8 *)((u8 *)eff + eff->step * 2 + 0x19) + 1;
        _call_via_r1((u32)eff, *(u32 *)((u8 *)eff->scriptTable + eff->scriptData[eff->step * 2] * 4));
        eff->step--;
        if ((eff->flags & 0x8000) != 0) {
            return;
        }
        stepAnimationTrack((u32)sprite, (u32)animTrack);
        advanceMotion((u32)actor, 0x16C1);
    }
    {
        u8 *scrollTbl; u8 *frameCounterPtr; u32 scrollRow; u8 *xBase; u8 *yBase;
        scrollTbl = gCameraState; frameCounterPtr = gMainWorkspace; frameCounterPtr += 0x18A8;
        scrollRow = ((u32)*frameCounterPtr + 1) * 0x40;
        xBase = scrollTbl + 0x1278;
        sprite->screenX = actor->worldX - ((*(s32 *)(xBase + scrollRow) + 0x8000) & 0xFFFF0000);
        scrollRow = ((u32)*frameCounterPtr + 1) * 0x40;
        yBase = scrollTbl + 0x127C;
        sprite->screenY = actor->worldY - ((*(s32 *)(yBase + scrollRow) + 0xFFFF8000) & 0xFFFF0000);
    }
}
