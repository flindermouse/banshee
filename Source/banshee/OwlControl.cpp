// Fill out your copyright notice in the Description page of Project Settings.


#include "OwlControl.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"

AOwlControl::AOwlControl(){
    percept = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Comp"));
    hearConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
}

void AOwlControl::BeginPlay(){
    Super::BeginPlay();

    hearConfig->HearingRange = hRange;
    hearConfig->SetMaxAge(maxAge);
    
    hearConfig->DetectionByAffiliation.bDetectEnemies = true;
    hearConfig->DetectionByAffiliation.bDetectFriendlies = true;
    hearConfig->DetectionByAffiliation.bDetectNeutrals = true;

    percept->ConfigureSense(*hearConfig);
    percept->SetDominantSense(hearConfig->GetSenseImplementation());

    percept->OnPerceptionUpdated.AddDynamic(this, &AOwlControl::HeardNoise);

    //start behaviour tree
    if(behave){
        RunBehaviorTree(behave);        
    }
}

void AOwlControl::HeardNoise(const TArray<AActor*> &instigators){
    UE_LOG(LogTemp, Display, TEXT("Heard"));

}