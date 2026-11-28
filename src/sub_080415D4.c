extern s32 setAnimationFrame(s32, s32, s32, s32);
extern void copyPoseAttrs(s32, s32);
extern u8 gEnemyActionParams[];

/* Readable aliases for the game's symbols (preprocessor-only, no effect on code). */
#define StartAnimation     setAnimationFrame
#define ApplyMotionParams  copyPoseAttrs
#define sActionParams      gEnemyActionParams

/* Enemy action indices; each selects an animation and one 8-byte table entry. */
enum {
    ACTION_IDLE,       /* stand / land                         */
    ACTION_LUNGE,      /* chase / lunge toward the player      */
    ACTION_ATTACK,     /* attack / finish action               */
    ACTION_KNOCKBACK   /* knocked back                         */
};

/*
 * Put an enemy into one of its actions: start that action's animation on the
 * animator (index plus a flag word), then copy the action's four s16 motion
 * parameters out of sActionParams into the work object's sprite state.
 */
void sub_080415D4(u8 action, s32 owner, void *work, s32 animator) {
    switch (action) {
    case ACTION_IDLE:
        StartAnimation(owner, animator, 0, 1);
        break;
    case ACTION_LUNGE:
        StartAnimation(owner, animator, 3, 1);
        break;
    case ACTION_ATTACK:
        StartAnimation(owner, animator, 0xA, 0);
        break;
    case ACTION_KNOCKBACK:
        StartAnimation(owner, animator, 0xE, 0);
        break;
    }
    ApplyMotionParams(*(s32 *)((u8 *)work + 0x28), (s32)(sActionParams + action * 8));
}
