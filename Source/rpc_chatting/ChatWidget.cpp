// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatWidget.h"
#include "ChatComponent.h"
#include "ChatGameStage.h"
#include "ChatLineWidget.h"
#include "ChatPlayerController.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Components/ScrollBox.h"


void UChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AChatGameStage* GameState = GetWorld()->GetGameState<AChatGameStage>();
	if (GameState && GameState->ChatComponent)
	{
		ChatComponent = GameState->ChatComponent;
		ChatComponent->OnChatMessageReceived.AddDynamic(this, &UChatWidget::OnChatReceived);
	}
	if (SendButton)
	{
		SendButton->OnClicked.AddDynamic(this, &UChatWidget::OnSendClicked);
	}
}

void UChatWidget::OnSendClicked()
{
	if (InputTextBox)
	{
		FString Text = InputTextBox->GetText().ToString();
		if (!Text.IsEmpty())
		{
			AChatPlayerController* PlayerController = Cast<AChatPlayerController>(GetOwningPlayer());
			if (PlayerController)
			{
				PlayerController->SendChatMessageToServer(Text);
				InputTextBox->SetText(FText::GetEmpty());
			}
		}
	}
}


void UChatWidget::OnChatReceived(const FChatMessage& ChatMessage)
{
	if (ChatScrollBox)
	{
		if (UChatLineWidget* ChatLineWidget = CreateWidget<UChatLineWidget>(this, ChatLineWidgetClass))
		{
			ChatLineWidget->Setup(ChatMessage);
			ChatScrollBox->AddChild(ChatLineWidget);
			ChatScrollBox->ScrollToEnd();
		}
	}
}

