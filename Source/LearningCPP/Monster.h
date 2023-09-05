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

	// Насколько он быстр
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float Speed;
	// Единицы здоровья монстра
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float HitPoints;
	// Опыт получаемый от побед
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	int32 Experience;
	// Blueprint типа предмета обронённого монстром
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPLoot;
	// Объём урона получаемого от атаки
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float BaseAttackDamage;
	// Объём времени, необходимый монстру для отдыха
	// между атаками
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	float AttackTimeout;
	// Время с последнего удара монстра, читаемое в blueprint
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = MonsterProperties)
	float TimeSinceLastStrike;
	// Расстояние на котором он видит
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* SightSphere;
	// Дальность его атаки. Визуализируемая в редакторе как сфера
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Collision)
	USphereComponent* AttackRangeSphere;

	// Класс MeleeWeapon, который использует монстр
// Если он не установлен, то монстр использует просто рукопашную атаку
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPMeleeWeapon;
	// Экземпляр MeleeWeapon (устанавливается если персонаж использует
	// оружие для рукопашной схватки)
	AActor* MeleeWeapon;

	// Блупринт класса пули, который использует монстр
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MonsterProperties)
	UClass* BPBullet;
	// Тяга позади запуска пули
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
