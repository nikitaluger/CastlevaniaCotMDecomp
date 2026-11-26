/* Update an entity's sprite view: set or clear a flag bit depending on whether
 * the entity's position is inside the camera-bounded rectangle, run the view's
 * movement callback, then subtract the camera scroll from its x/y velocity. */
s32 sub_0805F9B4(s32, s32);
void sub_080113A8(void *, void *);
struct S_02025FF0_18A8
{
    u8 _0[0x18A8];
    u8 camIndex;
};
extern struct S_02025FF0_18A8 gMainWorkspace;
extern u8 gCameraState[];
void sub_08097170(void *entity)
{
    void *view;
    int flagBits;
    void *body;
    void *motionData;
    u8 *flag;

    view = *(void **)((u8 *)entity + 0x38);
    body = *(void **)((u8 *)entity + 0x3C);
    motionData = (u8 *)body + 0x14;
    if (sub_0805F9B4(*(s32 *)((u8 *)body + 0x0C), *(s32 *)((u8 *)body + 0x10)) == 1)
    {
        flag = (u8 *)view + 0x2A;
        *flag = 0xBF & (*flag);
    }
    else
    {
        flag = (u8 *)view + 0x2A;
        flagBits = 0x40 | (*flag);
        *flag = flagBits;
    }
    sub_080113A8(view, motionData);
    {
        u8 *scrollTable = gCameraState;
        u32 camOffset = (gMainWorkspace.camIndex + 1) * 0x40;
        u8 *xScroll = scrollTable + 0x1278;
        *(s32 *)((u8 *)view + 0x14) = (*(s32 *)((u8 *)body + 0x0C)) - ((*(s32 *)(xScroll + camOffset) + 0x8000) & 0xFFFF0000);
    }
    {
        u8 *scrollTable = gCameraState;
        u32 camOffset = (gMainWorkspace.camIndex + 1) * 0x40;
        u8 *yScroll = scrollTable + 0x127C;
        *(s32 *)((u8 *)view + 0x18) = (*(s32 *)((u8 *)body + 0x10)) - ((*(s32 *)(yScroll + camOffset) + 0xFFFF8000) & 0xFFFF0000);
    }
}
