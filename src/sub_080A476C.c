struct GlobalState {
    u8 pad[0x174C];
    s32 playerX;
    s32 playerY;
};
extern struct GlobalState gMainWorkspace;
extern void stepAnimationTrack(void *, void *);
extern s32 getAngleFromDelta(s32, s32);
extern void setPolarOffset(void *, s32, s32);
extern void sub_080C31E4(void *, void *, s32);

/* Advances the actor's animation; when its current script action is 8, aims
 * the work state toward the player at fixed speed, stores a mirrored heading
 * for the child it spawns, clears the action byte and advances the script. */
void sub_080A476C(void *arg0)
{
    s32 angle;
    u8 *self = (u8 *) arg0;
    u8 *work;
    s32 heading;
    u8 *entity = self;
    void *gfx = *((void **) (self + 0x38));
    work = *((u8 **) (self + 0x3C));
    stepAnimationTrack(gfx, work + 0x34);
    if (*((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) == 8)
    {
        angle = getAngleFromDelta(gMainWorkspace.playerY - (*((s32 *) (work + 0x0C))), gMainWorkspace.playerX - (*((s32 *) (work + 0x08))));
        heading = angle;
        setPolarOffset(work, heading, 0x30000);
        heading = heading + 0x8000;
        heading = heading & 0xFFFF;
        *((s32 *) (self + 0x6C)) = 0xC000 - heading;
        *((u8 *) ((self + ((*((s16 *) (self + 0x22))) * 2)) + 0x19)) = 0;
        {
            u32 base = (u32) 0x08671BB0;
            sub_080C31E4(self + 0x18, self + 0x22, *((s32 *) base));
        }
    }
}
