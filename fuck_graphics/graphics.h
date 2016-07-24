/****************************************************/
/* VESA graphics library in Watcom C                */
/* copyright (C) Black White.  Feb 14, 2014         */
/* email: iceman@zju.edu.cn                         */
/* web: http://blackwhite.8866.org/bhh              */
/****************************************************/

#ifndef GRAPHICS_H
#define GRAPHICS_H 1
#define __interrupt
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mem.h>
#include <malloc.h>
#include <time.h>
#include <dos.h>
//#include <bios.h>
#include <conio.h>
//#include <i86.h>
#include "graph.h"
#pragma pack(1);
#pragma comment(lib, "graphics.lib");

/*===Part{1}============����Ϊͼ����ص����ͼ�����=========================*/
#define PI 3.14159265358979323846
typedef unsigned char byte;
typedef unsigned short int word;
typedef unsigned long int dword;
typedef void __interrupt (*InterruptFunctionPointer)(void);

enum MODE_SUPPORTED
{
   DETECT = 0,                 /* for compatibility with TC */
   VESA_320x200x8bit   = 0x01, /* 0x0151 G */ 
   VESA_320x200x24bit  = 0x02, /* 0x0152 G */
   VESA_320x200x32bit  = 0x03, /* 0x010F G */
   VESA_640x480x8bit   = 0x04, /* 0x0101 G */
   /* VESA_640x480x24bit  = 0x05, */ /* 0x0212 G */ 
   /* It does not work properly under DosBox,
      So it's deliberatly removed here.
    */
   VESA_640x480x32bit  = 0x06, /* 0x0112 G */
   VESA_800x600x8bit   = 0x07, /* 0x0103 G */
   VESA_800x600x24bit  = 0x08, /* 0x0178 G */
   VESA_800x600x32bit  = 0x09, /* 0x0115 G */
   VESA_1024x768x8bit  = 0x0A, /* 0x0105 G */
   VESA_1024x768x24bit = 0x0B, /* 0x0179 G */
   VESA_1024x768x32bit = 0x0C, /* 0x0118 G */
   TEXT_80x25x16bit    = 0x0D, /* 0x0003 T */
   TEXT                = 0x0D, /* shortcut for TEXT_80x25x16bit */
   C80                 = 0x0D, /* for compatibility with TC */
   VGAHI               = 0x04, /* for compatibility with TC */
   IBM8514LO           = 0x04, /* for compatibility with TC */
   IBM8514HI           = 0x0A  /* for compatibility with TC */
};


typedef struct 
{
   int  mode;
   int  width;
   int  height;
   int  color_bits;
   char *name;
} VIDEO_MODE;

typedef struct
{
   byte blue;
   byte green;
   byte red;
   byte reserved;
} BMP_PALETTE;

#define _UP    0x48
#define _DOWN  0x50
#define _LEFT  0x4B
#define _RIGHT 0x4D



/* The following types are for compatibility with Turbo C */
extern dword _EAX, _EBX, _ECX, _EDX, _ESP, _EBP, _ESI, _EDI;
extern word  _CS, _DS, _ES, _SS;
#define _AL  (*(byte *)&_EAX)
#define _BL  (*(byte *)&_EBX)
#define _CL  (*(byte *)&_ECX)
#define _DL  (*(byte *)&_EDX)
#define _AH  (*((byte *)&_EAX+1))
#define _BH  (*((byte *)&_EBX+1))
#define _CH  (*((byte *)&_ECX+1))
#define _DH  (*((byte *)&_EDX+1))
#define _AX  (*(word *)&_EAX)
#define _BX  (*(word *)&_EBX)
#define _CX  (*(word *)&_ECX)
#define _DX  (*(word *)&_EDX)
#define _SP  (*(word *)&_ESP)
#define _BP  (*(word *)&_EBP)
#define _SI  (*(word *)&_ESI)
#define _DI  (*(word *)&_EDI)

#define interrupt __interrupt
#define HORIZ_DIR	0	/* left to right */
#define VERT_DIR	1	/* bottom to top */

enum COLORS
{
   BLACK,       /* dark colors */
   BLUE,
   GREEN,
   CYAN,
   RED,
   MAGENTA,
   BROWN,
   LIGHTGRAY,
   DARKGRAY,    /* light colors */
   LIGHTBLUE,
   LIGHTGREEN,
   LIGHTCYAN,
   LIGHTRED,
   LIGHTMAGENTA,
   YELLOW,
   WHITE
};

