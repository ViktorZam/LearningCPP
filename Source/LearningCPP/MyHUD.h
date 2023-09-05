// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h"
#include "Avatar.h"
#include "Kismet/GameplayStatics.h"
#include "MyHUD.generated.h"

struct Icon
{
	FString name;
	UTexture2D* tex;
	Icon() { name = "UNKNOWN ICON"; tex = 0; }
	Icon(FString& iName, UTexture2D* iTex)
	{
		name = iName;
		tex = iTex;
	}
};
struct Widget
{
	Icon icon;
	// bpSpell является блупринтом заклинания, которое посылает этот графический элемент
	UClass* bpSpellClass;
	FVector2D pos, size;
	Widget(Icon iicon)
	{
		icon = iicon;
	}
	Widget(Icon iicon, UClass* bpSpell)
	{
		icon = iicon;
		bpSpellClass = bpSpell;
	}
	float left() { return pos.X; }
	float right() { return pos.X + size.X; }
	float top() { return pos.Y; }
	float bottom() { return pos.Y + size.Y; }
	bool hit(FVector2D p)
	{
		// +---+ top (0)
		// | |
		// +---+ bottom (2) (bottom > top)
		// L R
		return p.X > left() && p.X < right() && p.Y > top() && p.Y < bottom();
	}
};

struct Message
{
	FString message;
	float time;
	FColor color;
	UTexture2D* tex;

	Message()
	{
		// Устанавливаем время по умолчания.
		time = 5.f;
		color = FColor::White;
	}
	Message(FString iMessage, float iTime, FColor iColor, UTexture2D* itex)
	{
		message = iMessage;
		time = iTime;
		color = iColor;
		tex = itex;
	}
};

/**
 * 
 */
UCLASS()
class LEARNINGCPP_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	// Шрифт, используемый для изображения текста в HUD.
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* hudFont;
	APlayerController* PController;
	FVector2D dims;
	TArray<Widget> widgets;
	Widget* heldWidget;
	TArray<Message> messages;
	virtual void DrawHUD() override;
	// Новое! Функция для возможности добавлять сообщение для отображения
	void addMessage(Message msg);
	void MouseClicked();
	void MouseMoved();
	void DrawHealthbar();
	void DrawWidgets();
	void DrawMessages();
	void addWidget(Widget widget);
	void MouseRightClicked();



};
