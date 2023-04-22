// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTT_FlyTo.generated.h"

/**
 * 
 */
UCLASS()
class BANSHEE_API UBTT_FlyTo : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTT_FlyTo();

protected:
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);

private:
	FTimerHandle handle;

	UFUNCTION()
	void AddForceToOwl(class AOwl* owl, FVector origin, FVector destination);

};
