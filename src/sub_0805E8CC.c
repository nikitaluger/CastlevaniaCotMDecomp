extern s32 sub_08015850(s32, s32, s32, s32, s32, s32);
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08016238(void *);
extern s32 sub_080C31E0(void *, s32);
extern s32 sub_080C31E8(void *, void *, s32, s32);
extern s32 sub_080113A8(void *, void *);
extern s32 sub_08011898(void *, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_0866E9AC[];
extern s32 D_08671BDC;

struct TargetState { u8 a; u8 flag; };
struct ObjFlags2 { u8 flag; };
struct AnimFlag { u16 flag; };

/* Updates a projectile/hit entity: culls it when out of range, manages target
 * hit flags and attack state, advances its callback and snaps to camera. */
void sub_0805E8CC(u8 *self) {
    u8 *gfxObj;
    u8 *anim;
    void *animData;
    u8 *stateSlot;
    u8 *pt;
    u8 *pt1;
    u8 *pb;
    u32 idx;
    u32 v1;
    u32 v2v;
    u32 stateId;
    u8 *slots;
    s32 stateOffset;
    u8 *p1;
    s32 hitFlag;
    s32 *stateFn;
    u32 tmp;

    gfxObj = *(u8 **)(self + 0x38);
    anim = *(u8 **)(self + 0x3C);
    animData = anim + 0x34;
    if (sub_08015850(*(s32 *)(anim + 8), *(s32 *)(anim + 0xC), -8, 8, -8, 8) == 0) {
        sub_080C31E0(self, *(u32 *)(self + 0x24));
        return;
    }
    if (sub_0805F9B4(*(s32 *)(anim + 8), *(s32 *)(anim + 0xC)) == 1) {
        s32 tmp2 = 0xBF & ((struct ObjFlags2 *)(gfxObj + 0x2A))->flag;
        u8 v = 0;
        ((struct ObjFlags2 *)(gfxObj + 0x2A))->flag = tmp2;
        ((struct TargetState *)(*(u8 **)(anim + 0x28)))->flag = v;
    } else {
        ((struct TargetState *)(*(u8 **)(anim + 0x28)))->flag = 4;
        ((struct ObjFlags2 *)(gfxObj + 0x2A))->flag |= 0x40;
        if (sub_08016238(*(u8 **)(anim + 0x28)) != 0) {
            ((struct AnimFlag *)anim)->flag |= 1;
        }
    }
    hitFlag = *(u16 *)anim & 1;
    slots = self + 0x18;
    if (hitFlag) {
        ((struct TargetState *)(*(u8 **)(anim + 0x28)))->flag = 0;
        stateOffset = *(s16 *)(self + 0x22) * 2;
        p1 = (u8 *)((s32)stateOffset + (s32)self);
        tmp = *(u8 *)(p1 + 0x1A);
        tmp = (tmp - 1) << 24;
        tmp = tmp >> 24;
        if (tmp > 1) {
            *(u8 *)(p1 + 0x1B) = 0;
            stateFn = &D_08671BDC;
            sub_080C31E8(slots, self + 0x22, 1, *stateFn);
        }
    }
    *(u32 *)(self + 0x14) = (u32)D_0866E9AC;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    stateSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(stateSlot + 0x19) = *(u8 *)(stateSlot + 0x19) + 1;
    stateOffset = *(s16 *)(self + 0x22) * 2;
    stateId = *(u8 *)((u32)slots + (u32)stateOffset);
    sub_080C31E0(self, *(u32 *)(*(u32 *)(self + 0x14) + stateId * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & 0x8000) != 0) return;
    sub_080113A8(gfxObj, animData);
    sub_08011898(anim, 0x16C1);
    pt = D_02021E90;
    pb = D_02025FF0;
    pb += 0x18A8;
    idx = ((u32)*pb + 1) * 0x40;
    pt1 = pt + 0x1278;
    v1 = *(u32 *)(pt1 + idx);
    *(u32 *)(gfxObj + 0x14) = *(u32 *)(anim + 8) - ((v1 + 0x8000) & 0xFFFF0000);
    idx = ((u32)*pb + 1) * 0x40;
    pt += 0x127C;
    v2v = *(u32 *)(pt + idx);
    *(u32 *)(gfxObj + 0x18) = *(u32 *)(anim + 0xC) - ((v2v + 0xFFFF8000) & 0xFFFF0000);
}
