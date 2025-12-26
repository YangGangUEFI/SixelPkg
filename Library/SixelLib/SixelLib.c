/** @file
  SixelLib encode API from the libsixel project

  Copyright (c) 2025, Yang Gang. All rights reserved.<BR>
  SPDX-License-Identifier: MIT

**/

#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/BaseLib.h>
#include <Library/PrintLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/SixelLib.h>
#include "sixel.h"

/* encode specified pixel data to SIXEL format */
EFI_STATUS
EFIAPI
SixelEncodeBytes (
  UINT8            *Bytes,
  UINTN            Width,
  UINTN            Height,
  UINTN            NColors,
  SIXEL_OUTPUT_FN  OutPutFunc,
  VOID             *OutPutFuncPriv
  )
{
  SIXELSTATUS status = SIXEL_FALSE;
  sixel_output_t *output = NULL;
  sixel_dither_t *dither = NULL;

  status = sixel_output_new(&output, (sixel_write_function)OutPutFunc, OutPutFuncPriv, NULL);
  if (SIXEL_FAILED(status)) {
    // Print (L"Failed to create output\n");
    goto end;
  }

  dither = sixel_dither_get(SIXEL_BUILTIN_XTERM256);
  sixel_dither_set_pixelformat(dither, SIXEL_PIXELFORMAT_BGRA8888);
  status = sixel_encode(Bytes, Width, Height, 0, dither, output);
  if (SIXEL_FAILED(status)) {
    // Print (L"Failed to encode\n");
    goto end;
  }

end:
  return EFI_SUCCESS;
}
