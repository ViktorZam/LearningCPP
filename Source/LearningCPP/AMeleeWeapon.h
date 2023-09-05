// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "AMeleeWeapon.generated.h"

class AMonster;

UCLASS()
class LEARNINGCPP_API AAMeleeWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAMeleeWeapon(const FObjectInitializer& ObjectInitializer);
	// ����� ����� �� ����� ��� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
	float AttackDamage;
		// ������ ����, ��� ������ ��� ������� ���� �������
		// ����������, ��� �� ����� ��� �������� ���, �������� ���� ���� ���
	TArray<AActor*> ThingsHit;
	// ������������� ����, � ������
	// ��� �� ���� ������ ����
	bool Swinging;
	// "��������� ���� ����" � ������������, ����� ��������� ����
	// ����� �������� ������ ���� ��� ����
	AMonster* WeaponHolder;
	// �������������� ����, ������������, ����� ���� ������
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UBoxComponent* ProxBox;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = MeleeWeapon)
	UStaticMeshComponent* Mesh;
	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void Prox(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void Swing();
	void Rest();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
