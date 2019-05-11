// Fill out your copyright notice in the Description page of Project Settings.


#include "StaticLibrary.h"

void UStaticLibrary::PrintWarning(FString Message, FString File, int Line) {
	UE_LOG(LogTemp, Warning, TEXT("%s on Line %d -> %s"), *File, Line, *Message);
}