void stepAnimationTrack(void *, void *);
void sub_08011EE8(void *, s32, s32);
s32 sub_08013558(void *, void *, void *);
void spawnContactEffectOnHit(void *, void *);
s32 updateObjectDisplayState(void *, void *);
void applySpritePaletteVariant(void *, void *);
void sub_08013C8C(void *, void *);
void sub_08013CF4(void *, s32, s32);
s32 sub_08014114(s32, s32, s32, s32, s32, s32);
void uploadPendingSpriteGraphic(void *, void *);
void freeMotionTracker(void *);
void sub_08058978(void *, void *);
void sub_080C31E0(void *, s32);
void sub_080C31E8(void *, void *, s32, s32);

extern s32 gGameStatus[];
extern s32 sScriptStepCallbacks;

struct AnimFlags { u16 f0; };
struct Flags2 { u16 f0; u16 f2; };

/* Updates an enemy/projectile entity: culls it when out of bounds, handles
 * hit events, advances its state callback and applies camera positioning. */
/* Per-frame update for an enemy/projectile: cull it out of bounds, handle hit events, advance the script-step callback, step animation, and apply screen positioning. */ void updateEnemyEntity(void *self)
{
    void *gfxObj;
    void *anim;
    void *animData;

    gfxObj = *(void **)((u8 *)self + 0x38);
    anim = *(void **)((u8 *)self + 0x3C);
    animData = (u8 *)anim + 0x34;
    applySpritePaletteVariant(self, gfxObj);
    if (sub_08014114(*(s32 *)((u8 *)anim + 8), *(s32 *)((u8 *)anim + 0xC), -0x20, 0x20, -0x60, 0x20) == 0) {
        sub_080C31E0(self, *(s32 *)((u8 *)self + 0x24));
        return;
    }
    if (sub_08013558(gfxObj, anim, *(void **)((u8 *)anim + 0x28)) != 0) {
        *(u16 *)((u8 *)anim + 0x20) = 0x1E;
        spawnContactEffectOnHit(self, *(void **)((u8 *)anim + 0x28));
    }
    uploadPendingSpriteGraphic(self, *(void **)((u8 *)anim + 0x28));
    if (1 & *(u16 *)(*(u8 **)((u8 *)anim + 0x28) + 0x14)) {
        ((struct AnimFlags *)anim)->f0 |= 1;
    }
    if ((1 & *(u16 *)anim) && (*((u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x1A) != 2)) {
        s32 *cnt;
        struct Flags2 *p30;
        s32 *stateFn;
        sub_08013CF4(anim, *(s32 *)((u8 *)anim + 8), *(s32 *)((u8 *)anim + 0xC));
        cnt = gGameStatus;
        cnt[0xC0]++;
        if (cnt[0xC0] > 0x05F5E0FF) {
            cnt[0xC0] = 0x05F5E0FF;
        }
        if (*(void **)((u8 *)anim + 0x2C) != NULL) {
            freeMotionTracker(*(void **)((u8 *)anim + 0x2C));
            *(void **)((u8 *)anim + 0x2C) = NULL;
        }
        p30 = *(struct Flags2 **)((u8 *)anim + 0x30);
        if (p30 != NULL) {
            p30->f2 |= 2;
        }
        *((u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self) + 0x1B) = 0;
        stateFn = &sScriptStepCallbacks;
        sub_080C31E8((u8 *)self + 0x18, (u8 *)self + 0x22, 2, *stateFn);
    }
    if (updateObjectDisplayState(gfxObj, anim) == 0) {
        *(u32 *)((u8 *)self + 0x14) = 0x0866E81C;
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) + 1;
        {
            u8 *stateSlot = (u8 *)((s16)(*(u16 *)((u8 *)self + 0x22)) * 2 + (u32)self);
            stateSlot[0x19] = stateSlot[0x19] + 1;
        }
        {
            s32 idx2 = (s16)(*(u16 *)((u8 *)self + 0x22)) * 2;
            u8 *q = (u8 *)self;
            u8 val;
            q += 0x18;
            q += idx2;
            val = *q;
            sub_080C31E0(self, *(s32 *)((u32)(val * 4) + *(u32 *)((u8 *)self + 0x14)));
        }
        *(u16 *)((u8 *)self + 0x22) = *(u16 *)((u8 *)self + 0x22) - 1;
        if (*(u16 *)((u8 *)self + 2) & 0x8000)
            return;
        stepAnimationTrack(gfxObj, animData);
        sub_08011EE8(anim, 0x16C1, 0);
    }
    sub_08058978(gfxObj, anim);
    *(u16 *)(*(u8 **)((u8 *)anim + 0x28) + 0x14) = 0;
    sub_08013C8C(self, gfxObj);
}
