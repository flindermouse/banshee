// Fill out your copyright notice in the Description page of Project Settings.


#include "Owl.h"

#include "EngineUtils.h"
#include "Perch.h"

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

	//FVector landZone = GetHomePerch()->GetLandingZone();
	//UE_LOG(LogTemp, Warning, TEXT("Home Perch - X: %f Y: %f Z: %f"), landZone.X, landZone.Y, landZone.Z);
}

// Called every frame
void AOwl::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AOwl::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

