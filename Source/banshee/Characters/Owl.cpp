// Fill out your copyright notice in the Description page of Project Settings.


#include "Owl.h"

#include "EngineUtils.h"
#include "../SmartObjects/Perch.h"

// Sets default values
AOwl::AOwl()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AOwl::BeginPlay()
{
	Super::BeginPlay();

    for (TActorIterator<APerch> iter(GetWorld()); iter; ++iter){
		perches.Add(*iter);
	}

	if(!perches.IsEmpty()){
		SetHomePerch(perches[0]);
	}
}

