// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "FChatMessage.h"
#include "ChattingSubSystem.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChatMessageReceived, const FChatMessage&, ChatMessage);

UCLASS()
class RPC_CHATTING_API UChattingSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SendChat(const FString& MessageContent); //호출

protected:
	UFUNCTION(Server, Reliable, WithValidation)
	void SendToServer(const FChatMessage& ChatMessage);  

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastMessageToClient(const FChatMessage& ChatMessage);  

	UPROPERTY(BlueprintAssignable)
	FOnChatMessageReceived OnChatMessageReceived;

private:
	int32 MessageLimitLength = 512;
	
	void SendToServer_Implementation(const FChatMessage& ChatMessage);
	bool SendToServer_Validate(const FChatMessage& ChatMessage);
	void BroadcastMessageToClient_Implementation(const FChatMessage& ChatMessage);
	
};
