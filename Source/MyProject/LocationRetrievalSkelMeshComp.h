// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "LocationRetrievalSkelMeshComp.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class MYPROJECT_API ULocationRetrievalSkelMeshComp : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:
	ULocationRetrievalSkelMeshComp();

protected:
	virtual void BeginPlay() override;
	~ULocationRetrievalSkelMeshComp();

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
private:
	TArray<FName> BoneNames;
	FString FileName;
	USkeletalMeshComponent* OwnerComponent;
};
