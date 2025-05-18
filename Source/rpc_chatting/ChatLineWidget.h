// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "ChatLineWidget.generated.h"

/**
 *  
 */
UCLASS()
class RPC_CHATTING_API UChatLineWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	// 메시지 세팅
	UFUNCTION(Category = "ChattingSystem")
	void Setup(const FChatMessage& ChatMessage) const;

protected:
	// 상속시, 반드시 이름을 통일화 할 것.
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> SenderText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> MessageText;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UTextBlock> TimeText;
	
	
};
