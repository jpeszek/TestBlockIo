/**@file
    
**/
#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Protocol/BlockIo.h>
#include <Protocol/ComponentName.h>
#include <Protocol/DriverBinding.h>

#include "TestBlockIo.h"

//
// EFI Driver Diagnostics Functions
//
EFI_STATUS
EFIAPI
TestBlockIoDriverDiagnosticsRunDiagnostics (
  IN  EFI_DRIVER_DIAGNOSTICS_PROTOCOL               *This,
  IN  EFI_HANDLE                                    ControllerHandle,
  IN  EFI_HANDLE                                    ChildHandle  OPTIONAL,
  IN  EFI_DRIVER_DIAGNOSTIC_TYPE                    DiagnosticType,
  IN  CHAR8                                         *Language,
  OUT EFI_GUID                                      **ErrorType,
  OUT UINTN                                         *BufferSize,
  OUT CHAR16                                        **Buffer
  );

//
// EFI Driver Diagnostics Protocol
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_DIAGNOSTICS_PROTOCOL gTestBlockIoDriverDiagnostics = {
  TestBlockIoDriverDiagnosticsRunDiagnostics,
  "eng"
};

//
// EFI Driver Diagnostics 2 Protocol
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_DRIVER_DIAGNOSTICS2_PROTOCOL gTestBlockIoDriverDiagnostics2 = {
  (EFI_DRIVER_DIAGNOSTICS2_RUN_DIAGNOSTICS) TestBlockIoDriverDiagnosticsRunDiagnostics,
  "en"
};

EFI_STATUS
EFIAPI
TestBlockIoDriverDiagnosticsRunDiagnostics (
  IN  EFI_DRIVER_DIAGNOSTICS_PROTOCOL               *This,
  IN  EFI_HANDLE                                    ControllerHandle,
  IN  EFI_HANDLE                                    ChildHandle  OPTIONAL,
  IN  EFI_DRIVER_DIAGNOSTIC_TYPE                    DiagnosticType,
  IN  CHAR8                                         *Language,
  OUT EFI_GUID                                      **ErrorType,
  OUT UINTN                                         *BufferSize,
  OUT CHAR16                                        **Buffer
  )

{
  EFI_STATUS Status = EFI_SUCCESS;
 
  return Status;
}
