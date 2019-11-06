// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "FirstCharacter.generated.h"

UCLASS()
class MAZE_API AFirstCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFirstCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Moving forward and backward.
	UFUNCTION()
		void MoveForward(float Value);

	// Moving right and left.
	UFUNCTION()
		void MoveRight(float Value);	
	
	// Sets flag 
	UFUNCTION()
		void StartJump();

	// Clears flag
	UFUNCTION()
		void StopJump();

	// Characters camera.
	UPROPERTY(VisibleAnywhere)
		UCameraComponent* CameraComponent;
};
