/**@file


**/
#include <Uefi.h>
#include <Protocol/BlockIo.h>
#include <Protocol/ComponentName.h>
#include <Protocol/DriverBinding.h>
//
// The Library classes this module consumes
//
#include <Library/DebugLib.h>
#include <Library/BaseLib.h>
#include <Library/UefiDriverEntryPoint.h>
#include <Library/UefiLib.h>
#include <Library/BaseMemoryLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/MemoryAllocationLib.h>

#include "TestBlockIo.h"

TEST_BLOCK_IO_PRIVATE gTstBlkIo;

EFI_DRIVER_BINDING_PROTOCOL gTestBlockIoDriverBinding = {
  TestBlockIoDriverBindingSupported,
  TestBlockIoDriverBindingStart,
  TestBlockIoDriverBindingStop,
  0xa,
  NULL,
  NULL
};

// MBR
UINT8 Lba0[] = 
{
  /* 00000000: */ 0x33, 0xC0, 0x8E, 0xD0, 0xBC, 0x00, 0x7C, 0x8E, 0xC0, 0x8E, 0xD8, 0xBE, 0x00, 0x7C, 0xBF, 0x00,  /*3...............*/
  /* 00000010: */ 0x06, 0xB9, 0x00, 0x02, 0xFC, 0xF3, 0xA4, 0x50, 0x68, 0x1C, 0x06, 0xCB, 0xFB, 0xB9, 0x04, 0x00,  /*.......Ph.......*/
  /* 00000020: */ 0xBD, 0xBE, 0x07, 0x80, 0x7E, 0x00, 0x00, 0x7C, 0x0B, 0x0F, 0x85, 0x0E, 0x01, 0x83, 0xC5, 0x10,  /*................*/
  /* 00000030: */ 0xE2, 0xF1, 0xCD, 0x18, 0x88, 0x56, 0x00, 0x55, 0xC6, 0x46, 0x11, 0x05, 0xC6, 0x46, 0x10, 0x00,  /*.....V.U.F...F..*/
  /* 00000040: */ 0xB4, 0x41, 0xBB, 0xAA, 0x55, 0xCD, 0x13, 0x5D, 0x72, 0x0F, 0x81, 0xFB, 0x55, 0xAA, 0x75, 0x09,  /*.A..U..]r...U.u.*/
  /* 00000050: */ 0xF7, 0xC1, 0x01, 0x00, 0x74, 0x03, 0xFE, 0x46, 0x10, 0x66, 0x60, 0x80, 0x7E, 0x10, 0x00, 0x74,  /*....t..F.f`....t*/
  /* 00000060: */ 0x26, 0x66, 0x68, 0x00, 0x00, 0x00, 0x00, 0x66, 0xFF, 0x76, 0x08, 0x68, 0x00, 0x00, 0x68, 0x00,  /*&fh....f.v.h..h.*/
  /* 00000070: */ 0x7C, 0x68, 0x01, 0x00, 0x68, 0x10, 0x00, 0xB4, 0x42, 0x8A, 0x56, 0x00, 0x8B, 0xF4, 0xCD, 0x13,  /*.h..h...B.V.....*/
  /* 00000080: */ 0x9F, 0x83, 0xC4, 0x10, 0x9E, 0xEB, 0x14, 0xB8, 0x01, 0x02, 0xBB, 0x00, 0x7C, 0x8A, 0x56, 0x00,  /*..............V.*/
  /* 00000090: */ 0x8A, 0x76, 0x01, 0x8A, 0x4E, 0x02, 0x8A, 0x6E, 0x03, 0xCD, 0x13, 0x66, 0x61, 0x73, 0x1C, 0xFE,  /*.v..N..n...fas..*/
  /* 000000A0: */ 0x4E, 0x11, 0x75, 0x0C, 0x80, 0x7E, 0x00, 0x80, 0x0F, 0x84, 0x8A, 0x00, 0xB2, 0x80, 0xEB, 0x84,  /*N.u.............*/
  /* 000000B0: */ 0x55, 0x32, 0xE4, 0x8A, 0x56, 0x00, 0xCD, 0x13, 0x5D, 0xEB, 0x9E, 0x81, 0x3E, 0xFE, 0x7D, 0x55,  /*U2..V...]...>..U*/
  /* 000000C0: */ 0xAA, 0x75, 0x6E, 0xFF, 0x76, 0x00, 0xE8, 0x8D, 0x00, 0x75, 0x17, 0xFA, 0xB0, 0xD1, 0xE6, 0x64,  /*.un.v....u.....d*/
  /* 000000D0: */ 0xE8, 0x83, 0x00, 0xB0, 0xDF, 0xE6, 0x60, 0xE8, 0x7C, 0x00, 0xB0, 0xFF, 0xE6, 0x64, 0xE8, 0x75,  /*......`......d.u*/
  /* 000000E0: */ 0x00, 0xFB, 0xB8, 0x00, 0xBB, 0xCD, 0x1A, 0x66, 0x23, 0xC0, 0x75, 0x3B, 0x66, 0x81, 0xFB, 0x54,  /*.......f#.u;f..T*/
  /* 000000F0: */ 0x43, 0x50, 0x41, 0x75, 0x32, 0x81, 0xF9, 0x02, 0x01, 0x72, 0x2C, 0x66, 0x68, 0x07, 0xBB, 0x00,  /*CPAu2....r,fh...*/
  /* 00000100: */ 0x00, 0x66, 0x68, 0x00, 0x02, 0x00, 0x00, 0x66, 0x68, 0x08, 0x00, 0x00, 0x00, 0x66, 0x53, 0x66,  /*.fh....fh....fSf*/
  /* 00000110: */ 0x53, 0x66, 0x55, 0x66, 0x68, 0x00, 0x00, 0x00, 0x00, 0x66, 0x68, 0x00, 0x7C, 0x00, 0x00, 0x66,  /*SfUfh....fh....f*/
  /* 00000120: */ 0x61, 0x68, 0x00, 0x00, 0x07, 0xCD, 0x1A, 0x5A, 0x32, 0xF6, 0xEA, 0x00, 0x7C, 0x00, 0x00, 0xCD,  /*ah.....Z2.......*/
  /* 00000130: */ 0x18, 0xA0, 0xB7, 0x07, 0xEB, 0x08, 0xA0, 0xB6, 0x07, 0xEB, 0x03, 0xA0, 0xB5, 0x07, 0x32, 0xE4,  /*..............2.*/
  /* 00000140: */ 0x05, 0x00, 0x07, 0x8B, 0xF0, 0xAC, 0x3C, 0x00, 0x74, 0x09, 0xBB, 0x07, 0x00, 0xB4, 0x0E, 0xCD,  /*......<.t.......*/
  /* 00000150: */ 0x10, 0xEB, 0xF2, 0xF4, 0xEB, 0xFD, 0x2B, 0xC9, 0xE4, 0x64, 0xEB, 0x00, 0x24, 0x02, 0xE0, 0xF8,  /*......+..d..$...*/
  /* 00000160: */ 0x24, 0x02, 0xC3, 0x49, 0x6E, 0x76, 0x61, 0x6C, 0x69, 0x64, 0x20, 0x70, 0x61, 0x72, 0x74, 0x69,  /*$..Invalid parti*/
  /* 00000170: */ 0x74, 0x69, 0x6F, 0x6E, 0x20, 0x74, 0x61, 0x62, 0x6C, 0x65, 0x00, 0x45, 0x72, 0x72, 0x6F, 0x72,  /*tion table.Error*/
  /* 00000180: */ 0x20, 0x6C, 0x6F, 0x61, 0x64, 0x69, 0x6E, 0x67, 0x20, 0x6F, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69,  /* loading operati*/
  /* 00000190: */ 0x6E, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74, 0x65, 0x6D, 0x00, 0x4D, 0x69, 0x73, 0x73, 0x69, 0x6E,  /*ng system.Missin*/
  /* 000001A0: */ 0x67, 0x20, 0x6F, 0x70, 0x65, 0x72, 0x61, 0x74, 0x69, 0x6E, 0x67, 0x20, 0x73, 0x79, 0x73, 0x74,  /*g operating syst*/
  /* 000001B0: */ 0x65, 0x6D, 0x00, 0x00, 0x00, 0x63, 0x7B, 0x9A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20,  /*em...c......... */
  /* 000001C0: */ 0x21, 0x00, 0x01, 0x41, 0x01, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,  /*!..A............*/
  /* 000001D0: */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /*................*/
  /* 000001E0: */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,  /*................*/
  /* 000001F0: */ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x55, 0xAA   /*..............U.*/
};

