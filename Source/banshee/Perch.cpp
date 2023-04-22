// Fill out your copyright notice in the Description page of Project Settings.


#include "Perch.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APerch::APerch()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = boxComp;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	mesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void APerch::BeginPlay()
{
	Super::BeginPlay();

	SetLandingZone();	
}

// Called every frame
void APerch::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//TODO:
//update for other perch shapes (this assumes a post-like perch)
void APerch::SetLandingZone(){
	FBoxSphereBounds bounds = RootComponent->GetLocalBounds();
	landZone = GetActorLocation();
	landZone.Z += bounds.BoxExtent.Z;
	//UE_LOG(LogTemp, Warning, TEXT("Landing Zone - X: %f Y: %f Z: %f"), landZone.X, landZone.Y, landZone.Z);
}

