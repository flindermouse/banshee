
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTS_FindNearestPerch.generated.h"

/**
 * 
 */
UCLASS()
class BANSHEE_API UBTS_FindNearestPerch : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTS_FindNearestPerch();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
							float DeltaSeconds) override;
	
};
