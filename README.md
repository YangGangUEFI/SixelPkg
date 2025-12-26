# SixelPkg

> Provides a library for encoding `EFI_GRAPHICS_OUTPUT_BLT_PIXEL` into SIXEL format.

### Usage

```
// Blt              - Image pixel(EFI_GRAPHICS_OUTPUT_BLT_PIXEL)
// Width            - Image width
// Height           - Image height
// 0                - NColors, Reserved
// write_fn         - Callback function to write encoded data
// write_fn_private - Private data parameter for write_fn
SixelEncodeBytes ((UINT8 *)Blt, Width, Height, 0, write_fn, write_fn_private);

static
UINTN
EFIAPI
write_fn (
  CHAR8 *Data,
  UINTN Size,
  VOID  *Priv
  )
{

  SerialPortWrite((UINT8 *)Data, Size);  // example, write to serial port

  return EFI_SUCCESS;
}
```

> Please refer to the [SixelPkg/SixelTestApp](./Application/SixelTestApp/SixelTestApp.c) for a complete example.

### Demo(qemu with `-nographic` parameter)

1. Display TianoCore logo in UEFI Shell

    https://www.bilibili.com/video/BV111BeBPEXu

2. Display [UefiDashboard.efi](https://github.com/YangGangUEFI/LvglPkg) in UEFI Shell

    https://www.bilibili.com/video/BV111BeBPEaq

### TODO

- [ ] Use api from encoder.c
