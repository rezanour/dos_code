#include "W_SYS.H"

static long XMSControl;

typedef struct memblock_s
{
  unsigned short xms_handle;
  unsigned long start;
  unsigned long end;
  unsigned long current;
  struct memblock_s* nextblock;
} memblock;

static memblock* pHead;

void W_initmem()
{
  unsigned char err = 0;
  unsigned short version = 0;
  unsigned short extmem = 0;

  asm{
    // ensure himem.sys loaded
    mov ax, 0x4300
    int 0x2F
    mov err, al
  }

  if (err != 0x80)
  {
    printf("No XMS\n");
    exit(1);
  }

  asm{
    // get entry point for services
    mov ax, 0x4310
    int 0x2F
    mov word ptr [XMSControl], bx
    mov word ptr [XMSControl+2], es

    // get XMS driver version number
    mov ah, 0x00
    call [XMSControl]
    mov version, ax
  }

  printf("XMS version: %x\n", version);

  asm{
    // query free extended memory
    mov ah, 0x08
    call [XMSControl]
    mov extmem, dx
    mov err, bl
  }

  if (err == 0)
  {
    printf("Free extended memory: %dKB\n", extmem);
  }
  else
  {
    printf("Error reading memory info: %x\n", err);
    exit(2);
  }
}

void* W_allocmem(unsigned short size)
{
  unsigned short handle=0;
  unsigned char err = 0;
  unsigned long addr = 0;
  unsigned short num_kb_chunks =
           ((size + sizeof(memblock)) / 1000) + 1;
  memblock* p = pHead;
  memblock* pnew = 0;

  // try and find space for this allocation
  while (p)
  {
    if (p->end - p->current >= size)
    {
      void* out = (void*)p->current;
      p->current += size;
      return out;
    }

    if (p->nextblock)
    {
      p = p->nextblock;
    }
    else
    {
      break;
    }
 }

  // if we reached here, we need a new block & p should be pointing
  // to last entry (if any)

  asm{
    mov ah, 0x09
    mov dx, num_kb_chunks // in kb
    call [XMSControl]
    mov err, bl
    mov handle, dx
  }

  if (err != 0)
  {
    printf("Error allocating: %x\n", err);
    exit(3);
  }

  asm{
    // lock it
    mov ah, 0x0C
    mov dx, handle
    call [XMSControl]
    mov word ptr [addr], bx
    mov word ptr [addr+2], dx
    mov err, bl
  }

  if (err != 0)
  {
    printf("Error locking: %x\n", err);
    exit(4);
  }

  pnew = (memblock*)addr;
  pnew->xms_handle = handle;
  pnew->start = (unsigned long)(pnew) + sizeof(memblock);
  pnew->end = (unsigned long)(pnew) + (num_kb_chunks * 1024);
  pnew->current = pnew->start + size;
  pnew->nextblock = 0;

  if (p)
  {
    p->nextblock = pnew;
  }
  else
  {
    pHead = pnew;
  }

  return (void*)p->start;
}

void W_printstats()
{
  memblock* p = pHead;

  printf("\n* Memory Stats *\n");
  while (p)
  {
    printf(" Block: %u bytes,", p->end - (unsigned long)p);
    printf(" %u used,", p->current - p->start);
    printf(" %u free,", p->end - p->current);
    printf(" %u start,", p->start);
    printf(" %u current,", p->current);
    printf(" %u end\n", p->end);

    p = p->nextblock;
  }
  printf("\n* Done *\n");
}

void W_freeall()
{
  memblock* p = pHead;
  unsigned char err = 0;
  unsigned short handle;

  while (p)
  {
    handle = p->xms_handle;
    asm{
      // unlock it
      mov ah, 0x0D
      mov dx, handle
      call [XMSControl]
      mov err, bl
    }

    if (err != 0)
    {
      printf("Error unlocking mem: %d\n", err);
    }

    asm {
      // free block
      mov ah, 0x0A
      mov dx, handle
      call [XMSControl]
      mov err, bl
    }

    if (err != 0)
    {
      printf("Error freeing mem: %d\n", err);
    }

    p = p->nextblock;
  }

  pHead = 0;
}

