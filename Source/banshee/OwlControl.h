// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "OwlControl.generated.h"

/**
 * 
 */
UCLASS()
class BANSHEE_API AOwlControl : public AAIController
{
	GENERATED_BODY()

public:
	AOwlControl();

	void SenseNoise();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* behave;

	UPROPERTY(VisibleAnywhere)
	class UAISenseConfig_Hearing* hearConfig;

	//hearing variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hearing", 
		meta = (AllowPrivateAccess = "true"))
	float hRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hearing", 
		meta = (AllowPrivateAccess = "true"))
	float maxAge;
	
};
