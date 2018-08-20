// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Grabber rooty tooty"));
	// ...

}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector location;
	FRotator rotator;
	GetWorld()->
		GetFirstPlayerController()->
		GetPlayerViewPoint(location, rotator);
	
	UE_LOG(LogTemp, Warning, 
		TEXT("Person is at %s looking at angles %s"), 
		*location.ToString(), 
		*rotator.ToString()
	);

	FVector LineTraceEnd = location + rotator.Vector()*Reach;
	DrawDebugLine(GetWorld(), location, LineTraceEnd, FColor(100,1,1),false,-1.f,0,1.f);

	// ...
}

