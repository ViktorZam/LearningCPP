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
	// ќбъЄм урона от атаки его оружием
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = MeleeWeapon)
	float AttackDamage;
		// —писок того, что оружие уже ударило этим взмахом
		// ”беждаемс€, что всЄ через что проходит меч, получает удар один раз
	TArray<AActor*> ThingsHit;
	// предотвращаем урон, в кадрах
	// где не было взмаха меча
	bool Swinging;
	// "ѕерестань бить себ€" Ц используетс€, чтобы проверить если
	// актор держащий оружие бьЄт сам себ€
	AMonster* WeaponHolder;
	// ограничивающий блок, определ€ющий, когда бьЄт оружие
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
