// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	// ...
	Owner = GetOwner();
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnPlate() > TriggerMass)
	{
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
		OpenDoorAction();
	}

	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay)
		CloseDoorAction();
		
	// ...
}

float UOpenDoor::GetTotalMassOnPlate() {
	float TotalMass = 0.f;

	TArray<AActor*> OverlappingActors;
	PressurePlate->GetOverlappingActors(OUT OverlappingActors);
	for (const auto* actor : OverlappingActors) {
		TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("%s is on the pressure plate."), *actor->GetName());
	}

	return TotalMass;
}

void UOpenDoor::OpenDoorAction()
{
	auto rotation = Owner->GetActorRotation();
	if (rotation.Yaw <= OpenAngle)
	{
		rotation.Add(0.f, 1.f, 0.f);
		Owner->SetActorRotation(rotation);
	}
}

void UOpenDoor::CloseDoorAction()
{
	auto rotation = Owner->GetActorRotation();
	if (rotation.Yaw >= 0)
	{
		rotation.Add(0.f, -1.f, 0.f);
		Owner->SetActorRotation(rotation);
	}
}

