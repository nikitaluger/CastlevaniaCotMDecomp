s32 sub_08005910(s32, s32);
void sub_080114DC(s32, s32, s32, s32);
void sub_08011528(s32, s32);
void sub_0801165C(s32, s32);
void sub_080146D0(s32, s32, s32);
s32 sub_0801473C(s32, s32);
void sub_080C31E4(void *, void *, s32);

struct S_02025FF0 { u8 _0[0x174C]; u32 playerX; u32 playerY; };
extern struct S_02025FF0 D_02025FF0;
extern s32 D_08671BB0;

/* Per-frame update for a homing entity: refresh its animation, toggle between
 * two animation IDs when a state flag is set, turn its heading toward the player
 * by a fixed angular step and apply it, then fire an effect when the acting
 * child's flag reaches 0x1E. */
void sub_080AE464(u8 *self) {
    s32 view, actor, anim, motion;

    view = *(s32 *)(self + 0x38);
    actor = *(s32 *)(self + 0x3C);
    anim = actor;
    anim += 0x34;
    motion = actor;
    motion += 0x48;
    sub_08011528(view, anim);
    if (*(u8 *)anim & 2) {
        if (*(s16 *)(anim + 0xE) == 0x47)
            sub_080114DC(view, anim, 0x45, 0);
        else
            sub_080114DC(view, anim, 0x47, 0);
    }
    {
        s32 angle = *(s32 *)motion;
        *(s32 *)motion = *(s32 *)motion + sub_0801473C(angle, sub_08005910(D_02025FF0.playerY - *(s32 *)(actor + 0xC), D_02025FF0.playerX - *(s32 *)(actor + 8))) * 0x140;
    }
    sub_080146D0(actor, *(s32 *)motion, *(s32 *)(motion + 4));
    sub_0801165C(actor, 0);
    {
        u8 *child = (u8 *)((s32)((s16)*(s16 *)(self + 0x22) * 2) + (s32)self);
        if (child[0x19] == 0x1E) {
            child[0x19] = 0;
            { void **effectTable = (void **)&D_08671BB0; sub_080C31E4(self + 0x18, self + 0x22, (s32)*effectTable); }
        }
    }
}
