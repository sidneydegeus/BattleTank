// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "StaticLibrary.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API UStaticLibrary : public UObject
{
	GENERATED_BODY()

public:
	static void PrintWarning(FString Message, FString File, int Line);
};
