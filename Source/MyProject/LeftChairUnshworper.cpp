// Fill out your copyright notice in the Description page of Project Settings.

#include "LeftChairUnshworper.h"


// Sets default values for this component's properties
ULeftChairUnshworper::ULeftChairUnshworper()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULeftChairUnshworper::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Error, TEXT("Left chair unshworped successfully."));
	
}


// Called every frame
void ULeftChairUnshworper::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

