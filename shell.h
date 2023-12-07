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

/* for convert_number() */
#define CONVERT_LOWER	1
#define CONVERT_UNINT	2

/* for command chaining */
#define NORMAL_CMND	0
#define OR_CMND		1
#define AND_CMND	2
#define CHAIN_CMND	3

/* read/write buffers */
#define READ_BUFFER_SIZE 1024
#define WRITE_BUFFER_SIZE 1024
#define BUFFER_FLUSH -1

/* 1 if using system getline() */
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
}
	lst_m;

#define FILE_H	".simple_shell_history"
#define MAX_H	4096

pseuarg

/* toem_memory.c */
int freepoint(void **);

/**
 *struct embedstr - Struct contains embedded str and respective fn.
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
int _putchar(char); /* consult sharon for changes. This line has a betty error */

/* toem_parser.c */
int cmdprt(info_t *, char *);
char *chardup(char *, int, int);
char *locpath(info_t *, char *, char *);

/* toem_errors.c */
void putide(char *);
int charins(char);
int fputer(char c, int fd);
int fndpt(char *str, int fd);

/* toem_exits.c */
char *cppy_strng(char *, char *, int);
char *strngmod(char *, char *, int);
char *str_imp(char *, char);

/* toem_string.c */
int lngth_str(char *);
int strn_cmp(char *, char *);
char *at_strt(const char *, const char *);
char *strn_cat(char *, char *);

/* toem_errors1.c */
int exst_err(char *);
void errorprnt(info_t *, char *);
int disprnt(int, int);
char *conv_nmber(long int, int, int);
void rm_comm(char *);

/* toem_realloc.c */
char *mmry_arn(char *, char, unsigned int);
void dmfree(char **);
void *mem_ralloc(void *, unsigned int, unsigned int);

/*toem_getline.c */
ssize_t inpt_gt(info_t *);
int get_delim(info_t *, char **, size_t *);
void mngint(int);

/* toem_tokenizer.c */
char **mod_strng(char *, char *);
char **checkstrn(char *, char);

/* toem_memory.c */
int mem_free(void **);

/* toem_getinfo.c */
void infclr(info_t *);
void infprs(info_t *, char **);
void infree(info_t *, int);

/* toem_getenv.c */
char **aqrenv(info_t *);
int envunp(info_t *, char *);
int ptenv(info_t *, char *, char *);

/* toem_atoi.c */
int actv_int(info_t *);
int prser(char, char *);
int bst_int(int);
int atoi_t(char *);

/* toem_environ.c */
char *pop_env(info_t *, const char *);
int myown_env(info_t *);
int good_env(info_t *);
int bad_env(info_t *);
int fill_env(info_t *);

/* toem_lists1.c */
size_t lngth_lst(const list_t *);
char **strng_lst(list_t *);
size_t prnt_lst(const list_t *);
list_t *strt_strng(list_t *, char *, char);
ssize_t indx_gt(list_t *, list_t *);

/* toem_builtin1.c */
int hist_rep(info_t *);
int alum_hist(info_t *);

/* toem_history.c */
char *histfile_fetch(info_t *info);
int hist_updt(info_t *info);
int rdhist(info_t *info);
int histlst_b(info_t *info, char *buf, int linecount);
int nmber_hist(info_t *info);

/* toem_vars.c */
int str_ch(info_t *, char *, size_t *);
void look_ch(info_t *, char *, size_t *, size_t, size_t);
int rp_alias(info_t *);
int rp_vstr(info_t *);
int strn_chng(char **, char *);

/* toem_builtin.c */
int exist_sts(info_t *);
int cd_mine(info_t *);
int help_inf(info_t *);

/* toem_lists.c */
list_t *populate_node(list_t **, const char *, int);
list_t *endnode_add(list_t **, const char *, int);
size_t lststr_prnt(const list_t *);
int indxnode_del(list_t **, unsigned int);
void freelst(list_t **);





#endif


























