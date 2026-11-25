extern u32 D_03002690;
extern u32 D_03002694;
extern u32 D_03002700;
extern u32 D_03002924;
extern u32 D_03002E34;

/* Store the sprite/display buffer bases and their 0x80-byte sizes, supplied by
 * the display-engine initializer, into the shared engine-state globals. */
void sub_0800368C(s32 bufA, s32 sizeA, s32 bufB, s32 bufC, s32 sizeB)
{
    D_03002E34 = bufA;
    D_03002694 = sizeA;
    D_03002700 = bufB;
    D_03002924 = bufC;
    D_03002690 = sizeB;
}
