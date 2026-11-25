/* Spawns the sprite and sub-actor for one entity, seeds their positions and
 * direction from the entity, sets up the initial animation, then computes the
 * sprite's camera-relative screen position before registering its script. */
struct Actor {
    u8 _0[8];
    s32 posX;
    s32 posY;
    s32 velX;
    s32 velY;
    u8 _18[4];
    s16 angle;
    u8 _1E[4];
    s16 dirIndex;
};
struct Entity {
    u8 _0[2];
    u16 flags;
    u8 _4[0x22 - 4];
    s16 dirIndex;
    u8 _24[0x38 - 0x24];
    u8 *sprite;
    struct Actor *actor;
    u8 _40[0x4C - 0x40];
    s16 xPos;
    u8 _4E[6];
    s16 yPos;
    u8 _56[0x5C - 0x56];
    u32 velX;
    u8 _60[0x6C - 0x60];
    u32 velY;
    u8 _70[0x7C - 0x70];
    u16 angle;
};
struct CameraInfo { u8 _0[0x18A8]; u8 index; u8 _18A9[0x19]; u16 spriteAttrMask; };
extern struct CameraInfo D_02025FF0;
struct CoordTable { u8 _0[0x1278]; u32 camX; u32 camY; };
extern struct CoordTable D_02021E90;
extern u8 D_080CD400[];
extern u32 D_08671BB0;
extern u8 *sub_0800355C(void);
extern s32 sub_0800168C(u8 *, s32, s32, s32);
extern s32 sub_08013C2C(s32);
extern void sub_0801131C(u8 *, u8 *, s32);
extern void sub_08011368(u8 *, u8 *, s32, s32);
extern void sub_080C31E0(u8 *, s32);
extern void sub_080C31E4(u8 *, u8 *, u32);

void sub_08026A80(struct Entity *entity)
{
	u8 *sprite;
	struct Actor *actor;
	u8 *animState;
	u8 *coordBase;
	u32 *scriptData;
	sprite = sub_0800355C();
	if (sprite == NULL) goto fail;
	entity->sprite = sprite;
	sub_0800168C((u8 *)entity, 0, 0x48, 0);
	actor = entity->actor;
	if (actor == NULL) goto fail;
	animState = (u8 *)actor + 0x34;
	actor->angle = entity->angle;
	actor->posX = entity->xPos << 16;
	actor->posY = entity->yPos << 16;
	actor->dirIndex = sub_08013C2C((s32)actor->angle);
	if (actor->dirIndex >= 0) goto main;
fail:
	sub_080C31E0((u8 *)entity, *(s32 *)((u8 *)entity + 0x24));
	return;
main:
	sub_0801131C((u8 *)sprite, animState, (s32)D_080CD400 + actor->angle * 0xC);
	{
		u16 keptBits = 0xC00 & *(u16 *)sprite;
		s32 rotateAttr = (s16)(*(s16 *)((u8 *)actor + 0x22)) << 6;
		rotateAttr += 0x200;
		rotateAttr |= ((u16)(*(u16 *)((u8 *)actor + 0x22)) + 8) << 12;
		*(u16 *)sprite = (u16)(keptBits | rotateAttr);
	}
	*(u16 *)sprite = (u16)(*(u16 *)sprite | D_02025FF0.spriteAttrMask);
	*(u32 *)(sprite + 0x1C) = 0x8000000A;
	actor->velX = entity->velX;
	actor->velY = entity->velY;
	coordBase = (u8 *)&D_02021E90;
	{ u32 coordField = 0x1278; *(u32 *)(sprite + 0x14) = actor->posX - ((*(u32 *)(coordBase + coordField + ((D_02025FF0.index + 1) << 6)) + 0x8000) & 0xFFFF0000); }
	{ u32 coordField = 0x127C; *(u32 *)(sprite + 0x18) = actor->posY - ((*(u32 *)(coordBase + coordField + ((D_02025FF0.index + 1) << 6)) + 0xFFFF8000) & 0xFFFF0000); }
	sub_08011368((u8 *)sprite, animState, 0x1E, 0);
	entity->flags |= 0x1000;
	*(u8 *)((u8 *)entity + 2 * entity->dirIndex + 0x19) = 0;
	scriptData = &D_08671BB0;
	sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *scriptData);
	return;
}
