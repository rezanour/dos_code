/*
 *  sys/stat.h	Equates and prototype for fstat, stat functions
 *
 *  Copyright (C) by WATCOM Systems Inc. 1988-1991.  All rights reserved.
 */
#ifndef _TYPES_H_INCLUDED
 #include <sys/types.h>
#endif

#ifndef _STAT_H_INCLUDED
#pragma pack(1);

struct stat {
	dev_t	st_dev; 	/* disk drive file resides on */
	ino_t	st_ino; 	/* this inode's #, not used for DOS */
	unsigned short st_mode; /* file mode */
	short	st_nlink;	/* # of hard links */
	short	st_uid; 	/* user-id, always 'root' */
	short	st_gid; 	/* group-id, always 'root' */
	dev_t	st_rdev;	/* should be device type */
				/* but same as st_dev for the time being */
	off_t	st_size;	/* total file size */
	time_t	st_atime;	/* should be file last access time */
	time_t	st_mtime;	/* file last modify time */
	time_t	st_ctime;	/* should be file last status change time */
};

#define S_IFMT		0170000 /* type of file */
#define S_IFDIR 	0040000 /* directory */
#define S_IFCHR 	0020000 /* character special file */
#define S_IFREG 	0100000 /* regular */

#define S_ISDIR( m )	(((m) & S_IFMT) == S_IFDIR)
#define S_ISCHR( m )	(((m) & S_IFMT) == S_IFCHR)
#define S_ISREG( m )	(((m) & S_IFMT) == S_IFREG)
/* the following two are not possible on PC */
#define S_ISBLK( m )	0
#define S_ISFIFO( m )	0

/* owner permission */
#define S_IRWXU 	0000700
#define S_IRUSR 	0000400
#define S_IWUSR 	0000200
#define S_IXUSR 	0000100
#define S_IREAD 	0000400
#define S_IWRITE	0000200
#define S_IEXEC 	0000100

/* group permission.  same as owner's on PC */
#define S_IRWXG 	0000070
#define S_IRGRP 	0000040
#define S_IWGRP 	0000020
#define S_IXGRP 	0000010

/* other permission.  same as owner's on PC */
#define S_IRWXO 	0000007
#define S_IROTH 	0000004
#define S_IWOTH 	0000002
#define S_IXOTH 	0000001

/* setuid, setgid, and sticky.	always false on PC */
#define S_ISUID 	0004000
#define S_ISGID 	0002000
#define S_ISVTX 	0001000

int fstat(int, struct stat *);
int stat(const char *, struct stat *);

#pragma pack();
#define _STAT_H_INCLUDED
#endif
