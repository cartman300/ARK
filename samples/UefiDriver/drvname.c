#include "drv.h"

//
// EFI Component Name Protocol
//
EFI_COMPONENT_NAME_PROTOCOL gComponentNameProtocol =
{
    SampleComponentNameGetDriverName,
    SampleComponentNameGetControllerName,
    "eng"
};

//
// EFI Component Name 2 Protocol
//
EFI_COMPONENT_NAME2_PROTOCOL gComponentName2Protocol =
{
    (EFI_COMPONENT_NAME2_GET_DRIVER_NAME)SampleComponentNameGetDriverName,
    (EFI_COMPONENT_NAME2_GET_CONTROLLER_NAME)SampleComponentNameGetControllerName,
    "en"
};

//
// Internationalized names for the driver
//
EFI_UNICODE_STRING_TABLE gDriverNameTable[] =
{
    {
        "eng;en",
        L"Sample Driver"
    },
    {NULL, NULL}
};

//
// Internationalized names for the device
//
EFI_UNICODE_STRING_TABLE gDeviceNameTable[] =
{
    {
        "eng;en",
        L"Sample Device"
    },
    {NULL, NULL}
};

EFI_STATUS EFIAPI SampleComponentNameGetDriverName(IN EFI_COMPONENT_NAME_PROTOCOL *This, IN CHAR8 *Language, OUT CHAR16 **DriverName) {
	return LookupUnicodeString2(Language, This->SupportedLanguages, gDriverNameTable, DriverName, This == &gComponentNameProtocol);
}

EFI_STATUS EFIAPI SampleComponentNameGetControllerName(IN EFI_COMPONENT_NAME_PROTOCOL *This, IN EFI_HANDLE ControllerHandle,
	IN EFI_HANDLE ChildHandle OPTIONAL, IN CHAR8 *Language, OUT CHAR16 **ControllerName) {
	if (ChildHandle != NULL)
		return EFI_UNSUPPORTED;

	EFI_STATUS efiStatus = EfiTestManagedDevice(ControllerHandle, gDriverBindingProtocol.DriverBindingHandle, &gEfiPciIoProtocolGuid);
	if (EFI_ERROR(efiStatus))
		return efiStatus;

	return LookupUnicodeString2(Language, This->SupportedLanguages, gDeviceNameTable, ControllerName, This == &gComponentNameProtocol);
}