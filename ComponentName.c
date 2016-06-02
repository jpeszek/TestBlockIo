/**@file

**/
#include <Uefi.h>
#include <Protocol/ComponentName.h>
#include <Protocol/DriverBinding.h>

#include "TestBlockIo.h"

//
// EFI Component Name Functions
//
EFI_STATUS
EFIAPI
TestBlockIoComponentNameGetDriverName (
  IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  );


EFI_STATUS
EFIAPI
TestBlockIoComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  );


//
// EFI Component Name Protocol
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_COMPONENT_NAME_PROTOCOL  gTestBlockIoComponentName = {
  TestBlockIoComponentNameGetDriverName,
  TestBlockIoComponentNameGetControllerName,
  "eng"
};

//
// EFI Component Name 2 Protocol
//
GLOBAL_REMOVE_IF_UNREFERENCED EFI_COMPONENT_NAME2_PROTOCOL gTestBlockIoComponentName2 = {
  (EFI_COMPONENT_NAME2_GET_DRIVER_NAME) TestBlockIoComponentNameGetDriverName,
  (EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME) TestBlockIoComponentNameGetControllerName,
  "en"
};

EFI_STATUS
EFIAPI
TestBlockIoComponentNameGetDriverName (
  IN  EFI_COMPONENT_NAME_PROTOCOL  *This,
  IN  CHAR8                        *Language,
  OUT CHAR16                       **DriverName
  )
{
  *DriverName=L"Test Block I/O Driver";
  return EFI_SUCCESS;           
}

EFI_STATUS
EFIAPI
TestBlockIoComponentNameGetControllerName (
  IN  EFI_COMPONENT_NAME_PROTOCOL                     *This,
  IN  EFI_HANDLE                                      ControllerHandle,
  IN  EFI_HANDLE                                      ChildHandle        OPTIONAL,
  IN  CHAR8                                           *Language,
  OUT CHAR16                                          **ControllerName
  )
{
  *ControllerName=L"Test Block I/O Controller";
  return EFI_SUCCESS;
}
