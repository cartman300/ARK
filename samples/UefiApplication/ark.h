#pragma once

#include <Uefi.h>
#include <Library/BaseLib.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Library/CpuLib.h>
#include <Library/PrintLib.h>
#include <Library/PeCoffLib.h>
#include <Library/MemoryAllocationLib.h>
#include <Library/TimerLib.h>
#include <Library/UefiRuntimeLib.h>
#include <Library/SmmLib.h>

#include <Library/UefiBootServicesTableLib.h>
#include <Library/UefiRuntimeServicesTableLib.h>
#include <Library/SmmServicesTableLib.h>

#include <intrin.h>
#include "shell.h"

#define WaitForSingleEvent(ST, Ev) do { UINTN Idx; ST->BootServices->WaitForEvent(1, &Ev, &Idx); } while(FALSE)