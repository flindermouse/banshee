// Fill out your copyright notice in the Description page of Project Settings.


#include "BTT_FlyTo.h"

#include "AIController.h"
#include "Owl.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTT_FlyTo::UBTT_FlyTo(){
    NodeName = TEXT("Fly");
    bNotifyTick = true;
}

EBTNodeResult::Type UBTT_FlyTo::ExecuteTask(UBehaviorTreeComponent &OwnerComp, 
                                    uint8 *NodeMemory){
    Super::ExecuteTask(OwnerComp, NodeMemory); 

    if(!OwnerComp.GetAIOwner()) return EBTNodeResult::Failed;

    if(!OwnerComp.GetAIOwner()->GetPawn()) return EBTNodeResult::Failed;
 
    owl = Cast<AOwl>(OwnerComp.GetAIOwner()->GetPawn());

    return EBTNodeResult::InProgress;
}

void UBTT_FlyTo::TickTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds){    
    Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
    
    if(!OwnerComp.GetBlackboardComponent()) return;
    if(!owl) return;

    FVector destination = OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey());
    //UE_LOG(LogTemp, Display, TEXT("dest X: %f Y: %f Z: %f"), destination.X, destination.Y, destination.Z);
    float dist = FVector::Distance(owl->GetActorLocation(), destination);

    //UE_LOG(LogTemp, Display, TEXT("cX: %f  cY: %f  cZ: %f"), owl->GetActorLocation().X, owl->GetActorLocation().Y, owl->GetActorLocation().Z);
    //UE_LOG(LogTemp, Warning, TEXT("distance: %d"), dist);

    MoveOwl(destination);

    if(dist <= targetTolerance){
        UE_LOG(LogTemp, Display, TEXT("UBTT_FlyTo TickTask: task successfully completed"));
        FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded); 
    }

}

void UBTT_FlyTo::MoveOwl(FVector toGo){
    if(!owl) return;

    FVector direction = (toGo - owl->GetActorLocation()).GetSafeNormal();
    //UE_LOG(LogTemp, Error, TEXT("%f %f %f"), direction.X, direction.Y, direction.Z);
    //owl->AddMovementInput(direction, 1.f);

    FRotator toRotate = direction.ToOrientationRotator();
    owl->SetActorRotation(FMath::RInterpTo(owl->GetActorRotation(), toRotate, 0.016, (400*0.016)));

    FVector toMove = FVector::ZeroVector;
    toMove.X = 400 * 0.016;

    owl->AddActorLocalOffset(toMove);
} 
