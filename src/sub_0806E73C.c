s32 allocWorkSlot(void *, s32, s32, s32);
void *allocSpriteObject(void);
void sub_0806D2D0(void *);
void sub_080C31E4(void *, void *, s32);
void sub_080C31E0(void *, s32);

struct S_02025FF0 {
    u8 _0x000[0x18C2];
    u16 w;
};
extern struct S_02025FF0 gMainWorkspace;

extern u32 gMainObjTimerCallback[];

/* Entity setup: checks a spawn condition, allocates and initializes a display object,
   then runs the entity script and dispatches its handler. */
void sub_0806E73C(void *entity)
{
    u8 *obj = (u8 *)entity;
    void *sprite;

    if (allocWorkSlot(entity, 0, 0x68, 3) == 0)
    {
        sub_080C31E0(entity, *(s32 *)(obj + 0x24));
        return;
    }

    sprite = allocSpriteObject();
    if (sprite == 0)
    {
        sub_0806D2D0(entity);
        return;
    }

    *(void **)(obj + 0x38) = sprite;
    *(u32 *)((u8 *)sprite + 0x1C) = 0x80000006;
    {
        u16 globalWord = gMainWorkspace.w;
        u32 zero = 0;
        *(u16 *)sprite = globalWord;

        {
            void *flags = (u8 *)sprite + 0x2A;
            *(u8 *)flags = (u8)(*(u8 *)flags & 0xBF);
        }
        *(u32 *)((u8 *)sprite + 0x24) = 0x08472874;
        {
            s32 scriptIdx = *(s16 *)(obj + 0x22);
            *(u8 *)(obj + scriptIdx * 2 + 0x19) = (u8)zero;
        }
    }
    {
        const u32 *scriptId = (const u32 *)0x08671BB0;
        void *scriptPtr = obj + 0x18;
        sub_080C31E4(scriptPtr, obj + 0x22, *scriptId);
        *(u8 *)(obj + *(s16 *)(obj + 0x22) * 2 + 0x19) += 1;
        scriptPtr = (u8 *)scriptPtr + *(s16 *)(obj + 0x22) * 2;
        sub_080C31E0(entity, *(u32 *)(*(u32 *)(obj + 0x14) + *(u8 *)scriptPtr * 4));
    }
}
