// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatComponent.h"

UChatComponent::UChatComponent()
{
	SetIsReplicated(true);
}

void UChatComponent::MulticastChatMessage_Implementation(const FChatMessage& Message)
{
	OnChatMessageReceived.Broadcast(Message);
}
