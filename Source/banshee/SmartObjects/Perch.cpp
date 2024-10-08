// Fill out your copyright notice in the Description page of Project Settings.

#include "Perch.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APerch::APerch()
{
	boxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	RootComponent = boxComp;

	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	mesh->SetupAttachment(RootComponent);

	smartObject = CreateDefaultSubobject<USmartObjectComponent>(TEXT("Smart Object"));
	smartObject->SetupAttachment(RootComponent);
}

void APerch::SetLandingZone(){
	FBoxSphereBounds bounds = RootComponent->GetLocalBounds();
	landZone = GetActorLocation();
	landZone.Z += (bounds.BoxExtent.Z * RootComponent->GetComponentScale().Z);
}

