/* Entity AI tick: advances an oscillating (velocity, duration) pattern and a
 * rotating angle to move the entity, then dispatches a message when it leaves
 * range or when global state flags request it. */
struct MovePattern { u32 velocity; u32 duration; };
extern struct MovePattern D_080E00E8[];

struct GameState_70C78 {
    u8 _0x000[0x10];
    u32 field10;
    u8 _0x014[0x14ED - 0x14];
    u8 field14ED;
    u8 _0x14EE[0x14FC - 0x14EE];
    u32 field14FC;
    u8 _0x1500[0x173A - 0x1500];
    u8 field173A;
};
extern struct GameState_70C78 gMainWorkspace;

s32 applyAreaSpecialBehavior(void *, void *, void *);
void setDirectionVector(void *, u8);
void stepDelayTimer(void *, void *);
void sub_0806D588(void *, void *);
void sub_080719EC(void *, void *, void *);
void sub_080C31E0(void *, s32);

void sub_08070C78(void *entity)
{
    void *state;
    void *work;
    void *other;
    s32 timer;
    s32 step;

    state = *(void **)((s8 *)entity + 0x6C);
    work = (s8 *)state + 4;
    other = *(void **)((s8 *)entity + 0x38);

    if (applyAreaSpecialBehavior(entity, other, work) > 0) goto Lcall1;
    timer = *(s32 *)((s8 *)work + 0x5C) - 1;
    *(s32 *)((s8 *)work + 0x5C) = timer;
    if (timer == 0) {
        timer = *(s32 *)((s8 *)work + 0x60) + 1;
        *(s32 *)((s8 *)work + 0x60) = timer;
        *(s32 *)((s8 *)work + 0x5C) = (s32)D_080E00E8[timer].duration;
    }
    *(s32 *)((s8 *)work + 0x58) += (s32)D_080E00E8[*(s32 *)((s8 *)work + 0x60)].velocity;
    if (*(s32 *)((s8 *)work + 0x58) > 0x01000000) goto Lcall1;
    setDirectionVector(work, (u8)*(s32 *)((s8 *)work + 0x54));
    step = *(s32 *)((s8 *)work + 0x08) * (*(s32 *)((s8 *)work + 0x58) >> 12);
    if (step < 0) step += 15;
    *(s32 *)((s8 *)state + 4) = *(s32 *)((s8 *)work + 0x4C) + (step >> 4);
    step = *(s32 *)((s8 *)work + 0x0C) * (*(s32 *)((s8 *)work + 0x58) >> 12);
    if (step < 0) step += 15;
    *(s32 *)((s8 *)work + 4) = *(s32 *)((s8 *)work + 0x50) + (step >> 4);
    *(s32 *)((s8 *)work + 0x54) = (*(s32 *)((s8 *)work + 0x54) + 4) & 0xFF;
    stepDelayTimer((s8 *)state + 0x30, other);
    sub_0806D588(other, work);
    sub_080719EC(entity, work, work);
    if (gMainWorkspace.field14FC == 0) goto Lcheck;
Lcall1:
    sub_080C31E0(entity, *(s32 *)((s8 *)entity + 0x24));
    return;
Lcheck:
    if (gMainWorkspace.field173A == 0x1C) goto Lcall2;
    if (gMainWorkspace.field14ED != 0) return;
    if (gMainWorkspace.field10 == 0) return;
Lcall2:
    sub_080C31E0(entity, *(s32 *)((s8 *)entity + 0x24));
}
