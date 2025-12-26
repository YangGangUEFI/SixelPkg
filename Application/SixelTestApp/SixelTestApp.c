/** @file
  SixelLib test application

  Copyright (c) 2025, Yang Gang. All rights reserved.<BR>
  SPDX-License-Identifier: MIT

**/

#include <Uefi.h>
#include <Protocol/PlatformLogo.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SerialPortLib.h>
#include <Library/UefiLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/SixelLib.h>


static
UINTN
EFIAPI
sixel_write_to_port (
  CHAR8 *Data,
  UINTN Size,
  VOID  *Priv
  )
{

  SerialPortWrite((UINT8 *)Data, Size);

  return EFI_SUCCESS;
}


VOID
UefiLogoTest (
  VOID
  )
{
  EFI_STATUS                             Status;
  EDKII_PLATFORM_LOGO_PROTOCOL           *PlatformLogo;
  EDKII_PLATFORM_LOGO_DISPLAY_ATTRIBUTE  Attribute;
  INTN                                   OffsetX;
  INTN                                   OffsetY;
  UINT32                                 Instance;
  EFI_IMAGE_INPUT                        Image;
  EFI_GRAPHICS_OUTPUT_BLT_PIXEL          *Blt;
  UINTN                                  ComPort;

  Instance = 0;

  Blt = NULL;
  Status = gBS->LocateProtocol (&gEdkiiPlatformLogoProtocolGuid, NULL, (VOID **)&PlatformLogo);
  if (!EFI_ERROR (Status)) {
    //
    // Get EfiImageLogo from PlatformLogo protocol.
    //
    Status = PlatformLogo->GetImage (
                             PlatformLogo,
                             &Instance,
                             &Image,
                             &Attribute,
                             &OffsetX,
                             &OffsetY
                             );
  }

// SIXEL_PIXELFORMAT_BGRA8888
  Blt = Image.Bitmap;
  ComPort = 0x3F8;
  SixelEncodeBytes ((UINT8 *)Blt, Image.Width, Image.Height, 0, sixel_write_to_port, &ComPort);

  for (UINTN Index = 0; Index < Image.Height / EFI_GLYPH_HEIGHT; Index++) {
    Print (L"\n");
  }

  if (Blt != NULL) {
    FreePool(Blt);
  }
}



EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{

  UefiLogoTest();

  return EFI_SUCCESS;
}
