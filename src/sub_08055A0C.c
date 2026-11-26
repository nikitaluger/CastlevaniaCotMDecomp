extern void *allocSpriteObject(void);
extern void allocWorkSlot(void *a, s32 b, s32 c, s32 d);
extern s32 findKindIndex(s16);
extern void initSpriteGraphics(void *a, void *b, void *c);
extern void setAnimationFrame(void *a, void *b, s32 c, s32 d);
extern void sub_080C31E0(void *a, s32 b);
extern void sub_080C31E4(void *a, void *b, s32 c);

struct S_02025FF0 {
    u8 _0[0x18A8];
    u8 byte18A8;
    u8 _1[0x18C2 - 0x18A9];
    u16 w;
};
extern struct S_02025FF0 gMainWorkspace;
extern u8 gCameraState[];
extern u32 gSpriteAnimDataTable[];
extern s16 D_080CFB64[];

/* Animation record describing the new entity's position and direction. */
struct AnimRec {
    u8 _0[0x08];
    s32 x;
    s32 y;
    s32 f10;
    s32 f14;
    u8 _18[0x1C - 0x18];
    s16 animIndex;
    u8 _1E[0x22 - 0x1E];
    s16 dir;
};

/* Creates and initialises a projectile entity: allocates its graphics and
 * animation records, sets animation attributes and direction, places it on
 * the camera grid and dispatches its initial state. */
void sub_08055A0C(u8 *self) {
    struct AnimRec *gfxObj = allocSpriteObject();
    struct AnimRec *anim;
    s32 animData;
    s32 dir;
    u32 attr;
    s32 *animFn;
    s16 frameIdx;

    if (gfxObj == NULL) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
        return;
    }
    *(u32 *)(self + 0x38) = (u32)gfxObj;
    allocWorkSlot(self, 0, 0x48, 0);
    anim = (struct AnimRec *)*(u32 *)(self + 0x3C);
    if (anim == NULL) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
        return;
    }
    animData = (s32)anim + 0x34;
    anim->animIndex = *(u16 *)(self + 0x8C);
    anim->x = (s16)*(s16 *)(self + 0x4C) << 16;
    anim->y = (s16)*(s16 *)(self + 0x54) << 16;
    dir = findKindIndex(anim->animIndex);
    anim->dir = dir;
    if ((s32)(dir << 16) < 0) {
        sub_080C31E0(self, *(s32 *)(self + 0x24));
        return;
    }

    initSpriteGraphics(gfxObj, (void *)animData, (void *)&gSpriteAnimDataTable[anim->animIndex * 3]);

    frameIdx = *(s16 *)(self + 0x7C);
    setAnimationFrame(gfxObj, (void *)animData, D_080CFB64[frameIdx], 1);

    attr = *(u16 *)gfxObj & 0xC00;
    attr |= (((s16)anim->dir << 6) + 0x200) | (((u16)anim->dir + 8) << 12);
    *(u16 *)gfxObj = attr;
    *(u16 *)gfxObj |= gMainWorkspace.w;

    *(u32 *)((u8 *)gfxObj + 0x1C) = 0x8000000B;

    anim->f10 = *(s32 *)(self + 0x5C);
    anim->f14 = *(s32 *)(self + 0x6C);

    {
        u8 *base21 = gCameraState;
        u8 *p18A8 = (u8 *)&gMainWorkspace + 0x18A8;
        u32 k = 0x1278;
        *(s32 *)((u8 *)gfxObj + 0x14) = anim->x - ((*(s32 *)(base21 + k + (((u32)(*p18A8 + 1)) << 6)) + 0x8000) & 0xFFFF0000);
        k = 0x127C;
        *(s32 *)((u8 *)gfxObj + 0x18) = anim->y - ((*(s32 *)(base21 + k + (((u32)(*p18A8 + 1)) << 6)) + (s32)0xFFFF8000) & 0xFFFF0000);
    }

    if (*(s32 *)(self + 0x5C) < 0) {
        *(u16 *)((u8 *)gfxObj + 2) |= 0x10;
    }

    *(u16 *)(self + 2) |= 0x1000;
    *((u8 *)((s16)*(s16 *)(self + 0x22) * 2 + (u32)self) + 0x19) = 0;

    animFn = (s32 *)0x08671BB0;
    sub_080C31E4(self + 0x18, self + 0x22, *animFn);
}
