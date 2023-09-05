// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Avatar.generated.h"


class APickupItem; // forward declare the APickupItem class,
// since it will be "mentioned" in a member function decl below

UCLASS()
class LEARNINGCPP_API AAvatar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAvatar();

	// Карта для рюкзака – backpack игрока
	TMap<FString, int> Backpack;
	// Значки для предметов в рюкзаке, просматриваются строкой
	TMap<FString, UTexture2D*> Icons;
	// Флаг выводящий нам Интерфейс Пользователя показывает
	bool inventoryShowing;

	TMap<FString, UClass*> Spells;
	// функция-член даущая аватару иметь предмет
	void Pickup(APickupItem* item);
	// ... остальная часть файла Avatar.h такая же как до этого
	void ToggleInventory();
	void MoveForward(float amount);
	void MoveRight(float amount);
	void Yaw(float amount);
	void Pitch(float amount);
	void MouseClicked();

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, 
							class AController* EventInstigator, AActor* DamageCauser) override;

	float Hp = 100;
	const float MaxHp = 100;
	FVector knockback;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void CastSpell(UClass* bpSpell);
	void MouseRightClicked();
};
