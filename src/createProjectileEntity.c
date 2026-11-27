extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *a, s32 b, s32 c, s32 d);
extern s32 findKindIndex(s16);
extern void initSpriteGraphics(void *a, void *b, void *c);
extern void setAnimationFrame(void *a, void *b, s32 c, s32 d);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);

extern struct FixedEffectWorkspace gMainWorkspace;
extern u8 gCameraState[];
extern u32 gSpriteAnimDataTable[];
extern s16 gProjectileFrameTable[];
extern u32 gScriptStepCallbackTable[];

/* Work state allocated at the projectile entity's +0x3C. */
struct ProjectileWork {
    u8 _0[0x08];
    s32 x;         /* 0x08: fixed-point world X */
    s32 y;         /* 0x0C: fixed-point world Y */
    s32 targetX;   /* 0x10 */
    s32 targetY;   /* 0x14 */
    u8 _18[0x1C - 0x18];
    s16 animIndex; /* 0x1C: animation kind index */
    u8 _1E[0x22 - 0x1E];
    s16 dir;       /* 0x22: facing direction / animation slot */
};

/* Creates and initialises a projectile entity: allocates its sprite and work state, builds animation and OAM attributes from the script's parameters, places it in camera-relative screen space, then dispatches its initial script step; a failed allocation runs the saved cleanup callback. */
void createProjectileEntity(u8 *projectile) {
    struct ProjectileWork *sprite = allocSpriteObject();
    struct ProjectileWork *work;
    s32 animTrack;
    s32 slot;
    u32 attrs;
    s32 *scriptCallbacks;
    s16 frameIndex;

    if (sprite == NULL) {
        sub_080C31E0(projectile, *(s32 *)(projectile + 0x24));
        return;
    }
    *(u32 *)(projectile + 0x38) = (u32)sprite;
    allocWorkSlot(projectile, 0, 0x48, 0);
    work = (struct ProjectileWork *)*(u32 *)(projectile + 0x3C);
    if (work == NULL) {
        sub_080C31E0(projectile, *(s32 *)(projectile + 0x24));
        return;
    }
    animTrack = (s32)work + 0x34;
    work->animIndex = *(u16 *)(projectile + 0x8C);
    work->x = (s16)*(s16 *)(projectile + 0x4C) << 16;
    work->y = (s16)*(s16 *)(projectile + 0x54) << 16;
    slot = findKindIndex(work->animIndex);
    work->dir = slot;
    if ((s32)(slot << 16) < 0) {
        sub_080C31E0(projectile, *(s32 *)(projectile + 0x24));
        return;
    }

    initSpriteGraphics(sprite, (void *)animTrack, (void *)&gSpriteAnimDataTable[work->animIndex * 3]);

    frameIndex = *(s16 *)(projectile + 0x7C);
    setAnimationFrame(sprite, (void *)animTrack, gProjectileFrameTable[frameIndex], 1);

    attrs = *(u16 *)sprite & 0xC00;
    attrs |= (((s16)work->dir << 6) + 0x200) | (((u16)work->dir + 8) << 12);
    *(u16 *)sprite = attrs;
    *(u16 *)sprite |= gMainWorkspace.gfxFlags;

    *(u32 *)((u8 *)sprite + 0x1C) = 0x8000000B;

    work->targetX = *(s32 *)(projectile + 0x5C);
    work->targetY = *(s32 *)(projectile + 0x6C);

    {
        u8 *camera = gCameraState;
        u8 *frameCounter = (u8 *)&gMainWorkspace + 0x18A8;
        u32 offset = 0x1278;
        *(s32 *)((u8 *)sprite + 0x14) = work->x - ((*(s32 *)(camera + offset + (((u32)(*frameCounter + 1)) << 6)) + 0x8000) & 0xFFFF0000);
        offset = 0x127C;
        *(s32 *)((u8 *)sprite + 0x18) = work->y - ((*(s32 *)(camera + offset + (((u32)(*frameCounter + 1)) << 6)) + (s32)0xFFFF8000) & 0xFFFF0000);
    }

    if (*(s32 *)(projectile + 0x5C) < 0) {
        *(u16 *)((u8 *)sprite + 2) |= 0x10;
    }

    *(u16 *)(projectile + 2) |= 0x1000;
    *((u8 *)((s16)*(s16 *)(projectile + 0x22) * 2 + (u32)projectile) + 0x19) = 0;

    scriptCallbacks = (s32 *)gScriptStepCallbackTable;
    sub_080C31E4(projectile + 0x18, projectile + 0x22, *scriptCallbacks);
}
