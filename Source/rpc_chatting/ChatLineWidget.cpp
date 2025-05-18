// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatLineWidget.h"
#include "FChatMessage.h"

void UChatLineWidget::Setup(const FChatMessage& ChatMessage) const
{
	if(SenderText)
	{
		SenderText->SetText(FText::FromString(ChatMessage.Sender));
	}
	if(MessageText)
	{
		MessageText->SetText(FText::FromString(ChatMessage.Message));
	}
	if(TimeText)
	{
		TimeText->SetText(FText::AsDateTime(ChatMessage.Timestamp));
	}

	UE_LOG(LogTemp, Log, TEXT("SeutUp"));

}
