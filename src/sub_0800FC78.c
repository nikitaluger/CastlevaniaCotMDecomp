extern s8 gMenuState[];

/* State block reached through the entity's +0x38 sub-object pointer. */
struct SubObject {
    u8 reserved0[0x14];
    s32 counter;
    s32 coord;
    u8 reserved1[8];
    u32 dataTable;
    u8 reserved2[2];
    u8 flags;
};
struct Entity { u8 reserved[0x38]; struct SubObject *sub; };

/* Set up an entity's sub-object: raise the 0x40 flag, install the animation
 * data table, clear the counter and seed the fixed-point coordinate from the
 * game-state byte gMenuState[0xFB]. */
void sub_0800FC78(void *arg0) {
    struct SubObject *sub = ((struct Entity *)arg0)->sub;
    sub->flags |= 0x40;
    sub->dataTable = 0x086428C4;
    sub->counter = 0;
    sub->coord = (s32)gMenuState[0xFB] << 0x14;
}
