s32 sub_0806D518(void *, void *, void *); /* global pause/transition check */
void sub_0806D588(void *, void *);         /* sync sprite to world position */
void sub_0806D2F8(void *, void *);         /* despawn once off the room bounds */
void sub_0806D2F8(void *, void *);

/* Spinning-projectile update: unless a global pause/transition is pending, spin
 * the sprite, add gravity to its vertical speed, integrate the 16.16 position,
 * sync it to the screen and despawn it if it leaves the room. */
void sub_0806EC0C(void *arg0) {
    void *temp_r4;
    void *temp_r5;
    void *temp_r6;

    temp_r6 = *(void **)((u8 *)arg0 + 0x6C);
    temp_r4 = (u8 *)temp_r6 + 4;
    temp_r5 = *(void **)((u8 *)arg0 + 0x38);
    if (sub_0806D518(arg0, temp_r5, temp_r4) == 0) {
        *(u16 *)((u8 *)temp_r5 + 8) = (u16)(*(u16 *)((u8 *)temp_r5 + 8) + 0x1800);
        *(s32 *)((u8 *)temp_r4 + 0xC) = (s32)(*(s32 *)((u8 *)temp_r4 + 0xC) + 0x4000);
        *(s32 *)((u8 *)temp_r6 + 4) = (s32)(*(s32 *)((u8 *)temp_r6 + 4) + *(s32 *)((u8 *)temp_r4 + 8));
        *(s32 *)((u8 *)temp_r4 + 4) = (s32)(*(s32 *)((u8 *)temp_r4 + 4) + *(s32 *)((u8 *)temp_r4 + 0xC));
        sub_0806D588(temp_r5, temp_r4);
        sub_0806D2F8(arg0, temp_r5);
    }
}
