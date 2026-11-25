/* Entity reaction: handles a check result by setting a movement byte and a target
 * flag, dispatches a message from the entity's per-state table, then aligns the
 * target to the current room's coordinate table. */
extern s32 sub_0805F9B4(s32, s32);
extern s32 sub_080C31E0(s32, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern u8 D_0866FA30[];

struct TargetFlags { u8 flag; };

void sub_08093560(u8 *entity) {
    u8 *target;
    u8 *state;
    u8 *stateTail;
    s32 check;
    u8 *entry;
    u8 *coordTable;
    u8 *coordXPtr;
    u8 *roomIndex;
    u32 tableIdx;
    u32 xAdj;
    u32 yAdj;
    u32 msgIndex;
    u8 *msgArray;
    s32 byteIdx;

    target = *(u8 **)(entity + 0x38);
    state = *(u8 **)(entity + 0x3C);
    stateTail = state + 0x34;
    check = sub_0805F9B4(*(s32 *)(state + 0x8), *(s32 *)(state + 0xC));
    if (check == 1) {
        *(u8 *)(*(u8 **)(stateTail + 4) + 1) = 0;
        ((struct TargetFlags *)(target + 0x2A))->flag &= 0xBF;
        if (*(u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity + 0x1A) == 0) {
            return;
        }
    } else {
        *(u8 *)(*(u8 **)(stateTail + 4) + 1) = 7;
        ((struct TargetFlags *)(target + 0x2A))->flag |= 0x40;
    }
    *(u32 *)(entity + 0x14) = (u32)D_0866FA30;
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) + 1;
    entry = (u8 *)((u32)(*(s16 *)(entity + 0x22)) * 2 + (u32)entity);
    *(u8 *)(entry + 0x19) = *(u8 *)(entry + 0x19) + 1;
    byteIdx = *(s16 *)(entity + 0x22) * 2;
    msgArray = entity;
    msgArray += 0x18;
    msgIndex = *(u8 *)((u32)msgArray + (u32)byteIdx);
    sub_080C31E0((s32)entity, *(u32 *)(*(u32 *)(entity + 0x14) + msgIndex * 4));
    *(u16 *)(entity + 0x22) = *(u16 *)(entity + 0x22) - 1;

    if ((*(u16 *)(entity + 2) & 0x8000) == 0) {
        coordTable = D_02021E90;
        roomIndex = D_02025FF0;
        roomIndex += 0x18A8;
        tableIdx = ((u32)*roomIndex + 1) * 0x40;
        coordXPtr = coordTable + 0x1278;
        xAdj = *(u32 *)(coordXPtr + tableIdx);
        *(u32 *)(target + 0x14) = *(u32 *)(state + 0x8) - ((xAdj + 0x8000) & 0xFFFF0000);
        tableIdx = ((u32)*roomIndex + 1) * 0x40;
        coordTable += 0x127C;
        yAdj = *(u32 *)(coordTable + tableIdx);
        *(u32 *)(target + 0x18) = *(u32 *)(state + 0xC) - ((yAdj + 0xFFFF8000) & 0xFFFF0000);
    }
}
