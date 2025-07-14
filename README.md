#  RPC 기반 멀티플레이 채팅 시스템 (Unreal Engine)

UE5 멀티플레이 프로젝트용으로 제작된 **RPC 기반 채팅 시스템**입니다.  
클라이언트 → 서버 → 모든 클라이언트로 흐르는 RPC 통신 구조를 기반으로 제작 되었습니다.
<br/> 
<br/> 

##  시스템 아키텍처

[클라이언트] UChatWidget (UI)<br/> 
　　　　　　↓<br/> 
[클라이언트] APlayerController<br/> 
　　　　　　↓<br/> 
　　　　(Server RPC)<br/> 
　　　　　　↓<br/> 
[서버] APlayerController<br/> 
　　　　　　↓<br/> 
[서버] AGameState → UChatComponent<br/> 
　　　　　　↓<br/> 
　　　　(Multicast)<br/> 
　　　　　　↓<br/> 
[모든 클라이언트] UChatWidget (UI)<br/> 

<br/> 


## 핵심 기능

-  클라이언트 → 서버 RPC를 통해 메시지 전송
- 서버 → 모든 클라이언트 Multicast로 메시지 브로드캐스트


<br/> 

## 적용 방법
* 프로젝트에서 사용하고 있는 GameStage에 UChatComponent를 부착

* 프로젝트에서 사용하고 있는 PlayerController에 SendChatMessageToServer를 구현

* ChatWidget, ChatLineWidget을 블루프린트로 작성 후 Binding에 필요한 요소들을 추가

* ChatWidget의 ChatLineWidgetClass필드에 블루프린트로 작성 된 ChatLineWidget을 할당

* ChatWidget을 HUD에 추가

<br/> 

## 응용 방법

* 메시지 정보 추가
```c++
USTRUCT(BlueprintType)
struct FChatMessage
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Sender;

    UPROPERTY(BlueprintReadWrite)
    FString Message;

    UPROPERTY(BlueprintReadWrite)
    FDateTime Timestamp;

    // [예시 확장 정보]
    UPROPERTY(BlueprintReadWrite)
    int32 PlayerLevel;

    UPROPERTY(BlueprintReadWrite)
    FLinearColor TeamColor;
};
```

```c++
void AChatPlayerController::SendChatToServer(const FString& Content)
{
    if (Content.IsEmpty()) return;

    FChatMessage ChatMessage;
    ChatMessage.Sender = PlayerState->GetPlayerName();
    ChatMessage.Message = Content;
    ChatMessage.Timestamp = FDateTime::UtcNow();

    // [추가 정보 설정 예시]
    ChatMessage.PlayerLevel = GetMyLevel();
    ChatMessage.TeamColor = GetTeamColor();

    Server_SendChatMessage(ChatMessage);
}
```
```c++
void UChatLineWidget::Setup(const FChatMessage& ChatMessage)
{
    SenderTextBlock->SetText(FText::FromString(ChatMessage.Sender));
    MessageTextBlock->SetText(FText::FromString(ChatMessage.Message));

    // [추가 정보 UI 반영]
    LevelTextBlock->SetText(FText::AsNumber(ChatMessage.PlayerLevel));
    SenderTextBlock->SetColorAndOpacity(FSlateColor(ChatMessage.TeamColor));
}
```