enum EGA_COLORS {
    EGA_BLACK		 =  0,	    /* dark colors */
    EGA_BLUE		 =  1,
    EGA_GREEN		 =  2,
    EGA_CYAN		 =  3,
    EGA_RED		 =  4,
    EGA_MAGENTA 	 =  5,
    EGA_BROWN		 =  20,
    EGA_LIGHTGRAY	 =  7,
    EGA_DARKGRAY	 =  56,     /* light colors */
    EGA_LIGHTBLUE	 =  57,
    EGA_LIGHTGREEN	 =  58,
    EGA_LIGHTCYAN	 =  59,
    EGA_LIGHTRED	 =  60,
    EGA_LIGHTMAGENTA	 =  61,
    EGA_YELLOW		 =  62,
    EGA_WHITE		 =  63
};

enum line_styles {		/* Line styles for get/setlinestyle */
	SOLID_LINE   = 0,
	DOTTED_LINE  = 1,
	CENTER_LINE  = 2,
	DASHED_LINE  = 3,
	USERBIT_LINE = 4,	   /* User defined line style */
};

enum line_widths {		/* Line widths for get/setlinestyle */
	NORM_WIDTH  = 1,
	THICK_WIDTH = 3,
};


enum putimage_ops 
{  /* BitBlt operators for putimage */
	COPY_PUT,   /* MOV */
	XOR_PUT,    /* XOR */
	OR_PUT,     /* OR  */
	AND_PUT,    /* AND */
	NOT_PUT     /* NOT */
};

struct picture 
{ /* structure for getimage(), putimage() */
    short           picwidth;               /* # of pixels across   */
    short           picheight;              /* # of pixels down     */
    short           bpp;                    /* # of bits per pixel  */
    char            buffer;                 /* buffer for image     */
};

enum graphics_drivers 
{ 	/* define graphics drivers */
	DETECT_REMOVED, /* DETECT is moved to MODE_SUPPORTED */
	/* CGA, MCGA, EGA, EGA64, EGAMONO, IBM8514,	*/
	/* HERCMONO, ATT400, */ /* These old drivers will not be supported */
   VGA /* only this driver is kept */
   /* , PC3270, */
};

struct fillsettingstype 
{
	int pattern;
	int color;
};

enum fill_patterns 
{  /* Fill patterns for get/setfillstyle */
	EMPTY_FILL,		/* fills area in background color */
	SOLID_FILL,		/* fills area in solid fill color */
	LINE_FILL,		/* --- fill */
	LTSLASH_FILL,		/* /// fill */
	SLASH_FILL,		/* /// fill with thick lines */
	BKSLASH_FILL,		/* \\\ fill with thick lines */
	LTBKSLASH_FILL, 	/* \\\ fill */
	HATCH_FILL,		/* light hatch fill */
	XHATCH_FILL,		/* heavy cross hatch fill */
	INTERLEAVE_FILL,	/* interleaving line fill */
	WIDE_DOT_FILL,		/* Widely spaced dot fill */
	CLOSE_DOT_FILL, 	/* Closely spaced dot fill */
	USER_FILL		/* user defined fill */
};

enum text_just 
{  /* Horizontal and vertical justification
				   for settextjustify */
	LEFT_TEXT	= 0,
	CENTER_TEXT	= 1,
	RIGHT_TEXT	= 2,
	BOTTOM_TEXT	= 0,
     /* CENTER_TEXT	= 1,  already defined above */
	TOP_TEXT	= 2
};

enum font_names 
{
	DEFAULT_FONT	= 0,	/* 8x8 bit mapped font */
	TRIPLEX_FONT	= 1,	/* "Stroked" fonts */
	SMALL_FONT	= 2,
	SANS_SERIF_FONT = 3,
	GOTHIC_FONT	= 4
};


enum graphics_errors {		/* graphresult error return codes */
	grOk		   =   0,
	grNoInitGraph	   =  -1,
	grNotDetected	   =  -2,
	grFileNotFound	   =  -3,
	grInvalidDriver    =  -4,
	grNoLoadMem	   =  -5,
	grNoScanMem	   =  -6,
	grNoFloodMem	   =  -7,
	grFontNotFound	   =  -8,
	grNoFontMem	   =  -9,
	grInvalidMode	   = -10,
	grError 	   = -11,   /* generic error */
	grIOerror	   = -12,
	grInvalidFont	   = -13,
	grInvalidFontNum   = -14,
	grInvalidVersion   = -18
};


