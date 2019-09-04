/************************************************************************
 *
 * stdio.h: $Revision: 3526 $
 *
 * (c) Copyright 2002-2010 Analog Devices, Inc.  All rights reserved.
 * 
 ************************************************************************/

#pragma once
#ifndef __NO_BUILTIN
#pragma system_header /* stdio.h */
#endif

#ifndef __STDIO_DEFINED
#define __STDIO_DEFINED

#ifdef _MISRA_RULES
#pragma diag(push)
#pragma diag(suppress:misra_rule_5_3:"ADI header will re-use identifiers")
#pragma diag(suppress:misra_rule_6_3)
#pragma diag(suppress:misra_rule_16_1)
#pragma diag(suppress:misra_rule_19_1)
#pragma diag(suppress:misra_rule_19_4)
#pragma diag(suppress:misra_rule_20_1)
#pragma diag(suppress:misra_rule_20_2)
#endif /* _MISRA_RULES */

#ifndef NULL
# if defined(__cplusplus)
#  define NULL  0
# else
#  define NULL  ((void *)0)
# endif
#endif

# if defined(__cplusplus)
#include <yvals.h>
# endif

#define BUFSIZ          64
#define EOF             (-1)
#define FILENAME_MAX    32
#define FOPEN_MAX       10
#define L_tmpnam        32
#define TMP_MAX         25

/* C Standard names for setvbuf arg */
#define _IOFBF          0
#define _IOLBF          1
#define _IONBF          2

#define SEEK_SET        0
#define SEEK_CUR        1
#define SEEK_END        2

#ifdef __cplusplus
typedef struct _mbstatet {
   int  _wchar;
   char _state;
} _mbstatet;

typedef struct fpos_t {
   long      _off;
   _mbstatet _state;
} fpos_t;
#ifndef _FPOSOFF
 #define _FPOSOFF(fp)   ((fp)._off)
#endif
#else
typedef unsigned long fpos_t;
#endif

#ifndef __SIZE_T_DEFINED
#define __SIZE_T_DEFINED
typedef long unsigned int size_t;
#endif

/* Analog extensions to stdio.h are located in
 * a platform specific include file.
 * Use the compile option -D__NO_ANSI_EXTENSIONS__
 * to exclude any such extensions.
 */
#if !defined( __NO_ANSI_EXTENSIONS__ )
#if defined ( __ADSP21000__ )

 #include <stdio_21xxx.h>

#endif    /* __ADSP21000__          */
#endif    /* __NO_ANSI_EXTENSIONS__ */


typedef struct {
    unsigned int    _Mode;
    int             fileID;
    unsigned long   _Next;   /* always considered valid */
    unsigned long   _Rend;   /* always considered valid */
    unsigned long   _Wend;   /* always considered valid */
/* even more private: */
    unsigned char*  bufadr;
    unsigned long   _Buf;
    unsigned char*  _Bend;
    unsigned long   rsave;
    unsigned char   _Back[2];
    unsigned char   onechar;
    int             nback;
} FILE;

#define _FILET

#if defined(__cplusplus)
extern "C" {
#endif

extern FILE*    _Files[FOPEN_MAX];
#define stdin   _Files[0]
#define stdout  _Files[1]
#define stderr  _Files[2]

#ifdef __DOUBLES_ARE_FLOATS__
  #define printf   _printf32
  #define sprintf  _sprintf32
  #define fprintf  _fprintf32
  #define scanf    _scanf32
  #define sscanf   _sscanf32
  #define fscanf   _fscan32
  #define vfprintf _vfprintf32
  #define vprintf  _vprintf32
  #define vsprintf _vsprintf32
#else
  #define perror   _perror64
  #define printf   _printf64
  #define sprintf  _sprintf64
  #define fprintf  _fprintf64
  #define scanf    _scanf64
  #define sscanf   _sscanf64
  #define fscanf   _fscan64
  #define vfprintf _vfprintf64
  #define vprintf  _vprintf64
  #define vsprintf _vsprintf64
#endif /* __DOUBLES_ARE_FLOATS__ */

#pragma misra_func(io)
void clearerr(FILE *_stream);
#pragma misra_func(io)
int fclose(FILE *_stream);
#pragma misra_func(io)
int feof(FILE *_stream);
#pragma misra_func(io)
int ferror(FILE *_stream);
#pragma misra_func(io)
int fflush(FILE *_stream);
#pragma misra_func(io)
int fgetc(FILE *_stream);
#pragma misra_func(io)
int fgetpos(FILE *_stream, fpos_t *_pos);
#pragma misra_func(io)
char* fgets(char *_buf, int _n, FILE *_stream);
#pragma misra_func(io)
FILE* fopen(const char *_name, const char* _mods);
#pragma misra_func(io)
int fprintf(FILE* _stream, const char* _format, ...);
#pragma misra_func(io)
int fputc(int _c, FILE *_stream);
#pragma misra_func(io)
int fputs(const char *_s, FILE *_stream);
#pragma misra_func(io)
size_t fread(void* _buf, size_t _sz, size_t _nElem, FILE *_stream);
#pragma misra_func(io)
FILE* freopen(const char *_s, const char* _mods, FILE *_stream);
#pragma misra_func(io)
int fscanf(FILE *_stream, const char* _fmt, ...);
#pragma misra_func(io)
int fseek(FILE *_stream, long _off, int _smode);
#pragma misra_func(io)
int fsetpos(FILE *_stream, const fpos_t *_pos);
#pragma misra_func(io)
long ftell(FILE *_stream);
#pragma misra_func(io)
size_t fwrite(const void* _buf, size_t _sz, size_t _nElem, FILE *_stream);
#pragma misra_func(io)
int getc(FILE *_stream);
#pragma misra_func(io)
int getchar(void);
#pragma misra_func(io)
char* gets(char *_s);
#pragma misra_func(io)
void perror(const char *_e);
#pragma misra_func(io)
int printf(const char* _fmt, ...);
#pragma misra_func(io)
int putc(int _c, FILE *_stream);
#pragma misra_func(io)
int putchar(int _c);
#pragma misra_func(io)
int puts(const char *_s);
#pragma misra_func(io)
int remove(const char *_f);
#pragma misra_func(io)
int rename(const char* _oldname, const char* _newname);
#pragma misra_func(io)
void rewind(FILE *_stream);
#pragma misra_func(io)
int scanf(const char* _fmt, ...);
#pragma misra_func(io)
void setbuf(FILE *_stream, char *_buf);
#pragma misra_func(io)
int setvbuf(FILE *_stream, char *_cbuf, int _smode, size_t _sz);
#pragma misra_func(io)
int sprintf(char* _buf, const char* _fmt, ...);
#pragma misra_func(io)
int sscanf(const char* _buf, const char* _fmt, ...);
#pragma misra_func(io)
int ungetc(int _c, FILE *_stream);
#pragma misra_func(io)
int vfprintf(FILE *_stream, const char *_fmt, char *_ap);
#pragma misra_func(io)
int vprintf(const char *_fmt, char *_ap);
#pragma misra_func(io)
int vsprintf(char *_buf, const char *_fmt, char *_ap);

#if 0  /* stdio functions not supported */
  FILE* tmpfile(void);
  char* tmpnam(char*);
#endif

#if defined(__cplusplus)
}
#endif

#ifdef _MISRA_RULES
#pragma diag(pop)
#endif /* _MISRA_RULES */

#endif
