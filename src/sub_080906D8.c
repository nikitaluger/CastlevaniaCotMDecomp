extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_08014900(s32);
extern s32 sub_0801491C(s32);
extern void *sub_08015914(void);
extern void sub_08015974(void *);
extern s32 sub_080C31E0(s32, s32);
extern void sub_0801165C(void *, s32);
extern void sub_080113A8(void *, void *);
extern u8 gCameraState[];
extern u8 gMainWorkspace[];

struct S2A { u8 flag; };
struct SP { u8 _0[4]; void *volatile p; };

/* Updates a weapon entity's attached sprite/effect object: pick its state from the
 * entity's position check, create or free the sprite object, dispatch the current state
 * handler from 0x0866F96C, then copy the entity's animation state and camera-corrected
 * world position back to the parent. */
void sub_080906D8(u8 *self) {
    u8 *parent;
    u8 *obj;
    void *objSub;
    u8 *objState;
    s32 posResult;
    u8 *slot;
    u8 *coordTable;
    u8 *coordTableX;
    u8 *basePtr;
    u32 slotIndex;
    u32 camX;
    u32 camY;
    u8 *slotArea;
    s32 stateIdx;
    u8 stateByte;
    void *oldSprite;
    u32 highMask;
    u8 *spriteField;

    parent = *(u8 **)(self + 0x38);
    obj = *(u8 **)(self + 0x3C);
    objSub = (void *)(obj + 0x34);
    objState = obj + 0x48;

    posResult = sub_0805F9B4(*(s32 *)(obj + 0x08), *(s32 *)(obj + 0x0C));
    if (posResult == 1) {
        *(u8 *)((u8 *)((struct SP *)objState)->p + 1) = 0;
        ((struct S2A *)(parent + 0x2A))->flag &= 0xBF;
    } else {
        *(u8 *)((u8 *)((struct SP *)objState)->p + 1) = 7;
        ((struct S2A *)(parent + 0x2A))->flag |= 0x40;
    }

    if (sub_08014900(*(s32 *)(obj + 0x08)) <= 0x00400000 &&
        sub_0801491C(*(s32 *)(obj + 0x0C)) <= 0x00400000) {
        oldSprite = ((struct SP *)objState)->p;
        if (oldSprite == 0) {
            void *sprite = sub_08015914();
            ((struct SP *)objState)->p = sprite;
            if (sprite == 0) {
                sub_080C31E0((s32)self, *(s32 *)(self + 0x24));
                return;
            }
            {
                u8 *q = (u8 *)sprite;
                q[1] = 7;
                *(u16 *)((u8 *)((struct SP *)objState)->p + 2) = (u16)(u32)oldSprite;
                *(u16 *)((u8 *)((struct SP *)objState)->p + 8) = 0x10;
                *(u16 *)((u8 *)((struct SP *)objState)->p + 10) = 0x10;
                *(u8 **)((u8 *)((struct SP *)objState)->p + 12) = self;
            }
        }
    } else {
        void *sprite = ((struct SP *)objState)->p;
        if (sprite != 0) {
            sub_08015974(sprite);
            ((struct SP *)objState)->p = 0;
        }
    }

    *(u32 *)(self + 0x14) = (u32)0x0866F96C;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    slot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(slot + 0x19) = *(u8 *)(slot + 0x19) + 1;
    stateIdx = *(s16 *)(self + 0x22) * 2;
    slotArea = self;
    slotArea += 0x18;
    stateByte = *(u8 *)((u32)slotArea + (u32)stateIdx);
    sub_080C31E0((s32)self, *(u32 *)(*(u32 *)(self + 0x14) + stateByte * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;

    if ((*(u16 *)(self + 2) & 0x8000) == 0) {
        sub_0801165C(obj, 0);
        if (*(s16 *)(objState + 0x10) == 1) {
            sub_080113A8(parent, objSub);
        }
        *(u16 *)((u8 *)((struct SP *)objState)->p + 4) = *(u16 *)(obj + 0x0A);
        spriteField = (u8 *)((struct SP *)objState)->p + 6;
        highMask = 0xFFFF0000;
        *(u16 *)spriteField = *(u16 *)(obj + 0x0E) + 1;
        coordTable = gCameraState;
        basePtr = gMainWorkspace;
        basePtr += 0x18A8;
        slotIndex = ((u32)*basePtr + 1) * 0x40;
        coordTableX = coordTable + 0x1278;
        camX = *(u32 *)(coordTableX + slotIndex);
        *(u32 *)(parent + 0x14) = *(u32 *)(obj + 0x08) - ((camX + 0x8000) & highMask);
        slotIndex = ((u32)*basePtr + 1) * 0x40;
        coordTable += 0x127C;
        camY = *(u32 *)(coordTable + slotIndex);
        *(u32 *)(parent + 0x18) = *(u32 *)(obj + 0x0C) - ((camY + 0xFFFF8000) & highMask);
    }
}
