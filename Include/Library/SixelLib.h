/** @file
  SixelLib encode API from the libsixel project

  Copyright (c) 2025, Yang Gang. All rights reserved.<BR>
  SPDX-License-Identifier: MIT

**/

#ifndef __SIXEL_LIB_H__
#define __SIXEL_LIB_H__

typedef
UINTN
(EFIAPI *SIXEL_OUTPUT_FN)(
  CHAR8 *Data,
  UINTN Size,
  VOID  *Priv
  );

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
  );

#endif
