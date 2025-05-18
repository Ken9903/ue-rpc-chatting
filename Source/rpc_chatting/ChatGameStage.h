// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "ChatGameStage.generated.h"

/**
 * 
 */
UCLASS()
class RPC_CHATTING_API AChatGameStage : public AGameState
{
	GENERATED_BODY()

public:
	AChatGameStage();
	
	UPROPERTY()
	TObjectPtr<class UChatComponent> ChatComponent;
	
};
