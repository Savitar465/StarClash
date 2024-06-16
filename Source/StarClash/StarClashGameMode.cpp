// Copyright Epic Games, Inc. All Rights Reserved.

#include "StarClashGameMode.h"
#include "StarClashPlayerController.h"
#include "StarClashCharacter.h"
#include "UObject/ConstructorHelpers.h"

AStarClashGameMode::AStarClashGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AStarClashPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}