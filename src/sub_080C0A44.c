s32 sub_080C0758(void *);
void sub_080BFDB4(void *);   /* per-frame music player update */

struct MusicPlayerInfo;

/* Sound engine work area; ident 0x68736D53 marks it as running. */
struct SoundEngine {
    u32 ident;                          /* 0x00 */
    u8 _4[0x1C];
    void (*mplayMain)(void *);          /* 0x20 */
    struct MusicPlayerInfo *mplayInfo;  /* 0x24 */
};

/* A music player, linked into the sound engine's active player. */
struct MusicPlayerInfo {
    u8 _0[4];
    u32 status;                            /* 0x04, 0x80000000 while active */
    u8 trackCount;                         /* 0x08 */
    u8 _9[0x23];
    s8 *tracks;                            /* 0x2C */
    void *tone;                            /* 0x30 */
    u32 ident;                             /* 0x34 */
    void (*prevMplayMain)(void *);         /* 0x38 */
    struct MusicPlayerInfo *prevMplayInfo; /* 0x3C */
};

/* Open up to 16 tracks on a music player and link it into the sound engine:
 * initialise the player, clear the first byte of each 0x50-byte track, save
 * the engine's current player link and install this player together with the
 * per-frame update callback. */
void sub_080C0A44(struct MusicPlayerInfo *arg0, s8 *arg1, int arg2)
{
    void (*temp_r0)(void *);
    s32 temp_r1;
    s8 *var_r6;
    u8 var_r4;
    struct SoundEngine *temp_r5;

    var_r6 = arg1;
    var_r4 = arg2;
    if (var_r4 != 0)
    {
        if (((u32) var_r4) > 0x10U)
        {
            var_r4 = 0x10;
        }
        temp_r5 = *(struct SoundEngine **) 0x03007FF0;
        temp_r1 = temp_r5->ident;
        if (temp_r1 == 0x68736D53)
        {
            temp_r5->ident = temp_r1 + 1;
            sub_080C0758(arg0);
            arg0->tracks = var_r6;
            arg0->trackCount = var_r4;
            arg0->status = 0x80000000;
            if (var_r4 != 0)
            {
                do
                {
                    *var_r6 = 0;
                    var_r4 -= 1;
                    var_r6 += 0x50;
                }
                while (var_r4 != 0);
            }
            temp_r0 = temp_r5->mplayMain;
            if (temp_r0 != NULL)
            {
                arg0->prevMplayMain = temp_r0;
                arg0->prevMplayInfo = temp_r5->mplayInfo;
                temp_r5->mplayMain = NULL;
            }
            temp_r5->mplayInfo = arg0;
            temp_r5->mplayMain = sub_080BFDB4;
            temp_r5->ident = 0x68736D53;
            arg0->ident = 0x68736D53;
        }
    }
}
