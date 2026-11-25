/* Advances an entity's motion state, syncs its sprite, and either keeps it
   alive or hands control back when its timer or the room state ends. */
struct S_02025FF0_7438C
{
  u8 _0[0x10];
  u32 flags10;
  u8 _14[0x14ED - 0x14];
  u8 state14ED;
  u8 _14EE[0x173A - 0x14EE];
  u8 state173A;
  u8 _173B[0x18C2 - 0x173B];
  u16 gfxFlag;
};
extern struct S_02025FF0_7438C D_02025FF0;
extern s32 sub_0806D518(void *, void *, void *);
extern void sub_0806D588(void *, void *);
extern s32 sub_08003740(void *, void *);
extern void sub_080C31E0(void *, void *);
extern void sub_0806D2F8(void *, void *);

void sub_0807438C(void *arg0) {
    void *entity;
    u8 *child;
    u8 *motion;
    u8 *sprite;
    s32 speed, rounded, step;
    child = *((u8 **)((u8 *)arg0 + 0x6C));
    motion = child + 4;
    sprite = *((u8 **)((u8 *)arg0 + 0x38));
    if (sub_0806D518(arg0, sprite, motion) == 0) {
        entity = arg0;
        speed = *(s32 *)(motion + 8);
        rounded = speed;
        if (speed < 0) rounded += 0xF;
        step = speed - (rounded >> 4);
        *(s32 *)(motion + 8) = step;
        *(s32 *)(motion + 0xC) += 0x200;
        *(s32 *)(child + 4) += step;
        *(s32 *)(motion + 4) += *(s32 *)(motion + 0xC);
        sub_0806D588(sprite, motion);
        *(u16 *)sprite = D_02025FF0.gfxFlag;
        if (sub_08003740(child + 0x20, sprite) == 0 || D_02025FF0.state173A == 0x1C || (D_02025FF0.state14ED == 0 && D_02025FF0.flags10 != 0)) {
            sub_080C31E0(entity, *((void **)((u8 *)entity + 0x24)));
        } else {
            sub_0806D2F8(entity, sprite);
        }
    }
}
