extern void sub_0801604C(void *);

/* When the motion object reports contact (flag bits 1-2), mark the entity's
 * work state (work+0x14) as landed, then refresh the sprite's screen position. */
void sub_08096ED8(void *entity, void *motion) {
    u8 *work = *(u8 **)((u8 *)entity + 0x3C);
    if ((6 & *(u16 *)((u8 *)motion + 2)) && (4 & *(u16 *)motion)) {
        *(u16 *)(work + 0x14) = 1;
    }
    sub_0801604C(motion);
}
