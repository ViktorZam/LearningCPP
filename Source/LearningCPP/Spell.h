// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spell.generated.h"

class UBoxComponent;
class UParticleSystemComponent;

UCLASS()
class LEARNINGCPP_API ASpell : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpell(const FObjectInitializer& ObjectInitializer);
	// �������������� (box) ������������ ����� ����
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
	UBoxComponent* ProxBox;
	// ������������ ������ ����������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
	UParticleSystemComponent* Particles;
	// ������� ����� ������� ���������� �� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	float DamagePerSecond;
	// ��� ����� ������ ����������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	float Duration;
	// ������� �������, � ������� ���������� ���� � ������
	float TimeAlive;
	// ��������� ���������� ���������� (����� ����� �� �����
	// ��� � ����)
	AActor* Caster;
	// ������ ��������� ����� ���������� ����� ���������� ����������
	void SetCaster(AActor* caster);
	// ��������� ������ ����. ��������� ������� Tick, ����� �������� � ������
	// ��� ���� ������ � ProxBox ������ ����.





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
