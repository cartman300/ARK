#pragma once

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>

#include <Library/MemoryAllocationLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>

#include <intrin.h>
#include "shell.h"

#define WaitForSingleEvent(ST, Ev) do { UINTN Idx; ST->BootServices->WaitForEvent(1, &Ev, &Idx); } while(FALSE)