/* The following functions are compatible with TC */
void  geninterrupt(int intnum);
int   int86( int, union REGS *inregs, union REGS *outregs);
int   int86x(int intno, union REGS *inregs, union REGS *outregs, 
/*===================*/ struct SREGS *segregs);
void  disable(void);
void  enable(void);
void  setvect( unsigned intnum, void (__interrupt __far *handler)() );
void  (__interrupt __far *getvect(unsigned intnum))();
byte  inportb(int port);
void  outportb(int port, byte value);
int   bioskey(int cmd);
void  randomize(void);
int   random(int n);

void  textmode(int newmode); 
void  textbackground(int newcolor);
void  textcolor(int newcolor);
void  clrscr(void);
void  gotoxy(int x, int y);
int   wherex(void);
int   wherey(void);
int   putch(int x); // This function is a substitute for putch() declared in conio.h,
                    // because the original putch() does not trace the coordinates of 
                    // the cursor which results in _gettextposition()'s returning 
                    // incorrect value.
int   gettext(int left, int top, int right, int bottom, void *p);
int   puttext(int left, int top, int right, int bottom, void *p);
void  window(int left, int top, int right, int bottom);

void  initgraph(int *graphdriver, int *graphmode, char *pathtodriver);
void  closegraph(void);
void  cleardevice(void);
int   graphresult(void);
char  *grapherrormsg(int errorcode);

void  putpixel(int x, int y, dword pixelcolor);
dword getpixel(int x, int y);
dword imagesize(int left, int top, int right, int bottom);
void  getimage(int left, int top, int right, int bottom, void *bitmap);
void  putimage(int left, int top, void *bitmap, int op);
void  setactivepage(int page);
void  setvisualpage(int page);
void  setcolor(int color);
void  setbkcolor(int color);
void  setfillstyle(int pattern, int color);
void  settextjustify(int horiz, int vert); /* a dummy function */
void  settextstyle(int font, int direction, int charsize); /* a dummy function */
void  setlinestyle(int linestyle, unsigned upattern, int thickness); /* a dummy func */
void  setrgbcolor(int colornum, int red, int green, int blue);
int   getcolor(void);
int   getbkcolor(void);
int   getx(void);
int   gety(void);
int   getmaxx(void);
int   getmaxy(void);
void  outtextxy(int x, int y, char s[]);
void  getfillsettings(struct fillsettingstype *fillinfo);
void  setfillpattern(char *upattern, int color);

void  drawellipse(int x, int y, int xradius, int yradius);
/*====================== ����Բ�����, �߽�����ɫ��setcolor()�趨, TC�޴˺��� */
void  fillellipse(int x, int y, int xradius, int yradius);
/*====================== ����Բ�����, ����Ｐ��ǰ��ɫ��setfillstyle()�趨, 
                         ����ɫ��setbkcolor()�趨, �ޱ߽��� */
void  ellipse(int x, int y, int stangle, int endangle, int xradius, int yradius);
/*================== ����Բ�е�һ�λ�, Բ������㼰�յ��������, ����� */
void  arc(int x, int y, int stangle, int endangle, int radius);
/*================== ����Բ�е�һ�λ�, Բ������㼰�յ��������, ����� */
void  line(int x1, int y1, int x2, int y2);
void  lineto(int x, int y);
void  linerel(int dx, int dy);
void  moveto(int x, int y);
void  moverel(int dx, int dy);
void  rectangle(short x1, short y1, short x2, short y2);
/*======================= �����β����, �߽�����ɫ��setcolor()�趨 */
void  bar(short x1, short y1, short x2, short y2);
/*================= �����β����, ����Ｐ��ǰ��ɫ��setfillstyle()�趨, 
                    ����ɫ��setbkcolor()�趨, �ޱ߽��� */
void  bar3d(int left, int top, int right, int bottom, int depth, int topflag);
/*=================== ����ά���β����, ����Ｐ��ǰ��ɫ��setfillstyle()�趨, 
                      ����ɫ��setbkcolor()�趨, �߽�����ɫ��setcolor()�趨 */
void  circle(int x, int y, int radius);
/*================= ����Բ�����, �߽�����ɫ��setcolor()�趨; Ҫ����������Բ
                    ����ú���fillellipse() */
