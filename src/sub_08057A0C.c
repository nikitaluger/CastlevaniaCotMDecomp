extern u8 D_02021E90[];
extern u8 D_02025FF0[];
extern s32 sub_08057AB8();

/* Advances an entity's falling motion, converts its world position into screen
   coordinates via the room coordinate tables, and switches its update callback
   once a 30-frame timer elapses. */
void sub_08057A0C(u8 *entity) {
    void *sprite;
    u8 *data;
    s32 velY;
    s32 posX;
    u8 *coordTable;
    u8 *roomIdx;
    u8 *xTable;
    u8 *yTable;
    u32 tableIdx;
    u32 timer;

    sprite = *(void **)(entity + 0x38);
    data = *(u8 **)(entity + 0x3C);
    velY = *(s32 *)(data + 0x0C) + 0x16C1;
    *(s32 *)(data + 0x0C) = velY;
    posX = *(s32 *)(data + 0x00) + *(s32 *)(data + 0x08);
    *(s32 *)(data + 0x00) = posX;
    *(s32 *)(data + 0x04) = *(s32 *)(data + 0x04) + velY;
    coordTable = D_02021E90;
    roomIdx = D_02025FF0;
    roomIdx += 0x18A8;
    {
        tableIdx = ((u32)*roomIdx + 1) * 0x40;
        xTable = coordTable + 0x1278;
        posX -= (*(u32 *)(xTable + tableIdx) + 0x8000) & 0xFFFF0000;
        *(s32 *)((u8 *)sprite + 0x14) = posX;
        tableIdx = ((u32)*roomIdx + 1) * 0x40;
        yTable = coordTable + 0x127C;
        *(s32 *)((u8 *)sprite + 0x18) = *(s32 *)(data + 0x04) - ((*(u32 *)(yTable + tableIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
    timer = *(u8 *)(data + 0x10) + 1;
    *(u8 *)(data + 0x10) = timer;
    if ((u8)timer == 0x1E) {
        *(s16 *)(entity + 0x22) = 0;
        *(s32 *)(entity + 0x14) = (s32)sub_08057AB8;
    }
}
