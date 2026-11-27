void moveEntityWithCollision(void *, s32);
void sub_080C31E0(void *, s32);

/* While the current script command is above 0x0B, raise the actor's y position
 * by 3 (capped at 0x100) and advance its path movement; when the movement
 * flags become set, dispatch the object's stored callback. */
void sub_080A4AB4(void *arg0) {
    u8 *self = (u8 *)arg0;
    void *actor = *(void **)(self + 0x38);
    void *path = *(void **)(self + 0x3C);
    s32 slot = *(s16 *)(self + 0x22);
    u8 command = *(u8 *)(self + slot * 2 + 0x19);
    if (command > 0x0B) {
        int newY = *(u16 *)((u8 *)actor + 0x06) + 3;
        *(u16 *)((u8 *)actor + 0x06) = newY;
        if ((s16)newY > 0x100) {
            *(u16 *)((u8 *)actor + 0x06) = 0x100;
        }
        moveEntityWithCollision(path, *(s32 *)(self + 0x6C));
        if (*(u16 *)((u8 *)path + 0x02) != 0) {
            sub_080C31E0(self, *(s32 *)(self + 0x24));
        }
    }
}
