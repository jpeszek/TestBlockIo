/**@file
**/

#ifndef _TEST_BLOCK_IO_H_
#define _TEST_BLOCK_IO_H_

#include <Uefi.h>
#include <Protocol/BlockIo.h>
#include <Protocol/ComponentName.h>
#include <Protocol/ComponentName2.h>
#include <Protocol/DriverConfiguration.h>
#include <Protocol/DriverDiagnostics.h>
#include <Protocol/DriverDiagnostics2.h>
#include <Protocol/DriverBinding.h>
//
// The Library classes this module consumes
//


#define FILENAME_BUFFER_SIZE  80

//
// Language supported for driverconfiguration protocol
//
#define LANGUAGESUPPORTED "eng"

#define DP_LOG_UNIT 1
#define DP_SATA 2
#define MY_DEV_PATH DP_SATA

#if MY_DEV_PATH == MY_DP_LOG_UNIT
typedef struct
{
#if 0
	//EFI_DEVICE_PATH_PROTOCOL Head;
	//EFI_GUID Guid;
  UINT32                          PartitionNumber;
  UINT64                          PartitionStart;
  UINT64                          PartitionSize;
  UINT8                           Signature[16];
  UINT8                           MBRType;
  UINT8                           SignatureType;
#endif
  DEVICE_LOGICAL_UNIT_DEVICE_PATH Ludp;
	EFI_DEVICE_PATH_PROTOCOL Tail;
} TEST_BLOCK_IO_DEVICE_PATH;

#endif

#if MY_DEV_PATH == DP_SATA
typedef struct
{
  SATA_DEVICE_PATH SataDp;
	EFI_DEVICE_PATH_PROTOCOL Tail;
} TEST_BLOCK_IO_DEVICE_PATH;
#endif


#define TEST_BLOCK_IO_PRIVATE_SIGNATURE SIGNATURE_32 ('T', 'T', 'b', 'k')


typedef struct {
  UINTN                       Signature;
  UINT64                      LastBlock;
  UINTN                       BlockSize;
  UINT64                      NumberOfBlocks;
  VOID                        *Buffer;
  EFI_HANDLE                  EfiHandle;
  EFI_BLOCK_IO_MEDIA          Media;
  EFI_BLOCK_IO_PROTOCOL       BlockIo;
  TEST_BLOCK_IO_DEVICE_PATH   *DevicePath;
 
} TEST_BLOCK_IO_PRIVATE;

//
// Block I/O Global Variables
//
extern EFI_DRIVER_BINDING_PROTOCOL         gTestBlockIoDriverBinding;
extern EFI_COMPONENT_NAME_PROTOCOL         gTestBlockIoComponentName;
extern EFI_COMPONENT_NAME2_PROTOCOL        gTestBlockIoComponentName2;
extern EFI_DRIVER_CONFIGURATION_PROTOCOL   gTestBlockIoDriverConfiguration;
extern EFI_DRIVER_DIAGNOSTICS_PROTOCOL     gTestBlockIoDriverDiagnostics;
extern EFI_DRIVER_DIAGNOSTICS2_PROTOCOL    gTestBlockIoDriverDiagnostics2;

//
// EFI Driver Binding Functions
//
EFI_STATUS
EFIAPI
TestBlockIoDriverBindingSupported (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                    Handle,
  IN  EFI_DEVICE_PATH_PROTOCOL      *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
TestBlockIoDriverBindingStart (
  IN EFI_DRIVER_BINDING_PROTOCOL    *This,
  IN  EFI_HANDLE                    Handle,
  IN  EFI_DEVICE_PATH_PROTOCOL      *RemainingDevicePath
  );

EFI_STATUS
EFIAPI
TestBlockIoDriverBindingStop (
  IN  EFI_DRIVER_BINDING_PROTOCOL   *This,
  IN  EFI_HANDLE                    Handle,
  IN  UINTN                         NumberOfChildren,
  IN  EFI_HANDLE                    *ChildHandleBuffer
  );

//
// Block IO protocol member functions
//
EFI_STATUS
EFIAPI
TestBlockIoReadBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                Lba,
  IN UINTN                  BufferSize,
  OUT VOID                  *Buffer
  );

EFI_STATUS
EFIAPI
TestBlockIoWriteBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN UINT32                 MediaId,
  IN EFI_LBA                Lba,
  IN UINTN                  BufferSize,
  IN VOID                   *Buffer
  );

EFI_STATUS
EFIAPI
TestBlockIoFlushBlocks (
  IN EFI_BLOCK_IO_PROTOCOL  *This
  );

EFI_STATUS
EFIAPI
TestBlockIoResetBlock (
  IN EFI_BLOCK_IO_PROTOCOL  *This,
  IN BOOLEAN                ExtendedVerification
  );



#endif
