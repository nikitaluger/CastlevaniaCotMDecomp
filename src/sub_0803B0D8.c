s32 sub_08014938(s32 x);   /* sign(playerX - x): 1 if player is right of x */

struct Obj {
    u8 pad_0x00[0x08];
    s32 x;                  /* +0x08: world X position */
};

/* Set *speed to +magnitude or -magnitude so the object moves horizontally
 * toward the player. */
void sub_0803B0D8(struct Obj *obj, s32 *speed, s32 magnitude) {
    if (sub_08014938(obj->x) < 0) {
        *speed = 0 - magnitude;
        return;
    }
    *speed = magnitude;
}
