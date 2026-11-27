/* Per-frame AI update for the boss whose state script table is at 0x0866E5E4.
 * Applies contact/hit effects, runs the current state script and advances the
 * per-state animation flags, then syncs the hitbox component back to the boss. */
extern void *sScriptStepCallbacks;
extern void _call_via_r3(void *, void *, s32, void *);
void applySpritePaletteVariant(void *, void *);
s32 checkActorViewBounds(void *, void *);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
void uploadPendingSpriteGraphic(void *, void *);
void updateActorWorldPosition(void *);
void sub_08051CE8(void *);
void sub_08051D18(void *, void *);
s32 updateObjectDisplayState(void *, void *);
void sub_08051CA0(void *, void *, void *);
void sub_08013C8C(void *, void *);
s32 sub_080C31E0(s32, s32);

#define BOSS_STATE_TABLE 0x0866E5E4

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

void sub_08050AE0(void *arg0) {
    void *parent;
    struct BossHitbox *hitbox;
    struct BossData *bossData;
    u8 *scriptPtr;
    u8 *animStatePtr;
    u8 *animStatePtr2;
    u8 *counterPtr;
    u8 scriptIndex;
    u32 scriptTable;
    s32 scriptFunc;
    s32 stateOffset;
    s32 contactResult;

    parent = *(void **)((u8 *)arg0 + 0x38);
    hitbox = *(struct BossHitbox **)((u8 *)arg0 + 0x3C);
    bossData = (struct BossData *)((u8 *)hitbox + 0x48);
    applySpritePaletteVariant(arg0, parent);
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
    if (sub_08013558(parent, hitbox, hitbox->target) != 0) {
        spawnContactEffectOnHit(arg0, hitbox->target);
        animStatePtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        if (animStatePtr[0x1A] == 0) {
            animStatePtr[0x1B] = 0;
            { void **fnaddr = &sScriptStepCallbacks;
              _call_via_r3((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 6, *fnaddr); }
        }
    }
    uploadPendingSpriteGraphic(arg0, hitbox->target);
    if ((hitbox->flags & 1) && bossData->stateFlag == 0) {
        bossData->stateFlag = 1;
        updateActorWorldPosition(arg0);
        sub_08051CE8(arg0);
        animStatePtr2 = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        animStatePtr2[0x1B] = 0;
        { void **fnaddr = &sScriptStepCallbacks;
          _call_via_r3((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, 7, *fnaddr); }
    }
    sub_08051D18(parent, hitbox);
    if (updateObjectDisplayState(parent, hitbox) == 0) {
        *(u32 *)((u8 *)arg0 + 0x14) = BOSS_STATE_TABLE;
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
        counterPtr = (u8 *)((u32)(*(s16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
        counterPtr[0x19] = counterPtr[0x19] + 1;
        stateOffset = (s32)(s16)(*(s16 *)((u8 *)arg0 + 0x22)) * 2;
        scriptPtr = (u8 *)arg0;
        scriptPtr += 0x18;
        scriptPtr += stateOffset;
        scriptIndex = *scriptPtr;
        scriptTable = *(u32 *)((u8 *)arg0 + 0x14);
        scriptFunc = *(s32 *)((u32)(scriptIndex * 4) + scriptTable);
        sub_080C31E0((s32)arg0, scriptFunc);
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
    }
    sub_08051CA0(arg0, hitbox, bossData);
    sub_08013C8C(arg0, parent);
}
