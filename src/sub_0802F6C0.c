extern void *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern s32 _call_via_r1(u8 *, s32);
extern void _call_via_r2(u8 *, u8 *, s32);

/* Effect component stored in the main object at +0x3C. */
struct OwnerEffect {
    u8 _0[8];
    s32 worldX;      /* 16.16 fixed point */
    s32 worldY;
    s32 spawnX;
    s32 spawnY;
    u8 _18[4];
    s16 kind;
    u8 _1E[4];
    s16 slot;
};
struct MainObj {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22-4];
    s16 index;
    u8 _24[0x38-0x24];
    u8 *object;
    struct OwnerEffect *effect;
    u8 _40[0x4C-0x40];
    s16 posX;
    u8 _4E[6];
    s16 posY;
    u8 _56[0x5C-0x56];
    u32 spawnX;
    u8 _60[0x6C-0x60];
    u32 spawnY;
};
struct GameState { u8 _0[0x18A8]; u8 scrollIndex; u8 _18A9[0x19]; u16 flags; };
extern struct GameState D_02025FF0;
struct ScrollTable { u8 _0[0x1278]; u32 scrollX; u32 scrollY; };
extern struct ScrollTable D_02021E90;
extern u8 D_080CD400[];
extern u32 D_08671BB0;

/* Spawn a simple effect from a main object: allocate a free object, fill its
   OwnerEffect (kind 0x69) and place it at the object's world coordinates. */
void sub_0802F6C0(struct MainObj *arg0) {
    u8 *effect;
    struct OwnerEffect *owner;
    u8 *anim;
    s32 slot;
    u32 flags;
    u8 *scrollTable;
    s32 *audioCmd;

    effect = sub_0800355C();
    owner = NULL;
    anim = NULL;
    slot = 0;
    if (((effect == NULL) || ((arg0->object = effect, sub_0800168C((u8 *)arg0, 0, 0x48, 0), owner = arg0->effect, owner == NULL))) ||
        ((anim = (u8 *)owner + 0x34, owner->kind = 0x69, owner->worldX = arg0->posX << 16, owner->worldY = arg0->posY << 16,
          slot = sub_08013C2C(0x69), owner->slot = slot, ((s32)(slot << 16) < 0)))) {
        _call_via_r1((u8 *)arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    sub_0801131C(effect, anim, (s32)D_080CD400 + owner->kind * 0xC);
    sub_08011368(effect, anim, 0x0C, 0);
    flags = (*(u16 *)effect & 0xC00) |
          (((*(s16 *)((u8 *)owner + 0x22) << 6) + 0x200) |
           ((*(u16 *)((u8 *)owner + 0x22) + 8) << 12));
    *(u16 *)effect = flags;
    *(u16 *)effect = flags | D_02025FF0.flags;
    *(u32 *)(effect + 0x1C) = 0x8000000A;
    scrollTable = (u8 *)&D_02021E90;
    { u32 offset = 0x1278; *(u32 *)(effect + 0x14) = owner->worldX - ((*(u32 *)(scrollTable + offset + ((D_02025FF0.scrollIndex + 1) << 6)) + 0x8000) & 0xFFFF0000); }
    { u32 offset = 0x127C; *(u32 *)(effect + 0x18) = owner->worldY - ((*(u32 *)(scrollTable + offset + ((D_02025FF0.scrollIndex + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
    arg0->flags |= 0x1000;
    *(u8 *)((u8 *)arg0 + 2 * arg0->index + 0x19) = 0;
    audioCmd = (s32 *)0x08671BB0;
    do { _call_via_r2((u8 *)arg0 + 0x18, (u8 *)arg0 + 0x22, *audioCmd); } while (0);
}