#if (MY_DEV_PATH == DP_LOG_UNIT)
TEST_BLOCK_IO_DEVICE_PATH TestBlockIoDevicePath =
{
  MESSAGING_DEVICE_PATH,
  MSG_DEVICE_LOGICAL_UNIT_DP,
	sizeof (DEVICE_LOGICAL_UNIT_DEVICE_PATH),
  0,
  0,
  END_DEVICE_PATH_TYPE,
	END_ENTIRE_DEVICE_PATH_SUBTYPE,
	sizeof (EFI_DEVICE_PATH_PROTOCOL),
  0
};
#endif

#if (MY_DEV_PATH == DP_SATA)
TEST_BLOCK_IO_DEVICE_PATH TestBlockIoDevicePath =
{
  MESSAGING_DEVICE_PATH,
  MSG_SATA_DP,
	sizeof (SATA_DEVICE_PATH),
  0,
  1,
  1,
  1,
  END_DEVICE_PATH_TYPE,
	END_ENTIRE_DEVICE_PATH_SUBTYPE,
	sizeof (EFI_DEVICE_PATH_PROTOCOL),
  0
};
#endif

EFI_STATUS
EFIAPI
InitializeTestBlockIo(
  IN EFI_HANDLE           ImageHandle,
  IN EFI_SYSTEM_TABLE     *SystemTable
  )
{
  EFI_STATUS              Status;
  EFI_BLOCK_IO_PROTOCOL   *BlockIo;
  //
  // Install driver model protocol(s).
  //
  Status = EfiLibInstallAllDriverProtocols2 (
             ImageHandle,
             SystemTable,
             &gTestBlockIoDriverBinding,
             ImageHandle,
             &gTestBlockIoComponentName,
             &gTestBlockIoComponentName2,
             NULL,
             NULL,
             &gTestBlockIoDriverDiagnostics,
             &gTestBlockIoDriverDiagnostics2
             );
  ASSERT_EFI_ERROR (Status);

  DEBUG ((EFI_D_ERROR, "%a(%d)\n", __FUNCTION__, __LINE__));
  //Print(L"%a(%d)\n", __FUNCTION__, __LINE__);

  // Init Block I/O
  gTstBlkIo.NumberOfBlocks = 0x1000;
  gTstBlkIo.BlockSize = 0x200; 
  BlockIo = &gTstBlkIo.BlockIo;

  BlockIo->Revision = EFI_BLOCK_IO_PROTOCOL_REVISION;
  BlockIo->Reset = TestBlockIoResetBlock;
  BlockIo->ReadBlocks = TestBlockIoReadBlocks;
  BlockIo->WriteBlocks = TestBlockIoWriteBlocks;
  BlockIo->FlushBlocks = TestBlockIoFlushBlocks;
  
  BlockIo->Media = &gTstBlkIo.Media;
  BlockIo->Media->BlockSize = (UINT32)gTstBlkIo.BlockSize;
  BlockIo->Media->LastBlock = gTstBlkIo.NumberOfBlocks - 1;
  BlockIo->Media->MediaId = 0xBABA;
  BlockIo->Media->ReadOnly = FALSE;
  BlockIo->Media->RemovableMedia = FALSE;
  BlockIo->Media->LogicalPartition = FALSE;
  BlockIo->Media->MediaPresent = TRUE;
  BlockIo->Media->WriteCaching = FALSE;
  BlockIo->Media->IoAlign = 0;
 
 

  // Init Device Path
  gTstBlkIo.DevicePath = &TestBlockIoDevicePath;
  
  //Allocate memory for RAMDISK
  gBS->AllocatePool( 
        EfiBootServicesData,
        (UINTN)gTstBlkIo.NumberOfBlocks*gTstBlkIo.BlockSize,
        &gTstBlkIo.Buffer
        );
    
  // Copy MBR
  gBS->CopyMem((VOID*)((UINT8*)gTstBlkIo.Buffer), &Lba0, sizeof Lba0);
  
  
  //Install Block I/O and  Device Path protocols
  Status = gBS->InstallMultipleProtocolInterfaces(
                             &gTstBlkIo.EfiHandle,
														 &gEfiBlockIoProtocolGuid,
                             &gTstBlkIo.BlockIo,
                             &gEfiDevicePathProtocolGuid,
														 gTstBlkIo.DevicePath,
														 NULL);
 
  Status = gBS->ConnectController(gTstBlkIo.EfiHandle, NULL, NULL, TRUE);
 
  return Status;
}

