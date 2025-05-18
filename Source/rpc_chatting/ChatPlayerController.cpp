// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatPlayerController.h"

#include "ChatComponent.h"
#include "ChatGameStage.h"
#include "GameFramework/PlayerState.h"

void AChatPlayerController::SendChatMessageToServer_Implementation(const FString& Message)
{
	if (Message.IsEmpty())
	{
		return;
	}

	AChatGameStage* GameState = GetWorld()->GetGameState<AChatGameStage>();
	if (!GameState || !GameState->ChatComponent) return;

	FChatMessage ChatMessage;
	ChatMessage.Sender = PlayerState ? PlayerState->GetPlayerName() : TEXT("Unknown");
	ChatMessage.Message = Message;
	ChatMessage.Timestamp = FDateTime::UtcNow();

	GameState->ChatComponent->MulticastChatMessage(ChatMessage);
}

bool AChatPlayerController::SendChatMessageToServer_Validate(const FString& Message)
{
	return !Message.IsEmpty() && Message.Len() < 128;
}