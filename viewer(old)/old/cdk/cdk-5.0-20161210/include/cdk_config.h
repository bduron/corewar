/* include/cdk_config.h.  Generated automatically by configure.  */
/*
 * $Id: config.hin,v 1.2 2000/01/17 14:48:19 tom Exp $
 */

#ifndef CDK_CONFIG_H
#define CDK_CONFIG_H 1


#define CDK_CONST /*nothing*/
#define CDK_CSTRING CDK_CONST char *
#define CDK_CSTRING2 CDK_CONST char * CDK_CONST *
#define CDK_PATCHDATE 20161210
#define CDK_VERSION "5.0"
#define HAVE_DIRENT_H 1
#define HAVE_GETBEGX 1
#define HAVE_GETBEGY 1
#define HAVE_GETCWD 1
#define HAVE_GETLOGIN 1
#define HAVE_GETMAXX 1
#define HAVE_GETMAXY 1
#define HAVE_GETOPT_H 1
#define HAVE_GETOPT_HEADER 1
#define HAVE_GRP_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_LIMITS_H 1
#define HAVE_LSTAT 1
#define HAVE_MEMORY_H 1
#define HAVE_MKTIME 1
#define HAVE_NCURSES_H 1
#define HAVE_PWD_H 1
#define HAVE_SETLOCALE 1
#define HAVE_SLEEP 1
#define HAVE_START_COLOR 1
#define HAVE_STDINT_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRDUP 1
#define HAVE_STRERROR 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_TERM_H 1
#define HAVE_TYPE_CHTYPE 1
#define HAVE_UNCTRL_H 1
#define HAVE_UNISTD_H 1
#define NCURSES 1
#define PACKAGE "cdk"
#define STDC_HEADERS 1
#define SYSTEM_NAME "darwin15.6.0"
#define TYPE_CHTYPE_IS_SCALAR 1
#define setbegyx(win,y,x) ERR

#if !defined(HAVE_LSTAT) && !defined(lstat)
#define lstat(f,b) stat(f,b)
#endif

#endif /* CDK_CONFIG_H */
