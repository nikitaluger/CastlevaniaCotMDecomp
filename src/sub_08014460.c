s32 sub_080145D8(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
struct S_02025FF0_1870
{
  u8 _0x000[0x1870];
  void *v;
};
extern struct S_02025FF0_1870 gMainWorkspace;
s32 sub_080144A4(s32 arg0);

/* Unlink the entity from its current list (owner pointer at +0x28, whose list
 * head is at owner+0x30; next pointer at +0x2C), then push it onto the front of
 * the global active list based at gMainWorkspace+0x1870. */
void sub_08014460(void *arg0)
{
  void **self = (void **) arg0;
  void *node = *((void **) (((u8 *) self[10]) + 0x30));
  while (node != 0)
  {
    void *next = *((void **) (((u8 *) node) + 0x2C));
    if (next == arg0)
    {
      *((void **) (((u8 *) node) + 0x2C)) = *((void **) (((u8 *) arg0) + 0x2C));
      break;
    }
    if (node == arg0)
    {
      *((void **) (((u8 *) (*((void **) (((u8 *) arg0) + 0x28)))) + 0x30)) = next;
      break;
    }
    node = next;
  }

  {
    void *pool = gMainWorkspace.v;
    *((void **) (((u8 *) arg0) + 0x28)) = pool;
    *((void **) (((u8 *) arg0) + 0x2C)) = *((void **) (((u8 *) pool) + 0x30));
    *((void **) (((u8 *) pool) + 0x30)) = arg0;
  }
}

extern void sub_08015974(void);
void sub_08014060(void *arg0);
