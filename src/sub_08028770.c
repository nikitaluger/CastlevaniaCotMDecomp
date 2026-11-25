s32 sub_0805F9B4(s32, s32);
s32 sub_08013B5C(void *, void *);
void sub_080113A8(void *, void *);
void sub_0801165C(void *, s32);
void sub_080C31E0(void *, s32);
extern u8 D_02021E90[];
extern u8 D_02025FF0[];

/* Contact flags hung off the actor at +0x28. */
struct ScriptContact { u8 unused; u8 flag; };

/* One update tick for a scripted entity: cull the actor when it leaves the
 * view, dispatch the current script step, then sync the sprite to the actor. */
void sub_08028770(void *arg0)
{
    void *sprite;
    void *actor;
    void *anim;
    struct ScriptContact *contact;
    u8 *unusedPtr;
    sprite = *(void **)((u8 *)arg0 + 0x38);
    actor = *(void **)((u8 *)arg0 + 0x3C);
    anim = (u8 *)actor + 0x34;
    contact = *(struct ScriptContact **)((u8 *)actor + 0x28);
    contact->flag |= 1;
    if (sub_0805F9B4(*(s32 *)((u8 *)actor + 8), *(s32 *)((u8 *)actor + 0xC)) == 1) {
        sub_080C31E0(arg0, *(s32 *)((u8 *)arg0 + 0x24));
        return;
    }
    if (sub_08013B5C(sprite, actor) == 0) {
        /* 0x0866DA24 is the table of script-step callbacks. */
        *(u32 *)((u8 *)arg0 + 0x14) = 0x0866DA24;
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) + 1;
        {
            u8 *step = (u8 *)((s16)(*(u16 *)((u8 *)arg0 + 0x22)) * 2 + (u32)arg0);
            step[0x19] = step[0x19] + 1;
        }
        {
            s32 stepOffset = (s16)(*(u16 *)((u8 *)arg0 + 0x22)) * 2;
            u8 *stepBase = (u8 *)arg0;
            u8 stepId;
            stepBase += 0x18;
            stepBase += stepOffset;
            stepId = *stepBase;
            sub_080C31E0(arg0, *(s32 *)(*(u32 *)((u8 *)arg0 + 0x14) + (u32)(stepId * 4)));
        }
        *(u16 *)((u8 *)arg0 + 0x22) = *(u16 *)((u8 *)arg0 + 0x22) - 1;
        if (*(u16 *)((u8 *)arg0 + 2) & 0x8000)
            return;
        sub_080113A8(sprite, anim);
        sub_0801165C(actor, 0);
    }
    {
        u8 *scrollBase = D_02021E90;
        u8 *sceneBase = D_02025FF0;
        u32 scrollIdx;
        u8 *baseX;
        u8 *baseY;
        sceneBase += 0x18A8;
        scrollIdx = ((u32)*sceneBase + 1) * 0x40;
        baseX = scrollBase + 0x1278;
        *(u32 *)((u8 *)sprite + 0x14) = *(u32 *)((u8 *)actor + 8) - ((*(s32 *)(baseX + scrollIdx) + 0x8000) & 0xFFFF0000);
        scrollIdx = ((u32)*sceneBase + 1) * 0x40;
        baseY = scrollBase + 0x127C;
        *(u32 *)((u8 *)sprite + 0x18) = *(u32 *)((u8 *)actor + 0xC) - ((*(s32 *)(baseY + scrollIdx) + 0xFFFF8000) & 0xFFFF0000);
    }
}
