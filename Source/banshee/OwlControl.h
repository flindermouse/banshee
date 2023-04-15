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

	UFUNCTION()
	void HeardNoise(const TArray<AActor*> &instigators);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere)
	class UBehaviorTree* behave;

	UPROPERTY(BlueprintReadWrite, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAIPerceptionComponent* percept;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UAISenseConfig_Hearing* hearConfig;

	//hearing variables
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hearing", 
		meta = (AllowPrivateAccess = "true"))
	float hRange;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Hearing", 
		meta = (AllowPrivateAccess = "true"))
	float maxAge;
	
};
