#include "out.h"


undefined main;
undefined1 completed.0;
pointer __dso_handle;
undefined1[13] obf_bytes;
undefined8 stdin;

int _init(EVP_PKEY_CTX *ctx)

{
  int iVar1;
  
  iVar1 = __gmon_start__();
  return iVar1;
}



void FUN_00101020(void)

{
  (*(code *)(undefined *)0x0)();
  return;
}



void __cxa_finalize(void)

{
  __cxa_finalize();
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

void free(void *__ptr)

{
  free(__ptr);
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int putchar(int __c)

{
  int iVar1;
  
  iVar1 = putchar(__c);
  return iVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

char * strcpy(char *__dest,char *__src)

{
  char *pcVar1;
  
  pcVar1 = strcpy(__dest,__src);
  return pcVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int puts(char *__s)

{
  int iVar1;
  
  iVar1 = puts(__s);
  return iVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int fclose(FILE *__stream)

{
  int iVar1;
  
  iVar1 = fclose(__stream);
  return iVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

size_t strlen(char *__s)

{
  size_t sVar1;
  
  sVar1 = strlen(__s);
  return sVar1;
}



void __stack_chk_fail(void)

{
                    // WARNING: Subroutine does not return
  __stack_chk_fail();
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int printf(char *__format,...)

{
  int iVar1;
  
  iVar1 = printf(__format);
  return iVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

void __assert_fail(char *__assertion,char *__file,uint __line,char *__function)

{
                    // WARNING: Subroutine does not return
  __assert_fail(__assertion,__file,__line,__function);
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

char * fgets(char *__s,int __n,FILE *__stream)

{
  char *pcVar1;
  
  pcVar1 = fgets(__s,__n,__stream);
  return pcVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

void * calloc(size_t __nmemb,size_t __size)

{
  void *pvVar1;
  
  pvVar1 = calloc(__nmemb,__size);
  return pvVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

FILE * fopen(char *__filename,char *__modes)

{
  FILE *pFVar1;
  
  pFVar1 = fopen(__filename,__modes);
  return pFVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

void perror(char *__s)

{
  perror(__s);
  return;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

ulong strtoul(char *__nptr,char **__endptr,int __base)

{
  ulong uVar1;
  
  uVar1 = strtoul(__nptr,__endptr,__base);
  return uVar1;
}



// WARNING: Unknown calling convention -- yet parameter storage is locked

int atoi(char *__nptr)

{
  int iVar1;
  
  iVar1 = atoi(__nptr);
  return iVar1;
}



void processEntry _start(undefined8 param_1,undefined8 param_2)

{
  undefined1 auStack_8 [8];
  
  __libc_start_main(main,param_2,&stack0x00000008,0,0,param_1,auStack_8);
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



// WARNING: Removing unreachable block (ram,0x00101263)
// WARNING: Removing unreachable block (ram,0x0010126f)

void deregister_tm_clones(void)

{
  return;
}



// WARNING: Removing unreachable block (ram,0x001012a4)
// WARNING: Removing unreachable block (ram,0x001012b0)

void register_tm_clones(void)

{
  return;
}



void __do_global_dtors_aux(void)

{
  if (completed_0 != '\0') {
    return;
  }
  __cxa_finalize(__dso_handle);
  deregister_tm_clones();
  completed_0 = 1;
  return;
}



void frame_dummy(void)

{
  register_tm_clones();
  return;
}



long hash(byte *param_1)

{
  byte *local_20;
  long local_10;
  
  local_10 = 0x1505;
  local_20 = param_1;
  while( true ) {
    if (*local_20 == 0) break;
    local_10 = (long)(int)(uint)*local_20 + local_10 * 0x21;
    local_20 = local_20 + 1;
  }
  return local_10;
}



void make_secret(long param_1)

{
  long local_10;
  
  for (local_10 = 0; obf_bytes[local_10] != '\0'; local_10 = local_10 + 1) {
    *(byte *)(local_10 + param_1) = obf_bytes[local_10] ^ 0xaa;
  }
  *(undefined1 *)(param_1 + 0xc) = 0;
  hash(param_1);
  return;
}



undefined8 main(void)

{
  uint uVar1;
  char *pcVar2;
  undefined8 uVar3;
  long in_FS_OFFSET;
  int local_128;
  char *local_120;
  ulong local_118;
  char *local_110;
  size_t local_108;
  ulong local_100;
  ulong local_f8;
  FILE *local_f0;
  undefined1 local_e5 [13];
  char local_d8 [31];
  char acStack_b9 [65];
  char local_78 [104];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_110 = calloc(0x5a,1);
  for (local_118 = 0; local_118 < 0xd; local_118 = local_118 + 1) {
    local_110[local_118 + 0x3c] = obf_bytes[local_118] ^ 0xaa;
  }
  puts("Please set a password for your account:");
  pcVar2 = fgets(acStack_b9 + 1,0x32,stdin);
  if (pcVar2 != (char *)0x0) {
    strcpy(local_110,acStack_b9 + 1);
    puts("How many bytes in length is your password?");
    pcVar2 = fgets(local_d8,0x14,stdin);
    if (pcVar2 != (char *)0x0) {
      uVar1 = atoi(local_d8);
      printf("You entered: %d\n",(ulong)uVar1);
      puts("Your successfully stored password:");
      for (local_128 = 0; (local_128 <= (int)uVar1 && (local_128 < 0x5a)); local_128 = local_128 + 1
          ) {
        printf("%d ",(ulong)(uint)(int)local_110[local_128]);
      }
      putchar(10);
    }
  }
  puts("Enter your hash to access your account!");
  pcVar2 = fgets(acStack_b9 + 1,0x32,stdin);
  if (pcVar2 != (char *)0x0) {
    local_108 = strlen(acStack_b9 + 1);
    if ((local_108 != 0) && (acStack_b9[local_108] == '\n')) {
      acStack_b9[local_108] = '\0';
    }
    local_100 = strtoul(acStack_b9 + 1,&local_120,10);
    if (local_120 == acStack_b9 + 1) {
      printf("No digits were found");
                    // WARNING: Subroutine does not return
      __assert_fail("1 == 0","heartbleed.c",0x45,"main");
    }
    local_f8 = make_secret(local_e5);
    if (local_f8 == local_100) {
      local_f0 = fopen("flag.txt","r");
      if (local_f0 == (FILE *)0x0) {
        perror("Could not open flag.txt");
        uVar3 = 1;
        goto LAB_0010173e;
      }
      pcVar2 = fgets(local_78,100,local_f0);
      if (pcVar2 == (char *)0x0) {
        puts("Failed to read the flag");
      }
      else {
        printf("%s",local_78);
      }
      fclose(local_f0);
    }
  }
  free(local_110);
  uVar3 = 0;
LAB_0010173e:
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    // WARNING: Subroutine does not return
    __stack_chk_fail();
  }
  return uVar3;
}



void _fini(void)

{
  return;
}




