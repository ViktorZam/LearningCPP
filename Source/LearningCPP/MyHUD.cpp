// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/PlayerController.h"

void AMyHUD::DrawHUD()
{ 
	Super::DrawHUD();
	// ��������� �������� ����� ������, ��� ��� ���� �� �������
	// ����� �� ����� ��������, �� ��������� ������� �������
	
	DrawHealthbar();
	dims.X = Canvas->SizeX;
	dims.Y = Canvas->SizeY;
	DrawMessages();
	DrawWidgets();
}

void AMyHUD::DrawHealthbar()
{
	// ���������� ������ ��������.
	AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
	float barWidth = 200, barHeight = 50, barPad = 12, barMargin = 50;
	
	float percHp = FMath::Clamp(avatar->Hp / avatar->MaxHp, 0.0f, avatar->MaxHp);
	DrawRect(FLinearColor(0, 0, 0, 1), Canvas->SizeX - barWidth - barPad
		- barMargin, Canvas->SizeY - barHeight - barPad - barMargin, barWidth +
		2 * barPad, barHeight + 2 * barPad);
	DrawRect(FLinearColor(1 - percHp, percHp, 0, 1), Canvas->SizeX -
		barWidth - barMargin, Canvas->SizeY - barHeight - barMargin,
		barWidth * percHp, barHeight);
	
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, FString::SanitizeFloat(avatar->Hp) + FString::SanitizeFloat(avatar->MaxHp));
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::SanitizeFloat(avatar->Hp / avatar->MaxHp));
	
}



void AMyHUD::addMessage(Message msg)
{
	messages.Add(msg);
}

void AMyHUD::DrawWidgets()
{
	for (int c = 0; c < widgets.Num(); c++)
	{
		DrawTexture(widgets[c].icon.tex, widgets[c].pos.X, widgets[c].pos.Y, widgets[c].size.X,
			widgets[c].size.Y, 0, 0, 1, 1);
		DrawText(widgets[c].icon.name, FLinearColor::Yellow, widgets[c].pos.X, widgets[c].pos.Y,
			hudFont, .6f, false);
	}
}

void AMyHUD::DrawMessages() 
{
	for (int c = messages.Num() - 1; c >= 0; c--)
	{
		// ���������� ������� ���� ��� ���������
		// ������� �������
		float outputWidth, outputHeight, pad = 10.f;
		GetTextSize(messages[c].message, outputWidth, outputHeight, hudFont,
			1.f);
		float messageH = outputHeight + 2.f * pad;
		float x = 0.f, y = c * messageH;
		// ������ ���
		DrawRect(FLinearColor::Black, x, y, Canvas->SizeX, messageH);
		// ���������� ���� ��������� ��������� hudFont
		DrawText(messages[c].message, messages[c].color, x + pad, y + pad,
			hudFont);
		DrawTexture(messages[c].tex, x, y, messageH, messageH, 0, 0, 1, 1);

		// ��������� ����� ����������� �� ����� ���������
		// � ���������� �����.
		messages[c].time -= GetWorld()->GetDeltaSeconds();
		// ���� ����� ��������� �����, ������� ���
		if (messages[c].time < 0)
		{
			messages.RemoveAt(c);
		}
	}
}

void AMyHUD::addWidget(Widget widget)
{
	// ������� ��������� ������������ ��������, �������������� � �����.
	// ���������� ������...
	FVector2D start(200, 200), pad(12, 12);
	widget.size = FVector2D(100, 100);
	widget.pos = start;
	// ��������� ��������� �����
	for (int c = 0; c < widgets.Num(); c++)
	{
		// ������� ������� ��������� ������.
		widget.pos.X += widget.size.X + pad.X;
		// ���� ������ ������ ��� �����, ��
		// ��������� �� ��������� ������
		if (widget.pos.X + widget.size.X > dims.X)
		{
			widget.pos.X = start.X;
			widget.pos.Y += widget.size.Y + pad.Y;
		}
	}
	widgets.Add(widget);
	
}

void AMyHUD::MouseClicked()
{
	FVector2D mouse;
	PController->GetMousePosition(mouse.X, mouse.Y);
	heldWidget = NULL; // ������� ��������� ����������� ����������� �������
	// ������� ���� ��������� ������ ���� xy �������� �� ������-������ ��������
	for (int c = 0; c < widgets.Num(); c++)
	{
		if (widgets[c].hit(mouse))
		{
			heldWidget = &widgets[c];// ��������� ����������� �������
			return; // ���������� �����
		}
	}
}

void AMyHUD::MouseMoved()
{
	static FVector2D lastMouse;
	FVector2D thisMouse, dMouse;
	PController->GetMousePosition(thisMouse.X, thisMouse.Y);
	dMouse = thisMouse - lastMouse;
	// ������� ���� ����� ������ ���� ������������ �������
	// ����� ��� 0 ������. ���� ��� ������,
	// �� ����� ������ ��������������.
	float time = PController->GetInputKeyTimeDown(EKeys::LeftMouseButton);
	if (time > 0.f && heldWidget)
	{
		// ���� ������.
		// ������� ����������� �������, ������� ��������� amt
		heldWidget->pos.X += dMouse.X;
		heldWidget->pos.Y += dMouse.Y; // y inverted
	}
	lastMouse = thisMouse;
}

void AMyHUD::MouseRightClicked()
{
	FVector2D mouse;
	//APlayerController* PController = GetWorld()->GetFirstPlayerController();
	PController->GetMousePosition(mouse.X, mouse.Y);
	for (int c = 0; c < widgets.Num(); c++)
	{
		if (widgets[c].hit(mouse))
		{
			AAvatar* avatar = Cast<AAvatar>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
			if (widgets[c].bpSpellClass)
				avatar->CastSpell(widgets[c].bpSpellClass);
		}

	}
}


