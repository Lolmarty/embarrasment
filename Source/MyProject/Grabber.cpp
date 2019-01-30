// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	FindPhysicsHandleComponent();
	SetUpInputComponent();
}

void UGrabber::FindPhysicsHandleComponent() {

	PhysicsHandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandleComponent)
	{
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing it's Physics Handle"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetUpInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("Input Component found"));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing it's Input Component"), *(GetOwner()->GetName()));
	}
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	FHitResult HitResult;
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetPlayerViewpointLocation(),
		GetGrabPoint(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);
	return HitResult;
}

const FVector UGrabber::GetGrabPoint()
{
	FVector PlayerViewpointLocation;
	FRotator rotator;
	GetWorld()->
		GetFirstPlayerController()->
		GetPlayerViewPoint(PlayerViewpointLocation, rotator);
	return PlayerViewpointLocation + rotator.Vector() * Reach;
}
const FVector UGrabber::GetPlayerViewpointLocation()
{
	FVector PlayerViewpointLocation;
	FRotator rotator;
	GetWorld()->
		GetFirstPlayerController()->
		GetPlayerViewPoint(PlayerViewpointLocation, rotator);
	return PlayerViewpointLocation;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandleComponent->GetGrabbedComponent()) {
		FVector LineTraceEnd = GetGrabPoint();
		PhysicsHandleComponent->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("what am i looking at is this the one and only GRABBO?!"));
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	if (Hit.GetActor()) {
		UPrimitiveComponent* PrimitiveComponent = Hit.GetComponent();
		PhysicsHandleComponent->
			GrabComponentAtLocation(PrimitiveComponent, NAME_None, Hit.GetActor()->GetActorLocation());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("what am i looking at is this the one and only FLEXO?!"));
	if (PhysicsHandleComponent->GetGrabbedComponent())
		PhysicsHandleComponent->ReleaseComponent();
}

