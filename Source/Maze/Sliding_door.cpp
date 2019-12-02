// Fill out your copyright notice in the Description page of Project Settings.
#include "Sliding_door.h"

#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"


// Sets default values
ASliding_door::ASliding_door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Box_component = CreateDefaultSubobject<UBoxComponent>(TEXT("My_box_component"));
	Box_component->InitBoxExtent(FVector(150, 100, 100));
	Box_component->SetCollisionProfileName("Trigger");
	RootComponent = Box_component;

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> DoorAsset(TEXT("/Game/StarterContent/Props/SM_Door.SM_Door"));

	if (DoorAsset.Succeeded())
	{
		Door->SetStaticMesh(DoorAsset.Object);
		Door->SetRelativeLocation(FVector(0.0f, 50.0f, -100.0f));
		Door->SetWorldScale3D(FVector(1.f));
	}

	is_closed = true;

	is_opening = false;
	is_closing = false;

	DotP = 0.0f;
	MaxDegree = 0.0f;
	AddRotation = 0.0f;
	PosNeg = 0.0f;
	DoorCurrentRotation = 0.0f;

}

// Called when the game starts or when spawned
void ASliding_door::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugBox(GetWorld(), GetActorLocation(), Box_component->GetScaledBoxExtent(), FQuat(GetActorRotation()), FColor::Turquoise, true, -1, 0, 2);
	
}

// Called every frame
void ASliding_door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (is_opening)
	{
		Open_door(DeltaTime);
	}

	if (is_closing)
	{
		Close_door(DeltaTime);
	}

}

void ASliding_door::Open_door(float dt)
{
	DoorCurrentRotation = Door->RelativeRotation.Yaw;

	AddRotation = PosNeg * dt * 80;

	if (FMath::IsNearlyEqual(DoorCurrentRotation, MaxDegree, 1.5f))
	{
		is_closing = false;
		is_opening = false;
	}
	else if (is_opening)
	{
		FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
}

void ASliding_door::Close_door(float dt)
{
	DoorCurrentRotation = Door->RelativeRotation.Yaw;

	if (DoorCurrentRotation > 0)
	{
		AddRotation = -dt * 80;
	}
	else
	{
		AddRotation = dt * 80;
	}

	if (FMath::IsNearlyEqual(DoorCurrentRotation, 0.0f, 1.5f))
	{
		is_closing = false;
		is_opening = false;
	}
	else if (is_closing)
	{
		FRotator NewRotation = FRotator(0.0f, AddRotation, 0.0f);
		Door->AddRelativeRotation(FQuat(NewRotation), false, 0, ETeleportType::None);
	}
}

void ASliding_door::Switch_door(FVector ForwardVector)
{

	// is the chacter in front or behind the door
	DotP = FVector::DotProduct(Box_component->GetForwardVector(), ForwardVector);

	// get 1 or -1 from the the dot product
	PosNeg = FMath::Sign(DotP);

	// degree to clamp at
	MaxDegree = PosNeg * 90.0f;

	// toggle bools
	if (is_closed) {
		is_closed = false;
		is_closing = false;
		is_opening = true;

	}
	else {
		is_opening = false;
		is_closed = true;
		is_closing = true;
	}

}