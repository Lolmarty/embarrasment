// Fill out your copyright notice in the Description page of Project Settings.

#include "LightSwitch.h"
#include "GameFramework/Actor.h"
#include "Components/PointLightComponent.h"
#include "Components/LightComponentBase.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"


// Sets default values for this component's properties
ULightSwitch::ULightSwitch()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightSwitch::BeginPlay()
{
	Super::BeginPlay();
	if(!PressurePlate)
		UE_LOG(LogTemp, Warning, TEXT("Pressure plate component was not assigned to '%s'."), *GetOwner()->GetName());

	// ...
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

}


// Called every frame
void ULightSwitch::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (!PressurePlate)
		return;
	if(PressurePlate->IsOverlappingActor(ActorThatOpens))
		OnLightsOffRequest.Broadcast();
	else
		OnLightsOnRequest.Broadcast();
}
