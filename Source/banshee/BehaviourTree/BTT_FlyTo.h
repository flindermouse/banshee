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
	void MoveOwl(FVector toGo, float DeltaSeconds);

	UPROPERTY(VisibleAnywhere)
	class AOwl* owl;

public:
	UPROPERTY(EditAnywhere)
	float targetTolerance = 100.f;

	UPROPERTY(EditAnywhere)
	float speed = 500.f;


};
