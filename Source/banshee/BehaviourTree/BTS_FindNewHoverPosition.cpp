// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_FindNewHoverPosition.h"

#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "NavigationSystem.h"
#include "../Characters/Owl.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_FindNewHoverPosition::UBTS_FindNewHoverPosition(){
    NodeName = TEXT("hover over position");
}

void UBTS_FindNewHoverPosition::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, 
					                    float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);    

    if(!OwnerComp.GetAIOwner()) return;
    if(!OwnerComp.GetAIOwner()->GetPawn()) return;
    
    AOwl* owl = Cast<AOwl>(OwnerComp.GetAIOwner()->GetPawn());
    if(!owl) return;

    FNavLocation patrolPoint;
    const UNavigationSystemV1* navSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    bool gotPatrol = navSys->GetRandomReachablePointInRadius(OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), 
                                                                owl->GetPatrolRadius(), patrolPoint);

    if(gotPatrol){
        //set altitude to preffered flying height
        patrolPoint.Location.Z = owl->GetCruisingAltitude();
        DrawDebugLine(GetWorld(), owl->GetActorLocation(), patrolPoint.Location, FColor::Red, false, 
                        5.f, (uint8)0U, 10.f);

        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), patrolPoint.Location);
    }
    else{
        //OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), owl->GetActorLocation());
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}