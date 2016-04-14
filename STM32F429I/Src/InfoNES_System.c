#include "InfoNES_System.h"
#include "InfoNES.h"
#include <string.h>
#include <stdio.h>

extern DWORD * FrameBuffer;

WORD NesPalette[64]={
  0x738E,0x88C4,0xA800,0x9808,0x7011,0x1015,0x0014,0x004F,
  0x0148,0x0200,0x0280,0x11C0,0x59C3,0x0000,0x0000,0x0000,
  0xBDD7,0xEB80,0xE9C4,0xF010,0xB817,0x581C,0x015B,0x0A59,
  0x0391,0x0480,0x0540,0x3C80,0x8C00,0x0000,0x0000,0x0000,
  0xFFDF,0xFDC7,0xFC8B,0xFC48,0xFBDE,0xB39F,0x639F,0x3CDF,
  0x3DDE,0x1690,0x4EC9,0x9FCB,0xDF40,0x0000,0x0000,0x0000,
  0xFFDF,0xFF15,0xFE98,0xFE5A,0xFE1F,0xDE1F,0xB5DF,0xAEDF,
  0xA71F,0xA7DC,0xBF95,0xCFD6,0xF7D3,0x0000,0x0000,0x0000,
};

/* Menu screen */
int InfoNES_Menu()
{
    return 0;
}


extern const BYTE nes_rom[];
/* Read ROM image file */
int InfoNES_ReadRom( const char *pszFileName )
{
/*
 *  Read ROM image file
 *
 *  Parameters
 *    const char *pszFileName          (Read)
 *
 *  Return values
 *     0 : Normally
 *    -1 : Error
 */


  /* Read ROM Header */
  BYTE * rom = (BYTE*)nes_rom;
  memcpy( &NesHeader, rom, sizeof(NesHeader));
  if ( memcmp( NesHeader.byID, "NES\x1a", 4 ) != 0 )
  {
    /* not .nes file */
    return -1;
  }
  rom += sizeof(NesHeader);

  /* Clear SRAM */
  memset( SRAM, 0, SRAM_SIZE );

  /* If trainer presents Read Triner at 0x7000-0x71ff */
  if ( NesHeader.byInfo1 & 4 )
  {
    //memcpy( &SRAM[ 0x1000 ], rom, 512);
	rom += 512;
  }

  /* Allocate Memory for ROM Image */
  ROM = rom;
  rom += NesHeader.byRomSize * 0x4000;

  if ( NesHeader.byVRomSize > 0 )
  {
    /* Allocate Memory for VROM Image */
	VROM = (BYTE*)rom;
	rom += NesHeader.byVRomSize * 0x2000;
  }

  /* Successful */
  return 0;
}


/* Release a memory for ROM */
void InfoNES_ReleaseRom()
{
}


/* Transfer the contents of work frame on the screen */
void InfoNES_LoadFrame()
{

    unsigned int x,y;
    unsigned short *src,*dst;
    src = (unsigned short *)WorkFrame;
    
    for(x=0;x<NES_DISP_HEIGHT;x++)
    {
        dst = (unsigned short *)FrameBuffer + (NES_DISP_HEIGHT-1-x);
        for(y=0;y<NES_DISP_WIDTH;y++)
        {
            *dst = *src;
            dst += NES_DISP_HEIGHT;
            src++;
        }
    }
}


/* Get a joypad state */
void InfoNES_PadState( DWORD *pdwPad1, DWORD *pdwPad2, DWORD *pdwSystem )
{
}


/* memcpy */
void *InfoNES_MemoryCopy( void *dest, const void *src, int count )
{
    return memcpy(dest,src,count);
}


/* memset */
void *InfoNES_MemorySet( void *dest, int c, int count )
{
    return memset(dest,c,count);
}


/* Print debug message */
void InfoNES_DebugPrint( char *pszMsg )
{
}


/* Wait */
void InfoNES_Wait()
{
}


/* Sound Initialize */
void InfoNES_SoundInit( void )
{
}


/* Sound Open */
int InfoNES_SoundOpen( int samples_per_sync, int sample_rate )
{
    return 0;
}


/* Sound Close */
void InfoNES_SoundClose( void )
{
}


/* Sound Output 5 Waves - 2 Pulse, 1 Triangle, 1 Noise, 1 DPCM */
void InfoNES_SoundOutput(int samples, BYTE *wave1, BYTE *wave2, BYTE *wave3, BYTE *wave4, BYTE *wave5)
{
}


/* Print system message */
void InfoNES_MessageBox( char *pszMsg, ... )
{
}