void  sector(int x, int y, int start_angle, int end_angle, int xradius, int yradius);
/*================= ����Բ�е�һ�����������, ����Ｐ��ǰ��ɫ��setfillstyle()�趨, 
                    ����ɫ��setbkcolor()�趨, �߽�����ɫ��setcolor()�趨;
                    start_angle��end_angle��ʾ��ʼ�Ƕȼ���ֹ�Ƕ� */
void  pieslice(int x, int y, int start_angle, int end_angle, int radius);
/*=================== ����Բ�е�һ�����������, ����Ｐ��ǰ��ɫ��setfillstyle()�趨, 
                      ����ɫ��setbkcolor()�趨, �߽�����ɫ��setcolor()�趨;
                      start_angle��end_angle��ʾ��ʼ�Ƕȼ���ֹ�Ƕ� */
void  __arc(short fill, short x1, short y1, short x2, short y2,
/*===================*/ short x3, short y3, short x4, short y4 );
/*===================== ����Բ�е�һ�λ�, Բ������㼰�յ�������ߣ�������ɫ��
                        setcolor()�趨����fill==_GFILLINTERIORʱ, �˶λ���Ӧ��
                        �����ᱻ���, ����Ｐ��ǰ��ɫ��setfillstyle()�趨, ��
                        ��ɫ��setbkcolor()�趨; ��fill==_GBORDERʱ���˶λ���Ӧ
                        ���������ᱻ��䡣 (x1, y1)��(x2,y2)��ָ��Χ����Բ�ľ�
                        �ε����ϽǼ����½�����; (x3, y3)��������Բ���һ���㣬
                        �õ���Բ�Ĺ���һ��ֱ�ߣ���ֱ������Բ�Ľ�����ǻ������;
                        ͬ��(x4, y4)���������յ㡣TC�޴˺�����*/

void  __pie(short fill, short x1, short y1, short x2, short y2,
/*===================*/ short x3, short y3, short x4, short y4 );
/*===================== ����Բ�е�һ������, ��__arc()����Բ������ʼ�������, 
                        ������ɫ�뻡����ɫ��ͬ,��setcolor()�趨��TC�޴˺��� */
short floodfill( short x, short y, dword stop_color);
/*======================= ��(x,y)Ϊ�����к�ˮ����ʽ���,����Ｐ���ɫ�ɺ���
                          setfillstyle()ָ����stop_colorΪ�߽�ɫ, �����������
                          ��ɢʱ������������ɫ�ĵ���ֹͣ���; ��stop_color=-1,
                          ����(x,y)�����ɫΪ��׼, ��ɢʱ������(x,y)��ͬ��ɫ��
                          �������֮,��������(x,y)��ͬ��ɫ�ĵ���ֹͣ��䡣*/
                          
/* The following functions are not compatible with TC. */
/* They are included here to assist you in video programming. */
void text_mode(void);                       // �л���80x25�ı�ģʽ
int  graph_mode(int mode_index);            // �л���VESAͼ��ģʽ, ����:
                                            //    int d=DETECT, m=VESA_1024x768x8bit;
                                            //    initgraph(&driver, &mode, "");
                                            // �ɼ�Ϊ:
                                            //    graph_mode(VESA_1024x768x8bit);
int  set_bmp_palette(BMP_PALETTE *palette); // ����256ɫBMPͼƬ�ĵ�ɫ��
int  load_8bit_bmp(int x, int y, char *filename); 
                                            // ��(x,y)λ����ʾ256ɫbmpͼƬ
void set_timer_frequency(word divisor);     // ����ʱ����Ƶ��
                                            // divisor=1ʱΪ�����Ƶ��=1193180��/��
                                            // divisor=0ʱΪ�����Ƶ��=
                                            //    (1193180/65536)��/��
                                            // divisor=[1,65535]�����ڵ�����ֵʱ,
                                            //    ��Ƶ��=1193180/divisor
                                            // �ٶ�Ҫ��ʱ����1/1000��Ϊ�������1����
                                            // �Ӷ�ʵ��ÿ��1����͵���1��ʱ���ж�int 8,
                                            // ����԰�divisor���1193180/1000��
