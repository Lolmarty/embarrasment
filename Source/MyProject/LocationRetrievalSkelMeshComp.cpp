// Fill out your copyright notice in the Description page of Project Settings.


#include "LocationRetrievalSkelMeshComp.h"
#include "Engine/World.h"
#include "Engine/EngineTypes.h"
#include "Engine/Public/DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Misc/Paths.h"


ULocationRetrievalSkelMeshComp::ULocationRetrievalSkelMeshComp()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULocationRetrievalSkelMeshComp::BeginPlay()
{
	Super::BeginPlay();
	OwnerComponent = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	OwnerComponent->GetBoneNames(BoneNames);
	TArray<FName> temp;
	for (int i = 0; i < BoneNames.Num(); i++) {
		if (BoneNames[i].GetPlainNameString().Equals(FString(TEXT("hand_l"))) || BoneNames[i].GetPlainNameString().Equals(FString(TEXT("hand_r"))) || BoneNames[i].GetPlainNameString().Equals(FString(TEXT("head"))))
		{
			temp.Add(BoneNames[i]);
		}
	}
	BoneNames = temp;
	UE_LOG(LogTemp, Warning, TEXT("%s is the output folder"), *(FPaths::LaunchDir()));
	FileName = FPaths::LaunchDir() + TEXT("HARDCODEISHARD");
	FString SaveText("[");
	FFileHelper::SaveStringToFile(SaveText, *FileName, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

void ULocationRetrievalSkelMeshComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	TArray<FVector> BoneLocations = TArray<FVector>();
	FString SaveText;
	SaveText.Append(TEXT("{"));
	for (int i = 0; i < BoneNames.Num(); i++) {
		BoneLocations.Add(OwnerComponent->GetBoneLocation(BoneNames[i]));
		SaveText.Append(FString::Printf(TEXT("\"%s\" : { \"x\" : %s,  \"y\" : %s,  \"z\" : %s, "), *(BoneNames[i].GetPlainNameString()), *(FString::SanitizeFloat(BoneLocations[i].X)), *(FString::SanitizeFloat(BoneLocations[i].Y)), *(FString::SanitizeFloat(BoneLocations[i].Z))));
		FRotator rotoroboto = GetOwner()->FindComponentByClass<USkeletalMeshComponent>()->GetSocketRotation(BoneNames[i]);
		SaveText.Append(FString::Printf(TEXT("\"Roll\" : %s,  \"Pitch\" : %s,  \"Yaw\" : %s },"), *(FString::SanitizeFloat(rotoroboto.Roll)), *(FString::SanitizeFloat(rotoroboto.Pitch)), *(FString::SanitizeFloat(rotoroboto.Yaw))));
	}
	SaveText.RemoveFromEnd(TEXT(","));
	SaveText.Append(TEXT("},"));
	FFileHelper::SaveStringToFile(SaveText, *FileName, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_Append);
}

ULocationRetrievalSkelMeshComp::~ULocationRetrievalSkelMeshComp()
{
	FString SaveText;
	FFileHelper::LoadFileToString(SaveText, *FileName);
	SaveText.RemoveFromEnd(TEXT(","));
	SaveText.Append("]");
	FFileHelper::SaveStringToFile(SaveText, *FileName, FFileHelper::EEncodingOptions::AutoDetect, &IFileManager::Get(), FILEWRITE_None);
}