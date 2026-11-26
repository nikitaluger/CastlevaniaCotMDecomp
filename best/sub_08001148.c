struct S_1148_Node
{
  void *field0;
  s16 field4;
  s16 field6;
};
typedef struct S_1148_Node S_1148_Node;

s32 sub_08001148(s32 arg0)
{
  s32 key;
  S_1148_Node *new_var;
  s16 neg_one;
  s32 key_copy;
  u8 *D;
  u8 *table;
  u16 new_var3;
  u8 *new_var2;
  S_1148_Node *cur;
  S_1148_Node *prev;
  u16 v6;
  void *result;
  u16 idx;
  u16 temp;
  int temp2;
  key = arg0;
  D = (u8 *) 0x02021E90;
  neg_one = -1;
  temp = *((u16 *) (D + 0x0C));
  idx = temp;
  temp2 = idx * 4;
  table = D + 0x118;
  cur = *((S_1148_Node **) (table + temp2));
  if (cur == NULL)
  {
    return 0;
  }
  prev = cur;
  v6 = *((u16 *) (((u8 *) cur) + 6));
  new_var2 = (u8 *) cur;
  if ((*((s16 *) (new_var2 + 6))) == (-1))
  {
    return 0;
  }
  key_copy = neg_one;
  D += 0x18;
  while (1)
  {
    if ((*((s16 *) (((u8 *) cur) + 4))) == key)
    {
      new_var = prev;
      if (prev != cur)
      {
        *((u16 *) (((u8 *) new_var) + 6)) = v6;
      }
      else
      {
        s16 s6 = *((s16 *) (((u8 *) cur) + 6));
        *((void **) (table + (idx * 4))) = (s6 == (-1)) ? (NULL) : (D + (s6 * 8));
      }
      result = cur->field0;
      cur->field0 = NULL;
      return (s32) result;
    }
    prev = cur;
    { u8 *__fence_D; do { __fence_D = D; } while (0); cur = (S_1148_Node *) (__fence_D + ((*((s16 *) (((u8 *) cur) + 6))) * 8)); }
    temp2 = (u16)(*((u16 *) (((u8 *) cur) + 6)));
    v6 = temp2;
    if ((*((s16 *) (((u8 *) cur) + 6))) == key_copy)
    {
      return 0;
    }
  }
}
