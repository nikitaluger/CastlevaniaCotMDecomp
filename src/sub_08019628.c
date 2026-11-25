/* Entity script tick: mirrors the entity's zone/facing flags into the work
 * object, optionally runs the current script command, then syncs the work
 * object's X/Y coordinates to the entity's position in the shared coord
 * table. */
extern void sub_080113A8(void *, void *);
extern void sub_0801165C(void *, s32);
extern s32 sub_08013B5C(void *, void *);
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern void sub_080C31E8(void *, void *, s32, u32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

struct FlagByte { u8 flag; };
struct FlagWord { u16 f0; };

void sub_08019628(u8 *self) {
    u8 *work;
    u8 *entity;
    u8 *anim;
    u8 *actionSlot;
    u8 *scriptSlot;
    u8 *scriptPtr;
    u8 *coordTable;
    u8 *globalBase;
    u8 *xBase;
    s32 zoneResult;
    s32 cmdOffset;
    u32 coordIdx;
    u32 xCoord;
    u32 yCoord;
    u8 cmdId;

    work = *(u8 **)(self + 0x38);
    entity = *(u8 **)(self + 0x3C);
    anim = entity + 0x34;
    zoneResult = sub_0805F9B4(*(s32 *)(entity + 8), *(s32 *)(entity + 0xC));
    if (zoneResult == 1) {
        *(u8 *)(*(u8 **)(entity + 0x28) + 1) = 0;
        ((struct FlagByte *)(work + 0x2A))->flag &= 0xBF;
    } else {
        *(u8 *)(*(u8 **)(entity + 0x28) + 1) = 1;
        ((struct FlagByte *)(work + 0x2A))->flag |= 0x40;
    }
    if (*(u16 *)(self + 0x64) & 1) {
        ((struct FlagWord *)entity)->f0 |= 1;
    }
    if (*(u16 *)entity & 1) {
        *(u8 *)(*(u8 **)(entity + 0x28) + 1) = 0;
        actionSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
        if (*(u8 *)(actionSlot + 0x1A) != 1) {
            *(u8 *)(actionSlot + 0x1B) = 0;
            {
                u32 *cbTable = (u32 *)0x08671BDC;
                sub_080C31E8(self + 0x18, self + 0x22, 1, *cbTable);
            }
        }
    }

    if (sub_08013B5C(work, entity) != 0) {
        goto syncCoords;
    }
    *(u32 *)(self + 0x14) = 0x0866D5EC;
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) + 1;
    scriptSlot = (u8 *)((u32)(*(s16 *)(self + 0x22)) * 2 + (u32)self);
    *(u8 *)(scriptSlot + 0x19) = *(u8 *)(scriptSlot + 0x19) + 1;
    cmdOffset = *(s16 *)(self + 0x22) * 2;
    scriptPtr = self;
    scriptPtr += 0x18;
    cmdId = *(u8 *)((u32)scriptPtr + (u32)cmdOffset);
    sub_080C31E0((s32)self, *(u32 *)(*(u32 *)(self + 0x14) + cmdId * 4));
    *(u16 *)(self + 0x22) = *(u16 *)(self + 0x22) - 1;
    if ((*(u16 *)(self + 2) & (0x80 << 8)) != 0) {
        return;
    }
    sub_080113A8(work, anim);
    sub_0801165C(entity, 0);

syncCoords:
    coordTable = D_02021E90;
    globalBase = D_02025FF0;
    globalBase += 0x18A8;
    coordIdx = ((u32)*globalBase + 1) * 0x40;
    xBase = coordTable + 0x1278;
    xCoord = *(u32 *)(xBase + coordIdx);
    *(u32 *)(work + 0x14) = *(u32 *)(entity + 8) - ((xCoord + (0x80 << 8)) & 0xFFFF0000);
    coordIdx = ((u32)*globalBase + 1) * 0x40;
    coordTable += 0x127C;
    yCoord = *(u32 *)(coordTable + coordIdx);
    *(u32 *)(work + 0x18) = *(u32 *)(entity + 0xC) - ((yCoord + 0xFFFF8000) & 0xFFFF0000);
}
