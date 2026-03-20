

# Challenge: Secure Password Database

**Category:** Reverse Engineering
**Difficulty:** Medium

**Challenge Description:**
I made a new password authentication program that even shows you the password you entered saved in the database! Isn't that cool? system.out
Additional details will be available after launching your challenge instance.

# Solution

Running the `file` command on `system.out` made it clear that it''s an executable file.

```bash
$ file system.out
system.out: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=63224e5a94fa31cb071c82105d8a70ffc806ac0b, for GNU/Linux 3.2.0, not stripped
```

Since I didn't have Ghidra on my system, i used [https://dogbolt.org/](https://dogbolt.org/) instead

The decompiled file can be found at, [Decompiled C file](decompiled.c)

I analyzed the important parts of thee decompiled file line by line for myself as a beginner and for anyone that wants to learn at the end of the file. :)

---

## 1. Challenge Overview

The challenge provides a C binary that allows a user to set a password and "confirm" it by printing the stored bytes back to them. To get the flag, the user must provide a specific hash that matches a secret string hidden in the program's memory.

---

## 2. Vulnerability Identification

The vulnerability lies in how the program handles the password confirmation loop.

First:

```
Please set a password for your account:
```

The length of buffer is `0x32`

How many bytes in length is your password?
Length of buffer is `0x14`

But:

```c
for (local_128 = 0; (local_128 <= (int)uVar1 && (local_128 < 0x5a)); local_128++) {
    printf("%d ",(ulong)(uint)(int)local_110[local_128]);
}
```

`local_110` has buffer length of `0x5a`. But the `length_128` or `uVar1` storing the length of the password is provided by the user. If length of password provided by user is greater than the length of the password, the print statement will print the memory from `local_110`.

We can see the `obf_bytes[]`, or our secret, is XORed with `0xaa` and then XORed again with `0xaa` giving us the original secret and then put into `local_110` at offset `0x3c`. And then it is run through a simple hash:

```
hash = 0x1505*0x21 + obf_bytes[i]  for every byte i of obf_bytes.
```

Please set a password for your account:

A

How many bytes in length is your password?

90

You entered : A
Your successfully stored password: 105 85 98 104 56 49 33 106 42 104 110 33

Enter the hash to access your account!

A Python script using `ctypes.c_uint64` was used to mimic the C-style overflow:

```python
import ctypes
data = [105, 85, 98, 104, 56, 49, 33, 106, 42, 104, 110, 33]
h = ctypes.c_uint64(5381)
for b in data:
    h.value = (h.value * 33) + b
print(h.value) # Result: 15237662580160011234
```

Putting the result in gave us the flag:
`picoCTF{d0nt...}`

---

## Analysis of decompiled.c

```c
local_10 = *(long *)(in_FS_OFFSET + 0x28);
```

* `in_FS_OFFSET` : pointing to the thread-local storage(TLS). TLS is a special kind of variable that is global in scope but each thread gets its own copy.
* `*(long *)` : casts the address pointer to long and dereferences it. So, `local_10` is a 64-bit value now.

---

```c
local_110 = calloc(0x5a,1);
```

* allocates `number[0x5a]*size[1]` bytes of memory and initializes all bytes to 0.
* `local_110` contains pointer to said allocated memory or null if allocation fails.

---

```c
for (local_118 = 0; local_118 < 0xd; local_118 = local_118 + 1) {
    local_110[local_118 + 0x3c] = obf_bytes[local_118] ^ 0xaa;
}
```

* Simple for loop that runs 0xd times.
* 0x3c means its starting at offset 0x3c.
* `obf_bytes[]` probably contains flag.
* `obf_bytes[local_118] ^ 0xaa` means flag is being bitwise XORed with 0xaa = 10101010.

---

```c
puts("Please set a password for your account:");
```

* print statement

---

```c
pcVar2 = fgets(acStack_b9 + 1,0x32,stdin);
```

* Receives input. `acStack_b9+1` is the pointer to where input will be stored.
* Max 0x32-1 bytes will be read. Input stream is stdin.
* Adds a null terminator at the end. `pcVar2` points to `acStack_b9` if success, null if not.

---

```c
if (pcVar2 != (char *)0x0)
    strcpy(local_110,acStack_b9 + 1);
```

* If `fgets` is successful, copies all from `acStack_b9+1` to `local_110`.

---

```c
puts("How many bytes in length is your password?");
pcVar2 = fgets(local_d8,0x14,stdin);
```

* `local_d8` points to input buffer of max length 0x14-1.

---

```c
if (pcVar2 != (char *)0x0) {
    uVar1 = atoi(local_d8);
```

* Converts `local_d8` to integer.
* If `local_d8` is `"123"` → `uVar1` is 123.
* If `local_d8` is `"abc"` → `uVar1` is 0.
* If `local_d8` is `"123abc"` → `uVar1` is 123.

---

```c
for (local_128 = 0; (local_128 <= (int)uVar1 && (local_128 < 0x5a)); local_128 = local_128 + 1) {
    printf("%d ",(ulong)(uint)(int)local_110[local_128]);
}
putchar(10);
```

* Simple for loop. Runs till `uVar1` AND 0x5a. Prints each byte.
* `putchar(10);` prints newline (ASCII 10) to terminal.

---

```c
pcVar2 = fgets(acStack_b9 + 1,0x32,stdin);
```

* `pcVar2` contains pointer to buffer `acStack_b9` of max length 0x32-1

---

```c
if (pcVar2 != (char *)0x0) {
    local_108 = strlen(acStack_b9 + 1);
    if ((local_108 != 0) && (acStack_b9[local_108] == '\n')) {
        acStack_b9[local_108] = '\0';
    }
```

* `local_108` has string length of input `pcVar2`.
* Sets null terminator to `acStack_b9` if not already.

---

```c
local_100 = strtoul(acStack_b9 + 1,&local_120,10);
```

* Similar to `atoi`. Converts string to number.
* `acStack_b9` is the pointer to input string and `local_120` is pointer to where parsing stops.
* `local_100` has stored number.

---

```c
if (local_120 == acStack_b9 + 1) {
    printf("No digits were found");
}
```

* If start of pointer is equal to end, no digits found

---

```c
local_f8 = make_secret(local_e5);
if (local_f8 == local_100) {
    local_f0 = fopen("flag.txt","r");
```

* If `local_100` matches `local_f8`, `flag.txt` is read. So, we need to check `make_secret()`.

---

```c
void make_secret(long param_1)
```

* takes `param_1` input

---

```c
for (local_10 = 0; obf_bytes[local_10] != '\0'; local_10 = local_10 + 1) {
    *(byte *)(local_10 + param_1) = obf_bytes[local_10] ^ 0xaa;
}
```

* For loop. Till end of string `local_10` (inside main) is reached,
* Bitwise XOR `local_10` with 0xaa. Stores it at offset `local_10 + param_1`.

---

```c
*(undefined1 *)(param_1 + 0xc) = 0;
```

* Dereferences pointer `(param_1 + 0xc)` and writes 0 to memory.

---

```c
hash(param_1);
```

Lets check `hash()`:

```c
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
```

* `param_1` is now `local_20` as well
* While `*local_20 != 0`, `local_10 = (long)(int)(uint)*local_20 + local_10 * 0x21`
* `local_20 = local_20 + 1`
* Returns `local_10`

---

