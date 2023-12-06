#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>

extern char **environ;

/*  */
#define CONVERT_LOWER	1
#define CONVERT_UNINT	2

/* */
#define NORMAL_CMND	0
#define OR_CMND		1
#define AND_CMND	2
#define CHAIN_CMND	3

/* read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/**/
#define FOR_STRTOK 0
#define FOR_GETLINE 0

/**
 * struct strng_l - A singly linked list
 * @nmber: The field denoting numbers
 * @strng: The string
 * @nxt: The pointer to the next node
 */
typedef struct strng_l
{
        int nmber;
        char *strng;
        struct strng_l *nxt;
} lst_m;

#define FILE_H	".simple_shell_history"
#define MAX_H	4096

pseuarg

/* toem_memory.c */
int freepoint(void **);

/**
 *struct embedstr - Struct that contains embedded string and respective function
 *@cflg: The flag denoting the embedded command
 *@resfunc: The respective function
 */
typedef struct embedstr
{
	char *cflg;
	int (*resfunc)(pseuarg_ch *);
} embed_str;

/* loophsh.c */
int shelloop(char **);

/* toem_shloop.c */
int shellmain(pseuarg_ch *, char **);
int go_emb(pseuarg_ch *);
void loc_comm(pseuarg_ch *);
void loc_fork(pseuarg_ch *);

/* toem_string1.c */
char *strngcop(char *, char *);
char *strngclone(const char *);
void strngin(char *);
int _putchar(char); // Ask if this one is to be changed as well
