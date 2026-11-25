/* m4a sound engine: "Smsh" magic guards a reentrancy-sensitive update. */
#define SOUND_MAGIC 0x68736D53
#define TRACK_ACTIVE 0x80

struct MusicPlayerTrack {
    u8 flags;
    u8 pad1[0x12];
    u8 vol;
    u8 pad14[0x3C];
};

struct MusicPlayerInfo {
    u8 pad0[8];
    u8 trackCount;
    u8 pad9[0x23];
    struct MusicPlayerTrack *tracks;
    u8 pad30[4];
    u32 magic;
};

/* Sets the volume (arg2 >> 2) of every active track selected by the bit mask. */
void sub_080C129C(struct MusicPlayerInfo *arg0, u16 arg1, u16 arg2)
{
  if (arg0->magic == SOUND_MAGIC)
  {
    s32 count;
    struct MusicPlayerTrack *p;
    u32 mask;
    arg0->magic++;
    count = arg0->trackCount;
    p = arg0->tracks;
    mask = 1;
    if (count > 0)
    {
      u16 val;
      do
      {
        if (arg1 & mask)
        {
          if (p->flags & TRACK_ACTIVE)
          {
            p->vol = arg2 >> 2;
            p->flags |= 3;
          }
        }
        count--;
        p++;
        mask <<= 1;
      }
      while (count > 0);
    }
    arg0->magic = SOUND_MAGIC;
  }
}
