extern u32 D_02025FF0[];
extern void sub_08003740(void *, void *);
extern void sub_0806D330(void *, void *);

/* Advance the object's vertical motion (position plus bob offset) on both the
 * motion state and its sprite, latch the current screen word at
 * 0x02025FF0+0x18C2 into the sprite, then refresh and dispatch it. */
void sub_0808B270(void *entity) {
    void *self;
    void *stateHeader;
    void *motion;
    void *sprite;
    s32 dy;
    u32 screenWordOffset;
    u16 screenWord;

    self = entity;
    stateHeader = *(void **)((u8 *)entity + 0x6C);
    motion = (u8 *)stateHeader + 4;
    sprite = *(void **)((u8 *)entity + 0x38);
    dy = *(s32 *)((u8 *)motion + 0x0C) + *(s32 *)((u8 *)motion + 0x34);
    *(s32 *)((u8 *)motion + 0x0C) = dy;
    *(s32 *)((u8 *)sprite + 0x18) = *(s32 *)((u8 *)sprite + 0x18) + dy;
    screenWordOffset = 0x18C2;
    screenWord = *(u16 *)((u8 *)D_02025FF0 + screenWordOffset);
    *(u16 *)((u8 *)sprite + 0) = screenWord;
    sub_08003740((u8 *)stateHeader + 0x20, sprite);
    sub_0806D330(self, sprite);
}
