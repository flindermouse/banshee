// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FlyTo.h"

#include "AIController.h"
#include "Owl.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"

UBTT_FlyTo::UBTT_FlyTo(){
    NodeName = TEXT("Fly");
}

EBTNodeResult::Type UBTT_FlyTo::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory); 

    if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;
    if(!OwnerComp.GetAIOwner()->GetPawn()) return EBTNodeResult::Failed;
    
    AOwl* owl = Cast<AOwl>(OwnerComp.GetAIOwner()->GetPawn());
    if(!owl) return EBTNodeResult::Failed;
    FVector owlPos = owl->GetActorLocation();
        
    FTimerDelegate delegate;
    delegate.BindUFunction(this, "AddForceToOwl", owl, owlPos, GetSelectedBlackboardKey());

    GetWorld()->GetTimerManager().SetTimer(handle, delegate, GetWorld()->DeltaTimeSeconds, true);

    if(GetWorld()->GetTimerManager().IsTimerActive(handle)){
        return EBTNodeResult::InProgress;
    }

    return EBTNodeResult::Succeeded; 
}

void UBTT_FlyTo::AddForceToOwl(AOwl* owl, FVector origin, FVector destination){
    if(!owl) return;

    //the distance from our starting point and our destination
    float startDist = (origin - destination).Length();
    //how much we have left to move from current location
    FVector stillToMove = owl->GetActorLocation() - destination;

    //
    FVector movement = (destination - owl->GetActorLocation()).GetSafeNormal(); 
    //the percentage of how far we've moved from start position
    float movePercent = (startDist - stillToMove.Length()) / startDist;

    //set force based on movement towards destination, multiplied by max possible force
    FVector force = ((FMath::Lerp(movement, FVector(0.f), movePercent)) * (owl->GetMaximumForce()));
    owl->GetCapsuleComponent()->AddForce(force, NAME_None, true);

    //TODO:
    //change to an editable tolerance
    if((owl->GetActorLocation() - destination).Length() <= 30.f){
        GetWorld()->GetTimerManager().ClearTimer(handle);
    }
}