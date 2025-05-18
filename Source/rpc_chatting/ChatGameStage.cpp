// Fill out your copyright notice in the Description page of Project Settings.


#include "ChatGameStage.h"

#include "ChatComponent.h"

AChatGameStage::AChatGameStage()
{
	ChatComponent = CreateDefaultSubobject<UChatComponent>(TEXT("ChatComponent"));
}
