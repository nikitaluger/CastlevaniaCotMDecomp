s32 sub_0806D518(void *, void *, void *);
s32 sub_0806D588(void *, void *);
s32 sub_080719EC(void *, void *, void *);
s32 sub_0806D330(void *, void *);

/* Advance a thrown projectile: apply gravity (capped at terminal fall speed),
 * integrate its x/y motion, push the result into the sprite view and despawn
 * it once it has left the level. */
void sub_0806F358(void *self) {
    void *motion = *(void **)((u8 *)self + 0x6C);
    void *pos = (u8 *)motion + 4;
    void *view = *(void **)((u8 *)self + 0x38);
    s32 vy;
    if (sub_0806D518(self, view, pos) == 0) {
        sub_080719EC(self, pos, pos);
        vy = *(s32 *)((u8 *)pos + 0xC) + 0x4000;
        *(s32 *)((u8 *)pos + 0xC) = vy;
        if (vy > 0x80000) *(s32 *)((u8 *)pos + 0xC) = 0x80000;
        *(s32 *)((u8 *)motion + 4) = *(s32 *)((u8 *)motion + 4) + *(s32 *)((u8 *)pos + 8);
        *(s32 *)((u8 *)pos + 4) = *(s32 *)((u8 *)pos + 4) + *(s32 *)((u8 *)pos + 0xC);
        *(u16 *)((u8 *)view + 8) = (u16)(*(u16 *)((u8 *)view + 8) - 0xC00);
        sub_0806D588(view, pos);
        sub_0806D330(self, view);
    }
}
