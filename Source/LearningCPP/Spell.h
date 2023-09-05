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
	// параллелепипед (box) определяющий объём урон
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
	UBoxComponent* ProxBox;
	// визуализация частиц заклинания
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Spell)
	UParticleSystemComponent* Particles;
	// Сколько урона наносит заклинание за секунду
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	float DamagePerSecond;
	// Как долго длится заклинания
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Spell)
	float Duration;
	// Отрезок времени, в котором заклинание живёт в уровне
	float TimeAlive;
	// Настоящий насылатель заклинаний (чтобы игрок не попал
	// сам в себя)
	AActor* Caster;
	// Делаем родителем этого заклинания актор насылающий заклинание
	void SetCaster(AActor* caster);
	// Запускаем каждый кадр. Подменяем функцию Tick, чтобы работать с уроном
	// для чего угодно в ProxBox каждый кадр.





protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
