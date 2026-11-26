extern u32 gMainWorkspace[];
extern u32 gTilemapPages[];

/* Set the sprite's camera-relative Y (sprite+0x18): the entity's world Y
 * (state+8, high 16 bits) minus the rounded Y of the alternate camera record
 * selected by the inverted flag at gMainWorkspace+0x18A8. */
void sub_0808AB50(void *self) {
    void *state = *(void **)((u8 *)self + 0x6C);
    void *sprite = *(void **)((u8 *)self + 0x38);
    u32 flagOff = 0x18A8;
    u32 recordOff = (1U ^ *(u8 *)((u8 *)gMainWorkspace + flagOff)) << 6;
    u32 record = (u32)gTilemapPages + recordOff;
    u32 worldY = *(u32 *)((u8 *)state + 0x08) & 0xFFFF0000;
    u32 cameraY = (*(u32 *)((u8 *)record + 0x1C) + 0x8000) & 0xFFFF0000;
    *(u32 *)((u8 *)sprite + 0x18) = worldY - cameraY;
}
