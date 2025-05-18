// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FChatMessage.h"
#include "ChatComponent.generated.h"

/**
 *  PlayerController에 할당.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatMessageReceived, const FChatMessage&, ChatMessage);

UCLASS()
class RPC_CHATTING_API UChatComponent : public UActorComponent
{
	GENERATED_BODY()
public:
	UChatComponent();

	UPROPERTY(BlueprintAssignable)
	FOnChatMessageReceived OnChatMessageReceived;

	UFUNCTION(NetMulticast, Reliable)
	void MulticastChatMessage(const FChatMessage& Message);

private:
	void MulticastChatMessage_Implementation(const FChatMessage& Message);
	
};
