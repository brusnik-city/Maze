// Fill out your copyright notice in the Description page of Project Settings.
#include "FirstCharacter.h"
#include "Maze.h"


// Sets default values
AFirstCharacter::AFirstCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// First person camera Component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	// Attach to our capsule component.
	CameraComponent->SetupAttachment(GetCapsuleComponent());

	// Position the camera above the eyes.
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 25.0f + BaseEyeHeight));
	// Allow to control camera rotation.
	CameraComponent->bUsePawnControlRotation = true;

	TriggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	TriggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	TriggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	TriggerCapsule->SetupAttachment(RootComponent);

	// bind trigger events
	TriggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AFirstCharacter::OnOverlapBegin);
	TriggerCapsule->OnComponentEndOverlap.AddDynamic(this, &AFirstCharacter::OnOverlapEnd);

	Current_door = NULL;
}

// Called when the game starts or when spawned
void AFirstCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (GEngine)
	{
		// debug message for 5 second
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("First character in use"));
	}
	
}

// Called every frame
void AFirstCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFirstCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AFirstCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AFirstCharacter::MoveRight);

	// Set up "look" bindings.
	PlayerInputComponent->BindAxis("Turn", this, &AFirstCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFirstCharacter::AddControllerPitchInput);

	// Set up "jump" bindings.
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AFirstCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFirstCharacter::StopJump);

	// Set up "Action" bindings.
	PlayerInputComponent->BindAction("Action", IE_Pressed, this, &AFirstCharacter::OnAction);
}

void AFirstCharacter::MoveForward(float Value)
{
	// set where is forward and inform that player want to move
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AFirstCharacter::MoveRight(float Value)
{
	// set where is right and inform that player want to move
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AFirstCharacter::StartJump()
{
	bPressedJump = true;
}

void AFirstCharacter::StopJump()
{
	bPressedJump = false;
}

void AFirstCharacter::OnAction()
{
	FVector ForwardVector = CameraComponent->GetForwardVector();

	if (Current_door)
	{
		Current_door->Switch_door(ForwardVector);
	}
}

// overlap on begin function
void AFirstCharacter::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp && OtherActor->GetClass()->IsChildOf(ASliding_door::StaticClass()))
	{
		Current_door = Cast<ASliding_door>(OtherActor);
	}
}

// overlap on end function
void AFirstCharacter::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		Current_door = NULL;
	}
}

