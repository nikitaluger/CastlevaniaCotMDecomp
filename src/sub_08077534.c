extern void sub_08003A6C(void *, s32, const void *);
extern void sub_080C31E0(void *, void *);
extern void sub_080C31E4(void *, void *, void *);
extern void sub_0808449C(void);
extern void *gMainObjTimerCallback;
extern const void D_084D425C;
extern const void D_084D4434;
extern const void D_084D4478;
extern u8 gMainWorkspace[];

/*
 * Initialises an entity's animation state and callback, copies the global
 * position into it, selects an animation table by the global state, then fires
 * the entity's effect and next callback.
 */
void sub_08077534(void *arg0)
{
    u8 *subObj;
    u8 *obj;
    u8 *ctx;
    u8 *paramPtr;
    u32 *globalState;
    s16 index;
    u32 posIndex;

    subObj = *((u8 **) (((u8 *) arg0) + 0x6C));
    obj = subObj + 4;
    ctx = *((u8 **) (((u8 *) arg0) + 0x38));
    *((u32 *) (obj + 0x2C)) = 0;
    *((u32 *) (obj + 0x30)) = 0;
    *((u32 *) (obj + 0x34)) = 0;
    *((u32 *) (obj + 0x38)) = 0;
    *((u32 *) (obj + 0x3C)) = 0;
    *((u32 *) (obj + 0x18)) = *((u32 *) (((u8 *) arg0) + 0x24));
    *((void **) (((u8 *) arg0) + 0x24)) = sub_0808449C;

    globalState = (u32 *)gMainWorkspace;
    posIndex = 0x1728 / 4;
    *((u32 *)(subObj + 4)) = globalState[posIndex];
    posIndex += 1;
    *((u32 *)(obj + 4)) = globalState[posIndex];

    *((const void **) (ctx + 0x24)) = &D_084D425C;
    switch (*((u8 *) (gMainWorkspace + 0x173A)))
    {
        case 0x0D:
            sub_08003A6C(subObj + 0x20, 0, &D_084D4434);
            break;
        case 0x0E:
            sub_08003A6C(subObj + 0x20, 0, &D_084D4478);
            break;
    }

    index = *((s16 *) (((u8 *) arg0) + 0x22));
    ((u8 *) arg0)[(index * 2) + 0x19] = 0;
    {
        void **effectIds = &gMainObjTimerCallback;
        paramPtr = ((u8 *) arg0) + 0x18;
        sub_080C31E4(paramPtr, ((u8 *) arg0) + 0x22, *effectIds);
    }
    index = *((s16 *) (((u8 *) arg0) + 0x22));
    ((u8 *) arg0)[(index * 2) + 0x19]++;
    index = *((s16 *) (((u8 *) arg0) + 0x22));
    paramPtr = paramPtr + (index * 2);
    sub_080C31E0(arg0, *((void **) ((*((u32 *) (((u8 *) arg0) + 0x14))) + (paramPtr[0] * 4))));
}
