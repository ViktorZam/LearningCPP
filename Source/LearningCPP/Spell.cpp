// Fill out your copyright notice in the Description page of Project Settings.


#include "Spell.h"
#include "Monster.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/DamageEvents.h"


// Sets default values
ASpell::ASpell(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProxBox = ObjectInitializer.CreateDefaultSubobject<UBoxComponent>(this, TEXT("ProxBox"));
	Particles = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this,TEXT("ParticleSystem"));
	// Particles является корневым компонентом, а ProxBox
	// является дочерним объектом системы частиц - Particle.
	// Если бы это был другой способ, то масштабирование ProxBox
	// также масштабировало бы Particles, чего мы не хотим
	RootComponent = Particles;
	ProxBox->AttachToComponent(RootComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	Duration = 3; // Продолжительность
	DamagePerSecond = 1; // Урон за секунду
	TimeAlive = 0; // Время жизни

}

// Called when the game starts or when spawned
void ASpell::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// ищем ProxBox для всех акторов в объёме.
	TArray<AActor*> actors;
	ProxBox->GetOverlappingActors(actors);
	// наносим урон каждому актору попадающему в область блока
	for (int c = 0; c < actors.Num(); c++)
	{
		// чтобы не навредить тому, кто посылает заклинание
		if (actors[c] != Caster)
		{
			// Наносим урон только, если блок пересекается с
			// КОРНЕВЫМ компонентом актора.
			// Таким образом, урона не будет, если будет просто
			// пересечение с SightSphere монстра
			AMonster* monster = Cast<AMonster>(actors[c]);
			//ProxBox->IsOverlappingComponent
			//if (monster && ProxBox->IsOverlappingComponent((UPrimitiveComponent*)monster->GetCapsuleComponent()))
			if (monster && ProxBox->IsOverlappingComponent(monster->GetCapsuleComponent()))
			{
				monster->TakeDamage(DamagePerSecond * DeltaTime, FDamageEvent(), 0, this);
			}
			// чтобы наносить урон другим типам класса, попробуйте проверенное насылание
			// здесь...
		}
	}
	TimeAlive += DeltaTime;
	if (TimeAlive > Duration)
	{
		Destroy();
	}
}

void ASpell::SetCaster(AActor* caster)
{
	Caster = caster;
	AttachToComponent(caster->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}

