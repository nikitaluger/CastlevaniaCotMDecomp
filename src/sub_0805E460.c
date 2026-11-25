/* Per-frame update for one actor: despawn when it leaves a tight bounds box,
 * update visibility and sub-state flags, run a scripted action from D_0866E99C,
 * then refresh the sprite's camera-relative screen position. */
extern s32 sub_08015850(s32, s32, s32, s32, s32, s32);
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08016238(void *);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_08011898(void *, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_0866E99C[];
extern s32 D_08671BDC;

struct ActorBits { u8 unk0; u8 flags; };
struct SpriteFlags { u8 flags; };
struct AnimState { u16 flags; };

void sub_0805E460(u8 *entity) {
    u8 *anim;
    u8 *actor;
    u8 *frameEntry;
    u8 *coordBase;
    u8 *coordXField;
    u8 *camIndexPtr;
    u32 coordIndex;
    u32 camX;
    u32 camY;
    u32 patternValue;
    u8 *patternBase;
    s32 frameOffset;
    u8 *child;
    s32 stateBit;
    s32 *actionData;

    anim = *(u8 **)(entity + 0x38);
    actor = *(u8 **)(entity + 0x3C);
    if (sub_08015850(*(s32 *)(actor + 8), *(s32 *)(actor + 0xC), -8, 8, -8, 8) == 0) {
        sub_080C31E0(entity, *(u32 *)(entity + 0x24));
        return;
    }
    if (sub_0805F9B4(*(s32 *)(actor + 8), *(s32 *)(actor + 0xC)) == 1) {
        s32 keptFlags = 0xBF & ((struct SpriteFlags *)(anim + 0x2A))->flags;
        u8 zeroFlag = 0;
        ((struct SpriteFlags *)(anim + 0x2A))->flags = keptFlags;
        ((struct ActorBits *)(*(u8 **)(actor + 0x28)))->flags = zeroFlag;
    } else {
        ((struct ActorBits *)(*(u8 **)(actor + 0x28)))->flags = 4;
        ((struct SpriteFlags *)(anim + 0x2A))->flags |= 0x40;
        if (sub_08016238(*(u8 **)(actor + 0x28)) != 0) {
            ((struct AnimState *)actor)->flags |= 1;
        }
    }
    stateBit = *(u16 *)actor & 1;
    patternBase = entity + 0x18;
    if (stateBit) {
        ((struct ActorBits *)(*(u8 **)(actor + 0x28)))->flags = 0;
        frameOffset = *(s16 *)(entity + 0x22) * 2;
        child = (u8 *)((s32)frameOffset + (s32)entity);
        if (*(u8 *)(child + 0x1A) != 1) {
            *(u8 *)(child + 0x1B) = 0;
            actionData = &D_08671BDC;
            sub_080C31E8(patternBase, entity + 0x22, 1, *actionData);
        }
    }
    *(u32 *)(entity + 0x14) = (u32)D_0866E99C;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    frameEntry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(frameEntry + 0x19) = *(u8 *)(frameEntry + 0x19) + 1;
    frameOffset = *(s16 *)(entity + 0x22) * 2;
    patternValue = *(u8 *)((u32)patternBase + (u32)frameOffset);
    sub_080C31E0(entity, *(u32 *)(*(u32 *)(entity + 0x14) + patternValue * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;
    if ((*(u16 *)(entity + 2) & 0x8000) != 0) return;
    sub_08011898(actor, 0x16C1);
    coordBase = D_02021E90;
    camIndexPtr = D_02025FF0;
    camIndexPtr += 0x18A8;
    coordIndex = ((u32)*camIndexPtr + 1) * 0x40;
    coordXField = coordBase + 0x1278;
    camX = *(u32 *)(coordXField + coordIndex);
    *(u32 *)(anim + 0x14) = *(u32 *)(actor + 8) - ((camX + 0x8000) & 0xFFFF0000);
    coordIndex = ((u32)*camIndexPtr + 1) * 0x40;
    coordBase += 0x127C;
    camY = *(u32 *)(coordBase + coordIndex);
    *(u32 *)(anim + 0x18) = *(u32 *)(actor + 0xC) - ((camY + 0xFFFF8000) & 0xFFFF0000);
}
