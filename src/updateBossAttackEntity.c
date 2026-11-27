/* Per-frame update of the boss attack entity: applies its sprite variant,
 * resolves contact hits and their script events, advances the current script
 * step and animation counters, then copies the saved coordinates back to the
 * boss sprite and its linked children. */
extern void *gScriptEventCallbacks;
extern void _call_via_r3(void *, void *, s32, void *);
void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 detectActorHit(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
void sub_08051CE8(void *);
void sub_08051D18(void *, void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08051CA0(void *, void *, void *);
void syncSpriteToWorldPosition(void *, void *);
s32 _call_via_r1(s32, s32);

extern u8 gBossScriptStepTable[];

/* self+0x3C: the boss's contact/hitbox component. */
struct BossHitbox {
    u16 flags;          /* 0x00 */
    u8 pad02[6];
    u32 x;              /* 0x08, 16.16 fixed point */
    u32 y;              /* 0x0C, 16.16 fixed point */
    u8 pad10[0x18];
    void *target;       /* 0x28 */
    u8 pad2C[0x9C];
    u32 homeX;          /* 0xC8 */
    u8 padCC[0x20];
    u32 homeY;          /* 0xEC */
};

/* hitbox+0x48: boss parameters and saved positions. */
struct BossData {
    u8 pad00[8];
    u8 stateFlag;       /* 0x08 */
    u8 pad09[0x4F];
    u32 spawnX;         /* 0x58 */
    u32 spawnY;         /* 0x5C */
    u8 pad60[0x20];
    u32 retX;           /* 0x80 */
    u8 pad84[0x20];
    u32 retY;           /* 0xA4 */
};

void updateBossAttackEntity(void *self) {
    void *parent;
    struct BossHitbox *hitbox;
    struct BossData *bossData;
    u8 *stepPtr;
    u8 *animState;
    u8 *animState2;
    u8 *stepTimerPtr;
    u8 stepOpcode;
    u32 stepTable;
    s32 stepHandler;
    s32 stepOffset;
    s32 contactResult;

    parent = *(void **)((u8 *)self + 0x38);
    hitbox = *(struct BossHitbox **)((u8 *)self + 0x3C);
    bossData = (struct BossData *)((u8 *)hitbox + 0x48);
    applySpritePaletteVariant(self, parent);
    hitbox->x = bossData->spawnX;
    hitbox->y = bossData->spawnY;
    contactResult = checkActorViewBounds(parent, hitbox);
    if (contactResult == 1) {
        if ((hitbox->flags & 1) == 0) {
            hitbox->x = hitbox->homeX;
            hitbox->y = hitbox->homeY;
            return;
        }
    }
    hitbox->x = bossData->retX;
    hitbox->y = bossData->retY;
    if (detectActorHit(parent, hitbox, hitbox->target) != 0) {
        spawnContactEffectOnHit(self, hitbox->target);
        animState = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        if (animState[0x1A] == 0) {
            animState[0x1B] = 0;
            { void **fnaddr = &gScriptEventCallbacks;
              _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 6, *fnaddr); }
        }
    }
    uploadPendingSpriteGraphic(self, hitbox->target);
    if ((hitbox->flags & 1) && bossData->stateFlag == 0) {
        bossData->stateFlag = 1;
        updateActorWorldPosition(self);
        sub_08051CE8(self);
        animState2 = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        animState2[0x1B] = 0;
        { void **fnaddr = &gScriptEventCallbacks;
          _call_via_r3((u8 *)self + 0x18, (u8 *)self + 0x22, 7, *fnaddr); }
    }
    sub_08051D18(parent, hitbox);
    if (updateObjectDisplayState(parent, hitbox) == 0) {
        *(u32 *)((u8 *)self + 0x14) = (u32)gBossScriptStepTable;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        stepTimerPtr = (u8 *)((u32)(*(s16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
        stepTimerPtr[0x19] = stepTimerPtr[0x19] + 1;
        stepOffset = (s32)(s16)(*(s16 *)((u8 *)self + 0x22)) * 2;
        stepPtr = (u8 *)self;
        stepPtr += 0x18;
        stepPtr += stepOffset;
        stepOpcode = *stepPtr;
        stepTable = *(u32 *)((u8 *)self + 0x14);
        stepHandler = *(s32 *)((u32)(stepOpcode * 4) + stepTable);
        _call_via_r1((s32)self, stepHandler);
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
    }
    sub_08051CA0(self, hitbox, bossData);
    syncSpriteToWorldPosition(self, parent);
}
