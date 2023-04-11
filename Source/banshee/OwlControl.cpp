// Fill out your copyright notice in the Description page of Project Settings.


#include "OwlControl.h"

#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISense_Hearing.h"
#include "Perception/AISenseConfig_Hearing.h"

AOwlControl::AOwlControl(){
    PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Comp"));
    hearConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
}

void AOwlControl::BeginPlay(){
    Super::BeginPlay();

    hearConfig->HearingRange = hRange;
    hearConfig->SetMaxAge(maxAge);

    PerceptionComponent->ConfigureSense(*hearConfig);
    PerceptionComponent->SetDominantSense(hearConfig->GetSenseImplementation());
    //PerceptionComponent->OnPerceptionUpdated.AddDynamic(this, &AOwlControl::SenseNoise);

    //start behaviour tree
    if(behave){
        RunBehaviorTree(behave);        
    }
}

void AOwlControl::SenseNoise(){

}