// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perch.generated.h"

UCLASS()
class BANSHEE_API APerch : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerch();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FVector GetLandingZone() const {return landZone;}

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, 
		Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* boxComp;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, 
		Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* mesh;

	UPROPERTY(VisibleAnywhere, Category = "Dimensions")
	FVector landZone;
	void SetLandingZone();

};
