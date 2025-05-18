// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ChatLineWidget.h"
#include "ChatWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPC_CHATTING_API UChatWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct() override;

protected:
	// 상속시, 반드시 이름을 통일화 할 것.
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UScrollBox> ChatScrollBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UEditableTextBox> InputTextBox;

	UPROPERTY(meta=(BindWidget))
	TObjectPtr<class UButton> SendButton;

	//ChatLineWidget을 상속한 BP를 할당해 주세요.
	UPROPERTY(Category = "ChattingSystem", EditDefaultsOnly)
	TSubclassOf<UChatLineWidget> ChatLineWidgetClass;

	//통신을 담당할 SubSystem
	UPROPERTY()
	TObjectPtr<class UChatComponent> ChatComponent;
	
	UFUNCTION(Category = "ChattingSystem", BlueprintCallable)
	void OnSendClicked();
	
	UFUNCTION()
	void OnChatReceived(const FChatMessage& ChatMessage);
	
};