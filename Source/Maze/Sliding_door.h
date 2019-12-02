// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sliding_door.generated.h"

UCLASS()
class MAZE_API ASliding_door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASliding_door();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void Open_door(float dt);

	UFUNCTION()
		void Close_door(float dt);

	class UStaticMeshComponent* Door;

	// declare sphere comp
	UPROPERTY(VisibleAnywhere, Category = "BoxComp")
		class UBoxComponent* Box_component;

	UFUNCTION()
		void Switch_door(FVector Forward_vector);

	bool is_opening;
	bool is_closing;
	bool is_closed;

	float DotP;
	float MaxDegree;
	float AddRotation;
	float PosNeg;
	float DoorCurrentRotation;

};
