struct S_02025FF0 {
    u8 _0x000[0x1728];
    s32 playerX;   /* 16.16 world X */
    s32 playerY;   /* 16.16 world Y */
};
extern struct S_02025FF0 D_02025FF0;

/* True when the global 16.16 position (the player) lies within 32 px
 * horizontally and 48 px vertically of the entity's 16.16 point at +0x0C/+0x10. */
s32 sub_0808FBB4(void *arg0) {
    void *work = *(void **)((u8 *)arg0 + 0x3C);
    if (D_02025FF0.playerX >= *(s32 *)((u8 *)work + 0x0C) + (s32)0xFFE00000 &&
        D_02025FF0.playerX <= *(s32 *)((u8 *)work + 0x0C) + 0x200000 &&
        D_02025FF0.playerY >= *(s32 *)((u8 *)work + 0x10) + (s32)0xFFD00000 &&
        D_02025FF0.playerY <= *(s32 *)((u8 *)work + 0x10) + 0x300000) {
        return 1;
    }
    return 0;
}
