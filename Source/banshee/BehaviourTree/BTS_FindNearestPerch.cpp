// Fill out your copyright notice in the Description page of Project Settings.


#include "BTS_FindNearestPerch.h"

#include "AIController.h"
//#include "NavigationSystem.h"
#include "EngineUtils.h"
#include "../Characters/Owl.h"
#include "../SmartObjects/Perch.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

UBTS_FindNearestPerch::UBTS_FindNearestPerch(){
    NodeName = TEXT("find nearest perch");
}

void UBTS_FindNearestPerch::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds){
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);     

    if(!OwnerComp.GetAIOwner()){ 
        UE_LOG(LogTemp, Warning, TEXT("no ai controller (BTS_FNP)"));
        return;
    }
    if(!OwnerComp.GetAIOwner()->GetPawn()){ 
        UE_LOG(LogTemp, Warning, TEXT("no ai pawn (BTS_FNP)"));
        return;
    }
    
    AOwl* owl = Cast<AOwl>(OwnerComp.GetAIOwner()->GetPawn());
    if(!owl){ 
        UE_LOG(LogTemp, Warning, TEXT("no owl (BTS_FNP)"));
        return;
    }

    APerch* nearestPerch = owl->GetHomePerch();
    float nearestDist = MAX_flt;
    float currentDist = 0.f;

    for(APerch* perch : owl->GetPerches()){
        FVector perchLoc = perch->GetLandingZone(); 
        currentDist = FVector::DistSquared(owl->GetActorLocation(), perchLoc);

        if(currentDist < nearestDist){
            nearestDist = currentDist;
            nearestPerch = perch;
        }
    }

    if(!nearestPerch){
        UE_LOG(LogTemp, Warning, TEXT("no perch found (BTS_FNP)"));
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        return;
    }
    
    FVector landZone = nearestPerch->GetLandingZone();
    //UE_LOG(LogTemp, Warning, TEXT("Landing Zone - X: %f Y: %f Z: %f (BTS_FNP)"), landZone.X, landZone.Y, landZone.Z);
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), nearestPerch->GetLandingZone()); 
}