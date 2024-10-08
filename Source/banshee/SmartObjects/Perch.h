// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SmartObjectComponent.h"
#include "GameFramework/Actor.h"
#include "Perch.generated.h"

UCLASS()
class BANSHEE_API APerch :  public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerch();

	FVector GetLandingZone() const {return landZone;}

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<class UBoxComponent> boxComp;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UStaticMeshComponent> mesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USmartObjectComponent> smartObject;

private: 
	UPROPERTY(VisibleAnywhere, Category = "Dimensions")
	FVector landZone;
	void SetLandingZone();

};
