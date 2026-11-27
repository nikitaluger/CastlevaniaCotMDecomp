/* 16.16 fixed-point position and velocity, shared by object motion code. */
struct Motion {
    u8 pad[8];
    s32 x;
    s32 y;
    s32 vx;
    s32 vy;
};

extern void advanceMotion(struct Motion *motion, s32 gravity);

/* Advance the object's motion by its velocity with no gravity (used by objects
 * that drift in a straight line). */
void sub_0804A448(void *obj) {
    advanceMotion(*(struct Motion **)((u8 *)obj + 0x3C), 0);
}
