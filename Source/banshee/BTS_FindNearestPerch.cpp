// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_FindNearestPerch.h"

#include "AIController.h"
//#include "NavigationSystem.h"
#include "EngineUtils.h"
#include "Owl.h"
#include "Perch.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_FindNearestPerch::UBTS_FindNearestPerch(){
    NodeName = TEXT("find nearest perch");
}

void UBTS_FindNearestPerch::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);    

    if(!OwnerComp.GetAIOwner()) return;
    if(!OwnerComp.GetAIOwner()->GetPawn()) return;
    
    AOwl* owl = Cast<AOwl>(OwnerComp.GetAIOwner()->GetPawn());
    if(!owl) return;

    APerch* nearest = owl->GetHomePerch();
    FVector owlLoc = owl->GetActorLocation();
    float nearestDist = MAX_flt, currentDist;

    for(APerch* perch : owl->GetPerches()){
        FVector perchLoc = perch->GetActorLocation(); 
        currentDist = sqrt(pow((owlLoc.X - perchLoc.X), 2) + pow((owlLoc.Y - perchLoc.Y), 2) 
                            + pow((owlLoc.Z - perchLoc.Z), 2));

        if(currentDist < nearestDist){
            nearestDist = currentDist;
            nearest = perch;
        }
    }

    if(!nearest){
        UE_LOG(LogTemp, Warning, TEXT("no perch found (BTS_FNP)"));
    }
    FVector landZone = nearest->GetLandingZone();
    UE_LOG(LogTemp, Warning, TEXT("Landing Zone - X: %f Y: %f Z: %f (BTS_FNP)"), landZone.X, landZone.Y, landZone.Z);
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), nearest->GetLandingZone()); 
}