/**@file
**/
#include <Uefi.h>
#include <Protocol/BlockIo.h>
#include <Protocol/ComponentName.h>
#include <Protocol/DriverBinding.h>

#include "TestBlockIo.h"

//
// EFI Driver Configuration Functions
//
EFI_STATUS
EFIAPI
TestBlockIoDriverConfigurationSetOptions (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL                      *This,
  IN  EFI_HANDLE                                             ControllerHandle,
  IN  EFI_HANDLE                                             ChildHandle  OPTIONAL,
  IN  CHAR8                                                  *Language,
  OUT EFI_DRIVER_CONFIGURATION_ACTION_REQUIRED               *ActionRequired
  );

EFI_STATUS
EFIAPI
TestBlockIoDriverConfigurationOptionsValid (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL               *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle  OPTIONAL
  );

EFI_STATUS
EFIAPI
TestBlockIoDriverConfigurationForceDefaults (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL                      *This,
  IN  EFI_HANDLE                                             ControllerHandle,
  IN  EFI_HANDLE                                             ChildHandle  OPTIONAL,
  IN  UINT32                                                 DefaultType,
  OUT EFI_DRIVER_CONFIGURATION_ACTION_REQUIRED               *ActionRequired
  );

//
// EFI Driver Configuration Protocol
//
EFI_DRIVER_CONFIGURATION_PROTOCOL gTestBlockIoDriverConfiguration = {
  TestBlockIoDriverConfigurationSetOptions,
  TestBlockIoDriverConfigurationOptionsValid,
  TestBlockIoDriverConfigurationForceDefaults,
  LANGUAGESUPPORTED
};

EFI_STATUS
EFIAPI
TestBlockIoDriverConfigurationSetOptions (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL                      *This,
  IN  EFI_HANDLE                                             ControllerHandle,
  IN  EFI_HANDLE                                             ChildHandle  OPTIONAL,
  IN  CHAR8                                                  *Language,
  OUT EFI_DRIVER_CONFIGURATION_ACTION_REQUIRED               *ActionRequired
  )

{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestBlockIoDriverConfigurationOptionsValid (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL               *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle  OPTIONAL
  )
{
  return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
TestBlockIoDriverConfigurationForceDefaults (
  IN  EFI_DRIVER_CONFIGURATION_PROTOCOL                      *This,
  IN  EFI_HANDLE                                             ControllerHandle,
  IN  EFI_HANDLE                                             ChildHandle  OPTIONAL,
  IN  UINT32                                                 DefaultType,
  OUT EFI_DRIVER_CONFIGURATION_ACTION_REQUIRED               *ActionRequired
  )
{
  return EFI_SUCCESS;
}
