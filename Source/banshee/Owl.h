// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Owl.generated.h"

UCLASS()
class BANSHEE_API AOwl : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AOwl();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float GetPatrolRadius() const {return patrolRad;}
	void SetPatrolRadius(float newRad) {patrolRad = newRad;}

	float GetCruisingAltitude() const {return cruiseAlt;}
	void SetCruisingAltitude(float newAlt) {cruiseAlt = newAlt;}

	float GetMaximumForce() const {return maxForceVel;}
	void SetMaximumForce(float newMax) {maxForceVel = newMax;}

	TArray<class APerch*> GetPerches() const {return perches;}
	APerch* GetHomePerch() const {return homePerch;}
	void SetHomePerch(APerch* newPerch) {homePerch = newPerch;}

private:
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float patrolRad = 50.f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float cruiseAlt = 500.f;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float maxForceVel = 5000.f;

	TArray<class APerch*> perches;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, 
		Category = "Perches", meta = (AllowPrivateAccess = "true"))
	APerch* homePerch;

};
