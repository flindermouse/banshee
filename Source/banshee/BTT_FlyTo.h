// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"

#include "BTT_FlyTo.generated.h"


struct OwlFlightData{
	FVector destination;
	bool isInFlight = false;
	bool flightSuccess;
};

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
	virtual void InitializeFromAsset(UBehaviorTree &Asset) override;

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);

	void TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds);

	uint16 GetInstanceMemorySize() const;

private:
	EBTNodeResult::Type StartFlight(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory);
	void MoveOwl(UBehaviorTreeComponent &OwnerComp, OwlFlightData* locMemory, float DeltaSeconds);

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	FBlackboardKeySelector targetLocationKey;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	double targetTolerance = 25.f;

};
