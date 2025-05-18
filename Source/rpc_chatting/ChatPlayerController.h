// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ChatPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class RPC_CHATTING_API AChatPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	UFUNCTION(Server, Reliable, WithValidation)
	void SendChatMessageToServer(const FString& Message);
	
};
