// Fill out your copyright notice in the Description page of Project Settings.


#include "RTSCamera.h"

#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values
ARTSCamera::ARTSCamera()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create and set up the Spring Arm component
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 800.0f; // Default zoom distance
	SpringArmComponent->bDoCollisionTest = false; // Disable collision test
	SpringArmComponent->bEnableCameraLag = true; // Enable camera lag for smooth movement
	SpringArmComponent->CameraLagSpeed = 3.0f;

	// Create and set up the Collision Sphere component
	CollisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionSphere"));
	CollisionSphere->SetupAttachment(SpringArmComponent);
	// CollisionSphere->InitSphereRadius(100.0f); // Set radius as needed

	// Create and set up the Camera component
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(CollisionSphere);

	// Set default movement and zoom speeds
	MovementSpeed = 1000.0f;
	ZoomSpeed = 200.0f;
	MinZoom = 300.0f;
	MaxZoom = 2000.0f;
}

// Called when the game starts or when spawned
void ARTSCamera::BeginPlay()
{
	Super::BeginPlay();

	// Enable input for the player
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		EnableInput(PlayerController);
		InputComponent->BindAxis("MoveForward", this, &ARTSCamera::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &ARTSCamera::MoveRight);
		InputComponent->BindAxis("ZoomIn", this, &ARTSCamera::ZoomIn);
	}
}

// Called every frame
void ARTSCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Move the camera forward and backward
void ARTSCamera::MoveForward(float Value)
{
	if (Value != 0.0f)
	{
		AddActorLocalOffset(FVector(Value * MovementSpeed * GetWorld()->GetDeltaSeconds(), 0.0f, 0.0f), true);
	}
}

// Move the camera right and left
void ARTSCamera::MoveRight(float Value)
{
	if (Value != 0.0f)
	{
		AddActorLocalOffset(FVector(0.0f, Value * MovementSpeed * GetWorld()->GetDeltaSeconds(), 0.0f), true);
	}
}

// Zoom the camera in and out
void ARTSCamera::ZoomIn(float Value)
{
	if (Value != 0.0f)
	{
		float NewArmLength = SpringArmComponent->TargetArmLength + (Value * ZoomSpeed * GetWorld()->GetDeltaSeconds());
		SpringArmComponent->TargetArmLength = FMath::Clamp(NewArmLength, MinZoom, MaxZoom);
	}
}
