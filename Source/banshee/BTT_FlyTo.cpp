// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FlyTo.h"

#include "AIController.h"
#include "Owl.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/PawnMovementComponent.h"

UBTT_FlyTo::UBTT_FlyTo(){
    NodeName = TEXT("Fly");
    bNotifyTick = true;

    //targetLocationKey.AddVectorFilter(this, GET_MEMBER_NAME_CHECKED(UBTT_FlyTo, targetLocationKey));
    //targetLocationKey.AllowNoneAsValue(true);

    //UE_LOG(LogTemp, Display, TEXT("location key: %s"), *targetLocationKey.SelectedKeyName.ToString());
}

void UBTT_FlyTo::InitializeFromAsset(UBehaviorTree &Asset){
    Super::InitializeFromAsset(Asset);

    UBlackboardData* bb = GetBlackboardAsset();
    if(!bb){
        UE_LOG(LogTemp, Warning, TEXT("UBTT_FlyTo InitializeFromAsset: no bb"))
    }

    targetLocationKey.ResolveSelectedKey(*bb);
}

EBTNodeResult::Type UBTT_FlyTo::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory); 

    EBTNodeResult::Type status = StartFlight(OwnerComp, NodeMemory);

    return status; 
}

EBTNodeResult::Type UBTT_FlyTo::StartFlight(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	OwlFlightData* locMemory = (OwlFlightData*)NodeMemory;
    if(!locMemory) return EBTNodeResult::Failed;

	UBlackboardComponent* blackboard  =  OwnerComp.GetBlackboardComponent();
    if(!blackboard) return EBTNodeResult::Failed;
	
	//if(targetLocationKey.SelectedKeyType != UBlackboardKeyType_Vector::StaticClass()){
	//	UE_LOG(LogTemp, Display, TEXT("Invalid key. Expected Vector type, found %s"), *(targetLocationKey.SelectedKeyType ? targetLocationKey.SelectedKeyType->GetName() : FString("?")));
	//	return EBTNodeResult::Failed;
	//}

    UE_LOG(LogTemp, Warning, TEXT("%s"), *blackboard->DescribeKeyValue(GetSelectedBlackboardKey(), EBlackboardDescription::Full));

	FVector flightDestination = blackboard->GetValueAsVector(targetLocationKey.SelectedKeyName);
	locMemory->destination = flightDestination;

    locMemory->isInFlight = true;

	return EBTNodeResult::InProgress;
}

void UBTT_FlyTo::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds){    
    OwlFlightData* locMemory = (OwlFlightData*)NodeMemory;
    if(!locMemory) return;

    if(locMemory->isInFlight){
        MoveOwl(OwnerComp, locMemory, DeltaSeconds);
        return;
    }

    EBTNodeResult::Type flightResult = EBTNodeResult::Failed;
    if(locMemory->flightSuccess){
        flightResult = EBTNodeResult::Succeeded;
    }

    FinishLatentTask(OwnerComp, flightResult);
}

void UBTT_FlyTo::MoveOwl(UBehaviorTreeComponent &OwnerComp, OwlFlightData* locMemory, float DeltaSeconds){
    if(!OwnerComp.GetAIOwner()) return;
    if(!OwnerComp.GetAIOwner()->GetPawn()) return;
 
    AOwl* owl = Cast<AOwl>(OwnerComp.GetAIOwner()->GetPawn());
    if(!owl) return;
    
    FVector direction = (locMemory->destination - owl->GetActorLocation());
    owl->AddMovementInput(direction);

    if(direction.Size() <= targetTolerance){
        locMemory->isInFlight = false;
        locMemory->flightSuccess = true;
    }
}

uint16 UBTT_FlyTo::GetInstanceMemorySize() const{
    return sizeof(OwlFlightData);
}
