// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "RTSCamera.generated.h"

UCLASS()
class STARCLASH_API ARTSCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARTSCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Camera component
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	class UCameraComponent* CameraComponent;

	// Spring Arm component to control camera distance and rotation
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* SpringArmComponent;

	// Collision sphere to control camera movement
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	USphereComponent* CollisionSphere;
	
	// Movement speed of the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MovementSpeed;

	// Zoom speed of the camera
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float ZoomSpeed;

	// Minimum and maximum zoom limits
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MinZoom;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera")
	float MaxZoom;
	

	// Input handlers for movement and zoom
	void MoveForward(float Value);
	void MoveRight(float Value);
	void ZoomIn(float Value);
	
};
