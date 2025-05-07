// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingSubSystem.h"

#include "GameFramework/PlayerState.h"

void UChattingSubSystem::SendChat(const FString& MessageContent)
{
	if (MessageContent.IsEmpty()) return;

	FChatMessage ChatMessage;
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	ChatMessage.Sender = PlayerController->PlayerState->GetPlayerName();
	ChatMessage.Message = MessageContent;
	ChatMessage.Timestamp = FDateTime::UtcNow();
	
	if (PlayerController)
	{
		if (PlayerController->HasAuthority())
		{
			// 서버에서 실행
			BroadcastMessageToClient(ChatMessage);
			UE_LOG(LogTemp, Log, TEXT("Running on server"));
		}
		else
		{
			// 클라이언트에서 실행
			SendToServer(ChatMessage);
			UE_LOG(LogTemp, Log, TEXT("Running on client"));
		}
	}
}

void UChattingSubSystem::SendToServer_Implementation(const FChatMessage& ChatMessage)
{
	BroadcastMessageToClient(ChatMessage);
}

bool UChattingSubSystem::SendToServer_Validate(const FChatMessage& ChatMessage)
{
	return !ChatMessage.Message.IsEmpty() && ChatMessage.Message.Len() < MessageLimitLength;
}

void UChattingSubSystem::BroadcastMessageToClient_Implementation(const FChatMessage& ChatMessage)
{
	OnChatMessageReceived.Broadcast(ChatMessage);
}