EFI_STATUS
EFIAPI
TestBlockIoDriverBindingSupported (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Handle,
  IN  EFI_DEVICE_PATH_PROTOCOL     *RemainingDevicePath
  )
{
  //Print(L"%a(%d)\n", __FUNCTION__, __LINE__);
  DEBUG ((EFI_D_ERROR, "%a(%d)\n", __FUNCTION__, __LINE__));
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestBlockIoDriverBindingStart (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Handle,
  IN  EFI_DEVICE_PATH_PROTOCOL      *RemainingDevicePath
  )
{
  //Print(L"%a(%d)\n", __FUNCTION__, __LINE__);
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestBlockIoDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL  *This,
  IN  EFI_HANDLE                   Handle,
  IN  UINTN                        NumberOfChildren,
  IN  EFI_HANDLE                   *ChildHandleBuffer
  )
{
  //Print(L"%a(%d)\n", __FUNCTION__, __LINE__);
  return EFI_SUCCESS;
}



EFI_STATUS
TestBlockIoOpenDevice (
  TEST_BLOCK_IO_PRIVATE                 *Private
  )
{
  EFI_STATUS            Status = EFI_SUCCESS;
  //Print(L"%a(%d)\n", __FUNCTION__, __LINE__);
  
  return Status;
} 

EFI_STATUS
EFIAPI
TestBlockIoReadBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                Lba,
  IN UINTN                  BufferSize,
  OUT VOID                  *Buffer
  )
{
  EFI_BLOCK_IO_MEDIA      *Media;

  //Print(L"%a(%d)\n", __FUNCTION__, __LINE__);
  
  Media = This->Media;
  if (BufferSize % Media->BlockSize != 0) 
    return EFI_BAD_BUFFER_SIZE;
  
  if ((Lba > Media->LastBlock) || (Lba + BufferSize / Media->BlockSize - 1 > Media->LastBlock))
     return  EFI_DEVICE_ERROR;
  
  gBS->CopyMem(Buffer, (VOID*)((UINT8*)gTstBlkIo.Buffer + Lba*Media->BlockSize), BufferSize);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestBlockIoWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                Lba,
  IN UINTN                  BufferSize,
  IN VOID                   *Buffer
  )
{
  EFI_BLOCK_IO_MEDIA      *Media;

  Media = This->Media;
  if (BufferSize % Media->BlockSize != 0) 
    return EFI_BAD_BUFFER_SIZE;
  
  if ((Lba > Media->LastBlock) || (Lba + BufferSize / Media->BlockSize - 1 > Media->LastBlock))
     return  EFI_DEVICE_ERROR;
  
  gBS->CopyMem((VOID*)((UINT8*)gTstBlkIo.Buffer + Lba*Media->BlockSize), Buffer, BufferSize);
  
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestBlockIoFlushBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestBlockIoResetBlock (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN BOOLEAN                ExtendedVerification
  )
{
  return EFI_SUCCESS;
}


  