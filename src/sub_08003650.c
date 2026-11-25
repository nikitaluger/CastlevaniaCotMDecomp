extern s32 D_030026B0;
extern s32 D_03002698;
extern s32 D_030026AC;
extern s16 D_03002914;
extern s16 D_0300269C;
extern s16 D_030026A8;

/* Set the six display/effect engine state values: three word-sized state words
 * and three halfword-sized state halfwords, truncating the last two. */
void sub_08003650(s32 wordState0, s32 wordState1, s32 wordState2, s16 halfState0, s32 halfState1, s32 halfState2) {
    D_030026B0 = wordState0;
    D_03002698 = wordState1;
    D_030026AC = wordState2;
    D_03002914 = halfState0;
    D_0300269C = (s16)halfState1;
    D_030026A8 = (s16)halfState2;
}
