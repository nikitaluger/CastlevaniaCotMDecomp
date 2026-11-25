s32 sub_08005820(s32);
s32 sub_0800583C(s32);
s16 sub_080C389C(s32, s32);

/* Picks a new horizontal direction (0/1/2) stored in the pose block, then
 * returns a randomly scattered horizontal velocity and a rising vertical
 * velocity for that direction. */
void sub_0804C674(u8 *entity, s32 *outX, s32 *outY) {
    u8 *pose;
    s32 randRange, scatter, lift;

    pose = *(u8 **)(entity + 0x3C) + 0x48;
    *(s16 *)(pose + 6) = sub_080C389C(sub_08005820(2) + *(s16 *)(pose + 6) + 1, 3);
    randRange = 0x10000;
    scatter = sub_0800583C(randRange) * 0x10;
    lift = sub_0800583C(randRange) * 0x10 + 0xFFA80000;
    switch (*(s16 *)(pose + 6)) {
    case 0:
        *outX = scatter;
        break;
    case 1:
        *outX = -(scatter + 0x680000);
        break;
    case 2:
        *outX = scatter + 0x680000;
        break;
    }
    *outY = lift;
}
