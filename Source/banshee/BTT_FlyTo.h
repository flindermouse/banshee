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

	void TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds);

private:
	void MoveOwl(FVector toGo);

	UPROPERTY(VisibleAnywhere)
	class AOwl* owl;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float targetTolerance = 100.f;
};