int  enum_vesa_modes(void);                 // �оٵ�ǰ�Կ�֧�ֵ�����VESAͼ��ģʽ
void rep_stosd(void *pdest, dword data, dword count); 
                                            // �ظ�count������data��pdest��
                                            // long a[100];
                                            // int i;
                                            // for(i=0; i<100; i++)
                                            //    a[i] = 0x12345678;
                                            // ���ϳ������������һ�仰ʵ��:
                                            // rep_stosd(a, 0x12345678, 100);                                                 
int  flip_page(int row, int col, int retrace);
                                            // �л���ʾҳ��, row=�к�, col=�к�
                                            // retrace=�Ƿ�ȴ���ֱ��ɨ
                                            // ����, ��VESA_1024x768x24bitģʽ�£�
                                            // setvisualpage(1)�൱�ڵ���:
                                            //    flip_page(768, 0, 0x80);
                                            // setvisualpage(0)�൱�ڵ���:
                                            //    flip_page(0, 0, 0x80);
// if retrace == 0x00, do not wait for vertical retrace in page flipping
// if retrace == 0x80, must wait for vertical retrace to avoid flicker
/* The functions above are not compatible with TC. */


/* system internal variables */
extern byte * const _vp;
extern int _width, _height, _color_bits;
extern int _visual_page, _active_page, _back_page, _page_gap;
extern int _mode_index, _mode;
extern int _draw_color, _back_color;
extern int _fill_color, _fill_mask_index;
extern int _x, _y;
/*===End of Part{1}=====����Ϊͼ����ص����ͼ�����=========================*/



/*===Part{2}============����Ϊ������ص����ͼ�����=========================*/
typedef struct _PIC      // ��Ƭ�ṹ����
{
   struct picture *img;  // ��Ƭ��ͼ��
   struct picture *mask; // ��Ƭ������
   int width, height;    // ��Ƭ�Ŀ�ȼ��߶�
} PIC;
PIC * get_ttf_text_pic(char text[], char fontname[], int fontsize); 
// ���ַ���text��fontname���塢fontsize�����Сת������Ƭ

dword out_ttf_text_xy(int x0, int y0, char text[], char fontname[], int fontsize);
// ���ַ���text��fontname���塢fontsize�����С�����(x0,y0)����
// �����ķ���ֵ = (��Ƭ���<<16) | ��Ƭ�߶�

void  draw_picture(int x, int y, PIC *p);
// ��(x,y)���������Ƭp

void  destroy_picture(PIC *p);
// ������Ƭpռ�õ���Դ
/*===End of Part{2}=====����Ϊ������ص����ͼ�����=========================*/



/*===Part{3}============����Ϊ������ص����ͼ�����=========================*/
typedef struct midi // MIDI file data structure
{                 
   word format;                       // 0 or 1
   word num_tracks;                   // 1 - 32
   word divisions;                    // number ticks per quarter note
   byte  *track[16];                  // Track data pointers
   word repeat;
   struct midi *chain;
   void  (*chainfunc)(struct midi *);
} MIDI;
                  
typedef struct wave 
{
   dword id;
   dword sample_rate;
   dword byte_rate;
   byte *data;
   dword chunk_size;                   // size of this chunk in bytes
   dword sample_size;                  // size of entire linked sample
   struct wave  *next;                 // points to next link.
   struct wave  *head;                 // points to top link.
} WAVE;

int  initsound(void);                  // ������ʼ��
void closesound(void);                 // �ر�����
WAVE * load_wave(char *filename);      // ����wav�ļ�
void play_wave(WAVE *p, int repeat);   // ����wav, repeatΪѭ������, repeat=-1Ϊ����ѭ��
void stop_wave(WAVE *p);               // ֹͣ����wav
void pause_wave(WAVE *p);              // ��ͣ����wav
void resume_wave(WAVE *p);             // ��������wav
void free_wave(WAVE *p);               // �ͷ�wavռ�õ���Դ
MIDI * load_midi(char *filename);      // ����midi�ļ�
void play_midi(MIDI *p, int repeat);   // ����midi, repeatΪѭ������, repeat=-1Ϊ����ѭ��
void stop_midi(MIDI *p);               // ֹͣ����midi
void pause_midi(MIDI *p);              // ��ͣ����midi
void resume_midi(MIDI *p);             // ��������midi
void free_midi(MIDI *p);               // �ͷ�midiռ�õ���Դ
/*===End of Part{3}=====����Ϊ������ص����ͼ�����=========================*/

#endif
