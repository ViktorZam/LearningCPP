// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SphereComponent.h"
#include "Monster.generated.h"

class AAvatar;
UCLASS()
class LEARNINGCPP_API AMonster : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMonster(const FObjectInitializer& ObjectInitializer);

	// ��������� �� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Speed;
	// ������� �������� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float HitPoints;
	// ���� ���������� �� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 Experience;
	// Blueprint ���� �������� ���������� ��������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPLoot;
	// ����� ����� ����������� �� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BaseAttackDamage;
	// ����� �������, ����������� ������� ��� ������
	// ����� �������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float AttackTimeout;
	// ����� � ���������� ����� �������, �������� � blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	float TimeSinceLastStrike;
	// ���������� �� ������� �� �����
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;
	// ��������� ��� �����. ��������������� � ��������� ��� �����
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* AttackRangeSphere;

	// ����� MeleeWeapon, ������� ���������� ������
// ���� �� �� ����������, �� ������ ���������� ������ ���������� �����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPMeleeWeapon;
	// ��������� MeleeWeapon (��������������� ���� �������� ����������
	// ������ ��� ���������� �������)
	AActor* MeleeWeapon;

	// �������� ������ ����, ������� ���������� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPBullet;
	// ���� ������ ������� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BulletLaunchImpulse = 100000;



	UFUNCTION(BlueprintCallable, Category = Collision)
	void SwordSwung();
	void Attack(AActor* thing);
	void CheckTimeAttack(AAvatar* avatar, float DeltaTime);


	virtual void PostInitializeComponents() override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		class AController* EventInstigator,
		AActor* DamageCauser) override;


	inline bool isInSightRange(float d)
	{
		return d < SightSphere->GetScaledSphereRadius();
	}


	UFUNCTION(BlueprintCallable)
	inline bool isInAttackRange(float d)
	{
		return d < AttackRangeSphere->GetScaledSphereRadius();
	}

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
