extern void setObjectAnimationFrame(void *, void *, s32, s32);
extern void *spawnBudgetedEffect(s32, s32);
extern void sub_080C31E4(void *, void *, s32);
extern s32 gMainObjTimerCallbacks;
struct S_02025FF0_F { u8 _0[0x1870]; u32 v; };
extern struct S_02025FF0_F gMainWorkspace;
struct FlagByte { u8 pad; u8 flag; };

/* When the entity's active action is 0xC, pose its sprite, spawn a type-0xE3
 * object, copy state fields into it, clear the action and refresh its graphics. */
void sub_080342E8(void *entity) {
    u8 *self = (u8 *)entity;
    u8 *gfx = *(u8 **)(self + 0x38);
    u8 *data = *(u8 **)(self + 0x3C);
    u8 *anim = data + 0x34;
    u8 *ctrl = data + 0x48;
    void *newObj;
    u32 *lit;
    s32 flag;

    ((struct FlagByte *)(*(u8 **)(ctrl + 0xC)))->flag = 1;
    if (*(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) == 0xC) {
        if (1 & *(u8 *)(ctrl + 0x10)) {
            setObjectAnimationFrame(gfx, anim, 0x38, 0);
        } else {
            setObjectAnimationFrame(gfx, anim, 0x1F, 0);
        }
        ((struct FlagByte *)(*(u8 **)(ctrl + 0xC)))->flag = 0;
        newObj = spawnBudgetedEffect((s32)gMainWorkspace.v, 0xE3);
        if (newObj != NULL) {
            u8 *obj = (u8 *)newObj;
            *(s32 *)(obj + 0x4C) = *(s32 *)(data + 8);
            *(s32 *)(obj + 0x5C) = *(s32 *)(data + 0xC);
            flag = 1 & *(u8 *)(ctrl + 0x10);
            *(u8 *)(obj + 0x6C) = flag;
            if ((u16)(0x10 & *(u16 *)(gfx + 2)) == 0) {
                *(u8 *)(obj + 0x70) = 0;
            } else {
                *(u8 *)(obj + 0x70) = 1;
            }
        }
        *(u8 *)(self + *(s16 *)(self + 0x22) * 2 + 0x19) = 0;
        lit = &gMainObjTimerCallbacks;
        sub_080C31E4(self + 0x18, self + 0x22, *lit);
    }
}
