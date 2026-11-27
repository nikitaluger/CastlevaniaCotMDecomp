extern void sub_080C31E0(void *a, void *b);
extern void sub_080C31E4(void *a, void *b, s32 c);
extern void unlinkAndFreeObject(void *a);
extern void sub_08071FA0(void);
extern void sub_08072018(void *a);
extern void sub_08006120(void);

struct S_02025FF0 {
    u8 pad0[0x14EC];
    u8 b14EC;
    u8 pad1[0x1780 - 0x14ED];
    u32 arr1780[0x30];
    u8 pad2[0x1844 - (0x1780 + 0x30*4)];
    u32 f1844;
    u32 f1848;
    u8 pad3[0x18C5 - 0x184C];
    u8 b18C5;
    u8 b18C6;
};
extern struct S_02025FF0 gMainWorkspace;

struct S_02025368 {
    u8 pad0[0x2FC];
    s16 s2FC;
    u8 pad1[2];
    u32 u300;
};
extern struct S_02025368 gGameStatus;

extern s32 gMainObjTimerCallbacks[];
extern u32 gLevelExpTable[];

/* Set the global 0x08000000 flag, clear the entity's current script-step
 * counter, and advance its command script via the shared advance callback. */
void sub_08071E9C(void *entity)
{
    gMainWorkspace.f1844 |= 0x08000000;
    *(u8 *)((u8 *)entity + (*(s16 *)((u8 *)entity + 0x22)) * 2 + 0x19) = 0;
    {
        s32 *advanceCb = gMainObjTimerCallbacks;
        sub_080C31E4((u8 *)entity + 0x18, (u8 *)entity + 0x22, *advanceCb);
    }
}
